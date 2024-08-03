#pragma once

#include <cstdint>
#include <cassert>
#include <utility>

#include "Utility/Segment.h"

enum class GuildId : int32_t {
    GUILD_OF_ELEMENTS = 0,
    GUILD_OF_SELF = 1,
    GUILD_OF_AIR = 2,
    GUILD_OF_EARTH = 3,
    GUILD_OF_FIRE = 4,
    GUILD_OF_WATER = 5,
    GUILD_OF_BODY = 6,
    GUILD_OF_MIND = 7,
    GUILD_OF_SPIRIT = 8,
    GUILD_OF_LIGHT = 9,
    GUILD_OF_DARK = 10,

    GUILD_FIRST = GUILD_OF_ELEMENTS,
    GUILD_LAST = GUILD_OF_DARK
};
using enum GuildId;

/**
 * Ids of all NPC houses & dungeon pseudo-houses in the game.
 *
 * DON'T EDIT, THIS IS AUTOGENERATED CODE.
 *
 * @see runHouseIdCodeGen
 */
enum class HouseId {
    HOUSE_INVALID = 0,
    HOUSE_WEAPON_SHOP_EMERALD_ISLAND = 1, // "The Knight's Blade".
    HOUSE_WEAPON_SHOP_HARMONDALE = 2, // "Tempered Steel".
    HOUSE_WEAPON_SHOP_ERATHIA = 3, // "The Queen's Forge".
    HOUSE_WEAPON_SHOP_TULAREAN_FOREST = 4, // "Hunter's Lodge".
    HOUSE_WEAPON_SHOP_CELESTE = 5, // "The Hallowed Sword".
    HOUSE_WEAPON_SHOP_PIT = 6, // "Blades of Spite".
    HOUSE_WEAPON_SHOP_MOUNT_NIGHON = 7, // "The Blooded Dagger".
    HOUSE_WEAPON_SHOP_TATALIA_1 = 8, // "Vander's Blades & Bows".
    HOUSE_WEAPON_SHOP_AVLEE = 9, // "The Knocked Bow".
    HOUSE_WEAPON_SHOP_STONE_CITY = 10, // "The Balanced Axe".
    HOUSE_WEAPON_SHOP_CASTLE_HARMONDALE = 11, // "Swords Inc.".
    HOUSE_WEAPON_SHOP_TATALIA_2 = 12, // "Alloyed Weapons".
    HOUSE_13 = 13, // Unused WEAPON_SHOP named "The Best Defense".
    HOUSE_14 = 14, // Unused WEAPON_SHOP named "Ironwood Spears".
    HOUSE_ARMOR_SHOP_EMERALD_ISLAND = 15, // "Erik's Armory".
    HOUSE_ARMOR_SHOP_HARMONDALE = 16, // "The Peasant's Smithy".
    HOUSE_ARMOR_SHOP_ERATHIA = 17, // "Queen Catherine's Smithy".
    HOUSE_ARMOR_SHOP_TULAREAN_FOREST = 18, // "Buckskins and Bucklers".
    HOUSE_ARMOR_SHOP_CELESTE = 19, // "Armor of Honor".
    HOUSE_ARMOR_SHOP_PIT = 20, // "Shields of Malice".
    HOUSE_ARMOR_SHOP_MOUNT_NIGHON = 21, // "The Tannery".
    HOUSE_ARMOR_SHOP_TATALIA_1 = 22, // "The Missing Link".
    HOUSE_ARMOR_SHOP_AVLEE = 23, // "Avlee Outpost".
    HOUSE_ARMOR_SHOP_STONE_CITY = 24, // "The Polished Pauldron".
    HOUSE_ARMOR_SHOP_CASTLE_HARMONDALE = 25, // "Thel's Armor and Shields".
    HOUSE_ARMOR_SHOP_TATALIA_2 = 26, // "Alloyed Armor and Shields".
    HOUSE_27 = 27, // Unused ARMOR_SHOP named "The Greenwood Forge".
    HOUSE_28 = 28, // Unused ARMOR_SHOP named "The Thrown Gauntlet".
    HOUSE_MAGIC_SHOP_EMERALD_ISLAND = 29, // "Emerald Enchantments".
    HOUSE_MAGIC_SHOP_HARMONDALE = 30, // "Otto's Oddities".
    HOUSE_MAGIC_SHOP_ERATHIA = 31, // "Her Majesty's Magics".
    HOUSE_MAGIC_SHOP_TULAREAN_FOREST = 32, // "Natural Magic".
    HOUSE_MAGIC_SHOP_DEYJA = 33, // "Death's Door".
    HOUSE_MAGIC_SHOP_BRACADA_DESERT = 34, // "Artifacts & Antiquities".
    HOUSE_MAGIC_SHOP_CELESTE = 35, // "Esoteric Indulgences".
    HOUSE_MAGIC_SHOP_PIT = 36, // "Eldritch Influences".
    HOUSE_MAGIC_SHOP_MOUNT_NIGHON = 37, // "Arcane Items".
    HOUSE_MAGIC_SHOP_STONE_CITY = 38, // "Delicate Things".
    HOUSE_39 = 39, // Unused MAGIC_SHOP named "Rings & Relics".
    HOUSE_40 = 40, // Unused MAGIC_SHOP named "Mystical Forces".
    HOUSE_41 = 41, // Unused MAGIC_SHOP named "The Scribbled Page".
    HOUSE_ALCHEMY_SHOP_EMERALD_ISLAND = 42, // "The Blue Bottle".
    HOUSE_ALCHEMY_SHOP_HARMONDALE = 43, // "Philters and Elixirs".
    HOUSE_ALCHEMY_SHOP_ERATHIA = 44, // "Lead Transformations".
    HOUSE_ALCHEMY_SHOP_TULAREAN_FOREST = 45, // "The Bubbling Cauldron".
    HOUSE_ALCHEMY_SHOP_DEYJA = 46, // "The Blackened Vial".
    HOUSE_ALCHEMY_SHOP_BRACADA_DESERT = 47, // "Edmond's Ampules".
    HOUSE_ALCHEMY_SHOP_CELESTE = 48, // "Phials of Faith".
    HOUSE_ALCHEMY_SHOP_PIT = 49, // "Infernal Temptations".
    HOUSE_ALCHEMY_SHOP_STONE_CITY = 50, // "Potent Potions & Brews".
    HOUSE_ALCHEMY_SHOP_CASTLE_HARMONDALE = 51, // "Beakers and Bottles".
    HOUSE_52 = 52, // Unused ALCHEMY_SHOP named "Aromatic Therapies".
    HOUSE_53 = 53, // Unused ALCHEMY_SHOP named "Helpful Solutions".
    HOUSE_STABLE_HARMONDALE = 54, // "The J.V.C Corral".
    HOUSE_STABLE_ERATHIA = 55, // "Royal Steeds".
    HOUSE_STABLE_TULAREAN_FOREST = 56, // "Hu's Stallions".
    HOUSE_STABLE_DEYJA = 57, // "Faithful Steeds".
    HOUSE_STABLE_BRACADA_DESERT = 58, // "Crystal Caravans".
    HOUSE_STABLE_TATALIA = 59, // "Dry Saddles".
    HOUSE_STABLE_AVLEE = 60, // "Plush Coaches".
    HOUSE_61 = 61, // Unused STABLE named "Placeholder".
    HOUSE_62 = 62, // Unused STABLE named "Placeholder".
    HOUSE_BOAT_EMERALD_ISLAND = 63, // "Lady Margaret".
    HOUSE_BOAT_ERATHIA = 64, // "Lady Catherine".
    HOUSE_BOAT_TULAREAN_FOREST = 65, // "Sea Sprite".
    HOUSE_BOAT_BRACADA_DESERT = 66, // "Enchantress".
    HOUSE_BOAT_EVENMORN_ISLAND = 67, // "Sacred Sails".
    HOUSE_68 = 68, // Unused BOAT named "Dauntless".
    HOUSE_BOAT_TATALIA = 69, // "Narwhale".
    HOUSE_BOAT_AVLEE = 70, // "Wind Runner".
    HOUSE_71 = 71, // Unused BOAT named "Mist Flyer".
    HOUSE_72 = 72, // Unused BOAT named "Placeholder".
    HOUSE_73 = 73, // Unused BOAT named "Placeholder".
    HOUSE_TEMPLE_EMERALD_ISLAND = 74, // "Healer's Tent".
    HOUSE_TEMPLE_HARMONDALE = 75, // "WelNin Cathedral".
    HOUSE_TEMPLE_ERATHIA = 76, // "House of Solace".
    HOUSE_TEMPLE_TULAREAN_FOREST = 77, // "Nature's Remedies".
    HOUSE_TEMPLE_DEYJA = 78, // "Temple of Dark".
    HOUSE_TEMPLE_BRACADA_DESERT = 79, // "Temple of Light".
    HOUSE_TEMPLE_CELESTE = 80, // "Temple of Light".
    HOUSE_TEMPLE_PIT = 81, // "Temple of Dark".
    HOUSE_TEMPLE_MOUNT_NIGHON = 82, // "Offerings and Blessings".
    HOUSE_TEMPLE_TATALIA = 83, // "The Order of Tatalia".
    HOUSE_TEMPLE_AVLEE = 84, // "Temple of Tranquility".
    HOUSE_TEMPLE_STONE_CITY = 85, // "Temple of Stone".
    HOUSE_TEMPLE_CASTLE_HARMONDALE = 86, // "Sanctuary".
    HOUSE_87 = 87, // Unused TEMPLE named "Holy Ground".
    HOUSE_88 = 88, // Unused TEMPLE named "Healer's Tent".
    HOUSE_TRAINING_HALL_EMERALD_ISLAND = 89, // "Island Training Grounds".
    HOUSE_TRAINING_HALL_HARMONDALE = 90, // "Basic Principles".
    HOUSE_TRAINING_HALL_ERATHIA = 91, // "In Her Majesty's Service".
    HOUSE_TRAINING_HALL_TULAREAN_FOREST = 92, // "The Proving Grounds".
    HOUSE_TRAINING_HALL_CELESTE = 93, // "Trial of Honor".
    HOUSE_TRAINING_HALL_PIT = 94, // "Perdition's Flame".
    HOUSE_TRAINING_HALL_MOUNT_NIGHON = 95, // "Applied Instruction".
    HOUSE_TRAINING_HALL_TATALIA = 96, // "Training Essentials".
    HOUSE_TRAINING_HALL_AVLEE = 97, // "Avlee Gymnaisium".
    HOUSE_TRAINING_HALL_STONE_CITY = 98, // "War College".
    HOUSE_99 = 99, // Unused TRAINING_HALL named "Placeholder".
    HOUSE_100 = 100, // Unused TRAINING_HALL named "Placeholder".
    HOUSE_101 = 101, // Unused TRAINING_HALL named "Placeholder".
    HOUSE_TOWN_HALL_HARMONDALE = 102, // "Harmondale Townhall".
    HOUSE_TOWN_HALL_ERATHIA = 103, // "Steadwick Townhall".
    HOUSE_TOWN_HALL_TULAREAN_FOREST = 104, // "Pierpont Townhall".
    HOUSE_TOWN_HALL_CELESTE = 105, // "Hall of Dawn".
    HOUSE_TOWN_HALL_PIT = 106, // "Hall of Midnight".
    HOUSE_TAVERN_EMERALD_ISLAND = 107, // "Two Palms Tavern".
    HOUSE_TAVERN_HARMONDALE = 108, // "On the House".
    HOUSE_TAVERN_ERATHIA = 109, // "Griffin's Rest".
    HOUSE_TAVERN_TULAREAN_FOREST = 110, // "Emerald Inn".
    HOUSE_TAVERN_DEYJA = 111, // "The Snobbish Goblin".
    HOUSE_TAVERN_BRACADA_DESERT = 112, // "Familiar Place".
    HOUSE_TAVERN_CELESTE = 113, // "The Blessed Brew".
    HOUSE_TAVERN_PIT = 114, // "The Vampyre Lounge".
    HOUSE_TAVERN_EVENMORN_ISLAND = 115, // "The Laughing Monk".
    HOUSE_TAVERN_MOUNT_NIGHON = 116, // "Fortune's Folly".
    HOUSE_TAVERN_BARROW_DOWNS = 117, // "Miner's Only".
    HOUSE_TAVERN_TATALIA = 118, // "The Loyal Mercenary".
    HOUSE_TAVERN_AVLEE = 119, // "The Potted Pixie".
    HOUSE_TAVERN_STONE_CITY = 120, // "Grogg's Grog".
    HOUSE_121 = 121, // Unused TAVERN named "Knightly Pursuits".
    HOUSE_122 = 122, // Unused TAVERN named "The Last Resort".
    HOUSE_123 = 123, // Unused TAVERN named "Garrion's Roadhouse".
    HOUSE_124 = 124, // Unused TAVERN named "Creature Comforts".
    HOUSE_125 = 125, // Unused TAVERN named "So You Want to be a Hero?".
    HOUSE_126 = 126, // Unused TAVERN named "The Elegant Orc".
    HOUSE_127 = 127, // Unused TAVERN named "The Bird Paradise".
    HOUSE_BANK_HARMONDALE = 128, // "The Vault".
    HOUSE_BANK_ERATHIA = 129, // "Bank of Erathia".
    HOUSE_BANK_TULAREAN_FOREST = 130, // "Nature's Stockpile".
    HOUSE_BANK_CELESTE = 131, // "Material Wealth".
    HOUSE_BANK_PIT = 132, // "Frozen Assets".
    HOUSE_BANK_TATALIA = 133, // "The Depository".
    HOUSE_BANK_AVLEE = 134, // "Halls of Gold".
    HOUSE_BANK_STONE_CITY = 135, // "Mineral Wealth".
    HOUSE_136 = 136, // Unused BANK named "Placeholder".
    HOUSE_137 = 137, // Unused BANK named "Placeholder".
    HOUSE_138 = 138, // Unused BANK named "Placeholder".
    HOUSE_FIRE_GUILD_EMERALD_ISLAND = 139, // "Initiate Guild of Fire".
    HOUSE_FIRE_GUILD_HARMONDALE = 140, // "Adept Guild of Fire".
    HOUSE_FIRE_GUILD_TULAREAN_FOREST = 141, // "Master Guild of Fire".
    HOUSE_FIRE_GUILD_MOUNT_NIGHON = 142, // "Paramount Guild of Fire".
    HOUSE_AIR_GUILD_EMERALD_ISLAND = 143, // "Initiate Guild of Air".
    HOUSE_AIR_GUILD_HARMONDALE = 144, // "Adept Guild of Air".
    HOUSE_AIR_GUILD_TULAREAN_FOREST = 145, // "Master Guild of Air".
    HOUSE_AIR_GUILD_CELESTE = 146, // "Paramount Guild of Air".
    HOUSE_WATER_GUILD_HARMONDALE = 147, // "Initiate Guild of Water".
    HOUSE_WATER_GUILD_TULAREAN_FOREST = 148, // "Adept Guild of Water".
    HOUSE_WATER_GUILD_BRACADA_DESERT = 149, // "Master Guild of Water".
    HOUSE_WATER_GUILD_EVENMORN_ISLAND = 150, // "Paramount Guild of Water".
    HOUSE_EARTH_GUILD_HARMONDALE = 151, // "Initiate Guild of Earth".
    HOUSE_EARTH_GUILD_TULAREAN_FOREST = 152, // "Adept Guild of Earth".
    HOUSE_EARTH_GUILD_STONE_CITY = 153, // "Master Guild of Earth".
    HOUSE_EARTH_GUILD_PIT = 154, // "Paramount Guild of Earth".
    HOUSE_SPIRIT_GUILD_EMERALD_ISLAND = 155, // "Initiate Guild of Spirit".
    HOUSE_SPIRIT_GUILD_HARMONDALE = 156, // "Adept Guild of Spirit".
    HOUSE_SPIRIT_GUILD_DEYJA = 157, // "Master Guild of Spirit".
    HOUSE_SPIRIT_GUILD_ERATHIA = 158, // "Paramount Guild of Spirit".
    HOUSE_MIND_GUILD_HARMONDALE = 159, // "Initiate Guild of Mind".
    HOUSE_MIND_GUILD_ERATHIA = 160, // "Adept Guild of Mind".
    HOUSE_MIND_GUILD_TATALIA = 161, // "Master Guild of Mind".
    HOUSE_MIND_GUILD_AVLEE = 162, // "Paramount Guild of Mind".
    HOUSE_BODY_GUILD_EMERALD_ISLAND = 163, // "Initiate Guild of Body".
    HOUSE_BODY_GUILD_HARMONDALE = 164, // "Adept Guild of Body".
    HOUSE_BODY_GUILD_ERATHIA = 165, // "Master Guild of Body".
    HOUSE_BODY_GUILD_AVLEE = 166, // "Paramount Guild of Body".
    HOUSE_LIGHT_GUILD_BRACADA_DESERT = 167, // "Guild of Illumination".
    HOUSE_LIGHT_GUILD_CELESTE = 168, // "Guild of Enlightenment".
    HOUSE_DARK_GUILD_DEYJA = 169, // "Guild of Twilight".
    HOUSE_DARK_GUILD_PIT = 170, // "Guild of Night".
    HOUSE_171 = 171, // Unused SELF_GUILD named "Placeholder".
    HOUSE_172 = 172, // Unused SELF_GUILD named "Placeholder".
    HOUSE_HARMONDALE_CASTLE_HARMONDALE_1 = 173,
    HOUSE_CASTLE_HARMONDALE_THRONE_ROOM = 174,
    HOUSE_ERATHIA_CASTLE_GRYPHONHEART = 175,
    HOUSE_CASTLE_GRYPHONHEART_THRONE_ROOM = 176,
    HOUSE_TULAREAN_FOREST_CASTLE_NAVAN = 177,
    HOUSE_CASTLE_NAVAN_THRONE_ROOM = 178,
    HOUSE_PIT_CASTLE_GLOAMING = 179,
    HOUSE_CASTLE_GLOAMING_THRONE_ROOM_1 = 180,
    HOUSE_CELESTE_CASTLE_LAMBENT = 181,
    HOUSE_CASTLE_LAMBENT_THRONE_ROOM = 182,
    HOUSE_183 = 183, // Unused HOUSE named "Castle Deadwood".
    HOUSE_CASTLE_GLOAMING_THRONE_ROOM_2 = 184,
    HOUSE_ERATHIAN_SEWERS_MASTER_THIEF = 185,
    HOUSE_EMERALD_ISLAND_MARKHAMS_HEADQUARTERS = 186,
    HOUSE_JAIL = 187,
    HOUSE_HARMONDALE_ARBITER_1 = 188,
    HOUSE_BARROW_DOWNS_HARMONDALE_ARBITER = 189,
    HOUSE_HARMONDALE_ARBITER_2 = 190,
    HOUSE_EMERALD_ISLAND_TEMPLE_OF_THE_MOON = 191,
    HOUSE_EMERALD_ISLAND_DRAGONS_LAIR = 192,
    HOUSE_HARMONDALE_CASTLE_HARMONDALE_2 = 193,
    HOUSE_HARMONDALE_WHITE_CLIFF_CAVES = 194,
    HOUSE_ERATHIA_ERATHIAN_SEWER = 195,
    HOUSE_ERATHIA_FORT_RIVERSTRIDE = 196,
    HOUSE_TULAREAN_FOREST_TULAREAN_CAVES = 197,
    HOUSE_TULAREAN_FOREST_CLANKERS_LABORATORY = 198,
    HOUSE_DEYJA_HALL_OF_THE_PIT = 199,
    HOUSE_DEYJA_WATCHTOWER_6 = 200,
    HOUSE_BRACADA_DESERT_SCHOOL_OF_SORCERY = 201,
    HOUSE_BRACADA_DESERT_RED_DWARF_MINES = 202,
    HOUSE_CELESTE_WALLS_OF_MIST = 203,
    HOUSE_204 = 204, // Unused HOUSE named "Temple of the Light".
    HOUSE_205 = 205, // Unused HOUSE named "Breeding Zone".
    HOUSE_206 = 206, // Unused HOUSE named "Temple of the Dark".
    HOUSE_EVENMORN_ISLAND_GRAND_TEMPLE_OF_THE_MOON = 207,
    HOUSE_EVENMORN_ISLAND_GRAND_TEMPLE_OF_THE_SUN = 208,
    HOUSE_MOUNT_NIGHON_THUNDERFIST_MOUNTAIN = 209,
    HOUSE_MOUNT_NIGHON_THE_MAZE = 210,
    HOUSE_BARROW_DOWNS_STONE_CITY = 211,
    HOUSE_LAND_OF_THE_GIANTS_COLONY_ZOD = 212,
    HOUSE_TATALIA_MERCENARY_GUILD = 213,
    HOUSE_TATALIA_TIDEWATER_CAVERNS = 214,
    HOUSE_TATALIA_WINE_CELLAR = 215,
    HOUSE_AVLEE_TITANS_STRONGHOLD = 216,
    HOUSE_AVLEE_TEMPLE_OF_BAA = 217,
    HOUSE_AVLEE_HALL_UNDER_THE_HILL = 218,
    HOUSE_SHOALS_THE_LINCOLN = 219,
    HOUSE_220 = 220, // Unused HOUSE named "Placeholder".
    HOUSE_221 = 221, // Unused HOUSE named "Placeholder".
    HOUSE_222 = 222, // Unused HOUSE named "Placeholder".
    HOUSE_223 = 223, // Unused HOUSE named "Placeholder".
    HOUSE_EMERALD_ISLAND_DONNA_WYRITHS_RESIDENCE = 224,
    HOUSE_EMERALD_ISLAND_MIA_LUCILLE_HOME = 225,
    HOUSE_EMERALD_ISLAND_VANDALIR_RESIDENCE = 226,
    HOUSE_227 = 227, // Used in MAP_EMERALD_ISLAND, named "House 227", looks totally like a placeholder...
    HOUSE_228 = 228, // Used in MAP_EMERALD_ISLAND, named "House 228", looks totally like a placeholder...
    HOUSE_229 = 229, // Used in MAP_EMERALD_ISLAND, named "House 229", looks totally like a placeholder...
    HOUSE_230 = 230, // Unused HOUSE named "House 230".
    HOUSE_231 = 231, // Unused HOUSE named "House 231".
    HOUSE_232 = 232, // Unused HOUSE named "House 232".
    HOUSE_233 = 233, // Unused HOUSE named "House 233".
    HOUSE_234 = 234, // Unused HOUSE named "House 234".
    HOUSE_235 = 235, // Unused HOUSE named "House 235".
    HOUSE_236 = 236, // Unused HOUSE named "House 236".
    HOUSE_237 = 237, // Unused HOUSE named "House 237".
    HOUSE_EMERALD_ISLAND_THE_LADY_MARGARET = 238,
    HOUSE_EMERALD_ISLAND_CAROLYN_WEATHERS_HOUSE = 239,
    HOUSE_EMERALD_ISLAND_TELLMAR_RESIDENCE = 240,
    HOUSE_241 = 241, // Used in MAP_EMERALD_ISLAND, named "House 241", looks totally like a placeholder...
    HOUSE_242 = 242, // Used in MAP_EMERALD_ISLAND, named "House 242", looks totally like a placeholder...
    HOUSE_243 = 243, // Unused HOUSE named "House 243".
    HOUSE_244 = 244, // Unused HOUSE named "House 244".
    HOUSE_245 = 245, // Unused HOUSE named "House 245".
    HOUSE_246 = 246, // Unused HOUSE named "House 246".
    HOUSE_247 = 247, // Unused HOUSE named "House 247".
    HOUSE_248 = 248, // Unused HOUSE named "House 248".
    HOUSE_249 = 249, // Unused HOUSE named "House 249".
    HOUSE_250 = 250, // Unused HOUSE named "House 250".
    HOUSE_251 = 251, // Unused HOUSE named "House 251".
    HOUSE_252 = 252, // Unused HOUSE named "House 252".
    HOUSE_253 = 253, // Unused HOUSE named "House 253".
    HOUSE_254 = 254, // Used in MAP_EMERALD_ISLAND, named "House 254", looks totally like a placeholder...
    HOUSE_255 = 255, // Used in MAP_EMERALD_ISLAND, named "House 255", looks totally like a placeholder...
    HOUSE_256 = 256, // Unused HOUSE named "House 256".
    HOUSE_257 = 257, // Unused HOUSE named "House 257".
    HOUSE_258 = 258, // Unused HOUSE named "House 258".
    HOUSE_259 = 259, // Unused HOUSE named "House 259".
    HOUSE_260 = 260, // Unused HOUSE named "House 260".
    HOUSE_261 = 261, // Unused HOUSE named "House 261".
    HOUSE_262 = 262, // Unused HOUSE named "House 262".
    HOUSE_263 = 263, // Unused HOUSE named "House 263".
    HOUSE_264 = 264, // Unused HOUSE named "House 264".
    HOUSE_265 = 265, // Unused HOUSE named "House 265".
    HOUSE_266 = 266, // Unused HOUSE named "House 266".
    HOUSE_267 = 267, // Unused HOUSE named "House 267".
    HOUSE_268 = 268, // Unused HOUSE named "House 268".
    HOUSE_ERATHIA_GUTHWULFS_HOME = 269,
    HOUSE_ERATHIA_WOLVERTON_RESIDENCE = 270,
    HOUSE_271 = 271, // Used in MAP_ERATHIA, named "House 271", looks totally like a placeholder...
    HOUSE_272 = 272, // Used in MAP_ERATHIA, named "House 272", looks totally like a placeholder...
    HOUSE_273 = 273, // Used in MAP_ERATHIA, named "House 273", looks totally like a placeholder...
    HOUSE_ERATHIA_CASTROS_HOUSE = 274,
    HOUSE_LORD_MARKHAMS_MANOR_LORD_MARKHAMS_CHAMBER = 275,
    HOUSE_ERATHIA_LARASELLE_RESIDENCE = 276,
    HOUSE_ERATHIA_SOURBROW_HOME = 277,
    HOUSE_278 = 278, // Unused.
    HOUSE_ERATHIA_AGRAYNEL_RESIDENCE = 279,
    HOUSE_CASTLE_HARMONDALE__1 = 280,
    HOUSE_CASTLE_HARMONDALE__2 = 281,
    HOUSE_282 = 282, // Used in MAP_ERATHIA, named "House 282", looks totally like a placeholder...
    HOUSE_ERATHIA_TISH_RESIDENCE = 283,
    HOUSE_ERATHIA_TALION_HOUSE = 284,
    HOUSE_ERATHIA_RAVENHILL_RESIDENCE = 285,
    HOUSE_ERATHIA_CARDRIN_RESIDENCE = 286,
    HOUSE_287 = 287, // Unused.
    HOUSE_ERATHIA_GARETHS_HOME = 288,
    HOUSE_ERATHIA_FORGEWRIGHT_RESIDENCE = 289,
    HOUSE_ERATHIA_PRETTY_HOUSE = 290,
    HOUSE_ERATHIA_LOTTS_FAMILLY_HOME = 291,
    HOUSE_292 = 292, // Unused.
    HOUSE_ERATHIA_JULIANS_HOME = 293,
    HOUSE_ERATHIA_EVERSMYLE_RESIDENCE = 294,
    HOUSE_ERATHIA_DIRTHMOORE_RESIDENCE = 295,
    HOUSE_296 = 296, // Unused.
    HOUSE_297 = 297, // Unused.
    HOUSE_ERATHIA_HEARTSWORN_HOME = 298,
    HOUSE_ERATHIA_CARDRON_RESIDENCE = 299,
    HOUSE_300 = 300, // Unused.
    HOUSE_ERATHIA_THRUSH_RESIDENCE = 301,
    HOUSE_ERATHIA_HILLIER_RESIDENCE = 302,
    HOUSE_ERATHIA_QUIXOTE_RESIDENCE = 303,
    HOUSE_ERATHIA_ORG_HOUSE = 304,
    HOUSE_ERATHIA_TALREISH_RESIDENCE = 305,
    HOUSE_ERATHIA_BARNES_HOME = 306,
    HOUSE_ERATHIA_HAVEST_RESIDENCE = 307,
    HOUSE_TULAREAN_FOREST_BITH_RESIDENCE = 308,
    HOUSE_TULAREAN_FOREST_SURETRAIL_HOME = 309,
    HOUSE_TULAREAN_FOREST_SILVERPOINT_RESIDENCE = 310,
    HOUSE_TULAREAN_FOREST_MIYONS_HOME = 311,
    HOUSE_TULAREAN_FOREST_GREEN_HOUSE = 312,
    HOUSE_TULAREAN_FOREST_WARLIN_RESIDENCE = 313,
    HOUSE_TULAREAN_FOREST_DOTES_RESIDENCE = 314,
    HOUSE_TULAREAN_FOREST_BLUESWAN_HOME = 315,
    HOUSE_TULAREAN_FOREST_TREASURESTONE_HOME = 316,
    HOUSE_TULAREAN_FOREST_WINDSONG_HOUSE = 317,
    HOUSE_TULAREAN_FOREST_WHITECAP_RESIDENCE = 318,
    HOUSE_TULAREAN_FOREST_OTTIN_HOUSE = 319,
    HOUSE_TULAREAN_FOREST_BLACK_HOUSE = 320,
    HOUSE_TULAREAN_FOREST_FIDDLEBONE_RESIDENCE = 321,
    HOUSE_TULAREAN_FOREST_KERRID_RESIDENCE = 322,
    HOUSE_TULAREAN_FOREST_WILLOWBARKS_HOME = 323,
    HOUSE_324 = 324, // Used in MAP_TULAREAN_FOREST, named "House 324", looks totally like a placeholder...
    HOUSE_325 = 325, // Used in MAP_TULAREAN_FOREST, named "House 325", looks totally like a placeholder...
    HOUSE_326 = 326, // Used in MAP_TULAREAN_FOREST, named "House 326", looks totally like a placeholder...
    HOUSE_TULAREAN_FOREST_BENJAMINS_HOME = 327,
    HOUSE_TULAREAN_FOREST_STONEWRIGHT_RESIDENCE = 328,
    HOUSE_TULAREAN_FOREST_WEATHERSONS_HOUSE = 329,
    HOUSE_TULAREAN_FOREST_SOWER_RESIDENCE = 330,
    HOUSE_DEYJA_KARRAND_RESIDENCE = 331,
    HOUSE_DEYJA_CLEAREYES_HOME = 332,
    HOUSE_DEYJA_FOESTRYKE_RESIDENCE = 333,
    HOUSE_DEYJA_OXHIDE_RESIDENCE = 334,
    HOUSE_DEYJA_SHADOWRUNNERS_HOME = 335,
    HOUSE_DEYJA_KEDRIN_RESIDENCE = 336,
    HOUSE_DEYJA_BOTHAMS_HOME = 337,
    HOUSE_DEYJA_MOGREN_RESIDENCE = 338,
    HOUSE_DEYJA_DRAKEN_RESIDENCE = 339,
    HOUSE_DEYJA_HARLIS_PLACE = 340,
    HOUSE_DEYJA_NEVERMORE_RESIDENCE = 341,
    HOUSE_DEYJA_WISEMAN_RESIDENCE = 342,
    HOUSE_DEYJA_NIGHTCRAWLER_RESIDENCE = 343,
    HOUSE_DEYJA_FELBURNS_HOUSE = 344,
    HOUSE_DEYJA_UNDERSHADOWS_HOME = 345,
    HOUSE_DEYJA_SLICERS_HOUSE = 346,
    HOUSE_DEYJA_FALK_RESIDENCE = 347,
    HOUSE_EVENMORN_ISLAND_CAVERHILL_RESIDENCE = 348,
    HOUSE_EVENMORN_ISLAND_CRANE_RESIDENCE = 349,
    HOUSE_EVENMORN_ISLAND_SMITHSON_RESIDENCE = 350,
    HOUSE_TATALIA_RIVERSTONE_HOUSE = 351,
    HOUSE_MOUNT_NIGHON_WHITESKY_RESIDENCE = 352,
    HOUSE_MOUNT_NIGHON_ELMOS_HOUSE = 353,
    HOUSE_354 = 354, // Unused HOUSE named "Hostel".
    HOUSE_355 = 355, // Unused HOUSE named "Hostel".
    HOUSE_356 = 356, // Unused HOUSE named "Hostel".
    HOUSE_MOUNT_NIGHON_EVANDERS_HOME = 357,
    HOUSE_MOUNT_NIGHON_ANWYN_RESIDENCE = 358,
    HOUSE_MOUNT_NIGHON_SILKS_HOME = 359,
    HOUSE_360 = 360, // Unused HOUSE named "Hostel".
    HOUSE_361 = 361, // Unused HOUSE named "Hostel".
    HOUSE_362 = 362, // Unused HOUSE named "Hostel".
    HOUSE_363 = 363, // Unused HOUSE named "Hostel".
    HOUSE_MOUNT_NIGHON_DUSKS_HOME = 364,
    HOUSE_365 = 365, // Unused HOUSE named "Hostel".
    HOUSE_366 = 366, // Unused HOUSE named "Hostel".
    HOUSE_TATALIA_GREYDAWN_RESIDENCE = 367,
    HOUSE_TATALIA_STORMEYES_HOUSE = 368,
    HOUSE_TATALIA_BREMEN_RESIDENCE = 369,
    HOUSE_AVLEE_BRIGHTSPEAR_RESIDENCE = 370,
    HOUSE_AVLEE_HOLDEN_RESIDENCE = 371,
    HOUSE_372 = 372, // Unused.
    HOUSE_373 = 373, // Unused.
    HOUSE_374 = 374, // Unused.
    HOUSE_375 = 375, // Unused.
    HOUSE_AVLEE_FEATHERWIND_RESIDENCE = 376,
    HOUSE_AVLEE_RAVENHAIR_RESIDENCE = 377,
    HOUSE_AVLEE_JILLIANS_HOUSE = 378,
    HOUSE_AVLEE_GREENSTORM_RESIDENCE = 379,
    HOUSE_380 = 380, // Unused.
    HOUSE_381 = 381, // Unused.
    HOUSE_AVLEE_SNICK_HOUSE = 382,
    HOUSE_AVLEE_INFERNONS_HOUSE = 383,
    HOUSE_AVLEE_DEERHUNTER_RESIDENCE = 384,
    HOUSE_AVLEE_SWIFTFOOTS_HOUSE = 385,
    HOUSE_386 = 386, // Unused.
    HOUSE_TATALIA_STEELE_RESIDENCE = 387,
    HOUSE_TATALIA_CONSCIENCE_HOME = 388,
    HOUSE_TATALIA_EVERILS_HOUSE = 389,
    HOUSE_390 = 390, // Unused.
    HOUSE_391 = 391, // Unused.
    HOUSE_TATALIA_TRICIAS_HOUSE = 392,
    HOUSE_TATALIA_ISRAMS_HOUSE = 393,
    HOUSE_TATALIA_STONECLEAVER_RESIDENCE = 394,
    HOUSE_395 = 395, // Unused.
    HOUSE_TATALIA_CALINDRAS_HOME = 396,
    HOUSE_TATALIA_BROTHER_BOMBAHS = 397,
    HOUSE_TATALIA_REDDING_RESIDENCE = 398,
    HOUSE_399 = 399, // Unused.
    HOUSE_TATALIA_FISTS_HOUSE = 400,
    HOUSE_TATALIA_WACKOS = 401,
    HOUSE_TATALIA_WELDRICS_HOME = 402,
    HOUSE_403 = 403, // Unused.
    HOUSE_TATALIA_VISCONTI_RESIDENCE = 404,
    HOUSE_TATALIA_ARIN_RESIDENCE = 405,
    HOUSE_406 = 406, // Unused.
    HOUSE_407 = 407, // Unused.
    HOUSE_TATALIA_SAMPSON_RESIDENCE = 408,
    HOUSE_409 = 409, // Unused.
    HOUSE_TATALIA_TARENS_HOUSE = 410,
    HOUSE_TATALIA_MOORE_RESIDENCE = 411,
    HOUSE_TATALIA_ROTHHAMS_HOUSE = 412,
    HOUSE_STONE_CITY_KEENEDGE_RESIDENCE = 413,
    HOUSE_STONE_CITY_SELINES_HOUSE = 414,
    HOUSE_STONE_CITY_WELMAN_RESIDENCE = 415,
    HOUSE_STONE_CITY_THAINS_HOUSE = 416,
    HOUSE_STONE_CITY_GIZMOS = 417,
    HOUSE_STONE_CITY_SPARKS_HOUSE = 418,
    HOUSE_STONE_CITY_THORINSON_RESIDENCE = 419,
    HOUSE_STONE_CITY_URTHSMITE_RESIDENCE = 420,
    HOUSE_STONE_CITY_THRONE_ROOM = 421,
    HOUSE_CELESTE_HOUSE_DEVINE = 422,
    HOUSE_CELESTE_MORNINGSTAR_RESIDENCE = 423,
    HOUSE_CELESTE_HOUSE_WINTERBRIGHT = 424,
    HOUSE_CELESTE_HOSTEL_1 = 425,
    HOUSE_CELESTE_HOSTEL_2 = 426,
    HOUSE_CELESTE_HOSTEL_3 = 427,
    HOUSE_CELESTE_HOSTEL_4 = 428,
    HOUSE_CELESTE_TARENT_RESIDENCE = 429,
    HOUSE_CELESTE_RAMIEZ_RESIDENCE = 430,
    HOUSE_CELESTE_HOSTEL_5 = 431,
    HOUSE_CELESTE_HOSTEL_6 = 432,
    HOUSE_PIT_HOSTEL_1 = 433,
    HOUSE_PIT_HOSTEL_2 = 434,
    HOUSE_PIT_HOUSE_UMBERPOOL = 435,
    HOUSE_PIT_DARKENMORE_RESIDENCE = 436,
    HOUSE_PIT_SAND_RESIDENCE = 437,
    HOUSE_PIT_HOSTEL_3 = 438,
    HOUSE_PIT_HOSTEL_4 = 439,
    HOUSE_440 = 440, // Used in MAP_PIT but invalid, hmm...
    HOUSE_PIT_HOSTEL_5 = 441,
    HOUSE_PIT_HOSTEL_6 = 442,
    HOUSE_PIT_HOSTEL_7 = 443,
    HOUSE_PIT_HOSTEL_8 = 444,
    HOUSE_445 = 445, // Unused HOUSE named "Barrow".
    HOUSE_446 = 446, // Unused.
    HOUSE_447 = 447, // Unused.
    HOUSE_448 = 448, // Unused.
    HOUSE_449 = 449, // Unused.
    HOUSE_450 = 450, // Unused.
    HOUSE_451 = 451, // Unused.
    HOUSE_452 = 452, // Unused.
    HOUSE_453 = 453, // Unused.
    HOUSE_454 = 454, // Unused.
    HOUSE_455 = 455, // Unused.
    HOUSE_456 = 456, // Unused.
    HOUSE_457 = 457, // Unused.
    HOUSE_458 = 458, // Unused.
    HOUSE_459 = 459, // Unused.
    HOUSE_460 = 460, // Unused.
    HOUSE_461 = 461, // Unused.
    HOUSE_462 = 462, // Unused.
    HOUSE_463 = 463, // Unused.
    HOUSE_464 = 464, // Unused.
    HOUSE_HARMONDALE_MIST_MANOR = 465,
    HOUSE_HARMONDALE_HILLSMEN_RESIDENCE = 466,
    HOUSE_HARMONDALE_STILLWATER_RESIDENCE = 467,
    HOUSE_HARMONDALE_MARK_MANOR = 468,
    HOUSE_HARMONDALE_BOWES_RESIDENCE = 469,
    HOUSE_HARMONDALE_TEMPER_RESIDENCE = 470,
    HOUSE_HARMONDALE_KREWLEN_RESIDENCE = 471,
    HOUSE_HARMONDALE_WITHERSMYTHES_HOME = 472,
    HOUSE_473 = 473, // Unused HOUSE named "House 473".
    HOUSE_BRACADA_DESERT_SMILING_JACKS = 474,
    HOUSE_BRACADA_DESERT_PEDERTON_RESIDENCE = 475,
    HOUSE_BRACADA_DESERT_APPLEBEE_MANOR = 476,
    HOUSE_BRACADA_DESERT_LIGHTSWORN_RESIDENCE = 477,
    HOUSE_BRACADA_DESERT_ALASHANDRAS_HOME = 478,
    HOUSE_BRACADA_DESERT_GAYLES = 479,
    HOUSE_BRACADA_DESERT_BRIGHAMS_HOME = 480,
    HOUSE_BRACADA_DESERT_ROWANS_HOUSE = 481,
    HOUSE_BRACADA_DESERT_BRANDS_HOME = 482,
    HOUSE_BRACADA_DESERT_BENSON_RESIDENCE = 483,
    HOUSE_BRACADA_DESERT_ZIMMS_HOUSE = 484,
    HOUSE_HARMONDALE_KERN_RESIDENCE = 485,
    HOUSE_HARMONDALE_CHADRICS_HOUSE = 486,
    HOUSE_HARMONDALE_WEIDER_RESIDENCE = 487,
    HOUSE_HARMONDALE_SKINNERS_HOUSE = 488,
    HOUSE_HARMONDALE_TORRENTS = 489,
    HOUSE_HARMONDALE_HUME_RESIDENCE = 490,
    HOUSE_HARMONDALE_FARSWELL_RESIDENCE = 491,
    HOUSE_ERATHIA_RAVENSWOOD_RESIDENCE = 492,
    HOUSE_ERATHIA_BLAYZES = 493,
    HOUSE_ERATHIA_NORRIS_HOUSE = 494,
    HOUSE_ERATHIA_DREAMWRIGHT_RESIDENCE = 495,
    HOUSE_ERATHIA_WAIN_MANOR = 496,
    HOUSE_DEYJA_PUTNAM_RESIDENCE = 497,
    HOUSE_DEYJA_HAWKER_RESIDENCE = 498,
    HOUSE_DEYJA_AVALANCHES = 499,
    HOUSE_BRACADA_DESERT_STONE_HOUSE = 500,
    HOUSE_BRACADA_DESERT_WATERSHED_RESIDENCE = 501,
    HOUSE_BRACADA_DESERT_HOLLYFIELD_RESIDENCE = 502,
    HOUSE_BRACADA_DESERT_SWEET_RESIDENCE = 503,
    HOUSE_AVLEE_TEMPUS_HOUSE = 504,
    HOUSE_AVLEE_KAINES = 505,
    HOUSE_AVLEE_APPLE_RESIDENCE = 506,
    HOUSE_MOUNT_NIGHON_ROGGEN_RESIDENCE = 507,
    HOUSE_MOUNT_NIGHON_ELZBETS_HOUSE = 508,
    HOUSE_MOUNT_NIGHON_AZNOGS_PLACE = 509,
    HOUSE_MOUNT_NIGHON_HOLLIS_HOME = 510,
    HOUSE_MOUNT_NIGHON_LANSHEES_HOUSE = 511,
    HOUSE_MOUNT_NIGHON_NELDON_RESIDENCE = 512,
    HOUSE_MOUNT_NIGHON_HAWTHORNE_RESIDENCE = 513,
    HOUSE_LAND_OF_THE_GIANTS_LASITERS_HOME = 514,
    HOUSE_BARROW_DOWNS_DALLIAS_HOME = 515,
    HOUSE_BARROW_DOWNS_GEMSTONE_RESIDENCE = 516,
    HOUSE_BARROW_DOWNS_FELDSPARS_HOME = 517,
    HOUSE_BARROW_DOWNS_FISSURE_RESIDENCE = 518,
    HOUSE_BARROW_DOWNS_GARNET_HOUSE = 519,
    HOUSE_BARROW_DOWNS_RIVENROCK_RESIDENCE = 520,
    HOUSE_521 = 521, // Unused HOUSE named "Thomas Grey".
    HOUSE_CASTLE_GRYPHONHEART_ALICE_HARGREAVES = 522,
    HOUSE_523 = 523, // Unused.
    HOUSE_524 = 524, // Unused.

