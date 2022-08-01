#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "AssemblySentence.h"
#include "FileHandler.h"
#include "InputHandler.h"
#include "AddressingMode.h"
#include "AddressingMode.c"
#include "SymbolTable.h"




int foundEmptySentence(char* line){
  
    if(line == NULL){
        return 1;
    }
    return 0;
}



int foundCommendSentence(char* line){
    char *semicolon = NULL;
    semicolon = ";";

        if(strcmp(semicolon,line) == 0){
            return 1;
        }
    return 0;
}


int firstCharIsDot(char *line){

    if(line[0] == '.' ){
        return 1;
    }
    return 0;
}


char* cutColonFromLabel(char *line, char *firstWord) {/*cuts from the label the ":" from the end*/

    line[strlen(firstWord) - 1] = '\0';
    return line;
}


int doData(symbolTable table,char *line, int *DC,int numberOfLine)
{
    int i = 0;
    char *curr_line = line;
    /*long ret;*/
    while (curr_line[0] != '\n' && curr_line[0] != '\0')
    {
        /*ret = strtol(line, &curr_line, 10);*/
        if (strcmp(curr_line, line) == 0)
        { // this means that it couldn't convert any number
            printf("Couldn't parse one of the numbers!\n-%s-", curr_line);
            return 1;
        }
        if (curr_line[0] != '\0' && curr_line[0] != ',')
        {
            printf("Couldn't find an ',' after a number!");
            return 1;
        }
        curr_line++; /*shifting the ',' at the beginning*/
        line = curr_line;
        i++;
    }
    *DC = *DC + i;

    return 0;
}

int doString(symbolTable table,char *line, int *DC,int numberOfLine)
{
    int i = 0;
    int string_length = 0;
    int found_valid_string = 0;
    while (line[i] != '\n' && line[i] != '\0' && !found_valid_string)
    {
        if (line[i] != '\t' && line[i] != ' ')
        {
            printf("Found invalid text before string");
            return 1;
        }
        if (line[i] == '"')
        {
            while (line[i] != '\n' && line[i] != '\0' && !found_valid_string)
            {

                string_length++;
                i++;
                if (line[i] == '\"')
                {
                    found_valid_string = 1;
                }
            }
        }
        i++;
    }
    if (found_valid_string)
    {
        *DC = *DC + string_length;
        return 0;
    }
    return 1;
}


int doStruct(symbolTable table,char *line, int *DC,int numberOfLine)
{
    int i = 0;
    /*int ret = 0;*/
    int string_length = 0;
    int found_valid_string = 0;
    char *curr_line = line;

    /*ret = strtol(line, &curr_line, 10);*/
    if (strcmp(curr_line, line) == 0)
    { // this means that it couldn't convert any number
        printf("Couldn't parse the number!\n");
        return 1;
    }
    if (curr_line[0] != ',')
    {
        printf("Couldn't find an ',' after a number!");
        return 1;
    }
    curr_line++; // shifting the , at the begining

    while (line[i] != '\n' && line[i] != '\0' && !found_valid_string)
    {
        if (line[i] != '\t' && line[i] != ' ')
        {
            printf("Found invalid text after ','");
            return 1;
        }
        if (line[i] == '"')
        {
            while (line[i] != '\n' && line[i] != '\0' && !found_valid_string)
            {

                string_length++;
                i++;
                if (line[i] == '\"')
                {
                    found_valid_string = 1;
                }
            }
        }
        i++;
    }
    if (found_valid_string)
    {
        *DC = *DC + string_length + 1;
        return 0;
    }
    return 1;
}


int doEntry(symbolTable table,char *line, int *DC,int numberOfLine){/*only checks if the label is valid*/
    if(validLabelName(line)){
        return 1;
    }
    return 0;
}


int doExtern(symbolTable table,char *line, int *DC,int numberOfLine){/*checks if the label is valid*/
    if(validLabelName(line)){
        return 1;
    }
}




