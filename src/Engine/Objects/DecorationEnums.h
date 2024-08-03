#pragma once

#include <cstdint>

#include "Utility/Flags.h"

/**
 * Enum of all decorations in the game, e.g. trees, trash heaps, pedestals, etc.
 *
 * DON'T EDIT, THIS IS AUTOGENERATED CODE.
 *
 * @see runDecorationsCodegen
 */
enum class DecorationId : int32_t {
    DECORATION_NULL = 0,
    DECORATION_PENDING_1 = 1,             // Pending!, test, light_r=16
    DECORATION_PARTY_START_2 = 2,         // Party Start, test
    DECORATION_FOUNTAIN_3 = 3,            // fount1, fountain
    DECORATION_TRASH_HEAP_4 = 4,          // dec01, trash heap
    DECORATION_CAMPFIRE_5 = 5,            // dec02, campfire
    DECORATION_CAULDRON_6 = 6,            // dec03, cauldron
    DECORATION_CHANDELIER_7 = 7,          // dec04, chandelier
    DECORATION_CAGE_8 = 8,                // dec05, cage
    DECORATION_CAGE_9 = 9,                // dec06, cage
    DECORATION_CAGE_10 = 10,              // dec07, cage
    DECORATION_FRUIT_BOWL_11 = 11,        // dec08, fruit bowl
    DECORATION_ROCK_12 = 12,              // dec09, rock
    DECORATION_TRASH_HEAP_13 = 13,        // dec10, trash heap
    DECORATION_DIRT_14 = 14,              // dec11, dirt
    DECORATION_WOOD_15 = 15,              // dec12, wood
    DECORATION_WOOD_16 = 16,              // dec13, wood
    DECORATION_WOOD_17 = 17,              // dec14, wood
    DECORATION_WOOD_18 = 18,              // dec15, wood
    DECORATION_WOOD_19 = 19,              // dec16, wood
    DECORATION_WOOD_20 = 20,              // dec17, wood
    DECORATION_BONES_21 = 21,             // dec18, bones
    DECORATION_BONES_22 = 22,             // dec19, bones
    DECORATION_SKULL_23 = 23,             // dec20, skull
    DECORATION_CASK_24 = 24,              // dec21, cask, snd=10
    DECORATION_SHIP_25 = 25,              // dec22, ship, snd=18
    DECORATION_BAG_26 = 26,               // dec23, bag
    DECORATION_BARREL_27 = 27,            // dec24, barrel
    DECORATION_KEG_28 = 28,               // dec25, keg
    DECORATION_FIRE_29 = 29,              // dec26, fire
    DECORATION_FIRE_30 = 30,              // dec27, fire
    DECORATION_TORCH_31 = 31,             // torch01, torch, light_r=512, light_c=#ff8000
    DECORATION_TORCH_32 = 32,             // torch02, torch, light_r=512, light_c=#ff8000
    DECORATION_TORCH_33 = 33,             // torch03, torch, light_r=512, light_c=#ff8000
    DECORATION_BARREL_34 = 34,            // dec32, barrel, snd=228
    DECORATION_BUOY_35 = 35,              // dec33, buoy
    DECORATION_ROCK_36 = 36,              // dec34, rock
    DECORATION_FOUNTAIN_37 = 37,          // dec35, fountain, snd=10
    DECORATION_FIRE_38 = 38,              // fire01, large fire, light_r=256, light_c=#ff0000
    DECORATION_NORTH_START_39 = 39,       // north start, null
    DECORATION_SOUTH_START_40 = 40,       // south start, null
    DECORATION_EAST_START_41 = 41,        // east start, null
    DECORATION_WEST_START_42 = 42,        // west start, null
    DECORATION_BOTTLE_43 = 43,            // dec41, bottle
    DECORATION_BOWL_44 = 44,              // dec42, bowl
    DECORATION_STACK_OF_BOWLS_45 = 45,    // dec43, stack of bowls
    DECORATION_BOWL_46 = 46,              // dec44, bowl
    DECORATION_STACK_OF_BOWLS_47 = 47,    // dec45, stack of bowls
    DECORATION_GOBLET_48 = 48,            // dec46, goblet
    DECORATION_GOBLET_49 = 49,            // dec47, goblet
    DECORATION_GOBLET_50 = 50,            // dec48, goblet
    DECORATION_MILE_MARKET_51 = 51,       // dec49, mile market
    DECORATION_PLATE_52 = 52,             // dec50, plate
    DECORATION_STACK_OF_PLATES_53 = 53,   // dec51, stack of plates
    DECORATION_PLATE_54 = 54,             // dec52, plate
    DECORATION_STACK_OF_PLATES_55 = 55,   // dec53, stack of plates
    DECORATION_TREE_56 = 56,              // tree01, tree
    DECORATION_TREE_57 = 57,              // tree02, tree
    DECORATION_TREE_58 = 58,              // tree03, tree
    DECORATION_TREE_59 = 59,              // tree04, tree
    DECORATION_TREE_60 = 60,              // tree05, tree
    DECORATION_TREE_61 = 61,              // tree06, tree
    DECORATION_TREE_62 = 62,              // tree07, tree
    DECORATION_TREE_63 = 63,              // tree08, tree
    DECORATION_TREE_64 = 64,              // tree09, tree
    DECORATION_TREE_65 = 65,              // tree10, tree
    DECORATION_TREE_66 = 66,              // tree11, tree
    DECORATION_TREE_67 = 67,              // tree12, tree
    DECORATION_TREE_68 = 68,              // tree13, tree
    DECORATION_TREE_69 = 69,              // tree14, tree
    DECORATION_TREE_70 = 70,              // tree15, tree
    DECORATION_TREE_71 = 71,              // tree16, tree
    DECORATION_TREE_72 = 72,              // tree17, tree
    DECORATION_TREE_73 = 73,              // tree18, tree
    DECORATION_TREE_74 = 74,              // tree19, tree
    DECORATION_TREE_75 = 75,              // tree20, tree
    DECORATION_TREE_76 = 76,              // tree21, tree
    DECORATION_TREE_77 = 77,              // tree22, tree
    DECORATION_TREE_78 = 78,              // tree23, tree
    DECORATION_TREE_79 = 79,              // tree24, tree
    DECORATION_TREE_80 = 80,              // tree25, tree
    DECORATION_TREE_81 = 81,              // tree26, tree
    DECORATION_TREE_82 = 82,              // tree27, tree
    DECORATION_TREE_83 = 83,              // tree28, tree
    DECORATION_TREE_84 = 84,              // tree29, tree
    DECORATION_TREE_85 = 85,              // tree30, tree
    DECORATION_TREE_86 = 86,              // tree31, tree
    DECORATION_TREE_87 = 87,              // tree32, tree
    DECORATION_TREE_88 = 88,              // tree33, tree
    DECORATION_TREE_89 = 89,              // tree34, tree
    DECORATION_TREE_90 = 90,              // tree35, tree
    DECORATION_TREE_91 = 91,              // tree36, tree
    DECORATION_TREE_92 = 92,              // tree37, tree
    DECORATION_TREE_93 = 93,              // tree38, tree
    DECORATION_TREE_94 = 94,              // tree39, tree
    DECORATION_TREE_95 = 95,              // tree40, tree
    DECORATION_TREE_96 = 96,              // tree41, tree
    DECORATION_TREE_97 = 97,              // tree42, tree
    DECORATION_SND_BROOK_98 = 98,         // Snd_Brook, test, snd=10
    DECORATION_SND_BOAT_99 = 99,          // Snd_Boat, test, snd=18
    DECORATION_SND_HOWL_100 = 100,        // Snd_Howl, test, snd=233
    DECORATION_SND_DRAGON_101 = 101,      // Snd_Dragon, test, snd=1103
    DECORATION_BUSH_102 = 102,            // bush01, bush
    DECORATION_BUSH_103 = 103,            // bush02, bush
    DECORATION_BUSH_104 = 104,            // bush03, bush
    DECORATION_BUSH_105 = 105,            // bush04, bush
    DECORATION_BUSH_106 = 106,            // bush05, bush
    DECORATION_BUSH_107 = 107,            // bush06, bush
    DECORATION_BUSH_108 = 108,            // bush07, bush
    DECORATION_BUSH_109 = 109,            // bush08, bush
    DECORATION_ROCK_110 = 110,            // rock01, rock
    DECORATION_ROCK_111 = 111,            // rock02, rock
    DECORATION_ROCK_112 = 112,            // rock03, rock
    DECORATION_ROCK_113 = 113,            // rock04, rock
    DECORATION_ROCK_114 = 114,            // rock05, rock
    DECORATION_ROCK_115 = 115,            // rock06, rock
    DECORATION_ROCK_116 = 116,            // rock07, rock
    DECORATION_ROCK_117 = 117,            // rock08, rock
    DECORATION_ROCK_118 = 118,            // rock09, rock
    DECORATION_ROCK_119 = 119,            // rock10, rock
    DECORATION_ROCK_120 = 120,            // rock11, rock
    DECORATION_ROCK_121 = 121,            // rock12, rock
    DECORATION_ROCK_122 = 122,            // rock13, rock
    DECORATION_ROCK_123 = 123,            // rock14, rock
    DECORATION_ROCK_124 = 124,            // rock15, rock
    DECORATION_ROCK_125 = 125,            // rock16, rock
    DECORATION_ROCK_126 = 126,            // rock17, rock
    DECORATION_ROCK_127 = 127,            // rock18, rock
    DECORATION_ROCK_128 = 128,            // rock19, rock
    DECORATION_ROCK_129 = 129,            // rock20, rock
    DECORATION_TORCH_130 = 130,           // TORCH05, torch, light_r=512, light_c=#1c00ff
    DECORATION_TORCH_131 = 131,           // torch06, torch, light_r=512, light_c=#00ff00
    DECORATION_TORCH_132 = 132,           // torch07, torch, light_r=512, light_c=#ff0000
    DECORATION_BUSH_133 = 133,            // bush09, cactus
    DECORATION_BUSH_134 = 134,            // bush10, cactus
    DECORATION_BUSH_135 = 135,            // bush11, cactus
    DECORATION_BUSH_136 = 136,            // bush12, cactus
    DECORATION_BUSH_137 = 137,            // bush13, cactus
    DECORATION_BUSH_138 = 138,            // bush14, cactus
    DECORATION_BUSH_139 = 139,            // bush15, cactus
    DECORATION_BUSH_140 = 140,            // bush16, cactus
    DECORATION_FLOWER_141 = 141,          // flower01, flower
    DECORATION_FLOWER_142 = 142,          // flower02, flower
    DECORATION_FLOWER_143 = 143,          // flower03, flower
    DECORATION_FLOWER_144 = 144,          // flower04, flower
    DECORATION_FLOWER_145 = 145,          // flower05, flower
    DECORATION_FLOWER_146 = 146,          // flower06, flower
    DECORATION_FLOWER_147 = 147,          // flower07, flower
    DECORATION_FLOWER_148 = 148,          // flower08, flower
    DECORATION_FLOWER_149 = 149,          // flower09, flower
    DECORATION_FLOWER_150 = 150,          // flower10, flower
    DECORATION_FLOWER_151 = 151,          // flower11, flower
    DECORATION_FLOWER_152 = 152,          // flower12, flower
    DECORATION_FLOWER_153 = 153,          // flower13, flower
    DECORATION_FLOWER_154 = 154,          // flower14, flower
    DECORATION_FLOWER_155 = 155,          // flower15, flower
    DECORATION_FLOWER_156 = 156,          // flower16, flower
    DECORATION_PLANT_157 = 157,           // plant01a, plant
    DECORATION_PLANT_158 = 158,           // plant01b, plant
    DECORATION_PLANT_159 = 159,           // plant02a, plant
    DECORATION_PLANT_160 = 160,           // plant02b, plant
    DECORATION_PLANT_161 = 161,           // plant03a, plant
    DECORATION_PLANT_162 = 162,           // plant03b, plant
    DECORATION_PLANT_163 = 163,           // plant04a, plant
    DECORATION_PLANT_164 = 164,           // plant04b, plant
    DECORATION_PLANT_165 = 165,           // plant05a, plant
    DECORATION_PLANT_166 = 166,           // plant05b, plant
    DECORATION_PLANT_167 = 167,           // plant06a, plant
    DECORATION_PLANT_168 = 168,           // plant06b, plant
    DECORATION_PLANT_169 = 169,           // plant07a, plant
    DECORATION_PLANT_170 = 170,           // plant07b, plant
    DECORATION_PLANT_171 = 171,           // plant08a, plant
    DECORATION_PLANT_172 = 172,           // plant08b, plant
    DECORATION_PLANT_173 = 173,           // plant09a, plant
    DECORATION_PLANT_174 = 174,           // plant09b, plant
    DECORATION_PLANT_175 = 175,           // plant10a, plant
    DECORATION_PLANT_176 = 176,           // plant10b, plant
    DECORATION_PLANT_177 = 177,           // plant11a, plant
    DECORATION_PLANT_178 = 178,           // plant11b, plant
    DECORATION_PLANT_179 = 179,           // plant12a, plant
    DECORATION_PLANT_180 = 180,           // plant12b, plant
    DECORATION_STATUE_181 = 181,          // dec54, statue
    DECORATION_STATUE_182 = 182,          // dec55, statue
    DECORATION_VASE_183 = 183,            // dec97, vase
    DECORATION_FIRE_184 = 184,            // dec24, fire
    DECORATION_MUSHROOM_185 = 185,        // dec86, mushroom
    DECORATION_LOG_186 = 186,             // dec87, log
    DECORATION_MUSHROOM_187 = 187,        // dec88, mushroom
    DECORATION_FOSSIL_188 = 188,          // dec89, fossil
    DECORATION_FOSSIL_189 = 189,          // dec90, fossil
    DECORATION_MUSHROOM_190 = 190,        // dec91, mushroom
    DECORATION_STALAGMITE_191 = 191,      // dec92, stalagmite
    DECORATION_MUSHROOM_192 = 192,        // dec93, mushroom
    DECORATION_MUSHROOM_193 = 193,        // dec98, mushroom
    DECORATION_MUSHROOM_194 = 194,        // dec99, mushroom
    DECORATION_TREE_195 = 195,            // tree60, tree
    DECORATION_TREE_196 = 196,            // tree61, tree
    DECORATION_TREE_197 = 197,            // tree62, tree
    DECORATION_TREE_198 = 198,            // tree63, tree
    DECORATION_TREE_199 = 199,            // tree64, tree
    DECORATION_TREE_200 = 200,            // tree65, tree
    DECORATION_TREE_201 = 201,            // tree66, tree
    DECORATION_STATUE_202 = 202,          // dec94, statue
    DECORATION_STATUE_203 = 203,          // dec95, statue
    DECORATION_STATUE_204 = 204,          // dec96, statue
    DECORATION_TREE_205 = 205,            // tree69, tree69
    DECORATION_BEACON_FIRE_206 = 206,     // dec60, beacon fire, light_r=128
    DECORATION_BEACON_FIRE_207 = 207,     // dec61, beacon fire, light_r=128
    DECORATION_BEACON_FIRE_208 = 208,     // dec62, beacon fire, light_r=128
    DECORATION_BEACON_FIRE_209 = 209,     // dec63, beacon fire, light_r=128
    DECORATION_MAGIC_PEDASTAL_210 = 210,  // dec64, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_211 = 211,  // dec65, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_212 = 212,  // dec66, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_213 = 213,  // dec67, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_214 = 214,  // dec68, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_215 = 215,  // dec69, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_216 = 216,  // dec70, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_217 = 217,  // dec71, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_218 = 218,  // dec72, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_219 = 219,  // dec73, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_220 = 220,  // dec74, magic pedastal, light_r=64
    DECORATION_MAGIC_PEDASTAL_221 = 221,  // dec75, magic pedastal, light_r=64
    DECORATION_BURNED_OUT_FIRE_222 = 222, // dec24x, burned out fire
    DECORATION_223 = 223,                 // Unused.
    DECORATION_TREE_224 = 224,            // tree43, tree
    DECORATION_TREE_225 = 225,            // tree44, tree
    DECORATION_TREE_226 = 226,            // tree45, tree
    DECORATION_TREE_227 = 227,            // tree46, tree
};
using enum DecorationId;

