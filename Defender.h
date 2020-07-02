/* Defender Struct */
typedef struct {
	int T;			/* Defender's toughness value */
	int save;		/* Unit's basic armor save */
	int saveMod;		/* Modifier to a unit's armor save */
	char cover;		/* whether a unit is in cover or not */
	int invulnSave;		/* Unit's invulnerable save */
	int reroll;		/* criteria for a unit to re-roll a save */
	int W;			/* How many wounds each model has */
	int FnP;		/* Feel No Pain / Disgustingly Resilient */
	int LD;			/* Unit's leadership characteristic */
	int LDMod;		/* Modifier for a unit's LD */
	int models;		/* How many models are in the unit */
} Defender;
