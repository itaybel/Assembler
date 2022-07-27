#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "AssemblySentence.h"
#include "FileHandler.h"
#include "InputHandler.h"
#include "AddressingMode.h"
#include "AddressingMode.c"


/*
 Represents a single source line, including its details
 */
typedef struct line_info {
    /* Line number in file */
    long line_number;
    /* File name */
    char *file_name;
    /* Line content (source) */
    char *content;
} line_info;


int foundEmptySentence(char* line){/*need to change the parameter of the function to line*/
    char* result = NULL;
    result = strtok(line, " \t\n\v\f\r");

    if(result == NULL){
        return 0;
    }
    return 1;
}



int foundCommendSentence(char* line){//*we are working with lines we don't need to give to the function file, and its commend not command*//*
    char *result = NULL;
    result = strtok(line, " \t\n\v\f\r");

        if(result[0] == ';'){
            return 0;
        }
    return 1;
}



int validInstruction(char* name, char* line){
    int i = 0;
    int num = 0;
    unsigned char data;
    char *instruction = NULL;
    /*instruction= strtok(line, " \t\n\v\f\r.");*/
    if(strcmp(name, "data") == 0){
        instruction = strtok(line, " \t\n\v\f\r.,data");
        if (atoi(instruction)) {
            return 1;
        }
    }
    i++;
    if(strcmp(name, "string") == 0){
        instruction = strtok(line, " .\t\n\v\f\r string");
        while (instruction[i]) {
            if (isalpha(instruction[i])) {
                i++;
            }else{
                return 2;
            }
        }
        return 0;
    }

    if(strcmp(name, "struct") == 0){
        instruction = strtok(line, " .\t\n\v\f\r struct");
        if(instruction[0] == atoi(instruction)){
            while (instruction[i]) {
                if (isalpha(instruction[i])) {
                    i++;
                }else{
                    return 0;
                }
            }
            }
        return 3;
    }

    if(strcmp(name, "entry") == 0){
        instruction = strtok(line, " .\t\n\v\f\r entry");
        if((getSymbolName(instruction))){
            return 4;
        }
    }

    if(strcmp(name, "extern") == 0){
        instruction = strtok(line, " .\t\n\v\f\r extern");
        if(validLabelName(instruction)){
            InsertSymbol(instruction, data);
        }
        return 5;
        }

    return 0;

}



int validCommandSentence(char *line){
    char *token = NULL;
    char *name;
    int i = 0;


    data = strtok(line, token);

    token = strtok(line, " \t\n\v\f\r");
    if(validLabelName(token)){
        InsertSymbol(instruction, data);
        token = strtok(line, " :");
    }

    if(strcmp(getOperationName(token), token) == 0 && getOperandNum(token) == 2){
        name = getOperationName(token);
    }

    token = strtok(line,",");

    while (token[i]) {
        if (isalnum(token[i])) {
            i++;
        }else{
            return 0;
        }
    }

    return 0;

}






/* Returns the first instruction from the specified index. if no such one, returns NONE */
/*instructionName findInstruction(char* file) {
    FILE *inputFile = NULL;
    int i = 0;
    char line[MAX_LINE_LENGTH];
    char *originalLine = NULL;
    char* result = NULL;

    inputFile = openFile(line, "am", "r");

    while (!feof(inputFile)) {

        fgets(line, MAX_LINE_LENGTH, inputFile);

        originalLine = (char *) malloc(strlen(line) + 1);
        strcpy(originalLine, line);

        if (foundEmptySentence(file) ) {
            continue;
        }
        if (foundCommandSentence(file)) {
            continue;
        }

        *//* we can use strtok, to check if the word starts with dot, and after that need to check if the word is correct instruction.*//*
        result = strtok(line, " \t\n\v\f\r");
        if(result[0] == '.'){
            result = strtok(result,".");
        }



        if(strcmp(result, instructionsTable[i].name) == 0{

        return 0;

        }
    }
        result = getInstructionName(originalLine[i]);
        if (result != ERROR_INSTRUCTION) {
            return result;
        }

    return ERROR_INSTRUCTION;

    }*/

