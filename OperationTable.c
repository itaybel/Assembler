#include <stdio.h>
#include <string.h>
#include "OperationTable.h"

#define firstAddres 1
#define secondAddres 2
#define thirdAddres 4
#define fourthAddres 8

static const struct  operationConsts{

    const char *name;
    int opcode;
    int operandNum;
    int soruceOperand;
    int desttinationOperand;
} operationTable[] = {{"mov",0,2, firstAddres | secondAddres | thirdAddres | fourthAddres, secondAddres | thirdAddres | fourthAddres},
                      {"cmp",1,2, firstAddres | secondAddres | thirdAddres | fourthAddres, secondAddres | thirdAddres | fourthAddres},
                      {"add",2,2, secondAddres | thirdAddres | fourthAddres,secondAddres | thirdAddres | fourthAddres},
                      {"sub",3,2,0,  secondAddres | thirdAddres | fourthAddres},
                      {"not",4,1,0,  secondAddres | thirdAddres | fourthAddres},
                      {"clr",5,1, firstAddres | secondAddres,secondAddres | thirdAddres | fourthAddres},
                      {"lea",6,2,0,  secondAddres | thirdAddres | fourthAddres},
                      {"inc",7,1,0,  secondAddres | thirdAddres | fourthAddres},
                      {"dec",8,1,0,  secondAddres | thirdAddres | fourthAddres},
                      {"jmp",9,1,0,  secondAddres | thirdAddres | fourthAddres},
                      {"bne",10,1,0, secondAddres | thirdAddres | fourthAddres},
                      {"get",11,1,0, secondAddres | thirdAddres | fourthAddres},
                      {"prn",12,1,0, firstAddres | secondAddres | thirdAddres | fourthAddres},
                      {"jsr",13,1,0, secondAddres | thirdAddres | fourthAddres},
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
            return operationTable[i].operandNum;
        }
        i++;
    }
    printf("Error!, this name doest not exist in the OperationTable!");
    return error;
}

