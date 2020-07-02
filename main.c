#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Attacker Struct */
typedef struct {
	int A;			/* Attacking unit's Attacks stat or how many shots are fired */
	int BSWS;		/* Unit's weapon skill or ballistic skill */
	int hitMod;		/* Modifier to the unit's hit roll */
	int hitOfSix;		/* The event that occurs on a hit roll of 6 */
	int hitReroll;		/* The cause of re-rolling a hit roll */
	int S;			/* Unit's Weapon's Strength characteristic */
	int woundMod;		/* Modifier to a unit's wound roll */
	int woundOfSix; 	/* The event that occurs on a wound roll of 6 */
	int woundReroll;	/* The cause of re-rolling a wound roll */
	int AP;			/* Weapon's AP value */
	char *D;		/* Weapon's damage value */
} Attacker;

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


int main (int argc, char **argv) {
	
	Attacker *atk;
	Defender *dfd;

	atk = calloc(1, sizeof(Attacker));
	dfd = calloc(1, sizeof(Defender));

		

	return 0;
}
