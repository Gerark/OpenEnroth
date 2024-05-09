local Commands = {}
Commands.ConfigCommand = require "dev.commands.config_command"
Commands.GoldCommand = require "dev.commands.gold_command"
Commands.XpCommand = require "dev.commands.xp_command"
Commands.SpCommand = require "dev.commands.skillpoints_command"
Commands.FoodCommand = require "dev.commands.food_command"
Commands.AlignmentCommand = require "dev.commands.alignment_command"
Commands.InventoryCommand = require "dev.commands.inventory_command"
Commands.LuaCommand = require "dev.commands.run_lua_command"
Commands.ClearConsoleCommand = require "dev.commands.cls_command"
Commands.ConditionCommand = require "dev.commands.condition_command"
Commands.HpCommand = require "dev.commands.hp_command"
Commands.ManaCommand = require "dev.commands.mana_command"
Commands.SkillsCommand = require "dev.commands.skills_command"
Commands.ClassCommand = require "dev.commands.class_command"

local Renderer = require "bindings.renderer"

Commands.reloadShadersCommand = {
    name = "reload_shaders",
    description = "Reload all shaders",
    callback = function ()
        Renderer.reloadShaders()
        return "", true
    end
}

-- todo(Gerark) work in progress, need to expose in c++ the functionalities to reload the scripts
--local reloadScriptsCommand = {
--    name = "reload_scripts",
--    description = "Reload all scripts",
--    callback = function()
--        return "Not implemented yet", false
--    end
--}

return Commands
