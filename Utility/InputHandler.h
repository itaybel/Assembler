#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAX_FILE_NAME_LENGTH 255
#define MAX_LINE_LENGTH 82
#include "../PreAssembler/MacroTable.h"



void removeSpacesAndTabs(char line[MAX_LINE_LENGTH]);


int containsOnlyBlanks(char line[MAX_LINE_LENGTH]);

void substring(char* string, int length);

#endif
