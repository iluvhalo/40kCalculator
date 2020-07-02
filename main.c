#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Attacker.h"
#include "Defender.h"

int collectInt();
void printDPrompt();
void collectD(Attacker *atk);
void parseD (char *str, Attacker *atk);
double woundingOn(double S, double T);
double max(double a, double b);

int main (int argc, char **argv) {
	
	Attacker *atk;
	Defender *def;
	double expectedHits, expectedWounds, expectedUnsavedWounds, expectedDamagePerWound, expectedDamage;

	atk = (Attacker *) calloc(1, sizeof(Attacker));
	def = (Defender *) calloc(1, sizeof(Defender));

	printf("%s\n", "Welcome to the Warhammer 40k Mathhammer Calculator");
	printf("%s\n", "This will collect information about Attacking and Defending units and calculate expected hits, wound, damage, and morale");
	printf("%s\n", "Lets start by collecting information about the attacking unit...");

	/* Collect amount of Attacks coming in */
	printf("%s", "How many attacks (A) are are you sending into the other unit?  ");
	atk->A = collectInt();
	printf("%d entered\n", atk->A);
	
	/* Collect BS/WS of attacking unit */
	printf("%s", "BS/WS of the attacking unit AFTER modifiers?  ");
	atk->BSWS = collectInt();
	printf("%d entered\n", atk->BSWS);

	/* Collect weapon Strength (S) */	
	printf("%s", "Strength (S) of these attacks AFTER modifiers?  ");
	atk->S = collectInt();
	printf("%d entered\n", atk->S);

	/* Collect weapon AP value */
	printf("%s", "AP of these attacks AFTER modifiers?  ");
	atk->AP = abs(collectInt());
	printf("%d entered\n", atk->AP);

	/* Collect Damage (D) of weapon */	
	printDPrompt();
	collectD(atk);
	printf("D3: %d\nD6: %d\n D: %d\n", atk->d3, atk->d6, atk->dmg);

	printf("%s", "Great! Now, lets collect information for the Defending unit.\n");

	/* Collect Toughness (T) of Def. Unit */
	printf("%s", "Toughness (T) of defending unit?  ");
	def->T = collectInt();
	printf("%d entered\n", def->T);

	/* Collect Armor Save (Sv) of Def. Unit */
	printf("%s", "Basic Armor Save (Sv) of defending unit?  ");
	def->Sv = collectInt();
	printf("%d entered\n", def->Sv);

	/* Collect Wounds (W) per model of Def. Unit */
	printf("%s", "Wounds (W) per model in defending unit?  ");
	def->W = collectInt();
	printf("%d entered\n", def->W);

	/* calculate expectedHits = A * (1 - (BS / 6)) */
	expectedHits = (atk->A * 1.0) * (1.0 - (((atk->BSWS - 1) * 1.0) / 6.0));
	printf("Expected Hits: %0.2f\n", expectedHits);
	
	/* calculate expectedWounds */
	expectedWounds = expectedHits * woundingOn(atk->S * 1.0, def->T * 1.0);
	printf("Expected Wounds: %0.2f\n", expectedWounds);

	/* calculate expectedUnsavedWounds */
	expectedUnsavedWounds = expectedWounds * (1.0 - ((def->Sv - 1 - atk->AP) * 1.0) / 6.0);
	printf("Expected Unsaved Wounds: %0.2f\n", expectedUnsavedWounds);

	/* calculate expectedDamage */
	//expectedDamagePerWound = max(atk->d3 * 2.0, 1.0) * max(atk->d6 * 3.5, 1.0) * max(atk->dmg * 1.0, 1.0);
	expectedDamagePerWound = (atk->d3 * 2.0) + (atk->d6 * 3.5) + (atk->dmg * 1.0);
	expectedDamage = expectedUnsavedWounds * expectedDamagePerWound;
	printf("Expected Damage Per Wound: %0.2f\n", expectedDamagePerWound);
	printf("Expected Total Damage: %0.2f\n", expectedDamage);

	free(atk);
	free(def);
	return 0;
}

