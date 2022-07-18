
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
This function checks if a given string contains just blanks (spaces/tabs)
@param line - the line to to be checked
@return wether it contains just blanks
*/
int containsOnlyBlanks(char line[MAX_LINE_LENGTH]);


#endif 
