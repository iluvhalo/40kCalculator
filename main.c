#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Attacker.h"
#include "Defender.h"

int collectInt();
void parseD (char *str);

int main (int argc, char **argv) {
	
	Attacker *atk;
	Defender *dfd;
	char *tmp;
	char t;
	int amt, type, baseDmg;

	atk = (Attacker *) calloc(1, sizeof(Attacker));
	dfd = (Defender *) calloc(1, sizeof(Defender));
	tmp = calloc(1, sizeof(char) * 100);

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
	atk->AP = collectInt();
	printf("%d entered\n", atk->AP);

	/* Collect Damage (D) of weapon */	
	printf("%s", "\tx - amount of dice in damage roll\n");
	printf("%s", "\ty - either '3' for a d3 or '6' for a d6\n");
	printf("%s", "\tz - static damage\n");
	printf("%s", "\tEXAMPLE: 0d3+2 for a 2 D weapon\n");
	printf("%s", "Damage (D) of each attack (FORMAT: xDy+z)?  ");
	fgets(tmp, 100, stdin);
	parseD(tmp);
	if (sscanf(tmp, "%d%c%d+%d", &amt, &t, &type, &baseDmg) != 4) {
		fprintf(stderr, "%s", "Input Failed\n");
		return 1;
	} else {
		if (type == 3) {
			atk->d3 = amt;
		} else if (type == 6) {
			atk->d6 = amt;
		} else {
			fprintf(stderr, "%s", "Input Failed\n");
			return 1;
		}
		
		atk->dmg = baseDmg;
		printf("D3: %d\nD6: %d\n D: %d\n", atk->d3, atk->d6, atk->dmg);
	}
	memset(tmp, 0, 100);

	
	return 0;
}

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

void parseD (char *str) {
	char *tmp;

	tmp = calloc(1, sizeof(char) * 20);
	int a, b;
	
	a = 0;
	b = 0;

	/* clear out white space and invalid characters from parsed string */
	while (str[a] != '\0') {
		if ((str[a] != ' ') && (((str[a] >= '0') && (str[a] <= '9')) || (str[a] == '+') || (str[a] == 'D') || (str[a] == 'd'))) {
			if (str[a] == 'D') {
				str[a] = 'd';
			}
			tmp[b] = str[a];
			b++;
		}

		a++;
	}
	memcpy(str, tmp, 20);
	free(tmp);
}