    // These two are "pseudo" houses, they do not have entries in the building table.
    HOUSE_THRONEROOM_WIN_GOOD = 600, // Final task completion for good side
    HOUSE_THRONEROOM_WIN_EVIL = 601, // Final task completion for evil side

    HOUSE_FIRST_SHOP = HOUSE_WEAPON_SHOP_EMERALD_ISLAND,
    HOUSE_LAST_SHOP = HOUSE_52, // Using 52 and not 53 because vanilla shop arrays do not take it into account.

    HOUSE_FIRST_WEAPON_SHOP = HOUSE_WEAPON_SHOP_EMERALD_ISLAND,
    HOUSE_LAST_WEAPON_SHOP = HOUSE_14,

    HOUSE_FIRST_ARMOR_SHOP = HOUSE_ARMOR_SHOP_EMERALD_ISLAND,
    HOUSE_LAST_ARMOR_SHOP = HOUSE_28,

    HOUSE_FIRST_MAGIC_SHOP = HOUSE_MAGIC_SHOP_EMERALD_ISLAND,
    HOUSE_LAST_MAGIC_SHOP = HOUSE_41,

    HOUSE_FIRST_ALCHEMY_SHOP = HOUSE_ALCHEMY_SHOP_EMERALD_ISLAND,
    HOUSE_LAST_ALCHEMY_SHOP = HOUSE_53,

