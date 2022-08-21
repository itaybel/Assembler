#include <stdio.h>
#include <string.h>
#include "AssemblySentence.h"
#include "SymbolTable.h"
#include "AddressingMode.h"
#include "Utility/GeneralFunctions.h"
#include "OperationTable.h"


int checkFirstCharacter(char* line, char c){

    char lineCopy[MAX_LINE_LENGTH] = {0};
    strcpy(lineCopy, line);
    removeSpacesAndTabs(lineCopy);

    return lineCopy[0] == c;
}

void fixDataInstruction(char *line, char parsedLine[MAX_LINE_LENGTH * 2])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < strlen(line); i++)
    {
        parsedLine[j] = line[i];
        if (line[i] == ',') /* if we found a comma, we add a space right after it */
        {

            parsedLine[j + 1] = ' ';
            j++;
        }

        j++;
    }
}

int doData(symbolTable* table, char *line, int *DC, int numberOfLine, symbolTable symbol)
{
    char *restOfLine = NULL;
    int foundNumbers = 0;
    char parsedLine[MAX_LINE_LENGTH * 2] = {0};
    char *nextNumber = NULL;
    restOfLine = strtok(NULL, "");
    if (symbol != NULL) {
        setAddress(symbol,*DC);
        setType(symbol, DATA_SYMBOL);
    }else{

    }

    if(foundEmptySentence(restOfLine)){
        throwError("Missing numbers in .data instruction", numberOfLine);
        return 0;
    }
    if(checkFirstCharacter(restOfLine, ',')){
        throwError("Invalid ',' at the beginning of .data instruction", numberOfLine);
        return 0;
    }
    fixDataInstruction(restOfLine, parsedLine); /* adding spaces after commas, so we can catch comma errors */
    nextNumber = strtok(parsedLine, ",");

    while (nextNumber != NULL)
    {

        foundNumbers = 1;
        if (foundEmptySentence(nextNumber))
        {
            throwError("Invalid commas found in .data instruction!", numberOfLine);
            return 0;

        }else if (isNumber(nextNumber))
        {
            (*DC)++;
        }else
        {
            throwError("Found an invalid number in .data instruction!", numberOfLine);
            return 0;
        }
        nextNumber = strtok(NULL, ",");
    }
    if (!foundNumbers)
    {
        throwError("found a .data instruction without any numbers", numberOfLine);
    }
    return foundNumbers;
}

int doString(symbolTable* table, char *line, int *DC, int numberOfLine, symbolTable symbol)
{
    int i = 0;
    int string_length = 0;
    int found_valid_string = 0;
    char* restOfLine = NULL;

    restOfLine = strtok(NULL, "");
    if(restOfLine == NULL || strlen(restOfLine) == 0){
        throwError("Missing string", numberOfLine);
        return 0;
    }
    removeSpacesAndTabs(restOfLine);
    if (symbol != NULL) {
        setAddress(symbol,*DC);
        setType(symbol, DATA_SYMBOL);
    }
    if(restOfLine == NULL || foundEmptySentence(restOfLine)){
        throwError("Invalid definition of a string!", numberOfLine);
        return 0;
    }

    while (restOfLine[i] != '\n' && restOfLine[i] != '\0' && !found_valid_string)
    {

        if (restOfLine[i] == '\"')
        {
            while (restOfLine[i] != '\n' && restOfLine[i] != '\0' && !found_valid_string)
            {

                string_length++;
                i++;
                if (restOfLine[i] == '\"')
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

        if(i != strlen(restOfLine)){
            throwError("Found invalid text after string", numberOfLine);
            return 0;
        }
        return 1;
    }
    throwError("Found invalid string", numberOfLine);
    return 0;
}
int doStruct(symbolTable* table, char *line, int *DC, int numberOfLine, symbolTable symbol) {

    char *token = line;
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
            return 0;
        }

        return doString(table,token,DC,numberOfLine,NULL); /* returning weather its valid */

    }else{
        throwError(".struct got invalid amount of operands!", numberOfLine);
        return 0;
    }
}

int doEntry(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol){
    char* label;
    label = strtok(NULL, " \t\n\v\f\r");
    if(symbol != NULL){
        throwError("Found a new symbol declaration before .entry!", numberOfLine);
        return 0;
    }
    if (label == NULL)
    {
        throwError("Found .entry without specifying a label", numberOfLine);
        return 0;
    }

    if(validLabelName(label)){
        return 1;
    }
    return 0;
}


