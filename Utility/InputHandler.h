
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#define MAX_LINE_LENGTH 80

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
/*
This removes all the spaces and the tabs at the begining in a given line
@param line - the line to remove the spaces of
@return none
*/
void removeSpacesAndTabs(char line[MAX_LINE_LENGTH]);

/*
This function will check wether one string starts with other string
@param str1 - the string we want to check the start of
@param str2 - the string we want to check if its at the begininng of str1
@return 0 - if str1 doesn't start with str2, otherwise 1
*/
int startWith(char* str1, char* str2);

/*
This function will return the first field of a given line
@param line - the line to be scanned
@return the first field, avoiding any spaces and tabs
*/
char* getNextField(char* line);
#endif 
