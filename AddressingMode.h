
#ifndef UNTITLED4_ADDRESSINGMODE_H
#define UNTITLED4_ADDRESSINGMODE_H
#define NUM_OF_ADDRESS_MODE 6



 /*Instruction type (.data, .entry, etc.)*/

typedef enum instructionsName {


 /*.data instruction */

    DATA_INSTRUCTION,

 /*.string instruction */

    STRING_INSTRUCTION,

 /*.struct instruction */

    STRUCT_INSTRUCTION,

 /*.entry instruction */

    ENTRY_INSTRUCTION,

 /*.extern instruction */

    EXTERN_INSTRUCTION,

 /*Not found

    ERROR_INSTRUCTION*/

} instructionName;


typedef enum addressingMode{
    immediateAddress = 0,
    directAddress = 1,
    addressAccess = 2,
    directRegisterAddress = 3,
    error = -1} addressingMode;


char* getInstructionName(char *name);


int reservedWord(char *name);


int immediateAddressCheck(char *string);


enum addressingMode getAddressingMode(char *address);


#endif