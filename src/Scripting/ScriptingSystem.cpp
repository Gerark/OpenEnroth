#include "ScriptingSystem.h"

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>

#include "Library/Logger/Logger.h"
#include "Library/Logger/DistLogSink.h"
#include "Library/Platform/Application/PlatformApplication.h"
#include "Utility/DataPath.h"

#include "IBindings.h"
#include "InputScriptEventHandler.h"
#include "ScriptLogSink.h"

LogCategory ScriptingSystem::ScriptingLogCategory("Script");

ScriptingSystem::ScriptingSystem(std::string_view scriptFolder, std::string_view entryPointFile, PlatformApplication &platformApplication, DistLogSink &distLogSink)
    : _scriptFolder(scriptFolder), _entryPointFile(entryPointFile), _platformApplication(platformApplication), _distLogSink(distLogSink) {
    _solState = std::make_unique<sol::state>();
    _platformApplication.installComponent(std::make_unique<InputScriptEventHandler>(*_solState));
    _scriptingLogSink = std::make_unique<ScriptLogSink>(*_solState);
    _distLogSink.addLogSink(_scriptingLogSink.get());
    _initBaseLibraries();
    _initPackageTable();
    _initBindingFunction();
}

ScriptingSystem::~ScriptingSystem() {
    _callUninitializeFunction();
    _uninitializeFunctionReference.reset();
    _distLogSink.removeLogSink(_scriptingLogSink.get());
    _platformApplication.removeComponent<InputScriptEventHandler>();
}

void ScriptingSystem::executeEntryPoint() {
    try {
        sol::protected_function_result result = _solState->script_file(makeDataPath(_scriptFolder, _entryPointFile));
        if (result.valid()) {
            if (auto function = result.get<sol::function>(); function.valid()) {
                _uninitializeFunctionReference = sol::make_reference(*_solState, function);
            }
        }
    } catch (const sol::error &e) {
        logger->warning(ScriptingLogCategory, "An unexpected error has occurred: {}", e.what());
    }
}

void ScriptingSystem::reload() {
    _callUninitializeFunction();
    _uninitializeFunctionReference.reset();
    _distLogSink.removeLogSink(_scriptingLogSink.get());
    _platformApplication.removeComponent<InputScriptEventHandler>();

    _solState->collect_garbage();
    executeEntryPoint();
}

void ScriptingSystem::_callUninitializeFunction() {
    sol::table registry = _solState->registry();
    sol::protected_function function = registry[_uninitializeFunctionReference.registry_index()];
    if (function.valid()) {
        function.call();
    }
}

void ScriptingSystem::_initBaseLibraries() {
    _solState->open_libraries(
        sol::lib::base,
        sol::lib::io,
        sol::lib::os,
        sol::lib::package,
        sol::lib::table,
        sol::lib::math,
        sol::lib::string,
        sol::lib::debug,
        sol::lib::bit32,
        sol::lib::jit
    );
}

/**
 * @brief Internal Lua function used as package loader for the Bindings table.
 *
 * Usage in Lua:
 *   local gameBindings = require "bindings.game" -- If the module starts with 'bindings.' we try to load/create the binding table
 *   gameBindings.doSomething()
 *
 * @param luaState The Lua state.
 * @return int Returns 1 if the binding table is loaded, otherwise returns 0.
 *
 * @todo(Gerark) I'm asking in the sol2 repo if there's a way to avoid a lua_CFunction and use the sol2 approach instead.
 * Here's the question: [link to the question](https://github.com/ThePhD/sol2/issues/1601)
 */
int _loadBindingTableThroughRequire(lua_State *luaState) {
    std::string path = sol::stack::get<std::string>(luaState, 1);
    std::string_view prefix = "bindings.";
    if (path.starts_with(prefix)) {
        // When requesting a module, Lua expects us to place a code chunk on the stack.
        // We utilize loadbuffer to load this chunk, after which the Lua VM promptly executes it.
        std::string script = fmt::format("return _createBindingTable('{}')", path);
        luaL_loadbuffer(luaState, script.data(), script.size(), path.c_str());
        return 1;
    }
    return 0;
}

void ScriptingSystem::_initPackageTable() {
    sol::table packageTable = (*_solState)["package"];
    packageTable["path"] = makeDataPath(_scriptFolder, "?.lua");
    packageTable["cpath"] = ""; //Reset the path for any c loaders
    _solState->add_package_loader(_loadBindingTableThroughRequire);
}

void ScriptingSystem::_clearPackageTable() {
    sol::table packageTable = (*_solState)["package"];
    packageTable["loaded"] = _solState->create_table();
}

void ScriptingSystem::_initBindingFunction() {
    (*_solState)["_createBindingTable"] = [this](std::string tableName) {
        if (auto itr = _bindings.find(tableName); itr != _bindings.end()) {
            return itr->second->createBindingTable(*_solState);
        }
        logger->warning(ScriptingLogCategory, "Can't find a binding table with name: {}", tableName);
        return _solState->create_table();
    };
}
