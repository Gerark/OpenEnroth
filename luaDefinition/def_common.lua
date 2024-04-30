--- @meta

--- @alias PlatformKey integer

--- @class PlatformKeyEnum
--- @field KEY_DOWN PlatformKey
--- @field KEY_UP PlatformKey

--- @class InputBindings
--- @field PlatformKey PlatformKeyEnum

--- @class MiscBindings
--- @field goToScreen fun(screenId: integer)
--- @field canClassLearn fun(classType: integer, skillType: integer)

--- @class AudioBindings
--- @field playSound fun(soundId: integer, soundPlaybackMode: integer)
--- @field playMusic fun(musicId: integer)

--- @class SerializeBindings
--- @field partyAlignment fun(alignment: integer): string

--- @class DeserializeBindings
--- @field partyAlignment fun(alignment: string): integer

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
