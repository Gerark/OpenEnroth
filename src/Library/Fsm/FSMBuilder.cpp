#include "FSMBuilder.h"

#include <Library/Logger/Logger.h>

#include <memory>
#include <utility>
#include <string>

FSMBuilder &FSMBuilder::state(std::string_view stateName, std::unique_ptr<FSMState> state) {
    _latestOnTransition.clear();
    auto entry = std::make_unique<FSM::StateEntry>();
    entry->name = stateName;
    entry->state = std::move(state);
    _states.push_back(std::move(entry));
    return *this;
}

FSMBuilder &FSMBuilder::on(std::string_view transitionName) {
    _latestOnTransition.clear();
    if (_states.empty()) {
        logger->warning(FSM::fsmLogCategory, "Can't create a transition with name [{}]. No state has been setup in the FSMBuilder",
            transitionName);
        return *this;
    }

    if (_states.back()->transitions.contains(transitionName)) {
        logger->warning(FSM::fsmLogCategory, "Can't create a transition with the same name [{}]. State [{}]",
            transitionName, _states.back()->name);
        return *this;
    }

    _states.back()->transitions.insert({ transitionName, {} });
    _latestOnTransition = transitionName;
    return *this;
}

FSMBuilder &FSMBuilder::jumpTo(std::string_view targetState) {
    return jumpTo(nullptr, targetState);
}

FSMBuilder &FSMBuilder::jumpTo(std::function<bool()> condition, std::string_view targetState) {
    if (_states.empty()) {
        logger->warning(FSM::fsmLogCategory, "Can't add a target state to jumpTo. No state has been setup in the FSMBuilder. TargetState [{}]",
            targetState);
        return *this;
    }

    if (_latestOnTransition.empty()) {
        logger->warning(FSM::fsmLogCategory, "Can't add a target state to jumpTo. No 'on' event has been defined yet. State [{}], TargetState [{}]",
            _states.back()->name, targetState);
        return *this;
    }

    _states.back()->transitions[_latestOnTransition].targets.push_back(FSMTransitionTarget{std::string(targetState), condition});
    return *this;
}

std::unique_ptr<FSM> FSMBuilder::build() {
    auto fsm = std::make_unique<FSM>();
    for (auto &entry : _states) {
        fsm->addState(std::move(entry));
    }
    _states.clear();
    _latestOnTransition.clear();
    return std::move(fsm);
}

FSMBuilder &FSMBuilder::execute(const std::function<void()>& callback) {
    if (_states.empty()) {
        logger->warning(FSM::fsmLogCategory, "Can't set a callback to run during a transition. No state has been setup in the FSMBuilder.");
        return *this;
    }

    if (_latestOnTransition.empty()) {
        logger->warning(FSM::fsmLogCategory, "Can't set a callback to run during a transition. No 'on' event has been defined yet. State [{}]",
            _states.back()->name);
        return *this;
    }

    _states.back()->transitions[_latestOnTransition].callback = callback;
    return *this;
}
