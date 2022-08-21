#ifndef FUNCTION_H
#define FUNCTION_H


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <ctype.h>
#include "../AddressingMode.h"
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
This function checks if a given string is a reserved word in assembly
@param name - the string to be checked
@return wether its a reserved word
*/
int reservedWord(char *name);

/*
This function checks if the first character in a line is a dot
@param line - the line to check
@return wether it found a dot at the beginning of the string
*/
int firstCharIsDot(char *line);

/*
This function deletes the colon from a label 
@param labelName - the label
*/
void cutColonFromLabel(char *labelName);

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

/*
This function fixs the data instruction by adding spaces after a "," to handle more errors with strtok.
@param line - the string to be fixed
@param parsedLine a pointer to the string which will contain the fixed line
*/
void fixDataInstruction(char *line, char parsedLine[MAX_LINE_LENGTH * 2]);
  
/*
This function checks if a given line is a empty
@param line - the line to be checked
@return wether the given line is empty which means if it contains only blanks
*/
int foundEmptySentence(char* line);





#endif
