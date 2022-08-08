#include <stdio.h>
#include "Assembler.h"
#include "PreAssembler/PreAssembler.h"
#include "AssemblySentence.h"

int main(int argc, char** argv){

    int i = 0;
    symbolTable table = NULL;
    if(argc < 2){
        printf("Error - Invalid number of arguments was passed!");
        return 0;
    }
    for(i = 1; i < argc; i++){
        /*preAssemble(argv[i]);*/
        createSymbolTable(argv[i], &table);
        encodeAssembly(argv[i], table);
        freeTable(table);
    }
    return 0;
}
