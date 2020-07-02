/* Attacker Struct */
typedef struct {
	int A;				/* Attacking unit's Attacks stat or how many shots are fired */
	char BSWS[2];		/* Unit's weapon skill or ballistic skill */
	int hitMod;			/* Modifier to the unit's hit roll */
	int hitOfSix;		/* The event that occurs on a hit roll of 6 */
	int hitReroll;		/* The cause of re-rolling a hit roll */
	int S;				/* Unit's Weapon's Strength characteristic */
	int woundMod;		/* Modifier to a unit's wound roll */
	int woundOfSix; 	/* The event that occurs on a wound roll of 6 */
	int woundReroll;	/* The cause of re-rolling a wound roll */
	int AP;				/* Weapon's AP value */
	int d6;				/* D6's in weapons damage profile */
	int d3;				/* D3's in weapons damage profile */
	int dmg;			/* weapon's base damage */
} Attacker;
