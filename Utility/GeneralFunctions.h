#ifndef FUNCTION_H
#define FUNCTION_H


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAX_FILE_NAME_LENGTH 255
#define MAX_LINE_LENGTH 82




/*
This function takes a filename and its extension, concetrates them, and places it in fileWithExtension
@param fileName - the name of the file
@param extension - the extension of the file
@param fileWithExtension - the string to write to
@return none
*/
void getFileWithExtension(char* fileName, char* extension, char* fileWithExtension);

/*
This function takes opens a file with a specific mode
@param file_name - the name of the file
@param file_extention - the extension of the file
@param mode - the mode to open the file with
@return the opened file
*/
FILE* openFile(char* file_name, char* file_extention, char* mode);

/*
This function takes a filename and its extension, and deletes the file
@param file_name - the name of the file
@param extension - the extension of the file
@return none
*/
void deleteFile(char* file_name, char* file_extension);



/*
This function deletes the spaces at the beginning and at the end of a given string
@param line - the string to be changed
@return none
*/
void removeSpacesAndTabs(char line[MAX_LINE_LENGTH]);

/*
This function throws an error and prints it on the screen
@param errorMsg - the error message to be printed
@param numberOfLine - the number of line the error was occurred at
@return none
*/
void throwError(char* errorMsg, int numberOfLine);

/*
This function checks if a line contains only blanks (spaces/tabs)
@param line - the line to check
@return wether it found a none blank character in the string
*/
int containsOnlyBlanks(char line[MAX_LINE_LENGTH]);


/*
This function checks if the first character in a line is a dot
@param line - the line to check
@return wether it found a dot at the beginning of the string
*/
int firstCharIsDot(char *line);

/*
This function cuts the part of the string that ends with a colon
@param line - the line to change
@param firstWord - the part to slice of the string
@return the sliced part of the string
*/
char* cutColonFromLabel(char* line, char *firstWord);

/*
This function checks if a string represents a valid number
@param number - the string to check
@return wether the string represents a valid number
*/
int isNumber(char *number);

/*
This function converts a given string to int
@param numberString - the string to be converted
@param number - a pointer to the place where we want to convert to
@return wether it succeeded to convert the string
*/
int convertToNumber(char* numberString, int* number);



int validData(char* string, int *DC,int numberOfLine);
  
  

/*
This function allocates memory of a specific size
@param size - the size of the memory block to be allocated
@return a pointer to the allocated memory
*/
void *checkMalloc(int size);


#endif
