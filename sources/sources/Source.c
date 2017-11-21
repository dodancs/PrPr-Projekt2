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
	struct bazar* dalsi; //linked list
} BAZAR;

//global variables for ease of use
BAZAR* bazare;
int bazar_count = 0;

void readUntilBreak(char **string) { //read from stdin until '\n' line break character is present
	int i = 0;
	char* line = (char*)malloc(200 * sizeof(char));
	if (line == NULL) { printf("Nepodarilo sa priradit pamat\n"); } //if ram allocation wasn't successful, print error message
	while (1) {
		scanf("%c",&line[i]); //read new char from stdin
		if (line[i] == '\n') { break; } //if the char is '\n' break the loop
		i++; //otherwise increment index
	}
	line[i++] = '\n'; //add line break to the end
	line[i] = '\0'; //properly end string with \0
	*string = line; //return string
}

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
	bazare = (BAZAR*)malloc(sizeof(BAZAR)); //alloc enough ram for "bazare"
	if (bazare == NULL) { printf("Nepodarilo sa priradit pamat\n"); return; } //if ram allocation wasn't successful, print error message

	BAZAR* current = bazare;

	int i = 1;
	while (fgets(line, line_size, f) != NULL) { //go through the file
		if (strstr(line, "$") != NULL) { //store all data into the structure
			fgets(line, line_size, f); strcpy(current->kategoria, line);
			fgets(line, line_size, f); strcpy(current->znacka, line);
			fgets(line, line_size, f); strcpy(current->predajca, line);
			fgets(line, line_size, f); current->cena = atoi(line);
			fgets(line, line_size, f); current->rok_vyroby = atoi(line);
			fgets(line, line_size, f); strcpy(current->stav_vozidla, line);
			if (i < bazar_count) { //only create next item if there is another one
				current->dalsi = (BAZAR*)malloc(sizeof(BAZAR));
				current = current->dalsi;
				if (current == NULL) { printf("Nepodarilo sa priradit pamat\n"); return; } //if ram allocation wasn't successful, print error message
			}
			else { //next item does not exist - set it to NULL
				current->dalsi = NULL;
			}
			i++;
		}
	}

	printf("Nacitalo sa %d zaznamov\n",bazar_count); //print number of entries

	free(line); //put allocated ram back to heap
}

void f_v() {
	if (bazare == NULL) { return; }
	BAZAR* current = bazare;
	int i = 1;
	while (current != NULL) {
		printf("%d.\nkategoria: %sznacka: %spredajca: %scena: %d\nrok_vyroby: %d\nstav_vozidla: %s",i,current->kategoria,current->znacka,current->predajca,current->cena,current->rok_vyroby,current->stav_vozidla);
		current = current->dalsi;
		i++;
	}
}

void f_p() {
	int cislo = 0;
	scanf("%d\n",&cislo); //also read '\n' character to not mess up readUntilBreak() function
	
	//if (bazare == NULL) { return; }
	
	if ((cislo > bazar_count) || (cislo < 1)) { //if number is greater than the number of entries, or lower than 1, make it one more then the entry count
		cislo = bazar_count + 1;
	}

	BAZAR* novy; //new structure
	bazar_count++; //increment the size

	novy = malloc(bazar_count * sizeof(BAZAR)); //alloc enough ram for new structure
	if (novy == NULL) { printf("Nepodarilo sa priradit pamat\n"); return; } //if ram allocation wasn't successful, print error message

	char* line; //line buffer
	
	BAZAR tmp; //read new data and store them temporarily
	readUntilBreak(&line); strcpy(tmp.kategoria, line);
	readUntilBreak(&line); strcpy(tmp.znacka, line);
	readUntilBreak(&line); strcpy(tmp.predajca, line);
	readUntilBreak(&line); tmp.cena = atoi(line);
	readUntilBreak(&line); tmp.rok_vyroby = atoi(line);
	readUntilBreak(&line); strcpy(tmp.stav_vozidla, line);
	free(line);

	int index = 0; //index in the old array

	if ((cislo-1) <= (bazar_count-1)) { //if the index exists
		for (int i = 0; i < bazar_count; i++) { //go through the structure
			if (i == (cislo-1)) {  //add the new data in place of the index
				novy[i] = tmp;
				index--; //if index was altered, lower it back down
			}
			else { //otherwise copy old data
				novy[i] = bazare[index];
			}
			index++; //increment index of element in old array
		}
	}
	else { //the index did not exist - add new data to the end
		for (int i = 0; i < (bazar_count-1); i++) {
			novy[i] = bazare[i];
		}
		novy[(bazar_count - 1)] = tmp;
	}

	free(bazare);
	bazare = novy; //give back new array
}

