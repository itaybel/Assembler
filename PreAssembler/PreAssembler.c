#include <string.h>
#include "PreAssembler.h"
#include "../Utility/GeneralFunctions.h"


void WriteMacroToOutputFile(macroNode macro, FILE* inputFile, FILE* outputFile){
    int i = 0;

    fseek(inputFile, getStartIndex(macro), SEEK_SET);
    for(i = 0; i < getLength(macro); i++){
        fputc(fgetc(inputFile), outputFile);
    }
}

int addToMacroList(macroNode* head, char* line, FILE* inputFile){
    char* command = NULL;
    char* macroName = NULL;
    int macroContentLength = 0;
    macroNode newMacroNode =  NULL;
    int previousLineFtell = 0;

    macroName = strtok(NULL, "\t \n"); /* extracting the next field , which will be the name of the macro */
    removeSpacesAndTabs(macroName);

    if(isValidMacroName(macroName)){
        newMacroNode = createMacroNode(macroName);

        setStartIndex(newMacroNode, ftell(inputFile));

        while(!feof(inputFile)){
            fgets(line, MAX_LINE_LENGTH, inputFile);

            command = strtok(line, " \t\n\v\f\r");

            removeSpacesAndTabs(command);
            if(!foundEmptySentence(command) && strcmp(command, "endmacro") == 0) {
                break;
            }
            previousLineFtell = ftell(inputFile);
        }
        macroContentLength = (previousLineFtell - getStartIndex(newMacroNode)); /* we need to substract the length of endmacro since we don't want it to be in the output file */
        setLength(newMacroNode, macroContentLength);
        InsertMacroNode(head, newMacroNode);
        previousLineFtell = ftell(inputFile);
        return 0;

    }
    PRINT_RED();
    printf("Found an invalid macro name: '%s'\n", macroName);
    CLEAR_COLOR();
    return 1;


}

int preAssemble(char* fileName){
    FILE *inputFile = openFile(fileName , "as", "r"), *outputFile = NULL;
    macroNode macroTable = NULL, foundNode = NULL;
    char line[MAX_LINE_LENGTH] = {0}, lineCopy[MAX_LINE_LENGTH] = {0};
    int error = 0;
    char* command = NULL;
    int tempPos = 0;

    if(inputFile == NULL) {
        PRINT_RED();
        printf("Couldn't open file %s.as, terminating program...\n", fileName);
        CLEAR_COLOR();
        return 1;
    }

    if((outputFile = openFile(fileName , "am", "w")) == NULL) {
        fclose(inputFile);
        PRINT_RED();
        printf("Couldn't open file %s.am, terminating program...\n", fileName);
        CLEAR_COLOR();
        return 1;
    }
    PRINT_WHITE();
    printf("Started PreAssembler on the file: %s.as\n", fileName);
    CLEAR_COLOR();
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) { /* iterating through each line of the input file */
        strcpy(lineCopy, line);
        command = strtok(line, " \t\n\v\f\r"); /* get the first word in the line. */
        if(command != NULL && strcmp(command, "macro") == 0){
            if(addToMacroList(&macroTable, line, inputFile) == 1) { /* if it found an error */
                error = 1;
                break;
            }
            continue;
        }
        command = strtok(line, " \t\n\v\f\r"); /* get the first word in the line. */

        if((foundNode = (SearchNode(macroTable, command))) != NULL ){ /* if its a macro call */
            tempPos = (int)ftell(inputFile);
            WriteMacroToOutputFile(foundNode, inputFile, outputFile); /* we write the macro's code instead of the macro call */
            fseek(inputFile, tempPos, SEEK_SET);
        }
        else{
            fprintf(outputFile, "%s", lineCopy);
        }

    }
    fclose(inputFile);
    fclose(outputFile);
    freeMacroList(macroTable);
    if(error){
        PRINT_RED();
        printf("PreAssembler on file: %s.as failed!\n", fileName);
    }else{
        PRINT_GREEN();
        printf("Finished PreAssembler on file: %s.as\n", fileName);
    }
    CLEAR_COLOR();
    return error;
}
