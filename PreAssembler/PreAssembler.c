#include "PreAssembler.h"


/*
This function is used to write the content of a macro to the output file
@param macro the macro to be written
@param inputFile the input assembly file
@param outputFile the output am file to write to
@return none
*/
void WriteMacroToOutputFile(macroNode macro, FILE* inputFile, FILE* outputFile){
    int i = 0;

    fseek(inputFile, getStartIndex(macro), SEEK_SET);
    for(i = 0; i < getLength(macro); i++){
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
int addToMacroList(macroNode* head, char* line, FILE* inputFile){
    char* command;
    int macroContentLength = 0;
    macroNode newMacroNode =  NULL;
    int previousLineFtell = 0;
    command = strtok(line, " \t\n\v\f\r"); /* get the first word in the line. */

    if(command != NULL && strcmp(command, "macro") == 0){ /* if the line starts with "macro" , which means a new macro declartion is made*/
        command = strtok(NULL, "\n"); /* extracting the next field , which will be the name of the macro */
        removeSpacesAndTabs(command);
        newMacroNode = createMacroNode(command);

        setStartIndex(newMacroNode, ftell(inputFile));

        while(!feof(inputFile)){
            fgets(line, MAX_LINE_LENGTH, inputFile);
            line[strcspn(line, "\n")] = 0;
            command = strtok(line, " \t\n\v\f\r");
            removeSpacesAndTabs(line);
            if(strcmp(command, "endmacro") == 0) {
                break;
            }
            previousLineFtell = ftell(inputFile);
        }
        macroContentLength = (previousLineFtell - getStartIndex(newMacroNode)); /* we need to substract the length of endmacro since we don't want it to be in the output file */
        setLength(newMacroNode, macroContentLength);
        InsertMacroNode(head, newMacroNode);
        previousLineFtell = ftell(inputFile);

        return 1;
    }

    return 0;

}
/*
This function is opening up the macros for the assembler
@param file_name the name of the input file
@return 1 if it couldn't allocate memory, -1 if one of the files couldn't be opened, or 0 if it succeed
*/
int preAssemble(char* file_name){
        FILE *inputFile = openFile(file_name , "as", "r"), *outputFile = openFile(file_name , "am", "w");
        macroNode macroTable = NULL, foundNode = NULL;
        char line[MAX_LINE_LENGTH] = {0};
        char* command = NULL, *originaLine = NULL;
        int tempPos = 0;

        if(inputFile == NULL) return -1;
        if(outputFile == NULL) {
            fclose(inputFile);
            return -1;
        }

        while (fgets(line, MAX_LINE_LENGTH, inputFile)) { /* iterating through each line of the input file */
            if(containsOnlyBlanks(line)) continue;
            originaLine = (char *)malloc(strlen(line) + 1);/* storing a copy of the line, since strtok will be changing it */
            if(originaLine == NULL) return 1;
            strcpy(originaLine, line);

            if(!addToMacroList(&macroTable, line, inputFile)){ /* if we didn't add any new macros to the list */
                command = strtok(line, " \t\n\v\f\r"); /* get the first word in the line. */
                printf("command is: -%s-\n", command);
                if((foundNode = (SearchNode(macroTable, command))) != NULL ){ /* if its a macro call */
                    tempPos = (int)ftell(inputFile);
                    WriteMacroToOutputFile(foundNode, inputFile, outputFile); /* we write the macro's code instead of the macro call */
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
        freeMacroList(macroTable);
        return 1;
}
