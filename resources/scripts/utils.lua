---@class Utilities
local Utilities = {}

---Convert a string to a boolean
---@param value string
---@return boolean
Utilities.toBoolean = function (value)
    return value ~= "false" and value ~= "0"
end

---Convert a variable to a number. in case of failure the defaultValue is returned
---@param amount any
---@param defaultValue number
---@return number
Utilities.toNumberOr = function (amount, defaultValue)
    amount = tonumber(amount)
    return amount and amount or defaultValue
end

--- Tell if a string is empty or nil
---@param s string
---@return boolean
Utilities.isEmpty = function (s)
    return s == nil or s == ""
end

--- Split the string according to the separator. Uses regex identifier
---@param str string - base string
---@param separator string - separator to be used
---@return table<integer, string> - list of splitted strings
Utilities.splitString = function (str, separator)
    local result = {}
    for value in str:gmatch("([^" .. separator .. "]+)") do
        table.insert(result, value)
    end

    return result
end

--- Take an enum table and returns the string representation of the value provided
--- It basically returns the key of the corresponding row
---
--- Example:
--- Game.SkillType = {
---    Club = 0,
---    Sword = 1,
---    Dagger = 2,
--- }
--- local result = enumToString(Game.SkillType, 2)
--- The value of variable "result" is "Dagger"
---
---@param enumTable any - The enum table ( ex: Game.SkillType, Game.SkillMastery )
---@param value any
---@return string
function enumToString(enumTable, value)
    ---@cast enumTable table<string, any>
    for k, v in pairs(enumTable) do
        if v == value then
            return k
        end
    end

    return ""
end

---@param enumTable any - The enum table ( ex: Game.SkillType, Game.SkillMastery )
---@param valueStr string
---@return any
function stringToEnum(enumTable, valueStr)
    ---@cast enumTable table<string, any>
    for k, v in pairs(enumTable) do
        if k == valueStr then
            return v
        end
    end

    return 0
end

return Utilities
