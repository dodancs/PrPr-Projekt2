#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct bazar { //define bazar structure
	char kategoria[50];
	char znacka[50];
	char predajca[100];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
} BAZAR;

//global variables for ease of use
BAZAR* bazare;
int bazar_count = 0;

void f_n() { //function 'n'
	FILE* f = fopen("auta.txt","r"); //open file
	if (f == NULL) { printf("Zaznamy neboli nacitane\n"); return; } //if file wasn't opened, print error message

	char* line; //line buffer
	int line_size = 200; //max line size
	line = (char*)malloc(line_size * sizeof(char)); //alloc enough ram for "line"
	if (line == NULL) { printf("Nepodarilo sa priradit pamat\n"); } //if ram allocation wasn't successful, print error message

	bazar_count = 0; //reset entry count
	while (fgets(line, line_size, f) != NULL) { //count all entries
		if (strstr(line, "$") != NULL) { //every entry starts with '$'
			bazar_count++;
		}
	}

	rewind(f); //go back to the beginning of file

	if (bazare != NULL) { free(bazare); } //if "bazare" has some data in it, clear it
	bazare = malloc(bazar_count * sizeof(BAZAR)); //alloc enough ram for "bazare"
	if (bazare == NULL) { printf("Zaznamy neboli nacitane\n"); return; } //if ram allocation wasn't successful, print error message

	int index = 0; //set array index to 0
	while (fgets(line, line_size, f) != NULL) { //go through the file
		if (strstr(line, "$") != NULL) { //store all data into the structure
			fgets(line, line_size, f); strcpy(bazare[index].kategoria,line);
			fgets(line, line_size, f); strcpy(bazare[index].znacka, line);
			fgets(line, line_size, f); strcpy(bazare[index].predajca, line);
			fgets(line, line_size, f); bazare[index].cena = atoi(line);
			fgets(line, line_size, f); bazare[index].rok_vyroby = atoi(line);
			fgets(line, line_size, f); strcpy(bazare[index].stav_vozidla, line);
		}
	}

	printf("Nacitalo sa %d zaznamov\n",bazar_count); //print number of entries

	free(line); //put allocated ram back to heap
}

int main() {

	char cmd; // command

	while (cmd = getchar()) { //wait for command
		if (cmd == 'n') { f_n(); }
		else if (cmd == 'k') { break; } // finish program
	}

	return 0;
}