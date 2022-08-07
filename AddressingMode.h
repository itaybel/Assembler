#ifndef UNTITLED4_ADDRESSINGMODE_H

#define UNTITLED4_ADDRESSINGMODE_H
#include "RegisterTable.h"
#include "OperationTable.h"




#define NUM_OF_ADDRESS_MODE 5


 /*Instruction type (.data, .entry, etc.)*/



typedef enum addressingMode{
    immediateAddress = 0,
    directAddress = 1,
    addressAccess = 2,
    directRegisterAddress = 3,
    error = -1
} addressingMode;


int isInstructionName(char *name);


int reservedWord(char *name);


int immediateAddressCheck(char *string);


int getFirstDelimIndex(char *str, char delim);

enum addressingMode getAddressingMode(char *address, int getAddressingMode);


#endif
