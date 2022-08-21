#include <stdio.h>
#include <stdlib.h>
#include "PreAssembler/PreAssembler.h"
#include "Utility/GeneralFunctions.h"
#include "AssemblySentence.h"
#include "SecondPass.h"

int main(int argc, char** argv){
      
    int i = 0;
    symbolTable table = NULL;
    flags* status = NULL; 

    if(argc < 2){
        PRINT_RED();
        printf("Error - Invalid number of arguments was passed!\n");
        CLEAR_COLOR();
        return 0;
    }
    for(i = 1; i < argc; i++){
        status = (flags*)calloc(1, sizeof(flags));
        status->error = preAssemble(argv[i]); 

        if(status->error) {
            free(status);
            continue;
        }


        table = createSymbolTable(argv[i], status);
        if(status->error){
            deleteFile(argv[i], "am"); 
            free(status);
            continue;
        }
        encodeAssembly(argv[i], table, status);
        free(status);
        freeTable(table);
    }
    return 0;
}
