#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RegisterTable.h"
#include "AddressingMode.h"
#include "OperationTable.h"
#include "AssemblySentence.h"
#include "SymbolTable.h"




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




char* getInstructionName(char *name) {
    int i = 0;
    while( i < NUM_OF_ADDRESS_MODE) {
        if (strcmp(name, instructionsTable[i].name) == 0) {
            printf("%s", instructionsTable->message);
            return name;
        }
        i++;
    }

    return NULL;

}



int reservedWord(char *name) {

 /*check if register or instructionname or lable */

    if (strcmp(getRegisterName(name), name) == 0 || atoi(name) || strcmp(getInstructionName(name), name) == 0){
        return 1;
    }
    else if(strcmp(getOperationName(name),name) == 0){
        return 1;

    }


    return 0;
}




int immediateAddressCheck(char *string){/*we can use strtol instead of this function*/
    int i = 0;
    if (string[0] == '-' || string[0] == '+') {
        string++;
 /*if string starts with +/-, it's OK */

    }
    for(i; string[0]; i++){
 /*Just make sure that everything is a digit until the end*/

        if(!isdigit(string[i])){
            return 0;
 /*return false*/

        }
    }
    if( i > 0){
        return 1;
    }
    return 1;

}




addressingMode getAddressingMode(char *address) {/* address = "add #4, s.1"*/

    /*char *result = NULL;
    result = strtok(NULL, " \t\n\v\f\r");*/

    /*if nothing, just return none */

    if (address[0] == '\0') {
        return error;
    }

    /*if address starts with # and a number right after that, it's immediately addressed = 0 */

    if (address[0] == '#' && immediateAddressCheck(address + 1)) {
        return immediateAddress;
    }

        /*if its name of register from registerTable, its directRegisterAddress = 3 */

    else if (strcmp(getRegisterName(address), address) == 0) {
        return directRegisterAddress;
    }

        /*if address is a valid label name, it's directAddressed = 1 */

    else if (validLabelName(address)) {
        return directAddress;
    }

        /*if address is a valid label name & after the dot we have, it's addressAccess  = 2 */

    else{/*need to check the string until the dot, for example if the string utnil the dot is lable, need to check if after the dot if its a number.*/
        if(validLabelName(address)){
            if(firstCharIsDot(address) && address[1] == '1' || address[1] == '2'){
            /*if the label is valid, and checks if after the dot the number are 1 or 2*/
                return addressAccess;
            }
        }
    }
    return error;
}

