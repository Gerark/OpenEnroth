#pragma once

#include "IBindings.h"

class InputBindings : public IBindings {
 public:
    virtual sol::table createBindingTable(sol::state_view &solState) const override;

 private:
    void _fillTableWithEnums(sol::table &table) const;
};
