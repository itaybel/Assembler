

#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H

#include "../Utility/InputHandler.h"
#include "../Utility/FileHandler.h"
#include "../Utility/MacroTable.h"

/*
This function is responsible of creating the am files after laying out the macros
@param file_name - the name of the assembly input file
@return none
*/
int createAmFile(char* file_name);

#endif 
