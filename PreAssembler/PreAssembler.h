
#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H
#include <stdio.h>
#include "MacroTable.h"



/*
This function is used to write the content of a macro to the output file
@param macro the macro to be written
@param inputFile the input assembly file
@param outputFile the output am file to write to
@return none
*/
void WriteMacroToOutputFile(macroNode macro, FILE* inputFile, FILE* outputFile);

/*
This function is used to create a new macro node, by extracting its name, and its content
from the input file
@param head the head of the linked list of the macro table
@param line the next line in the input file
@param inputFile the input assembly file
@return 1 if an error occurred , 0 otherwise
*/
int addToMacroList(macroNode* head, char* line, FILE* inputFile);

/*
This function is the main function in the preAssembler, and it is used to
handle all the macro definitions
@param file_name the name of the input file
@return 1 if an error occured, 0 if everything is ok
*/
int preAssemble(char* file_name);


#endif 
