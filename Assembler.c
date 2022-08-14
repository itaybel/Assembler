#include <stdio.h>
#include "Assembler.h"
#include "PreAssembler/PreAssembler.h"
#include "AssemblySentence.h"
#include "SecondPass.h"
int main(int argc, char** argv){
      
    int i = 0;
    symbolTable table = NULL;
    flags* status; 

    if(argc < 2){
        printf("Error - Invalid number of arguments was passed!");
        return 0;
    }
    for(i = 1; i < argc; i++){
        status = (flags*)calloc(1, sizeof(flags));
        /* preAssemble(argv[i]); */
        table = createSymbolTable(argv[i], status);
        if(status->error) continue;
        encodeAssembly(argv[i], table, status);
        free(status);
    }
    return 0;
}
