#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct bazar {
	char kategoria[50];
	char znacka[50];
	char predajca[100];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
} BAZAR;

void f_n() {
	FILE* f = fopen("auta.txt","r");
	if (f == NULL) { printf("Zaznamy neboli nacitane\n"); return; }

	char* line;
	int line_size = 200;
	line = (char*)malloc(line_size * sizeof(char));
	if (line == NULL) { printf("Nepodarilo sa priradit pamat\n"); }

	int bazar_count = 0;

	while (fgets(line, line_size, f) != NULL) {
		if (strstr(line, "$") != NULL) {
			bazar_count++;
		}
	}

	rewind(f);

	BAZAR* bazare = malloc(bazar_count * sizeof(BAZAR));
	if (bazare == NULL) { printf("Zaznamy neboli nacitane\n"); return; }

	int index = 0;
	while (fgets(line, line_size, f) != NULL) {
		if (strstr(line, "$") != NULL) {
			fgets(line, line_size, f); strcpy(bazare[index].kategoria,line);
			fgets(line, line_size, f); strcpy(bazare[index].znacka, line);
			fgets(line, line_size, f); strcpy(bazare[index].predajca, line);
			fgets(line, line_size, f); bazare[index].cena = atoi(line);
			fgets(line, line_size, f); bazare[index].rok_vyroby = atoi(line);
			fgets(line, line_size, f); strcpy(bazare[index].stav_vozidla, line);
		}
	}
}

int main() {

	char cmd; // command

	while (cmd = getchar()) {
		if (cmd == 'n') { f_n(); }
		else if (cmd == 'k') { break; } // finish program
	}

	return 0;
}