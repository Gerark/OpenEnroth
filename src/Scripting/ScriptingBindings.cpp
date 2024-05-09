#include "ScriptingBindings.h"

#include "ScriptingSystem.h"

ScriptingBindings::ScriptingBindings(ScriptingSystem &scriptingSystem) : _scriptingSystem(scriptingSystem) {
}

sol::table ScriptingBindings::createBindingTable(sol::state_view &solState) const {
    return solState.create_table_with(
        "reloadSystem", sol::as_function([this](std::string_view alignment) {
            _scriptingSystem.reload();
        })
    );
}