    HOUSE_FIRST_STABLE = HOUSE_STABLE_HARMONDALE,
    HOUSE_LAST_STABLE = HOUSE_62,

    HOUSE_FIRST_BOAT = HOUSE_BOAT_EMERALD_ISLAND,
    HOUSE_LAST_BOAT = HOUSE_73,

    HOUSE_FIRST_TRANSPORT = HOUSE_STABLE_HARMONDALE,
    HOUSE_LAST_TRANSPORT = HOUSE_73,

    HOUSE_FIRST_MAGIC_GUILD = HOUSE_FIRE_GUILD_EMERALD_ISLAND,
    HOUSE_LAST_MAGIC_GUILD = HOUSE_DARK_GUILD_PIT, // self guilds (which is missing in MM7) are not counted here

    HOUSE_FIRST_TRAINING_HALL = HOUSE_TRAINING_HALL_EMERALD_ISLAND,
    HOUSE_LAST_TRAINING_HALL = HOUSE_TRAINING_HALL_STONE_CITY,

    HOUSE_FIRST_TOWN_HALL = HOUSE_TOWN_HALL_HARMONDALE,
    HOUSE_LAST_TOWN_HALL = HOUSE_TOWN_HALL_PIT,

    HOUSE_FIRST_TAVERN = HOUSE_TAVERN_EMERALD_ISLAND,
    HOUSE_LAST_TAVERN = HOUSE_TAVERN_STONE_CITY,

