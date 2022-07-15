#include <stdio.h>
#include <string.h>
#include "RegisterTable.h"


static const struct registerConsts{

    const char *name;
    int number;

} registerTable[] = {{"r0",0},
                     {"r1",1},
                     {"r2",2},
                     {"r3",3},
                     {"r4",4},
                     {"r5",5},
                     {"r6",6},
                     {"r7",7}
};


char* getRegisterName(char *name) {

    int i = 0;
    char *correct;
    char *error;
    correct =  "The Register name is Correct!";

    error = "Error!, this name doest not exist in the RegisterTable!";
    while (i < NUM_OF_REGISTERS) {


        if (strcmp(name,registerTable[i].name) == 0) {
            return  correct;
        }
        i++;
    }
    return  error;

}


int getRegisterNum(char *name){

    int i = 0;
    int error = -1;

    while(i < NUM_OF_REGISTERS){
        if(strcmp(name, registerTable[i].name) == 0){
            return registerTable[i].number;
        }
        i++;
    }
    printf("Error!, this name doest not exist in the OperationTable!");
    return error;
}
