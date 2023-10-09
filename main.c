#include <stdio.h>

//Function to get strings from a file
void getFileStrings(char output[][20], int size, char filename[]) {
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
	} while (output[i-1][0] != '\0');

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
		printf("%c", output[i]);
		i++;
	} while (output[i-1] != EOF);

	fclose(fptr);
}

//Main function
int main() {
	//declaring variables
	char d1[200][20], d2[200][20], d3[200][20], d4[200][20], stop[700][20], special[1000];
	int i = 0;

	//getting file contents and putting them into arrays
	getFileStrings(d1, 20, "d1.txt");
	getFileStrings(d2, 20, "d2.txt");
	getFileStrings(d3, 20, "d3.txt");
	getFileStrings(d4, 20, "d4.txt");
	getFileStrings(stop, 20, "stopwords.txt");
	getFileChars(special, "specialcharacters.txt");

	return 0;
}