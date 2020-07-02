#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Attacker.h"
#include "Defender.h"

int main (int argc, char **argv) {
	
	Attacker *atk;
	Defender *dfd;
	char *tmp;

	atk = calloc(1, sizeof(Attacker));
	dfd = calloc(1, sizeof(Defender));
	tmp = calloc(1, sizeof(char) * 100);
	memset(atk->D, 0, sizeof(char) * 100);

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
	printf("%s", "\nx - amount of dice in damage roll\n");
	printf("%s", "y - either '3' for a d3 or '6' for a d6\n");
	printf("%s", "z - static damage\n");
	printf("%s", "Damage (D) of each attack (xDy+z)?  ");
	fgets(tmp, 100, stdin);
	if (memcpy(atk->D, tmp, sizeof(char) * 20) == NULL) {
		fprintf(stderr, "%s", "Input Failed\n");
		return 1;
	} else {
		atk->D[strlen(atk->D)-1] = '\0';
		printf("%s entered\n", atk->D);
	}
	memset(tmp, 0, 100);

	parseD(atk);

	
	return 0;
}

void parseD (Attacker *atk) {
	char *tmp;

	tmp = calloc(1, sizeof(char) * 20);
	int a, b;
	
	a = 0;
	b = 0;

	/* clear out white space and invalid characters from parsed string */
	while (atk->D[a] != '\0') {
		if ((atk->D[a] != ' ') && (((atk->D[a] >= '0') && (atk->D[a] <= '9')) || (atk->D[a] == 'D') || (atk->D[a] == 'd'))) {
			if (atk->D[a] == 'D') {
				atk->D[a] = 'd';
			}
			tmp[b] = atk->D[a];
			b++;
		}

		a++;
	}
	memcpy(atk->D, tmp, 20);
	free(tmp);

	printf("%s\n", atk->D);

	/* check for d3 and d6 dammage */
	if (strstr(atk->D, "d3") != NULL) {
		tmp = strstr(atk->D, "d3");
	}	
}
