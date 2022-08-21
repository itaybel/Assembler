#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AddressingMode.h"
#include "Utility/GeneralFunctions.h"
#include "AssemblySentence.h"
#include "RegisterTable.h"



static const struct instructionTableName{
    const char *name;

}instructionsTable[] = {
        {".data"},
        {".string"},
        {".struct"},
        {".entry"},
        {".extern"},
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


int getFirstDelimIndex(char *str, char delim){
    int i = 0;

    for(i = 0; i< strlen(str);i++){
        if(str[i] == delim){
            return i;
        }
    }
    return 0;
}





addressingMode getAddressingMode(char *operand, int numberOfLine) {/* MAIN:    mov    S1.1 ,LENGTH"*/


    int labelEnd = 0;
    char parsedLabel[MAX_LENGTH] = {0};

    /*if nothing, just return none */

    if (operand[0] == '\0') {
        return error;
    }

    /*if address starts with # and a number right after that, it's immediately addressed = 0 */

    if (operand[0] == '#') {
        if(isNumber(operand + 1)){
            return immediateAddress;
        }else{
            throwError("Invalid immediate address number!", numberOfLine);
            return error;
        }
    }

        /*if its name of register from registerTable, its directRegisterAddress = 3 */

    else if (isRegisterName(operand)) {
        return directRegisterAddress;
    }

        /*if address is a valid label name, it's directAddressed = 1 */

    else if (validLabelName(operand)) {
        return directAddress;
    }

        /*if address is a valid label name & after the dot we have, it's addressAccess  = 2 */

    else{/*checks the string until the dot, if its legal label we check if after the dot we have number 1 or 2 */

        labelEnd = getFirstDelimIndex(operand,'.');
        strncpy(parsedLabel, operand, labelEnd);
        if(validLabelName(parsedLabel)){/*S1.1*/
            if((operand[labelEnd+1] == '1' || operand[labelEnd + 1] == '2') && foundEmptySentence(operand + (labelEnd+2))){
                return addressAccess;
            }
        }
    }

    throwError("Found illegal operand", numberOfLine);
    return error;
}
