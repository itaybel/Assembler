
#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H
#include "../Utility/GeneralFunctions.h"
#include "MacroTable.c"
#include <stdio.h>
#include <stdlib.h>

void WriteMacroToOutputFile(macroNode macro, FILE* inputFile, FILE* outputFile);

int addToMacroList(macroNode* head, char* line, FILE* inputFile);
/*
This function is responsible of creating the am files after laying out the macros
@param file_name - the name of the assembly input file
@return none
*/
int preAssemble(char* file_name);


#endif 
