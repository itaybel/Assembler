
#ifndef UNTITLED4_ADDRESSINGMODE_H
#define UNTITLED4_ADDRESSINGMODE_H
#include "RegisterTable.h"
#include "OperationTable.h"




#define NUM_OF_ADDRESS_MODE 6


typedef enum addressingMode{
    immediateAddress = 0,
    directAddress = 1,
    addressAccess = 2,
    directRegisterAddress = 3,
    error = -1
} addressingMode;


char* getInstructionName(char *name);


int reservedWord(char *name);


int immediateAddressCheck(char *string);


enum addressingMode getAddressingMode(char *address, int getAddressingMode);


#endif