int doExtern(symbolTable* table,char *line, int *DC,int numberOfLine, symbolTable symbol){

    char *label;
    char *token;
    if (symbol != NULL)
    { /* if it's a declaration like this: HELLO: .extern A, then we delete the symbol HELLO */
        throwWarning("found an extern instruction with a symbol declared to it. new symbol got deleted.",  numberOfLine);
        shiftHead(table);
    }
    label = strtok(NULL, " \t\n\v\f\r");
    if(label == NULL){
        throwError("Found an extern instruction without any label!", numberOfLine);
        return 0;
    }

    if (validLabelName(label))
    {
        if(findInTable(*table, label) != NULL){
            throwError("Found multiple definition of the same symbol", numberOfLine);
            return 0;
        }
        InsertSymbolNode(table, label, *DC);
        setType(*table, EXTERNAL_SYMBOL);
        /*  *DC = *DC + 1; */
    }
    else
    {
        throwError("Found invalid Label in Extern instruction!", numberOfLine);
        return 0;
    }
    token = strtok(NULL, " \t\n\v\f\r,");
    if (token != NULL)
    {
        throwError("Found invalid Label after the first label in Extern instruction!", numberOfLine);
        return 0;
    }
    return 1;
}

int checkValidOperand(char* operand , int numberOfLine){
    int i = 0;
    if(operand == NULL || strlen(operand) == 0) { /* if its empty */
        throwError("Missing operand", numberOfLine);
        return 0;
    }
    if(operand[0] == ','){ /* if it starts with a comma, it means that there was a comma before, which means the line contains 2 commas */
        throwError("Multiple consecutive commas found", numberOfLine);
        return 0;
    }
    for(i = 0; i < strlen(operand); i++){
        if(operand[i] == ','){ /* if it found extra commas in the operand , we got invalid amount of operands (since we are only looking for 1 comma at a line)*/
            throwError("Invalid amount of operands", numberOfLine);
            return 0;
        }
        if(operand[i] == ' ' || operand[i] == '\t'){ /* if it found blanks in an operand*/
            throwError("Found invalid characters in the operand", numberOfLine);
            return 0;
        }
    }
    return 1;
}


int isValidCommandSentence(int operandNum, char* restOfLine , int numberOfLine, char* firstOperand, char* secondOperand){
    int i = 0, j = 0;
    if(operandNum == 0){ /* if the command doesn't require any operands */
        if(foundEmptySentence(restOfLine)){
            return 1;
        }else{
            throwError("none operands command has got extra text", numberOfLine);
            return 0;
        }
    }
    else if(operandNum == 1){ /* if the command require one operand */
        removeSpacesAndTabs(restOfLine);
        for(i = 0; i < strlen(restOfLine); i++){ /* we fill the string with all the characters until the first comma */
            firstOperand[i] = restOfLine[i];
        }
        return checkValidOperand(firstOperand, numberOfLine);
    }
    else{ /* if the command require two operands */
        for(i = 0; i < strlen(restOfLine) && restOfLine[i] != ','; i++){ /* we fill the string with all the characters until the first comma */
            firstOperand[i] = restOfLine[i];
        }

        removeSpacesAndTabs(firstOperand);

        if(i >= strlen(restOfLine)){ /* if we reached the end without finding a , */
            throwError("Missing operand", numberOfLine);
            return 0;
        }

        for(++i; i < strlen(restOfLine) - 1; i++){ /* we fill the string with all the characters from the first comma to the end*/
            secondOperand[j] = restOfLine[i];
            j++;
        }
        removeSpacesAndTabs(secondOperand);
        return checkValidOperand(firstOperand, numberOfLine) && checkValidOperand(secondOperand, numberOfLine);

    }
}

int UpdateICforCommandSentence(char* command, int operandNum , int* IC, int numberOfLine, char* firstOperand, char* secondOperand){

    addressingMode prevOperand = immediateAddress;
    addressingMode curr = immediateAddress;

    if(operandNum == 1){
        curr = getAddressingMode(firstOperand, numberOfLine);
        if(curr == error){
            return 1;
        }
        if(!(getDestinationOperand(command) & (1 << curr))){ /* if the bit at position curr is off */
            throwError("Invalid addressing mode for destination operand", numberOfLine);
            return 1;
        }
        iCCounter(curr, prevOperand, IC);
    }else if(operandNum == 2){
        prevOperand = getAddressingMode(firstOperand, numberOfLine);
        curr = getAddressingMode(secondOperand, numberOfLine);
        if(curr == error || prevOperand == error){
            return 1;
        }
        if(!(getSourceOperand(command) & (1 << curr))){ /* if the bit at position curr is off */
            throwError("Invalid addressing mode for source operand", numberOfLine);
            return 1;
        }

        iCCounter(prevOperand, 0, IC);/* zero is just a default addressing node, to specify we don't have a previous operand */
        if(!(getDestinationOperand(command) & (1 << curr))){
            throwError("Invalid addressing mode for destination operand", numberOfLine);
            return 1;
        }
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
    if(restOfFile != NULL && !isValidCommandSentence(opNumber, restOfFile, numberOfLine, firstOperand, secondOperand)){
        return 1;
    }
    return UpdateICforCommandSentence(command, opNumber, IC, numberOfLine, firstOperand, secondOperand);

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

            if(!strcmp(instruction, ".entry") && !(strcmp(instruction, ".extern"))){
                if(symbol == NULL){
                    throwWarning("found an instruction without any label declared to it",  numberOfLine);
                }
            }
            isError = instructionFunc[i].doInstructions(table, instruction, DC, numberOfLine,symbol);
            return isError;

        }

    }
    throwError("Invalid instruction found", numberOfLine);
    return 0;
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