/* read and return an Int from stdin */
int collectInt () {
	char *tmp;
	int ret;

	tmp = (char *) calloc(100, sizeof(char));
	tmp = fgets(tmp, 100, stdin);
	if (sscanf(tmp, "%d", &ret) != 1) {
		fprintf(stderr, "%s", "Input Failed\n");
		exit(1);
	}
	free(tmp);

	return ret;
}

/* Print the instruction block for inputting damage values */
void printDPrompt() {
	printf("%s", "\tx - amount of dice in damage roll\n");
	printf("%s", "\ty - either '3' for a d3 or '6' for a d6\n");
	printf("%s", "\tz - static damage\n");
	printf("%s", "\tEXAMPLE: 0d3+2 for a 2 D weapon\n");
	printf("%s", "Damage (D) of each attack (FORMAT: xDy+z)?  ");
}

/* read the D from stdin, parse, then sort into respective variables */
void collectD(Attacker *atk) {
	char *tmp;

	tmp = (char *) calloc(100, sizeof(char));

	fgets(tmp, 100, stdin);
	parseD(tmp, atk);
	free(tmp);
}

/* cleans up input for D a little bit */
void parseD (char *str, Attacker *atk) {
	char *tmp;
	char t;
	int amt, type;
	char dPresent = 0;
	char plusPresent = 0;

	tmp = (char *) calloc(20, sizeof(char));
	int a, b;
	
	a = 0;
	b = 0;

	/* clear out white space and invalid characters from parsed string */
	while (str[a] != '\0') {
		if ((str[a] != ' ') && (((str[a] >= '0') && (str[a] <= '9')) || (str[a] == '+') || (str[a] == 'D') || (str[a] == 'd'))) {
			if (str[a] == 'D') {
				str[a] = 'd';
			}
			if (str[a] == 'd') dPresent = 1;
			if (str[a] == '+') plusPresent = 1;
			tmp[b] = str[a];
			b++;
		}

		a++;
	}
	memcpy(str, tmp, 20);
	free(tmp);

	if ((!dPresent) && plusPresent) {
		fprintf(stderr, "%s", "Input Format: [xDy+z] OR [z]\n");
		fprintf(stderr, "%s", "Exiting...\n");
		exit(1);
	} else if ((!dPresent) && (!plusPresent)) {
		if (sscanf(str, "%d", &atk->dmg) != 1) {
			fprintf(stderr, "%s", "Input Failed\n");
			exit(1);
		}
	} else if (dPresent && (!plusPresent)) {
		if (sscanf(str, "%d%c%d", &amt, &t, &type) != 3) {
			fprintf(stderr, "%s", "Input Failed\n");
			exit(1);
		} else {
			if (type == 3) {
				atk->d3 = amt;
			} else if (type == 6) {
				atk->d6 = amt;
			} else {
				fprintf(stderr, "%s", "Die type must be either d3 or d6\n");
				exit(1);
			}
		}
	} else if (dPresent && plusPresent) {
		if (sscanf(str, "%d%c%d+%d", &amt, &t, &type, &atk->dmg) != 4) {
			fprintf(stderr, "%s", "Input Failed\n");
			exit(1);
		} else {
			if (type == 3) {
				atk->d3 = amt;
			} else if (type == 6) {
				atk->d6 = amt;
			} else {
				fprintf(stderr, "%s", "Die type must be either d3 or d6\n");
				exit(1);
			}	
		}
	}
}

/* figure what value rolls to wound succeed on */
double woundingOn(double S, double T) {

	if (T == S) {
		return 3.0 / 6.0;
	} else if (S > T) {
		if (S >= (2 * T)) {
			return 5.0 / 6.0;
		} else {
			return 4.0 / 6.0;
		}
	} else {
		if (S <= (T / 2)) {
			return 1.0 / 6.0;
		} else {
			return 2.0 / 6.0;
		}
	}
}

double max (double a, double b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}
