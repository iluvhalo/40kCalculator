#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Attacker Struct */
typedef struct {
	int A;			/* Attacking unit's Attacks stat or how many shots are fired */
	char BSWS[2];		/* Unit's weapon skill or ballistic skill */
	int hitMod;		/* Modifier to the unit's hit roll */
	int hitOfSix;		/* The event that occurs on a hit roll of 6 */
	int hitReroll;		/* The cause of re-rolling a hit roll */
	int S;			/* Unit's Weapon's Strength characteristic */
	int woundMod;		/* Modifier to a unit's wound roll */
	int woundOfSix; 	/* The event that occurs on a wound roll of 6 */
	int woundReroll;	/* The cause of re-rolling a wound roll */
	int AP;			/* Weapon's AP value */
	char D[20];		/* Weapon's damage value */
	int d6;
	int d3;
	int dmg;
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
	char *tmp;

	atk = calloc(1, sizeof(Attacker));
	dfd = calloc(1, sizeof(Defender));
	tmp = calloc(1, sizeof(char) * 100);

	printf("%s\n", "Welcome to the Warhammer 40k Mathhammer Calculator");
	printf("%s\n", "This will collect information about Attacking and Defending units and calculate expected hits, wound, damage, and morale");
	printf("%s\n", "Lets start by collecting information about the attacking unit...");
	printf("%s", "How many attacks (A) are are you sending into the other unit?  ");
	
	/* Collect amount of Attacks coming in */
	tmp = fgets(tmp, 100, stdin);
	if (sscanf(tmp, "%d", &atk->A) != 1) {
		fprintf(stderr, "%s", "Input Failed\n");
		return 1;
	} else {
		printf("%d entered\n", atk->A);
	}
	memset(tmp, 0, sizeof(char) * 100);
	
	/* Collect weapon Strength (S) */	
	printf("%s", "Strength (S) of these attacks AFTER modifiers?  ");
	tmp = fgets(tmp, 100, stdin);
	if (sscanf(tmp, "%d", &atk->S) != 1) {
		fprintf(stderr, "%s", "Input Failed\n");
		return 1;
	} else {
		printf("%d entered\n", atk->S);
	}

	/* Collect BS/WS of attacking unit */
	printf("%s", "BS/WS of the attacking unit BEFORE modifiers?  ");
	tmp = fgets(tmp, 10, stdin);
	if (sscanf(tmp, "%s", &atk->BSWS) != 1) {
		fprintf(stderr, "%s", "Input Failed\n");
		return 1;
	} else {
		printf("%s entered\n", atk->BSWS);
	}
	
	/* Collect weapon AP value */
	printf("%s", "AP of attacking unit AFTER modifiers?  ");
	fgets(tmp, 100, stdin);
	if (sscanf(tmp, "%d", &atk->AP) != 1) {
		fprintf(stderr, "%s", "Input Failed\n");
		return 1;
	} else {
		printf("%d entered\n", atk->AP);
	}

	/* Collect Damage (D) of weapon */	
	printf("%s", "Damage (D) of each attack?  ");
	fgets(tmp, 100, stdin);
	if (sscanf(tmp, "%s", &atk->D) != 1) {
		fprintf(stderr, "%s", "Input Failed\n");
		return 1;
	} else {
		printf("%s entered\n", atk->D);
	}

	
	return 0;
}
