#include <stdio.h>
#include <string.h>
#include "AssemblySentence.h"
#include "SymbolTable.h"
#include "AddressingMode.h"
#include "Utility/GeneralFunctions.h"
#include "OperationTable.h"



int foundEmptySentence(char* line){
    int i = 0;

    if(line == NULL){
        return 1;
    }
    for(i = 0; i < strlen(line); i++){
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != EOF) return 0;
    }
    return 1;
}



int foundCommentSentence(char* line){
    return line[0] == ';';
}


int doData(symbolTable* table,char *command, int *DC,int numberOfLine,symbolTable symbol)
{
    char *token = NULL;

    if (symbol != NULL) {
        setAddress(symbol,*DC);
        setType(symbol, DATA_SYMBOL);
    }

    while ((token = strtok(NULL, " \t\n\v\f\r,")) != NULL)
    {

        if (isNumber(token))
        {
            (*DC)++;
        }
        else
        {
            throwError("Found an invalid number in .data instruction!", numberOfLine);
            return 1;
        }
    }
    return 0;
}

int doString(symbolTable* table, char *command, int *DC, int numberOfLine, symbolTable symbol)
{
    int i = 0;
    int string_length = 0;
    int found_valid_string = 0;
    char *token = NULL;

    token = strtok(NULL," \t\n\v\f\r");
    if(token == NULL){
        throwError("Invalid definition of a string!", numberOfLine);
        return 1;
    }
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
        token = strtok(NULL, ""); /* getting the remining string */
        *DC = *DC + string_length;

        if(!containsOnlyBlanks(token)){
            throwError("Found invalid text after string", numberOfLine);
            return 1;
        }
        return 0;
        
    }
    throwError("Found invalid text before string", numberOfLine);
    return 1;
}
int doStruct(symbolTable* table, char *command, int *DC, int numberOfLine, symbolTable symbol) {

    char *token = command;
     if (symbol != NULL) {
        setAddress(symbol,*DC);
        setType(symbol, STRUCT_SYMBOL);
    }

    token = strtok(NULL," \t\n\v\f\r,");
    
    if(token != NULL) {

        if (isNumber(token)) {
            (*DC)++;
        }else{
            throwError("Invalid number specified in .struct", numberOfLine);
            return 1;
        }

        return doString(table,token,DC,numberOfLine,NULL); /* returning wether its valid */

    }else{
        throwError(".struct got invalid amount of operands!", numberOfLine);
        return 1;
    }

    return 0;
}


int doEntry(symbolTable* table,char *command, int *DC,int numberOfLine,symbolTable symbol){
    char* label;
    label = strtok(NULL, " \t\n\v\f\r");
    if (label == NULL)
    {
        throwError("Found .entry without specifing a label", numberOfLine);
        return 1;
    }

    if(validLabelName(label)){
        return 0;
    }
    return 1;
}



int doExtern(symbolTable* table,char *command, int *DC,int numberOfLine, symbolTable symbol){

    char *label;
    char *token;
    if (symbol != NULL)
    { /* if its a declration like this: HELLO: .extern A, then we delete the symbol HELLO */
        shiftHead(table);
    }
    label = strtok(NULL, " \t\n\v\f\r");
    if (validLabelName(label))
    {
        InsertSymbolNode(table, label, *DC);
        setType(*table, EXTERNAL_SYMBOL);
        /*  *DC = *DC + 1; */
    }
    else
    {
        throwError("Found invalid Label in Extern instruction!", numberOfLine);
        return 1;
    }

    token = strtok(NULL, " \t\n\v\f\r,");
    if (token != NULL)
    {
        throwError("Found invalid Label after the first label in Extern instruction!", numberOfLine);
        return 1;
    }
    return 0;
}

int checkValidOperand(char* operand, int numberOfLine){
    int i = 0;
    if(operand == NULL || strlen(operand) == 0) {
        throwError("Missing operand", numberOfLine);
        return 0;
    }
    if(operand[0] == ','){
        throwError("Multiple consecutive commas found", numberOfLine);
        return 0;
    }
    for(i = 0; i < strlen(operand); i++){
        if(operand[i] == ','){
            throwError("Invalid amount of operands", numberOfLine);
            return 0;
        }
        if(operand[i] == ' ' || operand[i] == '\t'){
            throwError("Found invalid characters in the operand", numberOfLine);
            return 0;
        }
    }
    return 1;
}


