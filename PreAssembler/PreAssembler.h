

#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H

#include "input_handler.h"
#include "file_handler.h"
#include "linked_list.h"

/*
This function is responsible of creating the am files after laying out the macros
@param file_name - the name of the assembly input file
@return none
*/
int CreateAmFile(char* file_name);

#endif 