    HOUSE_FIRST_ARCOMAGE_TAVERN = HOUSE_TAVERN_HARMONDALE,
    HOUSE_LAST_ARCOMAGE_TAVERN = HOUSE_TAVERN_STONE_CITY,

    HOUSE_FIRST = HOUSE_WEAPON_SHOP_EMERALD_ISLAND,
    HOUSE_LAST = HOUSE_524
};
using enum HouseId;

inline Segment<HouseId> allTownhallHouses() {
    return {HOUSE_FIRST_TOWN_HALL, HOUSE_LAST_TOWN_HALL};
}

inline Segment<HouseId> allHouses() {
    return {HOUSE_FIRST, HOUSE_LAST};
}

inline Segment<HouseId> allArcomageTaverns() {
    return {HOUSE_FIRST_ARCOMAGE_TAVERN, HOUSE_LAST_ARCOMAGE_TAVERN};
}

inline bool isShop(HouseId houseId) {
    return houseId >= HOUSE_FIRST_SHOP && houseId <= HOUSE_LAST_SHOP;
}

inline bool isWeaponShop(HouseId houseId) {
    return houseId >= HOUSE_FIRST_WEAPON_SHOP && houseId <= HOUSE_LAST_WEAPON_SHOP;
}

inline bool isArmorShop(HouseId houseId) {
    return houseId >= HOUSE_FIRST_ARMOR_SHOP && houseId <= HOUSE_LAST_ARMOR_SHOP;
}

