#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AddressingMode.h"
#include "Utility/GeneralFunctions.h"
#include "AssemblySentence.h"



static const struct instructionTableName{
    const char *name;
    const char *message;

}instructionsTable[] = {
        {".data",   "DATA_INSTRUCTION"},
        {".string", "STRING_INSTRUCTION"},
        {".struct", "STRUCT_INSTRUCTION"},
        {".entry",  "ENTRY_INSTRUCTION"},
        {".extern", "EXTERN_INSTRUCTION",},
        /*{NULL,     "ERROR_INSTRUCTION"}* it will have problem when we will compare name between NULL*/
};




int isInstructionName(char *name) {
    int i = 0;
    while( i < NUM_OF_ADDRESS_MODE) {
        if (strcmp(name, instructionsTable[i].name) == 0) {
            return 1;
        }
        i++;
    }

    return 0;

}



int reservedWord(char *name) {

    /*check if register or instructionname or lable */

    return (isRegisterName(name) || atoi(name) || isInstructionName(name) || isOperationName(name));

}



int immediateAddressCheck(char *string){/*we can use strtol instead of this function*/
    int i = 0;
    if (string[0] == '-' || string[0] == '+') { /*if string starts with +/-, it's OK */
        string++;
    }
    for(i = 0; string[i] != '\0'; i++){
        /*Just make sure that everything is a digit until the end*/

        if(!isdigit(string[i])){
            return 0;
            /*return false*/

        }
    }
    return 1;

}

/*str != NULL*/

int getFirstDelimIndex(char *str, char delim){/*S1.1 .*/
    int i = 0;

    for(i = 0; i< strlen(str);i++){
        if(str[i] == delim){
            return i;
        }
    }
    return 0;
}





addressingMode getAddressingMode(char *address, int numberOfLine) {/* MAIN:    mov    S1.1 ,LENGTH"*/

    int labelEnd = 0;
    char parsedLabel[MAX_LENGTH] = {0};
    /*result = strtok(NULL, " \t\n\v\f\r");*/

    /*if nothing, just return none */

    if (address[0] == '\0') {
        return error;
    }

    /*if address starts with # and a number right after that, it's immediately addressed = 0 */

    if (address[0] == '#') {
        if(immediateAddressCheck(address + 1)){
            return immediateAddress;
        }else{
            throwError("Invalid immediate address number!", numberOfLine);
            return error;
        }
    }

        /*if its name of register from registerTable, its directRegisterAddress = 3 */

    else if (isRegisterName(address)) {
        return directRegisterAddress;
    }

        /*if address is a valid label name, it's directAddressed = 1 */

    else if (validLabelName(address)) {
        return directAddress;
    }

        /*if address is a valid label name & after the dot we have, it's addressAccess  = 2 */

    else{/*need to check the string until the dot, for example if the string utnil the dot is lable, need to check if after the dot if its a number.*/
    
        labelEnd = getFirstDelimIndex(address,'.');
        strncpy(parsedLabel, address, labelEnd);
        if(validLabelName(parsedLabel)){/*S1.1*/
            if((address[labelEnd+1] == '1' || address[labelEnd + 1] == '2') && strlen(address) == labelEnd+2){
                return addressAccess;
            }
            /*if(firstCharIsDot(address) && (address[1] == '1' || address[1] == '2')){
                *//*if the label is valid, and checks if after the dot the number are 1 or 2*//*
                return addressAccess;
            }*/
        }
    }
    throwError("invalid addressing mode!", numberOfLine);
    return error;
}
