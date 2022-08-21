#include <string.h>
#include "OperationTable.h"



static const struct  operationConsts{

    const char *name;
    int opcode;
    int operandNum;
    int sourceOperand;
    int destinationOperand;
} operationTable[] = {{"mov",0,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"cmp",1,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"add",2,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"sub",3,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"not",4,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"clr",5,1,0,   SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"lea",6,2,  SECOND_ADDRESS | THIRD_ADDRESS , SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"inc",7,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"dec",8,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"jmp",9,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"bne",10,1,0, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"get",11,1,0, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"prn",12,1,0, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"jsr",13,1,0, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"rts",14,0,0,0},
                      {"hlt",15,0,0,0}};




int isOperationName(char *name) {

    int i = 0;
    
    while (i < NUM_OF_OPERATIONS) {


        if (strcmp(name,operationTable[i].name) == 0) {
            return  1;
        }
        i++;
    }
    return  0;

}


int getOperationOpcode(char *name){

    int i = 0;
    int error = -1;

    while(i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0){
            return operationTable[i].opcode;
        }
        i++;
    }
    return error;
}



int getOperandNum(char *name){

    int i = 0;
    int error = -1;

    while(i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0){
            return operationTable[i].operandNum;
        }
        i++;
    }
    return error;
}


int getSourceOperand(char *name){
    int i = 0;
    int error = -1;


    while (i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0) {
            return operationTable[i].sourceOperand;
        }
         i++;
    }
    return error;
    
}


int getDestinationOperand(char *name){
    int i = 0;
    int error = -1;


    while (i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0) {
            return operationTable[i].destinationOperand;
        }
         i++;
    }
    return error;
}


