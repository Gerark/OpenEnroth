#pragma once

#include "IBindings.h"

class ScriptingSystem;

class ScriptingBindings : public IBindings {
 public:
    explicit ScriptingBindings(ScriptingSystem &scriptingSystem);
    virtual sol::table createBindingTable(sol::state_view &solState) const override;

 private:
    ScriptingSystem &_scriptingSystem;
};
