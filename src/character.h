//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef CHARACTER_H
#define CHARACTER_H

#include "main.h"

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum Race
{
	RACE_HUMAN,
	RACE_KRIGON,
	RACE_TOREM,
	RACE_VRISK
};

enum Job
{
	JOB_HUNTER,
	JOB_PIRATE,
	JOB_SCIENTIST,
	JOB_STREAMER
};

enum DamageRoll
{
	DMG_1D3,
	DMG_2D3,
	DMG_1D4,
	DMG_2D4,
	DMG_2D5,
	DMG_1D6,
	DMG_1D6_PLUS_1,
	DMG_1D6_PLUS_2,
	DMG_2D6,
	DMG_1D8,
	DMG_2D8,
	DMG_2D10,
	DMG_1D12,
	DMG_1D12_PLUS_1,
	DMG_1D12_PLUS_3,
	DMG_1D12_PLUS_5,
};

enum DamageType
{
	DT_KINETIC = 1 << 0,
	DT_ENERGY = 1 << 1
};

enum DamageResistance
{
	DR_NONE,	// Takes regular damage.
	DR_WEAK,	// Takes max damage.
	DR_STRONG,	// Takes minimum damage, at least 1.
	DR_IMMUNE,	// Zero damage.
	DR_REFLECT, // Reflects the damage to the attacker.
	DR_DRAIN	// Healed by the attack.
};

enum MeleeWeaponId
{
	MW_NONE,
	MW_ELECKNIFE,
	MW_ELECSTAFF,
	MW_SPEAR,
	MW_ELECAXE,
	MW_SHINYBLADE,
	MW_LASERSABER,
	MW_ICECUTLASS,
	MW_COSMICAXE,
	MW_FIREBLADE,
	MW_STARHAMMER
};

enum RangedWeaponId
{
	RW_NONE,
	RW_STUNGUN,
	RW_AIRPISTOL,
	RW_LASERBUSS,
	RW_CROSSBOW,
	RW_LASERGUN,
	RW_SHOTGUN,
	RW_LASERRIFLE,
	RW_HELLGUN,
	RW_SHARPSHOT,
	RW_ROCKETGUN
};

enum ArmorId
{
	ARMOR_NONE,
	ARMOR_LIGHTVEST,
	ARMOR_JUMPSUIT,
	ARMOR_NANOSKIN,
	ARMOR_HARDSUIT,
	ARMOR_SHADOWVEST,
	ARMOR_NOVASUIT,
	ARMOR_HELLVEST,
	ARMOR_BATTLESUIT,
	ARMOR_CYBERVEST,
	ARMOR_HEAVYARMOR,
	ARMOR_PHOTONSUIT
};

//------------------------------------------------------------------
// Typedefs.
//------------------------------------------------------------------

typedef struct
{
	uchar name[10];
	uchar level;

	uchar might;
	uchar dexterity;
	uchar intellect;
	uchar personality;

	uint max_hp;
	uint current_hp;
} BaseSheet;

typedef struct
{
	BaseSheet base_stats;

	enum Race race;
	enum Job job;

	long int current_xp;

	enum MeleeWeaponId equipped_melee_weapon;
	enum RangedWeaponId equipped_ranged_weapon;
	enum ArmorId equipped_armor;
} CharacterSheet;

typedef struct
{
	BaseSheet base_stats;

	enum DamageResistance kinetic_resistance;
	enum DamageResistance energy_resistance;

	enum DamageRoll damage_roll;
	enum DamageType damage_type;

	uchar defense;
} CreatureSheet;

typedef struct
{
	uchar name[10];
	uint price;

	uchar req_might;
	uchar req_dexterity;
	uchar req_job;

	enum DamageRoll damage_roll;
	enum DamageType damage_type;
} Weapon;

typedef struct
{
	uchar name[10];
	uint price;

	uchar req_might;
	uchar req_job;

	enum DamageResistance kinetic_resistance;
	enum DamageResistance energy_resistance;

	uchar dexterity_penalty;
	uchar defense_bonus;
} Armor;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_add_damage_type(uchar *mask, enum DamageType type);
int sr_has_damage_type(uchar mask, enum DamageType type);

void sr_debug_create_default_character(CharacterSheet *character);
void sr_debug_create_default_creature(CreatureSheet *creature);

#endif
