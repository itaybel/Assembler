#ifndef ADDRESSINGMODE_H

#define ADDRESSINGMODE_H

#define NUM_OF_ADDRESS_MODE 5

typedef enum addressingMode{
    immediateAddress = 0,
    directAddress = 1,
    addressAccess = 2,
    directRegisterAddress = 3,
    error = -1
} addressingMode;

/*
This function checks if a given string is an instruction name
@param name - the string to be checked
@return weather it's a valid instruction (.data/.string/.struct/.entry/.extern)
*/
int isInstructionName(char *name);


/*
This function returns the index of the first occurrence of a given delimiter
@param name - the string to be searched on
@param delim - the delimiter to search for
@return the index of the first occurrence of the given delimiter or 0 if it weren't found
*/
int getFirstDelimIndex(char *str, char delim);


/*
This function returns the addressing mode of a given operand
@param operand - the operand to get its addressing mode
@param numberOfLine - the current line processed in the input file
@return the addressing mode of the given operand
*/
enum addressingMode getAddressingMode(char *operand, int numberOfLine);


#endif