enum class DecorationDescFlag : uint16_t {
    DECORATION_DESC_MOVE_THROUGH = 0x0001,
    DECORATION_DESC_DONT_DRAW = 0x0002,
    DECORATION_DESC_FLICKER_SLOW = 0x0004,
    DECORATION_DESC_FICKER_AVERAGE = 0x0008,
    DECORATION_DESC_FICKER_FAST = 0x0010,
    DECORATION_DESC_MARKER = 0x0020,
    DECORATION_DESC_SLOW_LOOP = 0x0040,
    DECORATION_DESC_EMITS_FIRE = 0x0080,
    DECORATION_DESC_SOUND_ON_DAWN = 0x0100,
    DECORATION_DESC_SOUND_ON_DUSK = 0x0200,
    DECORATION_DESC_EMITS_SMOKE = 0x0400,
};
using enum DecorationDescFlag;
MM_DECLARE_FLAGS(DecorationDescFlags, DecorationDescFlag)
MM_DECLARE_OPERATORS_FOR_FLAGS(DecorationDescFlags)


enum class LevelDecorationFlag : uint16_t {
    LEVEL_DECORATION_TRIGGERED_BY_TOUCH = 0x01,
    LEVEL_DECORATION_TRIGGERED_BY_MONSTER = 0x02,
    LEVEL_DECORATION_TRIGGERED_BY_OBJECT = 0x04,
    LEVEL_DECORATION_VISIBLE_ON_MAP = 0x08,
    LEVEL_DECORATION_CHEST = 0x10,
    LEVEL_DECORATION_INVISIBLE = 0x20,
    LEVEL_DECORATION_OBELISK_CHEST = 0x40,
};
using enum LevelDecorationFlag;
MM_DECLARE_FLAGS(LevelDecorationFlags, LevelDecorationFlag)
MM_DECLARE_OPERATORS_FOR_FLAGS(LevelDecorationFlags)
