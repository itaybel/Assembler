#include <stdio.h>
#include "Assembler.h"
#include "PreAssembler/PreAssembler.h"
#include "AssemblySentence.h"
#include "SecondPass.h"
int main(int argc, char** argv){
      
    int i = 0;
    symbolTable table = NULL;
    if(argc < 2){
        printf("Error - Invalid number of arguments was passed!");
        return 0;
    }
    for(i = 1; i < argc; i++){
        preAssemble(argv[i]);
        table = createSymbolTable(argv[i]);
        if(table == NULL) continue;
        encodeAssembly(argv[i], table);
        
    }
    return 0;
}
