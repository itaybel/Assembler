#ifndef FUNCTION_H
#define FUNCTION_H


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAX_FILE_NAME_LENGTH 255
#define MAX_LINE_LENGTH 82




void removeSpacesAndTabs(char line[MAX_LINE_LENGTH]);

void getFileWithExtension(char* fileName, char* extension, char* fileWithExtension);

void deleteFile(char* file_name, char* file_extension);


FILE* openFile(char* file_name, char* file_extention, char* mode);


void throwError(char* errorMsg, int numberOfLine);


int containsOnlyBlanks(char line[MAX_LINE_LENGTH]);

void substring(char* string, int length);


int firstCharIsDot(char *line);

char* cutColonFromLabel(char* line, char *firstWord);

int isNumber(char *number);

int convertToNumber(char* numberString, int* number);

void *checkMalloc(int size);


#endif
