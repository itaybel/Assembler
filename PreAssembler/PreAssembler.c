#include "PreAssembler.h"

/*
This function is used to open the input assembly file
@param file_name - the name of the file
@return a pointer to the opened file
*/
FILE* getInputFile(char* file_name){
    FILE *asmFile = NULL;

    asmFile = openFile(file_name , "as", "r");
        
    if(asmFile == NULL){
        printf("Error - Couldn't open the file: %s\n", file_name);
        return NULL;
    }
    return asmFile;
}
/*
This function is used to open the output am file
@param file_name - the name of the file
@return a pointer to the opened file
*/
FILE* getOutputFile(char* file_name){
    FILE *amFile = NULL;

    amFile = openFile(file_name , "am", "w");
        
    if(amFile == NULL){
        printf("Error - Couldn't open the file: %s\n", file_name);
        return NULL;
    }

    return amFile;
}

/*
This function is used to write the content of a macro to the output file
@param macro the macro to be written
@param inputFile the input assembly file
@param outputFile the output am file to write to
@return none
*/
void WriteMacroToOutputFile(MacroNode* macro, FILE* inputFile, FILE* outputFile){
    int i = 0;

    fseek(inputFile, macro->startIndex, SEEK_SET);
    for(i = 0; i < macro->length; i++){
        fputc(fgetc(inputFile), outputFile);
    }
}
/*
This function is used to look for new macros defintions and add them to the macro table.
@param head the head of the linked list of the macro table
@param line the next line in the input file
@param inputFile the input assembly file
@return 1 if a new macro was added, 0 otherwise
*/
int addToMacroList(Node** head, char* line, FILE* inputFile){
    char* command;
    MacroNode* newMacroNode =  NULL;
    removeSpacesAndTabs(line);

    command = strtok(line, " "); /* get the first word in the line. */

    if(command != NULL && strcmp(command, "macro") == 0){ /* if the line starts with "macro" , which means a new macro declartion is made*/
        command = strtok(NULL, "\n"); /* extracting the next field seprated with space, which will be the name of the macro */
        newMacroNode = createMacroNode(command);
        newMacroNode->startIndex = ftell(inputFile);
        while(!feof(inputFile)){
            fgets(line, MAX_LINE_LENGTH, inputFile);
            removeSpacesAndTabs(line);
            if(strcmp(line, "endmacro\n") == 0) {
                break;
            }
        }
        newMacroNode->length = (ftell(inputFile) - (strlen("endmacro") + 1)- newMacroNode->startIndex); /* we need to substract the length of endmacro since we don't want it to be in the output file */
        InsertNode(head, newMacroNode);
        
        return 1;
    }

    return 0;

}
/*
This function is opening up the macros for the assembler
@param file_name the name of the input file
@return 0 if it faced any errors, 1 otherwise
*/
int preAssemble(char* file_name){
        FILE *inputFile = NULL, *outputFile = NULL;
        Node* macroTable = NULL, *foundNode = NULL;
        char line[MAX_LINE_LENGTH] = {0};
        char* command = NULL, *originaLine = NULL;
        int tempPos = 0;

        if((inputFile = getInputFile(file_name)) == NULL) return 0;
        if((outputFile = getOutputFile(file_name)) == NULL) {
            fclose(inputFile);
            return 0;
        }

        while (!feof(inputFile)) { /* iterating through each line of the input file */
            fgets(line, MAX_LINE_LENGTH, inputFile); /* storing a copy of the line, since strtok will be changing it */
            originaLine = (char *)malloc(strlen(line) + 1);
            strcpy(originaLine, line);

            if(!addToMacroList(&macroTable, line, inputFile)){ /* if we didn't add any new macros to the list */
                command = strtok(line, " \n"); /* get the first word in the line. */
                if((foundNode = (SearchNode(macroTable, command, compareMacro))) != NULL ){ /* if its a macro call */
                    tempPos = ftell(inputFile);
                    WriteMacroToOutputFile(foundNode->data, inputFile, outputFile); /* we write the macro's code instead of the macro call */
                    fseek(inputFile, tempPos, SEEK_SET);
                }
                else{
                    fprintf(outputFile, "%s", originaLine);
                }
            }
            free(originaLine);
            
        }
        
        fclose(inputFile);
        fclose(outputFile);
        freeList(macroTable, freeNode);
        return 1;
}




