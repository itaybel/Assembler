#include "Assembler.h"

int main(int argc, char** argv){

    int i = 0;
    if(argc < 2){
        printf("Error - Invalid number of arguments was passed!");
        return 0;
    }
    for(i = 1; i < argc; i++){
        preAssemble(argv[i]);
    }
    return 0;
}