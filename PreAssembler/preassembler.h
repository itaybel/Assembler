

#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H

#include "../Utility/input_handler.h"
#include "../Utility/file_handler.h"
#include "../Utility/macro_table.h"

/*
This function is responsible of creating the am files after laying out the macros
@param file_name - the name of the assembly input file
@return none
*/
int createAmFile(char* file_name);

#endif 