symbolTable handleLabelDefinition(symbolTable* table,  char* labelName, flags* status, int IC, int numberOfLine){
    symbolTable symbol = NULL;
    if(validLabelName(labelName)){
        cutColonFromLabel(labelName);
        if(findInTable(*table, labelName) != NULL){
            throwError("Found multiple definition of the same label", numberOfLine);
            status->error = 1;
        }
        if(reservedWord(labelName)){
            throwError("label can't be a reserved word", numberOfLine);
            status->error = 1;
        }
        InsertSymbolNode(table, labelName, IC);
        setType(*table,CODE_SYMBOL);
        symbol = *table;

    }else{
        PRINT_RED();
        printf("Error occurred at line %d: Invalid label name: '%s'\n", numberOfLine, labelName);
        CLEAR_COLOR();
        status->error = 1;
    }
    return symbol;
}


symbolTable createSymbolTable(char* fileName, flags* status) {

    FILE *inputFile = NULL;
    char line[MAX_LINE_LENGTH] = {0};
    char *firstWord = NULL;
    symbolTable symbol = NULL;
    int numberOfLine = 0;
    symbolTable table = NULL;
    int IC = 100;
    int DC = 0;

    inputFile = openFile(fileName, "am", "r");
    if (inputFile == NULL){
        throwError("Couldn't open input file!", numberOfLine);
        status ->error = 1;
        return NULL;
    }
    PRINT_WHITE();
    printf("Started first iteration on the file: %s...\n",  fileName);
    CLEAR_COLOR();

    while (!feof(inputFile)) {

        symbol = NULL;
        memset(line, 0, MAX_LINE_LENGTH);
        /* iterating through each line of the input file */
        fgets(line, MAX_LINE_LENGTH, inputFile); 
        numberOfLine++;
        if (foundEmptySentence(line) || checkFirstCharacter(line, ';')) {/* if line is empty or comment continue to the next line*/
            continue;
        }
        /* subString receives the first string*/
        firstWord = strtok(line, " \t\n\v\f\r");

        if (isLabel(firstWord)) {/* if subString is label XYZ: we're cutting the colon(:) from it,*/
            symbol = handleLabelDefinition(&table, firstWord, status, IC, numberOfLine);
            firstWord = strtok(NULL, " \t\n\v\f\r");

            if(firstWord == NULL || foundEmptySentence(firstWord)){
                throwError("Found an empty label declaration", numberOfLine);
                status->error = 1;
                continue;
            }
            
        }

        if (firstCharIsDot(firstWord)) {
            if(strcmp(firstWord, ".entry") == 0) status ->foundEntry = 1;
            if(strcmp(firstWord, ".extern") == 0) status->foundExtern = 1;

            if(!validInstructions(&table, firstWord, &DC, numberOfLine, symbol)) status->error = 1;

        } else {
            if(isOperationName(firstWord)){
                IC++;
                /* if it occurred an error */
                if(doCommandSentence(firstWord, &IC, numberOfLine, symbol)){
                    status ->error = 1;
                }

            }else{
                PRINT_RED();
                printf("Error occurred at line %d: Invalid command: '%s'\n", numberOfLine, firstWord);
                CLEAR_COLOR();
                status ->error = 1;
            }
        }

    }

    updateDataSymbols(table,IC);
    status->finalIC = IC;
    status->finalDC = DC;
    fclose(inputFile);
    if(status ->error ){
        PRINT_RED();
        printf("First iteration on file: %s.am failed!\n", fileName);
        CLEAR_COLOR();
        freeTable(table);
        return NULL;
    }
    PRINT_GREEN();
    printf("Finished first iteration on file: %s.am!\n", fileName);
    CLEAR_COLOR();
    return table;
}