inline bool isMagicShop(HouseId houseId) {
    return houseId >= HOUSE_FIRST_MAGIC_SHOP && houseId <= HOUSE_LAST_MAGIC_SHOP;
}

inline bool isAlchemyShop(HouseId houseId) {
    return houseId >= HOUSE_FIRST_ALCHEMY_SHOP && houseId <= HOUSE_LAST_ALCHEMY_SHOP;
}

inline bool isMagicGuild(HouseId houseId) {
    return houseId >= HOUSE_FIRST_MAGIC_GUILD && houseId <= HOUSE_LAST_MAGIC_GUILD;
}

inline bool isStable(HouseId houseId) {
    return houseId >= HOUSE_FIRST_STABLE && houseId <= HOUSE_LAST_STABLE;
}

inline bool isBoat(HouseId houseId) {
    return houseId >= HOUSE_FIRST_BOAT && houseId <= HOUSE_LAST_BOAT;
}

inline bool isTavern(HouseId houseId) {
    return houseId >= HOUSE_FIRST_TAVERN && houseId <= HOUSE_LAST_TAVERN;
}

inline bool isArcomageTavern(HouseId houseId) {
    return houseId >= HOUSE_FIRST_ARCOMAGE_TAVERN && houseId <= HOUSE_LAST_ARCOMAGE_TAVERN;
}

