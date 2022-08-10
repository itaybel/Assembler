#ifndef FUNCTION_H
#define FUNCTION_H


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAX_FILE_NAME_LENGTH 255
#define MAX_LINE_LENGTH 82
#include "../PreAssembler/MacroTable.h"



void removeSpacesAndTabs(char line[MAX_LINE_LENGTH]);
FILE* openFile(char* file_name, char* file_extention, char* mode);

int containsOnlyBlanks(char line[MAX_LINE_LENGTH]);

void substring(char* string, int length);


int firstCharIsDot(char *line);

char* cutColonFromLabel(char *line, char *firstWord);

int isNumber(char *number);
#endif
