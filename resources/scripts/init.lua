require "core.error"

local Overlay = require "bindings.overlay"
local Input = require "bindings.input"
local Scripting = require "bindings.scripting"

local ConsoleOverlay = require "dev.console_overlay"
local CheatOverlay = require "dev.cheat_command_overlay"
local Commands = require "dev.commands.game_commands"
local CommandManager = require "dev.commands.command_manager"
local InputListener = require "core.input_listener"

CommandManager.registerCommands(Commands)
Overlay.addOverlay("console", ConsoleOverlay)
Overlay.addOverlay("cheatTable", CheatOverlay)

local unregisterReloadInput = InputListener.registerKeyPress(
    Input.PlatformKey.KEY_TILDE,
    ---@param mods integer
    function (mods)
        ---@diagnostic disable-next-line: no-unknown
        if bit32.band(mods, Input.PlatformModifier.MOD_CTRL) ~= 0 then
            Scripting.reloadSystem()
        end
    end
)

--- The init.lua returns a function called when the scripting system shutdown/reload
return function ()
    unregisterReloadInput()
    CommandManager.clearCommands()
    Overlay.removeOverlay("console")
    Overlay.removeOverlay("cheatTable")
end
