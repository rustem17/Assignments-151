#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeFile (char filename[], char ssData[], char oStringData[][50], int nrIOfileLines) {
	FILE *file = fopen(filename, "a");
	
	if (ssData[strlen(ssData) - 1] == '\n' || ssData[strlen(ssData) - 1] == '\r') {
        	ssData[strlen(ssData) - 1] = 0;					//Checking for trailing chars
	}

	fputs(ssData, file);							//Writing the substring firstly
	fputs("\n", file);							//Writing the new line char in file
	printf("%s\n", ssData);
	int j;

	for (j = 0; j < nrIOfileLines; j++) {					//Writing each line from oString into oStrings.txt
		printf("%s", oStringData[j]);
		fputs(oStringData[j], file);
	}
	
	printf("\n");
	fputs("\n", file);							//Writing a new line char in file for diving different cases of substrings

	fclose(file);
}

int isPalindrome (char str[]) {
	int n = strlen(str);
	
	int j = n - 1;
	int i;

	for (i = 0; i < n / 2; i++) {						//We are going through only half of the word, even if the length of string is odd
										//Because if length is odd, the division of two will give us only the celoe chislo without ostatok
		if (j <= n / 2) {						//If the j iterator will be suddenly at the first half of string, we should break the function;\
			break;
		}

		if (str[i] != str[j]) {						//If any of chars is not equals on both sides, it is not palindrome
			return 0;
		}

		j--;
	}
	return 1;
}

char *getPalindrome (char str[]) {
	
	if (isPalindrome(str)) {						//isPalindrome return 1 or 0, which means that we can use it immediately as if statement
		return "Is_Palindrome";
	} else {
		return "Not_Palindrome";
	}

}

int howManySubstrings (char subStr[], char str[]) {
	
	int i;
	int j = 0;
	int count = 0;

	for (i = 0; i < strlen(str); i++) {					//Going through the single line of iString
		if (subStr[j] == str[i]) {					//Checking if any char of string from iString is equal to first char of substring
			j++;
			
			if (j == strlen(subStr) - 1) {				//If the iterator equals to index of last char of substring
				count++;					//It means if we found the substring in string from iString array
				j = 0;
			}

		} else {
			j = 0;							//If some of char of string from iString array is not equal to char of subString then iterator equals 0.
		}
	}
	return count;
}

void checkSubstringPalindrome (char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines) {
	
	int i;
	for (i = 0; i < nrIOfileLines; i++) {					//Going through each line of iString
		int count = howManySubstrings(subStr, iStringData[i]);		//Checking for palindrome each string
		char *pal = getPalindrome(iStringData[i]);
		char temp[50];							//Temporary string for checking if the read content of the file is NULL.

		sprintf(temp, "\t%i\t%s\n", count, pal);			//Formatting the data collected before into beautiful string for output.
		strcat(iStringData[i], temp);					//Concatenating the iString content with data collected and formatted before. 
		strcpy(oStringData[i], iStringData[i]);				//Copying the resulted text into oString array.
	}
	
}							

void readFile (char filename[], char twoDimArr[][50]) {
	
	FILE *file = fopen(filename, "r");					//Reading the file iStrings.txt.
	
	int i = 0;
	int j;
	char temp[50];								//Temporary string for checking if the read content of the file is NULL.
	
	while (fgets(temp, 50, file)) {

		for (j = 0; j < strlen(temp); j++) {
			if (temp[j] == '\n' || temp[j] == '\r') {		//Getting rid of the trailing characters.
				temp[j] = '\0';
			}
		}
		strcpy(twoDimArr[i], temp);					//Formatted string copied into iString array.
		i++;
	}

	fclose(file);
}

int countFileLines (char filename[]) {
	
	FILE *file = fopen(filename, "r");					//Reading the file iStrings.txt
	int count = 0;								//Setting count to 0
	char temp[50];
	
	while (fgets(temp, 50, file) != NULL) {					//If file is empty then it will not increment
		count++;
	}
	
	fclose(file);

	return count;
}

int main () {
	char in[255][50];							//A two dimensional array for storing the raw input
	char out[255][50];							//A two dimensional array for storing the evaluated output
	
	char iString[] = "iStrings.txt";
	char subString[] = "subStrings.txt";
	char oString[] = "oStrings.txt";
	
	char subStr[50];							//An array for storing substring
	char temp[50];								//Temporary string for checking if the read content of the file is NULL.

	FILE *file_trash = fopen(oString, "w");					//The file oStrings.txt is opened and cleaned this file up.
	fclose(file_trash);

	FILE *file = fopen(subString, "r");					//Opening the file with substrings.
	
	readFile(iString, in);
	int lines = countFileLines(iString);					//Counting lines in iString array.

	while (fgets(temp, 50, file)) {						//Reading each substring into temporary array without storing them in array.
		
		strcpy(subStr, temp);						//Copying the content into substring array if temporary is not NULL.

		if (subStr[strlen(subStr) - 1] == '\n' || subStr[strlen(subStr) - 1] == '\r') {
			subStr[strlen(subStr) - 1] = 0;				//Getting rid of trailing characters.
		}
		
		readFile(iString, in);						//Reading file for iString array.

       		checkSubstringPalindrome(subStr, in, out, lines);		//Writing to oStrings number of substrings and palindromes.
        	writeFile(oString, subStr, out, lines);				//Writing each substring and iString content from oString into file.
	}

	fclose(file);
}
