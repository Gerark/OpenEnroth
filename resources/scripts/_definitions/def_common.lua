--- @meta

--- @enum PlatformKey
--- @class PlatformKeyEnum
--- @field KEY_TILDE PlatformKey
--- @field KEY_DOWN PlatformKey
--- @field KEY_UP PlatformKey
--- @field KEY_LEFT PlatformKey
--- @field KEY_RIGHT PlatformKey

--- @enum PlatformModifier
--- @class PlatformModifierEnum
--- @field MOD_SHIFT PlatformModifier
--- @field MOD_CTRL PlatformModifier
--- @field MOD_ALT PlatformModifier
--- @field MOD_META PlatformModifier
--- @field MOD_NUM PlatformModifier

--- @class InputBindings
--- @field PlatformKey PlatformKeyEnum
--- @field PlatformModifier PlatformModifierEnum

--- @class MiscBindings
--- @field goToScreen fun(screenId: integer)
--- @field canClassLearn fun(classType: ClassType, skillType: SkillType)

--- @class AudioBindings
--- @field playSound fun(soundId: integer, soundPlaybackMode: integer)
--- @field playMusic fun(musicId: integer)

--- @class RendererBindings
--- @field reloadShaders fun()

--- @class LogBindings
--- @field info fun(message:string)
--- @field trace fun(message:string)
--- @field debug fun(message:string)
--- @field warning fun(message:string)
--- @field error fun(message:string)
--- @field critical fun(message:string)

--- @class NuklearBindings

--- @class PlatformWindow
--- @field dimensions fun(): integer, integer

--- @class PlatformBindings
--- @field window PlatformWindow

--- @class ScriptingBindings
--- @field reloadSystem fun()

--- CONFIG Bindings

--- @class ConfigBindings
--- @field setConfig fun(section: string, configName: string, value: any): boolean
--- @field getConfig fun(section: string, configName?: string): string

--- OVERLAY Bindings
--- @class Overlay
--- @field init fun()
--- @field close fun()
--- @field update fun(ctx: NuklearContext)

--- @class OverlayBindings
--- @field addOverlay fun(name: string, view: Overlay)
--- @field removeOverlay fun(name: string)
--- @field nk Nuklear