int doCommandSentence(char *line, int *IC) {
    char *token = NULL;
    int opNumber = 0;
    char *temp;


    token = strtok(line, " \t\n\v\f\r");
    opNumber = getOperandNum(token);

    while (token != NULL)
        token = strtok(NULL, ", ");
    if (getAddressingMode(token) == immediateAddress) {/* token = mov #-1,r2*/
        IC++;
    }

    if (getAddressingMode(token) == directAddress) {/*token = x: .data 23*/
        IC++;
    }

    if (getAddressingMode(token) == directRegisterAddress) {/*token = mov r1,r2*/
        strcpy(temp, &token[2]);/*copy substring to check if substring is register as well*/
        if (getRegisterName(temp)) {
            IC++;
        } else {
            IC += 2;
        }
    }

    if (getAddressingMode(token) == addressAccess) {/*token = add #4, s.1*/
        IC += 2;
    }

    return 1;

}


struct inst
{
    const char *name;
    int(*doInstructions)(/*SymbolTable *, char */symbolTable table,char *line, int DC, int numberOfLine);
}

validInstructions(char *instruction)
{
    struct inst instructionFunc[] = {{".data", doData}, {".string", doString}, {".struct", doStruct}, {".entry",doEntry}, {".extern",doExtern}};
    int i = 0;

    for(i = 0; i < sizeof(instructionFunc)/sizeof(instructionFunc[0]); ++i)
    {
        if(strcmp(instructionFunc[i].name, instruction) == 0){
            instructionFunc[i].doInstructions(Symbol, line, DC, numberOfLine);
        }
    }
}



int crateSymbolTable(char* fileName){

    FILE *inputFile = NULL;
    char line[MAX_LINE_LENGTH] = {0};
    char *originalLine = NULL;
    char *firstWord = NULL;
    char *token = NULL;
    char *label = NULL;
    int i = 0;

    static int IC,DC;

    inputFile = openFile(fileName,"am","r");

    /* iterating through each line of the input file */
    fgets(line, MAX_LINE_LENGTH, inputFile); /* XYZ: .data 7, -57, +17, 9*/
    /* storing a copy of the line, since strtok will be changing it */
    strcpy(originalLine, line);
    /* token recives the first string*/
    firstWord = strtok(originalLine, " \t\n\v\f\r");/*XYZ:*/

        while (!feof(inputFile)) {

            if(foundEmptySentence(originalLine) || foundCommendSentence(originalLine)){/* if line is empty or commend continue to the next line*/
                continue;
            }

            if(validLabelName(firstWord)) {/* if firstWord is label XYZ: we cuting the colon(:) from it,*/
                label = cutColonFromLabel(originalLine,firstWord);
            }

            else if(getInstructionName(firstWord)) {
                validInstructions(firstWord);/*need to check all the type of sentence, and the function need to return the do instruction that we found in the line*/
                if(symbolHead((symbolTable *) label, DC) == NULL) {
                    crateTable(label, DC,DC);/*if we had label before instruction we crate the symbolTable for first time*/
                    symbolHead((symbolTable *) label, DC);
                } else{/*if symbolTable is not empty we only add new symbol to the table*/
                    symbolHead((symbolTable *) label, DC);

                }

            } else{/*if the firstword in line is not instruction its command*/
                doCommandSentence(originalLine,  IC);
                if(symbolHead((symbolTable *) label, DC) == NULL) {
                    crateTable(label, DC,DC);/*if we had label before instruction we crate the symbolTable for first time*/
                    symbolHead((symbolTable *) label, DC);
                } else{/*if symbolTable is not empty we only add new symbol to the table*/
                    symbolHead((symbolTable *) label, DC);
            }

            /* iterating through each line of the input file */
            fgets(line, MAX_LINE_LENGTH, inputFile); /*XYZ: .data 7, -57, +17, 9*/

            /* storing a copy of the line, since strtok will be changing it */
            strcpy(originalLine, line);
            /* token receives the next char in line*/
            token = strtok(NULL," ,");

            }
        }




