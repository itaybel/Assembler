#include <stdio.h>
#include <string.h>
#include "OperationTable.h"


static const struct  operationConsts{

    const char *name;
    int opcode;
    int operandNum;
    int sourceOperand;
    int destinationOperand;
} operationTable[] = {{"mov",0,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"cmp",1,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"add",2,2, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS,SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"sub",3,2,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"not",4,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"clr",5,1, FIRST_ADDRESS | SECOND_ADDRESS,SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"lea",6,2,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"inc",7,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"dec",8,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"jmp",9,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"bne",10,1,0, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"get",11,1,0, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"prn",12,1,0, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"jsr",13,1,0, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"rts",14,0,0,0},
                      {"hlt",15,0,0,0}};


enum addressingMode{immediateAddress = 0,DirectAddress = 1,addressAccess = 2,directRegisterAddress = 3};


char* getOperationName(char *name) {

    int i = 0;
    char *correct;
    char *error;
    correct =  "Correct name!";

    error = "Error!, this name doest not exist in the OperationTable!";
    while (i < NUM_OF_OPERATIONS) {


        if (strcmp(name,operationTable[i].name) == 0) {
            return  correct;
        }
        i++;
    }
    return  error;

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
    printf("Error!, this name doest not exist in the OperationTable!");
    return error;
}



int getOperandNum(char *name){

    int i = 0;
    int error = -1;

    while(i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0){
            printf("\ncorrect! the number of operands for: ");
            printf("%s is: \n",operationTable[i].name);
            printf("%d",operationTable[i].operandNum);
            return operationTable[i].operandNum;
        }
        i++;
    }
    printf("Error!, this name doest not exist in the OperationTable!");
    return error;
}


int getSourceOperand(char *name, int sourceOperand){
    int i = 0;
    int error = -1;
    char bit = 1;


    while (i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0) {
            if (bit << sourceOperand & operationTable[i].sourceOperand){
                printf("\ncorrect!! the number of sourceOperand for: ");
                printf("%s ",operationTable[i].name);
                printf("and the operand number is: \n");
                return sourceOperand;
            }
        }
        i++;
    }
    printf("error! invalid sourceOperand for this operation name! the error name is: ");
    return error;
}


int getDestinationOperand(char *name, int destinationOperand){
    int i = 0;
    int error = -1;
    char bit = 1;


    while (i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0) {
            if (bit << destinationOperand & operationTable[i].destinationOperand){
                printf("\ncorrect!! the number of destinationOperand for: ");
                printf("%s ",operationTable[i].name);
                printf("and the operand number is: \n");
                return destinationOperand;
            }
        }
        i++;
    }
    printf("error! invalid destinationOperand for this operation name! the error name is: ");
    return error;
}