int isValidCommandSentence(int operandNum, char* restOfLine , int numberOfLine, char* firstOperand, char* secondOperand){
    int i = 0, j = 0;
    if(operandNum == 0){
        if(containsOnlyBlanks(restOfLine)){
            return 1;
        }else{
            throwError("A none operands command has got extra text", numberOfLine);
            return 0;
        }
    }
    else if(operandNum == 1){
        removeSpacesAndTabs(restOfLine);
        for(i = 0; i < strlen(restOfLine); i++){
            firstOperand[i] = restOfLine[i];
        }
        return checkValidOperand(firstOperand, numberOfLine);
    }
    else{
        for(i = 0; i < strlen(restOfLine) && restOfLine[i] != ','; i++){
            firstOperand[i] = restOfLine[i];
        }
        
        removeSpacesAndTabs(firstOperand);
        
        if(i >= strlen(restOfLine)){ /* if we reached the end without finding a , */
            throwError("Missing operand", numberOfLine);
            return 0;
        }
        
        for(++i; i < strlen(restOfLine) - 1; i++){
            secondOperand[j] = restOfLine[i];
            j++;
        }
        removeSpacesAndTabs(secondOperand);
        return checkValidOperand(firstOperand, numberOfLine) && checkValidOperand(secondOperand, numberOfLine);

    }
}

int handleCommandSentence(int operandNum , int* IC, int numberOfLine, char* firstOperand, char* secondOperand){

    addressingMode prevOperand = immediateAddress;
    addressingMode curr = immediateAddress;

    if(operandNum == 1){
        curr = getAddressingMode(firstOperand, numberOfLine);
         if(curr == error){
            return 1;
        } 
        iCCounter(curr, prevOperand, IC);
    }else if(operandNum == 2){
        prevOperand = getAddressingMode(firstOperand, numberOfLine);
        curr = getAddressingMode(secondOperand, numberOfLine);
         if(curr == error || prevOperand == error){
            return 1;
        } 
        iCCounter(curr, 0, IC);
        iCCounter(curr, prevOperand, IC);
    }
    return 0;
}

int doCommandSentence(char *command, int *IC,int numberOfLine,symbolTable symbol) {
    int opNumber = 0;
    char* restOfFile;
    char firstOperand[MAX_LINE_LENGTH] = {0};
    char secondOperand[MAX_LINE_LENGTH] = {0};

    opNumber = getOperandNum(command);
    restOfFile = strtok(NULL, "");
    if(!isValidCommandSentence(opNumber, restOfFile, numberOfLine, firstOperand, secondOperand)){
        return 1;
    }
	return handleCommandSentence(opNumber, IC, numberOfLine, firstOperand, secondOperand);
  
}


struct inst
{
    const char *name;
    int(*doInstructions)(/*SymbolTable *, char */symbolTable* table,char *line, int *DC, int numberOfLine,symbolTable symbol);
};

int validInstructions(symbolTable* table,char *instruction,int *DC, int numberOfLine,symbolTable symbol)
{
    struct inst instructionFunc[] = {{".data", doData}, {".string", doString}, {".struct", doStruct}, {".entry",doEntry}, {".extern",doExtern}};
    int i = 0;
    int isError = 0;

    
    for(i = 0; i < sizeof(instructionFunc)/sizeof(instructionFunc[0]); ++i)
    {
        if(strcmp(instructionFunc[i].name, instruction) == 0){
            
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



    
symbolTable createSymbolTable(char* fileName, flags* status) {

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
    if (inputFile == NULL){
        throwError("Could't open input file!", numberOfLine);
        status ->error = 1;
        return NULL;
    }
    printf("Started first phase on the file: %s...\n",  fileName);

    while (!feof(inputFile)) {

        /* iterating through each line of the input file */
        fgets(line, MAX_LINE_LENGTH, inputFile); /* MAIN:    mov    S1.1 ,LENGTH*/
       

        numberOfLine++;
        /* storing a copy of the line, since strtok will be changing it */
        /* subString recives the first string*/
        firstWord = strtok(line, " \t\n\v\f\r");/*XYZ:*/

        if (foundEmptySentence(line) || foundCommentSentence(line)) {/* if line is empty or commend continue to the next line*/
            continue;
        }

        if (isLabel(firstWord)) {/* if subString is label XYZ: we cuting the colon(:) from it,*/
        	

            label = cutColonFromLabel(line, firstWord);
            InsertSymbolNode(&table, label, IC);
            symbol = table;
            firstWord = strtok(NULL, " \t\n\v\f\r");
        }

        if (firstCharIsDot(firstWord)) {
            if(strcmp(firstWord, ".entry") == 0) {
                status ->foundEntry = 1;
            }
            status ->foundEntry |= strcmp(firstWord, ".entry") == 0;
            status ->foundExtern |= strcmp(firstWord, ".extern") == 0;
            status ->instructionError = validInstructions(&table, firstWord, &DC, numberOfLine, symbol);
            if(status ->instructionError){
                status ->error = 1;
                continue;
            }
        } else {
            if(isOperationName(firstWord)){
            status ->error  |= doCommandSentence(firstWord, &IC, numberOfLine, symbol); /* if it returned 1 (error), than errorFlag will be changed */
        }else{
                throwError("Invalid InstructionName", numberOfLine);
                status ->error = 1;
            
            }
        }
        symbol = NULL;
    }
    printf("\n\nerror flag is: %d\n", status ->error );
    
    updateTable(table,IC);
    printSymbol(table);
    status->finalIC = IC;
    status->finalDC = DC;
    fclose(inputFile);
    if(status ->error ){
        freeTable(table);
        free(status);
        return NULL;
    }
    return table;
}