inline int arcomageTopicForTavern(HouseId houseId) {
    assert(isArcomageTavern(houseId));
    return std::to_underlying(houseId) - std::to_underlying(HOUSE_FIRST_ARCOMAGE_TAVERN) + 355;
}

enum class HouseSoundType : uint32_t {
    HOUSE_SOUND_GENERAL_GREETING = 1,
    HOUSE_SOUND_GENERAL_NOT_ENOUGH_GOLD = 2,

    HOUSE_SOUND_MAGIC_GUILD_MEMBERS_ONLY = 3,
    HOUSE_SOUND_SHOP_GOODBYE_RUDE = 3,
    HOUSE_SOUND_SHOP_GOODBYE_POLITE = 4,
    HOUSE_SOUND_ALCHEMY_SHOP_GOODBYE_REGULAR = 3,
    HOUSE_SOUND_ALCHEMY_SHOP_GOODBYE_BOUGHT = 4,
    HOUSE_SOUND_TEMPLE_GOODBYE = 3,
    HOUSE_SOUND_BANK_GOODBYE = 3,
    HOUSE_SOUND_TAVERN_RENT_ROOM = 2,
    HOUSE_SOUND_TAVERN_BUY_FOOD = 3,
    HOUSE_SOUND_TAVERN_NOT_ENOUGH_GOLD = 4,
    HOUSE_SOUND_TRAINING_TRAIN = 2,
    HOUSE_SOUND_TRAINING_CANT_TRAIN = 3,
    HOUSE_SOUND_TRAINING_NOT_ENOUGH_GOLD = 4,
    HOUSE_SOUND_TRANSPORT_TRAVEL = 2,
    HOUSE_SOUND_TRANSPORT_NOT_ENOUGH_GOLD = 3
};
using enum HouseSoundType;
