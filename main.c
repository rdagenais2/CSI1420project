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
		for (int j = 0; j < 21; j++) {
			if (output[i][j] == ' ' || output[i][j] == '\n') {
				output[i][j] = '\0';
				break;
			}
		}
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
void alphabetize (char arr[][21], int size){
	//declaring variables
	char temp[21]; 
	
	//set all letters to lowercase
	for (int i = 0; i < size; i++){
		for (int j = 0; j < 21; j++) {
			arr[i][j] = tolower(arr[i][j]);
		}
	}

	//sort words into alphabetical order
	
	for (int i = 1; i < size; i++) {
		int position = i;
		for (int j = i - 1; j >= 0; j--) {
			if (strcmp(arr[position], arr[j]) < 0) {
				memcpy(temp, arr[position], 21);
				memcpy(arr[position], arr[j], 21);
				memcpy(arr[j], temp, 21);
				position--;
			}
			else {
				break;
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
	
	i = 0;
	do{
		fputs(arr[i], output_file);
		fputc('\n', output_file);
		i++;
	} while (arr[i][0] != '\0');

	fclose(output_file);
	
}

//Function to remove chars from array of strings
void removeChars(char from[][21], char removalList[], int fromSize, int removalSize) {
	char empty[21];
	for (int i = 0; i < fromSize; i++) {
		for (int j = 0; j < removalSize; j++) {
			if (from[i][0] == removalList[j]) {
				memcpy(from[i], empty, 21);
			}
		}
	}
}

//Function to remove strings from array of strings
void removeStrings(char from[][21], char removalList[][21], int fromSize, int removalSize) {
	char empty[21];
	for (int i = 0; i < fromSize; i++) {
		for (int j = 0; j < removalSize; j++) {
			if (strcmp(from[i], removalList[j]) == 0) {
				memcpy(from[i], empty, 21);
			}
		}
	}
}

//Calculates the frequency of each word in the documents
void calculateFrequency(char input[][21], char outputWords[][21], int outputFrequency[], int size) {
	int unique = 0;
	memcpy(outputWords[0], input[0], 21);
	outputFrequency[0] = 1;

	for (int i = 1; i < size; i++) {
		if (strcmp(input[i], outputWords[unique]) == 0) {
			outputFrequency[unique]++;
		}
		else {
			unique++;
			memcpy(outputWords[unique], input[i], 21);
			outputFrequency[unique] = 1;
		}
	}

}

//Removes blank spaces from array
void removeBlanks(char input[][21], int size) {
	int newIndex = 0;
	char empty[21];
	for (int i = 0; i < size; i++) {
		if (strcmp(input[i], empty) != 0) {
			memcpy(input[newIndex], input[i], 21);
			newIndex++;
		}
	}
	for (int i = newIndex; i < size; i++) {
		memcpy(input[i], empty, 21);
	}
}

//Calculates the weight of each word in the document
void calculateWeights(char words[][21], int frequencies[], double weights[], int size) {
	double maxFrequency = 0;
	for (int i = 0; i < size && words[i][0] != '\0'; i++) {
		if (frequencies[i] > maxFrequency) {
			maxFrequency = (double) frequencies[i];
		}
	}
	
	for (int i = 0; i < size && words[i][0] != '\0'; i++) {
		weights[i] = ((double)frequencies[i]) / maxFrequency;
	}
}

//Prints out the frequency and weight of the words
void printData(char words[][21], int frequencies[], double weights[], char name[]) {
	printf("Data for %s\n", name);
	printf("Word\t\t|\t    Frequency\t\t|\t\tWeight\n");
	printf("\t\t|\t\t\t\t|\n");
	for (int i = 0; words[i][0] != '\0'; i++) {
		if (words[i][7] == '\0'||words[i][6] == '\0') {
			printf("%s\t\t|\t\t%d\t\t|\t\t%f\n", words[i], frequencies[i], weights[i]);
		}
		else {
			printf("%s\t|\t\t%d\t\t|\t\t%f\n", words[i], frequencies[i], weights[i]);
		}
		
	}
}

//Main function
int main() {
	//declaring variables
	char d1[201][21], d2[201][21], d3[201][21], d4[201][21], stop[901][21], special[101], words[4][201][21];
	int frequencies[4][201], i = 0;
	double weights[4][201];
	//getting file contents and putting them into arrays
	
	getFileStrings(d1, 20, "d1.txt");
	getFileStrings(d2, 20, "d2.txt");
	getFileStrings(d3, 20, "d3.txt");
	getFileStrings(d4, 20, "d4.txt");
	getFileStrings(stop, 20, "stopwords.txt");
	getFileChars(special, "specialcharacters.txt");
	
	//alphabetizing d1-d4
	
	alphabetize(d1, 200); 
	alphabetize(d2, 200);
	alphabetize(d3, 200);
	alphabetize(d4, 200);

	
	removeChars(d1, special, 200, 100);
	removeChars(d2, special, 200, 100);
	removeChars(d3, special, 200, 100);
	removeChars(d4, special, 200, 100);

	removeStrings(d1, stop, 200, 900);
	removeStrings(d2, stop, 200, 900);
	removeStrings(d3, stop, 200, 900);
	removeStrings(d4, stop, 200, 900);

	removeBlanks(d1, 200);
	removeBlanks(d2, 200);
	removeBlanks(d3, 200);
	removeBlanks(d4, 200);
	
	putFileStrings(d1, "Tokenizedd1.txt");
	putFileStrings(d2, "Tokenizedd2.txt");
	putFileStrings(d3, "Tokenizedd3.txt");
	putFileStrings(d4, "Tokenizedd4.txt");

	calculateFrequency(d1, words[0], frequencies[0], 200);
	calculateFrequency(d2, words[1], frequencies[1], 200);
	calculateFrequency(d3, words[2], frequencies[2], 200);
	calculateFrequency(d4, words[3], frequencies[3], 200);

	i = 0;
	
	calculateWeights(words[0], frequencies[0], weights[0], 200);
	calculateWeights(words[1], frequencies[1], weights[1], 200);
	calculateWeights(words[2], frequencies[2], weights[2], 200);
	calculateWeights(words[3], frequencies[3], weights[3], 200);
	
	printData(words[0], frequencies[0], weights[0], "D1");
	printf("\n");
	printData(words[1], frequencies[1], weights[1], "D2");
	printf("\n");
	printData(words[2], frequencies[2], weights[2], "D3");
	printf("\n");
	printData(words[3], frequencies[3], weights[3], "D4");
	
	return 0;
}
