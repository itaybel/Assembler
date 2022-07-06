
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
/*
This function is responsible for opening different files with different file extenstions
@param file_name - the name of the input file
@param file_extention - the file extension of the input file
@param mode - the way we open the file (can be rb/rw/r/w)

@return the opened file if it could have opened it, otherwise NULL
*/
FILE* openFile(char* file_name, char* file_extention, char* mode);

#endif