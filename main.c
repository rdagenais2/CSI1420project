#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Function to get strings from a file
void getFileStrings(char output[][21], int size, char filename[]) {
	//declaring variables
	int i = 0;

	//get file pointer
	FILE* fptr = fopen(filename, "r");

	//test if file opened successfully
	if (fptr == NULL) {
		printf("The file is not opened. The program will now exit.");
	}

	//getting data from file
	do {
		fgets(output[i], size, fptr);
		i++;
	} while (output[i - 1][0] != '\0');

	fclose(fptr);
	
}

//Function to get characters from a file
void getFileChars(char* output, char filename[]) {
	//declaring variables
	int i = 0;

	//get file pointer
	FILE* fptr = fopen(filename, "r");

	//test if file opened successfully
	if (fptr == NULL) {
		printf("The file is not opened. The program will now exit.");
	}

	//getting data from file
	do {
		output[i] = fgetc(fptr);
		i++;
	} while (output[i-1] != EOF);

	fclose(fptr);
}

//Function to alphabetize the arrays
void alphabetize (char arr[][21]){
	//declaring variables
	char swap[20]; 
	int n, x; 
	
	//set all letters to lowercase
	for (int y = 0; y < 200; y++){
			arr[y][0] = tolower(arr[y][0]);  
	}

	//sort words into alphabetical order
	for (x=0; x < 200; x++){ 
		for (n=x+1; n < 200; n++){ 
			if (strcmp(arr[x], arr[n]) > 0){
				memcpy(swap, arr[x], 20);
				memcpy(arr[x], arr[n], 20);
				memcpy(arr[n], swap, 20); 
			}
		}
	}
	
}

//Function to read from txt files and put them in token files
void putFileStrings(char arr[][21] ,const char *output_filename) {
	FILE *output_file = fopen(output_filename, "w");
	int i, j;
	
	if(output_file == NULL){
		printf("Error opening the file: %s\n", output_filename);
		return;
	}
	
    for (i = 0; i < 200; i++) { 
        for (j = 0; j< 21; j++) {
			fprintf(output_file, "%c", arr[i][j]);
		}			
    } 

	fclose(output_file);
	
}


//Main function
int main() {
	printf("a");
	//declaring variables
	char d1[201][21], d2[201][21], d3[201][21], d4[201][21], stop[901][21], special[101];
	int i = 0;
	//getting file contents and putting them into arrays
	
	getFileStrings(d1, 20, "d1.txt");
	getFileStrings(d2, 20, "d2.txt");
	getFileStrings(d3, 20, "d3.txt");
	getFileStrings(d4, 20, "d4.txt");
	getFileStrings(stop, 20, "stopwords.txt");
	getFileChars(special, "specialcharacters.txt");
	
	//alphabetizing d1-d4
	alphabetize(d1); 
	alphabetize(d2);
	alphabetize(d3);
	alphabetize(d4);
	

	putFileStrings(d1,"Tokenizedd1.txt");
	
	return 0;
}
