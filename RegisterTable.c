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


int isRegisterName(char *name) {

    int i = 0;

    while (i < NUM_OF_REGISTERS) {


        if (strcmp(name,registerTable[i].name) == 0) {
            return 1;
        }
        i++;
    }
    return  0;

}


int getRegisterNum(char *name){

    int i = 0;

    while(i < NUM_OF_REGISTERS){
        if(strcmp(name, registerTable[i].name) == 0){
            return registerTable[i].number;
        }
        i++;
    }
    return 0;
}
