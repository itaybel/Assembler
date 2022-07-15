#include <stdio.h>
#include <string.h>
#include "OperationTable.h"

static const struct  operationConsts{

    const char *name;
    int opcode;
    int operandNum;
    int soruceOperand;
    int desttinationOperand;
} operationTable[] = {{"mov",0,2,1,1},
                      {"cmp",1,2,1,1},
                      {"add",2,2,1,1},
                      {"sub",3,2,1,1},
                      {"not",4,1,1,1},
                      {"clr",5,1,1,1},
                      {"lea",6,2,1,1},
                      {"inc",7,1,1,1},
                      {"dec",8,1,1,1},
                      {"jmp",9,1,1,1},
                      {"bne",10,1,1,1},
                      {"get",11,1,1,1},
                      {"prn",12,1,1,1},
                      {"jsr",13,1,1,1},
                      {"rts",14,0,1,1},
                      {"hlt",15,0,1,1}};


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


int main(){


    printf("%s\n", getOperationName("hlt"));
    printf("%d\n", getOperationOpcode("hlt1"));
    printf("%d\n", getOperandNum("cmp"));

    return 1;
}
