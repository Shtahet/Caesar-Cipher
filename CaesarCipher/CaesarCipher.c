#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define START_INDEX_FOR_UPPERCASE_LETTER	26
#define ALPHABET_SIZE						52
//void *realloc(void *aptr, size_t bytes);
int IsValidLetter(char*);
int IsUpperCaseLetter(char* letter);
int GetDictionaryIndex(char* letter);
char DecodeLetter(char* letter, int offset);
int FindStatisticMode(int, int[]);

int main()
{
	//settings variables
	const int alphabetSize = 52;					//26 upper case letters & 26 lower case letter
	const int defaultBufferSize = 256;

	int charOffset = 0;
	int currentBufferSize = defaultBufferSize;
	int eds = 0;									//Encrypted Data Size - lengs for encrypted array
	int isUpperCase = 0;
	int errCode = 0, exitCode = 0;

	//char alp[52] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

	char* encryptedData;
	encryptedData = (char*)malloc(defaultBufferSize * sizeof(char));

	//read encrypted data
	printf("Enter encoding string:\n");
	while (1) {
		scanf("%c", &encryptedData[eds]);

		if (encryptedData[eds] == '\n' || encryptedData[eds] == EOF)
		{
			break;
		}

		if (!IsValidLetter(&encryptedData[eds]))
		{ 
			errCode = 1; 
		}

		++eds;
		if (eds == currentBufferSize) 
		{ 
			currentBufferSize = eds + defaultBufferSize;
			encryptedData = (char*)realloc(encryptedData, currentBufferSize);
		}
	}

	//read wrong decoded data & write statistic
	int* deltaStat = (int*)malloc(eds * sizeof(int));
	int currIdx = 0;
	int offset, modeOffset;
	char letter;

	printf("Enter wrong decoding string:\n");
	while (1) {
		scanf("%c", &letter);
		if (letter == '\n' || letter == EOF)
		{
			break;
		}
		if (currIdx > eds)
		{
			break;
		}

		if (!IsValidLetter(&letter)) 
		{ 
			errCode = 1;
			continue;
		}
		int a = GetDictionaryIndex(&letter);
		int b = GetDictionaryIndex(&encryptedData[currIdx]);
		offset = GetDictionaryIndex(&letter) - GetDictionaryIndex(&encryptedData[currIdx]);
		if (offset < 0)
		{
			offset += alphabetSize;
		}

		deltaStat[currIdx++] = offset;
	}

	//check parsing for input data
	if (errCode) 
	{ 
		fprintf(stderr, "Error: Chybny vstup!\n"); exitCode = 100; 
	}
	else if (eds != currIdx) 
	{ 
		fprintf(stderr, "Error: Chybna delka vstupu!\n"); exitCode = 101; 
	}
	else 
	{
		//look for offset & write correct answer
		modeOffset = FindStatisticMode(currIdx, deltaStat);
		
		printf("\nCorrect decoded string:\n");
		for (int i = 0; i < eds; ++i)
		{
			printf("%c", DecodeLetter(&encryptedData[i], modeOffset));
		}
	}

	free(deltaStat);
	deltaStat = NULL;
	free(encryptedData);
	encryptedData = NULL;

	if (errCode == 0 && eds != currIdx)
		printf("\n");

	return exitCode;
}

int IsValidLetter(char* letter) {
	if (*letter < 'A')
	{
		return 0;
	}
	if (*letter > 'z')
	{
		return 0;
	}
	if (*letter > 'Z' && *letter < 'a')
	{
		return 0;
	}

	return 1;
}

int IsUpperCaseLetter(char* letter) {
	if (*letter < 'a')
		return 1;
	else
		return 0;
}

int GetDictionaryIndex(char* letter) {
	int idx = 0;
	if (IsUpperCaseLetter(letter))
	{
		idx = *letter - 'A' + START_INDEX_FOR_UPPERCASE_LETTER;
	}
	else
	{
		idx = *letter - 'a';
	}
	return idx;
}

char DecodeLetter(char* letter, int offset) {
	int encodedLetterIndex = GetDictionaryIndex(letter) - offset;
	if (encodedLetterIndex < 0)
	{
		encodedLetterIndex += ALPHABET_SIZE - 1;
	}
	int letterIndex;
	if (encodedLetterIndex < START_INDEX_FOR_UPPERCASE_LETTER)
	{
		letterIndex = encodedLetterIndex + 'a' - 1;
	}
	else
	{
		letterIndex = encodedLetterIndex - START_INDEX_FOR_UPPERCASE_LETTER - 1 + 'A';
	}
	return (char)letterIndex;
}

int FindStatisticMode(int size, int  x[]) {

	int* dictionary = (int*)malloc(ALPHABET_SIZE * sizeof(int));
	int mode;

	for (int i = 0; i < size; ++i)
	{
		dictionary[x[i]]++;
	}

	int maxFrequency = dictionary[0];
	mode = 0;
	for (int i = 0; i < ALPHABET_SIZE; ++i) 
	{
		if (dictionary[i] > maxFrequency)
		{
			maxFrequency = dictionary[i];
			mode = i;
		}
	}
	free(dictionary);
	return mode;
}