void f_z() {
	if (bazare == NULL) { return; }

	char temp1[50]; //temp string 1 - from structure
	char temp2[50]; //temp string 2 - from stdin
	int* indexes; //array of indexes of entries being kept
	indexes = (int*)malloc(bazar_count * sizeof(int));
	if (indexes == NULL) { printf("Nepodarilo sa priradit pamat\n"); return; } //if ram allocation wasn't successful, print error message

	scanf("%s",&temp2); //scan for input to compare
	temp2[strlen(temp2)] = '\0'; //properly finish string
	for (int j = 0; j < strlen(temp2); j++) { temp2[j] = tolower(temp2[j]); } //convert to lowercase

	int kept = 0; //number of kept entries

	for (int i = 0; i < bazar_count; i++) { //go throught the structure
		strcpy(temp1,bazare[i].znacka);
		for (int j = 0; j < strlen(temp1); j++) { temp1[j] = tolower(temp1[j]); } //convert string to lowercase
		if (strstr(temp1, temp2) == NULL) { indexes[kept] = i; kept++; } //if no match is found, put index of entry to the array
	}

	int removed = bazar_count - kept;
	bazar_count = kept;

	BAZAR* novy; //new structure without removed items
	novy = malloc(bazar_count * sizeof(BAZAR)); //alloc enough ram for new structure
	if (novy == NULL) { printf("Nepodarilo sa priradit pamat\n"); return; } //if ram allocation wasn't successful, print error message

	for (int i = 0; i < bazar_count; i++) {
		novy[i] = bazare[indexes[i]]; //put kept items to the new array
	}

	free(bazare);
	bazare = novy;
	free(indexes);

	printf("Vymazalo sa %d zaznamov\n",removed);
}

void f_h() {
	if (bazare == NULL) { return; }

	int* indexes; //array of indexes of entries to print
	indexes = (int*)malloc(bazar_count * sizeof(int));
	if (indexes == NULL) { printf("Nepodarilo sa priradit pamat\n"); return; } //if ram allocation wasn't successful, print error message

	int cena;
	scanf("%d", &cena); //scan for input to compare

	int index = 0; //number of entries to print
	for (int i = 0; i < bazar_count; i++) { //go throught the structure
		if (bazare[i].cena <= cena) { indexes[index] = i; index++; } //if match is found, store the index
	}

	if (index == 0) { printf("V ponuke su len auta s vyssou cenou\n"); return; } //if no match was found, print message and return;

	int j = 0;
	for (int i = 0; i < index; i++) { //print all matches
		j = indexes[i];
		printf("%d.\nkategoria: %sznacka: %spredajca: %scena: %d\nrok_vyroby: %d\nstav_vozidla: %s", i + 1, bazare[j].kategoria, bazare[j].znacka, bazare[j].predajca, bazare[j].cena, bazare[j].rok_vyroby, bazare[j].stav_vozidla);
	}

	free(indexes);
}

void f_a() {
	char* line; //line buffer
	char* znacka;
	int cena;

	scanf("\n"); //read line break after executing command

	readUntilBreak(&znacka); //read znacka to compare
	readUntilBreak(&line); //read cena to compare
	cena = atoi(line);

	BAZAR tmp; //read new data and store them temporarily
	readUntilBreak(&line); strcpy(tmp.kategoria, line);
	readUntilBreak(&line); strcpy(tmp.znacka, line);
	readUntilBreak(&line); strcpy(tmp.predajca, line);
	readUntilBreak(&line); tmp.cena = atoi(line);
	readUntilBreak(&line); tmp.rok_vyroby = atoi(line);
	readUntilBreak(&line); strcpy(tmp.stav_vozidla, line);
	free(line);

	int* indexes; //array of indexes of entries to edit
	indexes = (int*)malloc(bazar_count * sizeof(int));
	if (indexes == NULL) { printf("Nepodarilo sa priradit pamat\n"); return; } //if ram allocation wasn't successful, print error message

	int index = 0; //number of entries to edit
	for (int i = 0; i < bazar_count; i++) { //go throught the structure
		if ((bazare[i].cena == cena) && (strcmp(bazare[i].znacka, znacka) == 0)) { indexes[index] = i; index++; } //if match is found, store the index
	}

	for (int i = 0; i < index; i++) {
		bazare[indexes[i]] = tmp; //replace existing data with updated data
	}

	printf("Aktualizovalo sa %d zaznamov\n",index);
	free(indexes);
}

int main() {

	char cmd; // command

	while (cmd = getchar()) { //wait for command
		if (cmd == 'n') { f_n(); }
		else if (cmd == 'v') { f_v(); }
		else if (cmd == 'p') { f_p(); }
		else if (cmd == 'z') { f_z(); }
		else if (cmd == 'h') { f_h(); }
		else if (cmd == 'a') { f_a(); }
		else if (cmd == 'k') { if (bazare != NULL) { free(bazare); } break; } // finish program
	}

	return 0;
}