#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAX_FILE_NAME_LENGTH 255
#include "MacroTable.h"



void removeSpacesAndTabs(char line[MAX_LINE_LENGTH]);

void throwError(char* errorMsg, int numberOfLine);

int containsOnlyBlanks(char line[MAX_LINE_LENGTH]);

void substring(char* string, int length);

getSpacesAtBegining(char* substring);

int firstCharIsDot(char *line);

char* cutColonFromLabel(char *line, char *firstWord);

int isNumber(char *number);



#endif
