#include "InputScriptEventHandler.h"

#include <sol/sol.hpp>

#include "Library/Logger/Logger.h"

#include "ScriptingSystem.h"

InputScriptEventHandler::InputScriptEventHandler(sol::state_view &solState) : PlatformEventFilter({ EVENT_KEY_PRESS }), _solState(solState) {}

void InputScriptEventHandler::updateState(sol::state_view solState) {
    _solState = solState;
}

bool InputScriptEventHandler::keyPressEvent(const PlatformKeyEvent *event) {
    // TODO(Gerark) Instead of looking for the _global functions we should store them in the lua registry
    sol::safe_function function = _solState["_globalOnKeyPress"];
    if (function.valid()) {
        try {
            // TODO(Gerark) There should be a better way to set error handler function without having to do this all the time. Double check the sol2 docs
            sol::function errorHandler = _solState["_globalErrorHandler"];
            if (errorHandler.valid()) {
                function.set_error_handler(errorHandler);
            }

            int32_t mods = *reinterpret_cast<const int32_t*>(&event->mods);
            auto result = function(event->key, mods);
            if (result.valid()) {
                return result;
            }
        } catch (const sol::error &e) {
            logger->error(ScriptingSystem::ScriptingLogCategory, "An unexpected error has occurred: {}", e.what());
        }
    }

    return false;
}
