#include "FSM.h"

#include <Library/Logger/Logger.h>

#include <memory>
#include <utility>
#include <string>

const LogCategory FSM::fsmLogCategory("FSM");
const std::string_view FSM::exitState = "_Exit";

FSM::FSM() {
    // By default, when the FSM has no states, it's treated as if it reached the exit state
    _hasReachedExitState = true;
}

void FSM::jumpToState(std::string_view stateName) {
    _hasReachedExitState = stateName == exitState;
    if (!_hasReachedExitState) {
        if (StateEntry *entry = _getStateByName(stateName)) {
            _nextState = entry;
        } else {
            logger->warning(fsmLogCategory, "Cannot jump to state [{}]. The state does not exist.", stateName);
        }
    }
}

void FSM::update() {
    if (!_hasReachedExitState) {
        if (_nextState) {
            if (_currentState) {
                _currentState->state->exit();
                _currentState->hasExited = true;
                _callTransitionCallback();
            }
            _currentState = _nextState;
            _nextState = nullptr;
            _currentState->state->enter();
            _currentState->hasExited = false;
        }

        _currentState->state->update();

        if (_hasReachedExitState) {
            _currentState->state->exit();
            _currentState->hasExited = true;
            _callTransitionCallback();
            _currentState = nullptr;
        }
    }
}

bool FSM::hasReachedExitState() const {
    return _hasReachedExitState;
}

void FSM::addState(std::unique_ptr<StateEntry> stateEntry) {
    stateEntry->state->setTransitionHandler(this);
    _states.insert({ stateEntry->name, std::move(stateEntry) });
}

void FSM::executeTransition(std::string_view transition) {
    // Check if we have a valid current state
    if (!_currentState) {
        logger->warning(fsmLogCategory, "Cannot execute transition. No current state to transit from. Transition [{}].", transition);
        return;
    }

    // Look for the correct transition
    FSMTransitions &transitions = _currentState->transitions;
    auto itr = transitions.find(transition);
    if (itr == transitions.end()) {
        logger->warning(fsmLogCategory, "Cannot execute transition from state [{}]. Transition [{}] does not exist.",
            _currentState->name, transition);
        return;
    }

    // Check if there's at least one transition condition that evaluates to true
    FSMTransitionTarget *transitionTarget = nullptr;
    for (auto &target : itr->second.targets) {
        if (!target.condition || target.condition()) {
            transitionTarget = &target;
            break;
        }
    }
    if (!transitionTarget) {
        logger->warning(fsmLogCategory, "Cannot execute transition [{}] from state [{}]. No condition evaluated to true",
            transition, _currentState->name);
        return;
    }

    jumpToState(transitionTarget->stateName);
    _setNextTransitionCallback(&itr->second.callback);
}

FSM::StateEntry *FSM::_getStateByName(std::string_view stateName) {
    if (auto itr = _states.find(stateName); itr != _states.end()) {
        return itr->second.get();
    }
    return nullptr;
}

bool FSM::keyPressEvent(const PlatformKeyEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->keyPressEvent(event);
}

bool FSM::keyReleaseEvent(const PlatformKeyEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->keyReleaseEvent(event);
}

bool FSM::mouseMoveEvent(const PlatformMouseEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->mouseMoveEvent(event);
}

bool FSM::mousePressEvent(const PlatformMouseEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->mousePressEvent(event);
}

bool FSM::mouseReleaseEvent(const PlatformMouseEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->mouseReleaseEvent(event);
}

bool FSM::wheelEvent(const PlatformWheelEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->wheelEvent(event);
}

bool FSM::moveEvent(const PlatformMoveEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->moveEvent(event);
}

bool FSM::resizeEvent(const PlatformResizeEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->resizeEvent(event);
}

bool FSM::activationEvent(const PlatformWindowEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->activationEvent(event);
}

bool FSM::closeEvent(const PlatformWindowEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->closeEvent(event);
}

bool FSM::gamepadConnectionEvent(const PlatformGamepadEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->gamepadConnectionEvent(event);
}

bool FSM::gamepadKeyPressEvent(const PlatformGamepadKeyEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->gamepadKeyPressEvent(event);
}

bool FSM::gamepadKeyReleaseEvent(const PlatformGamepadKeyEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->gamepadKeyReleaseEvent(event);
}

bool FSM::gamepadAxisEvent(const PlatformGamepadAxisEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->gamepadAxisEvent(event);
}

bool FSM::nativeEvent(const PlatformNativeEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->nativeEvent(event);
}

bool FSM::textInputEvent(const PlatformTextInputEvent *event) {
    if (!_currentState || _currentState->hasExited) {
        return false;
    }
    return _currentState->state->textInputEvent(event);
}

void FSM::_setNextTransitionCallback(std::function<void()> *callback) {
    _nextTransitionCallback = callback;
}

void FSM::_callTransitionCallback() {
    if (_nextTransitionCallback && *_nextTransitionCallback) {
        (*_nextTransitionCallback)();
    }
    _nextTransitionCallback = nullptr;
}
