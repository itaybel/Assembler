#include <stdio.h>
#include <string.h>
#include "AssemblySentence.h"
#include "SymbolTable.h"
#include "AddressingMode.h"
#include "Utility/GeneralFunctions.h"
#include "OperationTable.h"
#include "PreAssembler/MacroTable.h"


int foundEmptySentence(char* line){
    int i = 0;

    if(line == NULL){
        return 1;
    }
    for(i = 0; i < strlen(line); i++){
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n') return 0;
    }
    return 1;
}




int foundCommendSentence(char* line){
    char *semicolon = NULL;
    semicolon = ";";

    if(strcmp(semicolon,line) == 0){
        return 1;
    }
    return 0;
}




int doData(symbolTable table,char *command, int *DC,int numberOfLine,symbolTable symbol)
{
    char *token = NULL;

    if (symbol != NULL) {
        setAddress(symbol,*DC);
        setType(symbol, DATA_SYMBOL);
    }
    while((token = strtok(NULL," \t\n\v\f\r,")) != NULL)
    {

        if(isNumber(token)){
            (*DC)++;
        }
    }



    return 0;
}


int doString(symbolTable table, char *command, int *DC, int numberOfLine, symbolTable symbol)
{
    int i = 0;
    int string_length = 0;
    int found_valid_string = 0;
    char *token = NULL;
    token = strtok(NULL," \t\n\v\f\r,");
    if (symbol != NULL) {
        setAddress(symbol,*DC);
        setType(symbol, DATA_SYMBOL);
    }
    while (token[i] != '\n' && token[i] != '\0' && !found_valid_string)
    {
        /*if (token[i] == '\t' && token[i] == ' ')
        {
            throwError("Found invalid text before string", numberOfLine);
            return 1;
        }*/

        if (token[i] == '\"')
        {
            while (token[i] != '\n' && token[i] != '\0' && !found_valid_string)
            {

                string_length++;
                i++;
                if (token[i] == '\"')
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
    throwError("Found invalid text before string", numberOfLine);
    return 1;
}

int doStruct(symbolTable table, char *command, int *DC, int numberOfLine, symbolTable symbol)
{
    int i = 0;
    /*int ret = 0;*/
    int string_length = 0;
    int found_valid_string = 0;
    char *curr_line = command;
    /*todo need to fix this function*/
    /*ret = strtol(command, &curr_line, 10);*/
    if (strcmp(curr_line, command) == 0)
    { /* this means that it couldn't convert any number */
        throwError("Couldn't parse the number!\n", numberOfLine);
        return 1;
    }
    if (curr_line[0] != ',')
    {
        throwError("Couldn't find an ',' after a number!", numberOfLine);
        return 1;
    }
    curr_line++; /* shifting the , at the begining */

    while (command[i] != '\n' && command[i] != '\0' && !found_valid_string)
    {
        if (command[i] != '\t' && command[i] != ' ')
        {
            throwError("Found invalid text after ','", numberOfLine);
            return 1;
        }
        if (command[i] == '"')
        {
            while (command[i] != '\n' && command[i] != '\0' && !found_valid_string)
            {

                string_length++;
                i++;
                if (command[i] == '\"')
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
        if (symbol != NULL) {
            setType(symbol, STRUCT_SYMBOL);
        }
        return 0;
    }
    return 1;
}


int doEntry(symbolTable table,char *label, int *DC,int numberOfLine,symbolTable symbol){
    if(validLabelName(label)){
        return 1;
    }
    return 0;
}


int doExtern(symbolTable table,char *label, int *DC,int numberOfLine, symbolTable symbol){
    char *token = NULL;
    /*need to check if after the extern we dont have label*/
    if(validLabelName(label)){
        InsertSymbolNode(&table, label,*DC);
        setType(symbol,EXTERNAL_SYMBOL);
        return 1;
    }
    return 0;
}



int doCommandSentence(char *command, int *IC,int numberOfLine,symbolTable symbol) {
    int opNumber = 0;
    int i = 0;
    char *nextWord = NULL;
    addressingMode prevOperand = immediateAddress;
    addressingMode curr = immediateAddress;

    opNumber = getOperandNum(command);

    for (i = 0; i < opNumber && command != NULL; i++) {
        nextWord = strtok(NULL, " \t\n\v\f\r,");
        printf("the operand we found in the line is: %s\n", nextWord);
        curr = getAddressingMode(nextWord, numberOfLine);
        /*todo: need to check if the addressing mode we get is valid(destination and source operand)*/
        iCCounter(curr, prevOperand, IC);
        printf("and his addressMode is: %d\n", curr);
        printf("and after adding the value of the addressingMode to the value of IC now we have IC: %d\n", *IC);
        prevOperand = curr;

    }

    /* todo: need to check if we dont have to many perimeters and we need to print error if we have less then we expected,
     * todo: and we need to continue to the next line*/


    return 1;
}


struct inst
{
    const char *name;
    int(*doInstructions)(symbolTable table,char *line, int *DC, int numberOfLine,symbolTable symbol);
};

void validInstructions(symbolTable table,char *instruction,int *DC, int numberOfLine,symbolTable symbol)
{
    struct inst instructionFunc[] = {{".data", doData}, {".string", doString}, {".struct", doStruct}, {".entry",doEntry}, {".extern",doExtern}};
    int i = 0;



    for(i = 0; i < sizeof(instructionFunc)/sizeof(instructionFunc[0]); ++i)
    {
        if(strcmp(instructionFunc[i].name, instruction) == 0){
            /*instruction = strtok(NULL," ");*/
            instructionFunc[i].doInstructions(table, instruction, DC, numberOfLine,symbol);
        }

    }
}

void iCCounter(addressingMode address,addressingMode prevAddress, int *IC){

    if (address == immediateAddress) {
        (*IC)++;
    }

    if (address == directAddress) {/*firstWord = x: .data 23*/
        (*IC)++;
    }

    if(address == directRegisterAddress && prevAddress != directRegisterAddress){
        (*IC)++;

    }

    if (address== addressAccess) {/*firstWord = add #4, s.1,*/
        (*IC) += 2;
    }


}


symbolTable createSymbolTable(char* fileName) {

    FILE *inputFile = NULL;
    char line[MAX_LINE_LENGTH] = {0};
    char *firstWord = NULL;
    char *label = NULL;
    symbolTable symbol = NULL;
    int numberOfLine = 0;
    symbolTable table = NULL;
    int IC = 100;
    int DC = 0;

    inputFile = openFile(fileName, "am", "r");



    while (!feof(inputFile)) {

        /* iterating through each line of the input file */
        fgets(line, MAX_LINE_LENGTH, inputFile); /* MAIN:    mov    S1.1 ,LENGTH*/
        numberOfLine++;
        /* storing a copy of the line, since strtok will be changing it */
        /* subString recives the first string*/
        firstWord = strtok(line, " \t\n\v\f\r");/*XYZ:*/

        if (foundEmptySentence(firstWord) || foundCommendSentence(firstWord)) {/* if line is empty or commend continue to the next line*/
            continue;
        }

        if (isLabel(firstWord)) {/* if subString is label XYZ: we cuting the colon(:) from it,*/


            label = cutColonFromLabel(line, firstWord);/*MAIN:*/
            InsertSymbolNode(&table, label, IC);
            symbol = table;
            firstWord = strtok(NULL, " \t\n\v\f\r,");
        }

        if (firstCharIsDot(firstWord)) {
            validInstructions(table, firstWord, &DC, numberOfLine, symbol);
        } else {
            if(isOperationName(firstWord)){
                doCommandSentence(firstWord, &IC, numberOfLine, symbol);
            }else{
                throwError("Invalid InstructionName", numberOfLine);
                freeTable(table);
                return NULL;
            }
        }


    }
    printSymbol(table);
    updateTable(table,IC);

    fclose(inputFile);
    return table;
}



