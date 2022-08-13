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

    while((token = strtok(NULL," \t\n\v\f\r,")) != NULL) {

        if (isNumber(token)) {
            (*DC)++;
        } else {
            if(strcmp(command,".struct") == 0) {
                return 1;
            }else
                throwError("Found an invalid number in .data instruction!", numberOfLine);
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

        return 1;
    }
    throwError("Found invalid text before string", numberOfLine);
    return 0;
}


int doStruct(symbolTable table, char *command, int *DC, int numberOfLine, symbolTable symbol) {

    char *token = command;

    while((token = strtok(NULL," \t\n\v\f\r,")) != NULL) {

        if (isNumber(token)) {
            (*DC)++;
    }
        if(doString(table,token,DC,numberOfLine,NULL)){
                if (symbol != NULL) {
                    setAddress(symbol,*DC);
                    setType(symbol, STRUCT_SYMBOL);
                }
                return 1;
            }

            }

    return 0;
}


int doStruct(symbolTable table, char *command, int *DC, int numberOfLine, symbolTable symbol) {

    char *token = command;

    while((token = strtok(NULL," \t\n\v\f\r,")) != NULL) {

        if (isNumber(token)) {
            (*DC)++;
    }else {
            if(doString(table,token,DC,numberOfLine,NULL)){
                if (symbol != NULL) {
                    setAddress(symbol,*DC);
                    setType(symbol, STRUCT_SYMBOL);
                }
                return 1;
            }

            }
        }

    return 0;
}

int doEntry(symbolTable table,char *label, int *DC,int numberOfLine,symbolTable symbol){
    if(validLabelName(label)){
        return 1;
    }
    return 0;
}


int doExtern(symbolTable table,char *label, int *DC,int numberOfLine, symbolTable symbol){

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
        if(nextWord == NULL){
            throwError("Invalid amount of operands!",numberOfLine);
            return 1;
        }
	    printf("the operand we found in the line is: %s\n", nextWord);
        curr = getAddressingMode(nextWord, numberOfLine);
        iCCounter(curr, prevOperand, IC);
        printf("and his addressMode is: %d\n", curr);
        printf("and after adding the value of the addressingMode to the value of IC now we have IC: %d\n", *IC);
        prevOperand = curr;
        
    }
    if(strtok(NULL, " \t\n\v\f\r,") != NULL){
        throwError("Invalid amount of operands!", numberOfLine);
        return 1;
    }
     /* todo: and we need to continue to the next line*/
    return 0;
}


struct inst
{
    const char *name;
    int(*doInstructions)(/*SymbolTable *, char */symbolTable table,char *line, int *DC, int numberOfLine,symbolTable symbol);
};

int validInstructions(symbolTable table,char *instruction,int *DC, int numberOfLine,symbolTable symbol)
{
    struct inst instructionFunc[] = {{".data", doData}, {".string", doString}, {".struct", doStruct}, {".entry",doEntry}, {".extern",doExtern}};
    int i = 0;
    int isError = 0;


    for(i = 0; i < sizeof(instructionFunc)/sizeof(instructionFunc[0]); ++i)
    {
        if(strcmp(instructionFunc[i].name, instruction) == 0){
            /* instruction = strtok(NULL," "); */
            isError = instructionFunc[i].doInstructions(table, instruction, DC, numberOfLine,symbol);
            return isError;
        }

    }
    throwError("Invalid instruction found", numberOfLine);
    return 1;
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
    int errorFlag = 0;
    int instructionErrorFlag = 0;
    inputFile = openFile(fileName, "am", "r");
    
    printf("Started first phase on the file: %s...\n",  fileName);

    while (!feof(inputFile)) {

        /* iterating through each line of the input file */
        fgets(line, MAX_LINE_LENGTH, inputFile); /* MAIN:    mov    S1.1 ,LENGTH*/
        numberOfLine++;
        /* storing a copy of the line, since strtok will be changing it */
        /* subString recives the first string*/
        firstWord = strtok(line, " \t\n\v\f\r");/*XYZ:*/

        if (foundEmptySentence(line) || foundCommendSentence(line)) {/* if line is empty or commend continue to the next line*/
            continue;
        }

        if (isLabel(firstWord)) {/* if subString is label XYZ: we cuting the colon(:) from it,*/
        	

            label = cutColonFromLabel(line, firstWord);
            InsertSymbolNode(&table, label, IC);
            symbol = table;
            firstWord = strtok(NULL, " \t\n\v\f\r,");
        }

        if (firstCharIsDot(firstWord)) {
            instructionErrorFlag = validInstructions(table, firstWord, &DC, numberOfLine, symbol);
            if(instructionErrorFlag){
                errorFlag = 1;
                continue;
            }
        } else {
            if(isOperationName(firstWord)){
            printf("after cuting the symbol we found the operation: %s\n", firstWord);
            errorFlag |= doCommandSentence(firstWord, &IC, numberOfLine, symbol); /* if it returned 1 (error), than errorFlag will be changed */
        }else{
                throwError("Invalid InstructionName", numberOfLine);
                errorFlag = 1;
            
            }
        }


    }
    printf("\n\nerror flag is: %d\n", errorFlag);
    printSymbol(table);
   /*  updateTable(table,IC); */
    fclose(inputFile);
    if(errorFlag){
        freeTable(table);
        return NULL;
    }
    return table;
}



