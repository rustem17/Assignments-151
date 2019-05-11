#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Node {
	char strData[50];
	struct _Node *next;
} Node;

void writeFile2 (char filename[], char ssData[], Node **oLinkedList) {
	FILE *file = fopen(filename, "a");
	Node *next_node = malloc(sizeof(Node));
	next_node = *oLinkedList;							
	//we are going through the linkedlist, but do not move the pointer from the last element (oLinkedList still points to the last element of linkedlist)
	
	fputs(ssData, file);								
	//substring is without '\n' char
	
	fputs("\n", file);
	int j;
	
	while (next_node != NULL) {
		fputs(next_node -> strData, file);
		next_node = next_node -> next;	
	}
	
	fputs("\n", file);								
	//blank line for dividing the cases of different substrings
	fclose(file);
}

int isPalindrome (char str[]) {
	int n = strlen(str);
	int j = n - 1;
	int i;

	for (i = 0; i < n / 2; i++) {
		if (j <= n / 2) break;							
		//if pointer j points to the first half of string, then stop the function (I think it is useless check for error)
		if (str[i] != str[j]) return 0;						
		//if any char of first half of string is not equal to the char of second half, then stop the function and return False
		j--;
	}
	return 1;
}

char *getPalindrome (char str[]) {
	if (isPalindrome(str)) return "Is_Palindrome";
	return "Not_Palindrome";
}

int howManySubstrings (char subStr[], char str[]) {
	int i;
	int j = 0;
	int count = 0;

	for (i = 0; i < strlen(str); i++) {
		if (subStr[j] == str[i]) {						
			//checking if subString's first char is equal to any char in a given string
			j++;
			if (j == strlen(subStr)) {					
				//if you are not removing the \r char, j == strlen(subStr) - 1
				count++;
				j = 0;
			}
		} else
			j = 0;
	}

	return count;
}

void freeLinkedlist (Node *head) {
	while (head != NULL) {
		free(head);
		head = head -> next;							
		//freeing up all the elements of linkedlist and passing the pointer to the next element
	}
}

void printLinkedlist (Node *head) {
	while (head != NULL) {
		printf("%s", head -> strData);						
		//printing the elements of every element in list and passing the pointer to the next element
		head = head -> next;
	}
	printf("\n");
}

void appendNode (Node **oLinkedList, char outputLine[]) {
	Node *new = malloc(sizeof(Node));
	Node *tail = *oLinkedList;
	strcpy(new -> strData, outputLine); 						
	//putting the formatted string into the new node
	new -> next = NULL;
	
	if (*oLinkedList == NULL)
		*oLinkedList = new;							
		//assigning the head of linkedlist
	else {
		while (tail -> next != NULL) 						
			//going through all the linkedlist and adding new node to the last position
			tail = tail -> next;
		
		tail -> next = new;							
		//tail will point to the last element of linkedlist
	}
}

void checkSubstringPalindrome2 (char ssData[], char *iStringData[], Node **oLinkedList, int nrIOfileLines) {
	int i;

	for (i = 0; i < nrIOfileLines; i++) {
		char temp[50];								
		//blank string for easy formatting
		int count = howManySubstrings(ssData, iStringData[i]);			
		//checking the amount of subStrings in a given string
		char *pal = getPalindrome(iStringData[i]);				
		//checking if string is palindrome
		sprintf(temp, "\t%i\t%s\n", count, pal);				
		//formatting the strings using obtained values
		strcat(iStringData[i], temp);
		appendNode(oLinkedList, iStringData[i]);				
		//add to linkedlist new nodes from tail
	}
}

char* removeLeadingWSpace (char *string) {
    	while (string[0] == ' ')
        	string++;
    	return string;
}

void readFile2 (char filename[], char *ArrayPtr[]) {
	FILE *file = fopen(filename, "r");
	int i = 0;

	while (fgets(ArrayPtr[i], 50, file)) {						
		//writing immediately into Array with strings
		while (ArrayPtr[i][0] == ' ')					
			//removing leading whitespaces
			ArrayPtr[i]++;

		int size = strlen(ArrayPtr[i]);
		int k;
		for (k = size - 1; k >= 0; k--) {
			if (ArrayPtr[i][k] == ' ' || ArrayPtr[i][k] == '\n' || ArrayPtr[i][k] == '\r')
				ArrayPtr[i][k] = 0;					
				//removing all trailing irritating characters
			else
				break;
		}
		i++;
	}
	fclose(file);
} 

int countFileLines (char filename[]) {
	FILE *file = fopen(filename, "r");
	int count = 0;
	char temp[50];									
	//blank string
	while (fgets(temp, 50, file)) count++;						
	//counting the number of lines
	fclose(file);
	return count;
}

int main () {
	char fileIn[] = "iStrings.txt";
	char fileOut[] = "oStrings.txt";
	char fileSub[] = "subStrings.txt";

	int count = countFileLines(fileIn);
	int sub_count = countFileLines(fileSub);
	int j;										
	//variable for iteration

	char *in[255];									
	//array for strings from iStrings.txt
	for (j = 0; j < 50; j++)
		in[j] = malloc(sizeof(char) * 50);					
		//allocating memory for every string

	char *sub[255];									
	//array for strings from subStrings.txt
	for (int j = 0; j < 50; j++)
		sub[j] = malloc(sizeof(char) * 50);					
		//allocating memory for every string

	FILE *trash = fopen(fileOut, "w");						
	//overwrite the file iStrings.txt
	fclose(trash);
	
	readFile2(fileSub, sub);							
	//reading subStrings
	
	for (j = 0; j < sub_count; j++) {
		Node *head = NULL;							
		//creating new linkedlist
		readFile2(fileIn, in);							
		//reading the content from file	
		int sub_size = strlen(sub[j]);						
		//size of a subString
		
		checkSubstringPalindrome2(sub[j], in, &head, count);			
		//creating formatted strings
		writeFile2(fileOut, sub[j], &head);					
		//writing formatted strings to oStrings.txt
		
		printLinkedlist(head);							
		//printing formatted strings
		freeLinkedlist(head);							
		//removing all elements of linkedlist
	}
}
