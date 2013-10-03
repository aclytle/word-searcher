#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define ROWS 200
#define COLS 200
#define WORDBANK 200


int main() {

	char puzzle[ROWS][COLS];
	char words[WORDBANK][ROWS];
	int matched[ROWS][COLS];
	char buf;
	int row = 0;
	int col = 0;
	int maxcol = 0;
	FILE* filestream;
	FILE* wordbank;
	int numwords = 0;
	int i, j, k, l;

	zeroMatched(matched);

	printf("Reading file\n");
	// Puzzle is in a standard file, rows split by newlines, columns split by spaces or tabs
	filestream = fopen("puzzle.txt", "r");
	if (filestream == NULL) {
		printf("File open error \n");
		return 0;
	}

	while(!feof(filestream)) {
		buf = fgetc(filestream); 
		
		if (buf == '\n'){
			row++;
			printf("%d\n", row);
			col = 0;
		}
		else if(isalnum(buf)) {
			puzzle[col][row] = toupper(buf);
			col++;
			max (col, &maxcol);
		}
		
	}
	printf("EOF reached. %d lines read.\n",row);	
	

	// Read in wordbank
	wordbank = fopen("wordbank.txt", "r");
	if (wordbank == NULL) {
		printf("File open error\n");
		return 0;
	}
		
	while(!feof(wordbank)) {
		fgets(words[numwords], 100, wordbank);
		strip(words[numwords]);
		numwords++;
	}
	numwords--;
	printf("numwords: %d\n", numwords);

	// Match wordbank words to puzzle. For each wordbank word, iterate through the puzzle
	// Strategy: Scan through the rows until we hit the first letter, then attempt matching in all directions that word will fit.
	for (i=0; i < numwords; i++) {
		for (k=0; k < row; k++) { // For each row (Y)
			for (j=0; j < maxcol; j++) { // For each item in each row (X)
				if (puzzle[j][k] == words[i][0]){
					//printf("Matched %c from %s at %d %d\n", words[i][0], words[i], j, k);
					if (maxcol > (wordlen(words[i]) + j)) { // Search right
						//printf("Searching right\n", maxcol, wordlen(words[i]), j);
						for(l=0; words[i][l] == puzzle[j+l][k]; l++) {
							//printf("%c\n",words[i][l]);
							if(words[i][l+1]=='\0') {
								printf("Matched %s at %d %d right\n",words[i], j, k);
								for(l=0; words[i][l] == puzzle[j+l][k]; l++)
									matched[j+l][k] = 1;
								break;
							}
						}
						if (row > (wordlen(words[i]) + k)) { // Search diag right down
							//printf("Searching right down\n");	

						for(l=0; words[i][l] == puzzle[j+l][k+l]; l++) {
							//printf("%c\n",words[i][l]);
							if(words[i][l+1]=='\0') {
								printf("Matched %s at %d %d right down\n",words[i], j, k);
								for(l=0; words[i][l] == puzzle[j+l][k+l]; l++)
									matched[j+l][k] = 1;
								break;
							}
						}
						}
						if (0 <= (k - wordlen(words[i]))) { // Search diag right up
							//printf("Searching right up\n");
							
						for(l=0; words[i][l] == puzzle[j+l][k-l]; l++) {
							//printf("%c\n",words[i][l]);
							if(words[i][l+1]=='\0') {
								printf("Matched %s at %d %d right up\n",words[i], j, k);
								for(l=0; words[i][l] == puzzle[j+l][k-l]; l++)
									matched[j+l][k-l] = 1;
								break;
							}
						}
						}
					}
					if (0 <= (j - wordlen(words[i]))) { // Search left
						//printf("Searching left\n");
							
						for(l=0; words[i][l] == puzzle[j-l][k]; l++) {
							//printf("%c\n",words[i][l]);
							if(words[i][l+1]=='\0') {
								printf("Matched %s at %d %d left\n",words[i], j, k);
								for(l=0; words[i][l] == puzzle[j-l][k]; l++)
									matched[j-l][k] = 1;
								break;
							}
						}
						if (row > (wordlen(words[i]) + k)) { // Search diag left down
							//printf("Searching left down\n");
								
						for(l=0; words[i][l] == puzzle[j-l][k+l]; l++) {
							//printf("%c\n",words[i][l]);
							if(words[i][l+1]=='\0') {
								printf("Matched %s at %d %d left down\n",words[i], j, k);
								for(l=0; words[i][l] == puzzle[j-l][k+l]; l++)
									matched[j-l][k+l] = 1;
								break;
							}
						}
							
						}
						if (0 <= (k - wordlen(words[i]))) { // Search diag left up
							//printf("Searching left up\n");
						for(l=0; words[i][l] == puzzle[j-l][k-l]; l++) {
							//printf("%c\n",words[i][l]);
							if(words[i][l+1]=='\0') {
								printf("Matched %s at %d %d left up\n",words[i], j, k);
								for(l=0; words[i][l] == puzzle[j-l][k-l]; l++)
									matched[j-l][k-l] = 1;
								break;
							}
						}
						}

					}
					if (row > (wordlen(words[i]) + k)) { // Search down
						//printf("Searching down\n");

						for(l=0; words[i][l] == puzzle[j][k+l]; l++) {
							//printf("%c\n",words[i][l]);
							if(words[i][l+1]=='\0') {
								printf("Matched %s at %d %d down\n",words[i], j, k);
								for(l=0; words[i][l] == puzzle[j][k+l]; l++)
									matched[j][k+l] = 1;
								break;
							}
						}
					}
					if (0 <= (k - wordlen(words[i]))) { // Search up
						//printf("Searching up\n");
						for(l=0; words[i][l] == puzzle[j][k-l]; l++) {
							//printf("%c\n",words[i][l]);
							if(words[i][l+1]=='\0') {
								printf("Matched %s at %d %d up\n",words[i], j, k);
								for(l=0; words[i][l] == puzzle[j][k-l]; l++)
									matched[j][k-l] = 1;
								break;
							}
						}
						
					}
					
					
				}
			}
		}
	}
	l = 0;
	i = 0;
	for (k = 0; k < row; k++)
		for (j = 0; j < maxcol; j++){
			i++;
			if (matched[j][k] == 0){
				printf("%c", puzzle[j][k]);
				l++;
			}
		}

	printf("\n%d %d\n", l, i);

	for(j=0; j<maxcol; j++)
		for(k=0; k < row; k++) {
			if(matched[j][k] == 0)
				printf("%c", puzzle[j][k]);

			}
	printf("\n\n");

	l = 0;
	i = 0;
	for (k = 0; k < row; k++)
		for (j = 0; j < maxcol; j++){
			i++;
			if (matched[j][k] == 1){
				printf("%c", puzzle[j][k]);
				l++;
			}
		}

	printf("\n%d %d\n", l, i);

	for (k = 0; k < row; k++) {
		for (j = 0; j < maxcol; j++){
			if (matched[j][k] == 1){
				printf("%c ", puzzle[j][k]);
			}
			else {
				printf("  ");
			}

		}
		printf("\n");
	}

	printf("\n\n\n");
	for (k = 0; k < row; k++) {
		for (j = 0; j < maxcol; j++){
			if (matched[j][k] == 0){
				printf("%c ", puzzle[j][k]);
			}
			else {
				printf("  ");
			}

		}
		printf("\n");
	}

}

void max(int current, int* max) { if (current > *max) *max = current; } 

int wordlen(char* word) {
	int i;
	for (i=0; word[i] != '\0'; i++) {}
	i--;
	return i;
}

void strip(char* word) {
	int i;
	for(i=0; word[i] != '\0'; i++) {
		if (word[i] == '\n')
			word[i] = '\0';
	}
}

void zeroMatched(int matched[ROWS][COLS]) {
	int i, j;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			matched[i][j] = 0;
}

