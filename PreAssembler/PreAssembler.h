
#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H
#include "../Utility/GeneralFunctions.h"
#include "MacroTable.h"

#include <stdio.h>
#include <stdlib.h>

/*
This function is used to write the content of a macro to the output file
@param macro the macro to be written
@param inputFile the input assembly file
@param outputFile the output am file to write to
@return none
*/
void WriteMacroToOutputFile(macroNode macro, FILE* inputFile, FILE* outputFile);

/*
This function is used to look for new macros defintions and add them to the macro table.
@param head the head of the linked list of the macro table
@param line the next line in the input file
@param inputFile the input assembly file
@return 1 if a new macro was added, 0 otherwise
*/
int addToMacroList(macroNode* head, char* line, FILE* inputFile);

/*
This function is opening up the macros for the assembler
@param file_name the name of the input file
@return 1 if an error occured, 0 if everything is ok
*/
int preAssemble(char* file_name);


#endif 
