#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SecondPass.h"
#include "Utility/GeneralFunctions.h"
#include "RegisterTable.h"
#include "OperationTable.h"
#include "SymbolTable.h"

void writeToFile(char* content, FILE* file, int IC){
    char base32Address[2] = {0};
    toBase32(IC, base32Address);
   
    fprintf(file, "%.2s\t%.2s\n", base32Address, content);
    
}

void toBase32(int num, char* base)
{
    const char base32chars[] = "!@#$%^&*<>abcdefghijklmnopqrstuv";
    unsigned int leftGroup = 0;
    unsigned int rightGroup = 0;
    
    leftGroup =  (num & (((1 << 5) - 1) << 5)); /* we will bitwise and the number and the mask: 1111100000 */
    leftGroup >>= 5; /* shifting it back to be in the first 5 bits */
    rightGroup = (num & ((1 << 5) - 1)); /* reseting any bits except the 5 at the right, and then m*/

    base[0] = base32chars[leftGroup];
    base[1] = base32chars[rightGroup];
}


void encodeData(symbolTable table , int* IC, int numberOfLine, FILE* outFile){
    char* nextNumber = NULL;
    char inBase32[2] = {0};
    int number = 0;


    while((nextNumber = strtok(NULL," \t\n\v\f\r,")) != NULL) {

        *IC = *IC + 1;
        convertToNumber(nextNumber, &number);
        toBase32(number, inBase32);
        writeToFile(inBase32, outFile, *IC);
        
    }
}

void encodeString(symbolTable table , int* IC, int numberOfLine, FILE* outFile)
{

    int i = 0;
    int string_length = 0;
    int found_valid_string = 0;
    char *token = NULL;
    char inBase32[2] = {0};
    token = strtok(NULL," \t\n\v\f\r "); /* getting the string */
    while (token[i] != '\n' && token[i] != '\0' && !found_valid_string)
    {

        if (token[i] == '\"')
        {
            i++;
            while (token[i] != '\n' && token[i] != '\0' && !found_valid_string)
            {
                toBase32(token[i], inBase32);
                *IC = *IC + 1;
                writeToFile(inBase32, outFile, *IC);
                string_length++;
                i++;
                if (token[i] == '\"')
                {
                    *IC = *IC + 1;
                    writeToFile("!!", outFile, *IC); /* "!!" represents NULL escape character */
                    found_valid_string = 1;
                }
            }
        }
        i++;
    }
}


void encodeStruct(symbolTable table, int* IC, int numberOfLine, FILE* outFile)
{
    int number = 0;
    char* token = NULL;
    char inBase32[2] = {0};

    token = strtok(NULL," \t\n\v\f\r,");
    
    if(isNumber(token)){
        *IC = *IC + 1;
        convertToNumber(token, &number);
        toBase32(number, inBase32);
        writeToFile(inBase32, outFile, *IC);
    }
    
    encodeString(table, IC, numberOfLine, outFile);
   
}


int handleEntryAndExtern(char* firstWord, symbolTable table, int numberOfLine, FILE* entFile , flags* status){
    symbolTable symbol = NULL;
    char* token = NULL;
    char inBase32[2] = {0};
    if(!strcmp(firstWord, ".entry")){
       
        token = strtok(NULL, " \t\n\v\f\r ");
        if((symbol = findInTable(table, token)) == NULL){
            throwError("Found an entry declaration of an undefined label", numberOfLine);
            status->error = 1;
        }else if(getType(symbol) == EXTERNAL_SYMBOL){
            throwError("Found an entry declaration of an extern label", numberOfLine);
            status->error = 1;
        }
        else{
            toBase32(getAddress(symbol) , inBase32);
            fprintf(entFile, "%s\t%.2s\n", getSymbolName(symbol),inBase32);
        }
        return 1;
    }

    if(!strcmp(firstWord, ".extern")){
        token = strtok(NULL, " \t\n\v\f\r ");
        
        if((symbol = findInTable(table, token)) != NULL && getType(symbol) != EXTERNAL_SYMBOL){ /* if it found a symbol with that name which is not extern */
            throwError("Found an extern declaration of a declared label", numberOfLine);
            status->error = 1;
        }
        return 1;
    }
    
    return 0;
}




struct encodeInst
{
    const char *name;
    void(*encodeInstructions)(symbolTable table, int *IC, int numberOfLine, FILE* outFile);
};


void handleInstructions(symbolTable table, char *instruction, int *IC, int numberOfLine, FILE* outFile){
    struct encodeInst instructionFunc[] = {{".data", encodeData}, {".string", encodeString}, {".struct", encodeStruct}};
    int i = 0;

    for(i = 0; i < sizeof(instructionFunc)/sizeof(instructionFunc[0]); ++i)
    {
        if(strcmp(instructionFunc[i].name, instruction) == 0){
            instructionFunc[i].encodeInstructions(table, IC, numberOfLine, outFile);
        }

    }
}

int encodeNoneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile) {
    char inBase32[2] = {0};
    *IC = *IC + 1;
    toBase32(getOperationOpcode(command) << 6, inBase32);
    writeToFile(inBase32, outFile, *IC);
    return 0;
}   

int encodeOneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile, FILE* extFile) {
    char inBase32[2] = {0};
    int opCode = 0;
    char* operand = NULL;
    addressingMode operandMode = 0;
    opCode = getOperationOpcode(command);
    operand = strtok(NULL, " \t\n\v\f\r ");
    operandMode = getAddressingMode(operand, numberOfLine);
    
    *IC = *IC + 1;

    toBase32(opCode << 6 | operandMode << 2, inBase32);

    writeToFile(inBase32, outFile, *IC);
    
    return handleAddressingAccesses(operandMode, table, TRUE,  operand, IC,  numberOfLine, outFile, extFile);
}   


int encodeTwoOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile, FILE* extFile) {
    char inBase32[2] = {0};
    int opCode = 0;
    char* operand1 = NULL;
    char* operand2 = NULL;
    addressingMode operand1Mode = 0;
    addressingMode operand2Mode = 0;

    opCode = getOperationOpcode(command);
    operand1 = strtok(NULL, " \t\n\v\f\r,");
  
    operand1Mode = getAddressingMode(operand1, numberOfLine);
   
    operand2 = strtok(NULL, " \t\n\v\f\r,");
   
    operand2Mode = getAddressingMode(operand2, numberOfLine);
   
    *IC = *IC + 1;
    toBase32(opCode << 6 | operand1Mode << 4 | operand2Mode << 2, inBase32);
    writeToFile(inBase32, outFile, *IC);

    /* we handle this case seperetly */
    if(operand1Mode == directRegisterAddress && operand2Mode == directRegisterAddress){
        *IC = *IC + 1;
        toBase32(getRegisterNum(operand1) << 6 | getRegisterNum(operand2) << 2, inBase32);
        writeToFile(inBase32, outFile, *IC);
        return 0;
    }
    /* if one of them has returned an error, we need to return an error, thats why we use the || operator */
    return handleAddressingAccesses(operand1Mode, table, FALSE, operand1, IC,  numberOfLine, outFile, extFile) || handleAddressingAccesses(operand2Mode, table, TRUE,  operand2, IC, numberOfLine, outFile, extFile);
}   

int handleImmediateAddress(char* operand, int* IC, int numberOfLine, FILE* outFile){
    char inBase32[2] = {0};
    char* end;
    int operandToInt = 0;
    operandToInt = strtol(operand + 1, &end, 10); /* we need the +1 to shift the # */ 
    if (end == operand + 1 || (*end != ' ' && *end != '\t' && *end != '\n' && *end != '\0')){
        throwError("invalid number", numberOfLine);
        return 1;
    }
    *IC = *IC + 1;


    toBase32(operandToInt << 2, inBase32);
    writeToFile(inBase32, outFile, *IC);
        
    return 0;
}

int handleDirectAddress(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* outFile, FILE* extFile){
    char inBase32[2] = {0};
    int ARE = 0;
    symbolTable foundSymbol = NULL;

   
    foundSymbol = findInTable(table, operand);
    if(foundSymbol == NULL){
        throwError("Invalid label found", numberOfLine);
        return 1;
    }else{
        *IC = *IC + 1;

        if(getType(foundSymbol) == EXTERNAL_SYMBOL){ /* if its an external operand, we write it to the ext file */
            ARE = 1; /* 01 */
            toBase32(*IC, inBase32);
            fprintf(extFile, "%s\t%.2s\n", getSymbolName(foundSymbol), inBase32);
        }
        else {
            ARE = 2; /* 10 */
        }
        
        toBase32(getAddress(foundSymbol) << 2 | ARE, inBase32);
        writeToFile(inBase32, outFile, *IC);
              
        
    }
    return 0;
}

int handleAddressAccess(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* outFile, FILE* extFile){

    char parsedLabel[MAX_LENGTH] = {0};
    int labelEnd = 0;
    char inBase32[2] = {0};
    int ARE = 0;
    symbolTable foundSymbol = NULL;

   
    labelEnd = getFirstDelimIndex(operand,'.');
    strncpy(parsedLabel, operand, labelEnd);
    
    foundSymbol = findInTable(table, parsedLabel);
    if(foundSymbol == NULL){
        throwError("Invalid label found", numberOfLine);
        return 1;
    }

    if(getType(foundSymbol) == EXTERNAL_SYMBOL){ /* if its an external operand, we write it to the ext file */
            ARE = 1; /* 01 */
            toBase32(*IC, inBase32);
            fprintf(extFile, "%s\t%.2s\n", getSymbolName(foundSymbol), inBase32);
        }
        else {
            ARE = 2; /* 10 */
        }
    
    *IC = *IC + 1;
    toBase32(getAddress(foundSymbol) << 2 | ARE, inBase32);
   
    writeToFile(inBase32, outFile, *IC);
                   
    *IC = *IC + 1;
   
    toBase32((operand[labelEnd+1] - '0') << 2, inBase32);
    writeToFile(inBase32, outFile, *IC);
               
    return 0;
}

int handleAddressingAccesses(addressingMode operandMode, symbolTable table, int isDest , char* operand, int* IC, int numberOfLine, FILE* outFile, FILE* extFile){
    char inBase32[2] = {0};

    switch(operandMode){
        case immediateAddress:
            return handleImmediateAddress(operand, IC, numberOfLine, outFile);
            break;
        case directAddress:
            return handleDirectAddress(table, operand, IC, numberOfLine, outFile, extFile);
            break;
        case addressAccess:
            return handleAddressAccess(table, operand, IC, numberOfLine, outFile, extFile);
        break;

        case directRegisterAddress:

            *IC = *IC + 1;
            if(isDest){
                toBase32(getRegisterNum(operand) << 2, inBase32);
            }else{
                toBase32(getRegisterNum(operand) << 6, inBase32);
            }
            writeToFile(inBase32, outFile, *IC);           
            
            return 0;
        break;

        case error:
            throwError("Invalid operand", numberOfLine);
            return 1;
        break;
         
    }
    return 1;
}


int encodeCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile, FILE* extFile) {
    int opNumber = 0;
    int isErr = 0;
    opNumber = getOperandNum(command);
    if(opNumber == 0){
        isErr = encodeNoneOperandsCommand(table, command, IC, numberOfLine, outFile);
    }
    else if(opNumber == 1){
        isErr = encodeOneOperandsCommand(table, command, IC, numberOfLine, outFile, extFile);
    }else if(opNumber == 2){
        isErr = encodeTwoOperandsCommand(table, command, IC, numberOfLine, outFile, extFile);
    }else{
        throwError("Error parsing the command!", numberOfLine);
        isErr = 1;
    }
    return isErr;
   

}

void terminateSecondPhase(char* fileName,symbolTable table, FILE* inputFile,  FILE* entFile,  FILE* extFile, FILE* cmdFile, FILE* dataFile){
    
    fclose(inputFile);
    if(entFile != NULL) fclose(entFile);
    if(extFile != NULL) fclose(extFile);
    fclose(cmdFile);
    fclose(dataFile);
    deleteFile(fileName, "cmd");
    deleteFile(fileName, "data");
}


void handleFinalOutputFiles(char* fileName, FILE* cmdFile, FILE* dataFile,  flags* status){
    char c;
    FILE* obFile = openFile(fileName, "ob" , "w");
   
    fseek(cmdFile, 0, SEEK_SET);
     fseek(dataFile, 0, SEEK_SET);
    /* Copy contents of the command instructions to the ob file */
    while ((c = fgetc(cmdFile)) != EOF)
        fputc(c, obFile);
    

    /* Copy contents of the data instructions to the ob file */
    while ((c = fgetc(dataFile)) != EOF)
        fputc(c, obFile);

    fclose(obFile);
    
}

void openFiles(char* fileName, FILE** inputFile, FILE** cmdFile, FILE** dataFile, FILE** entFile, FILE** extFile, flags* status){
    char ICBase32[2];
    char DCBase32[2];
    *inputFile = openFile(fileName, "am", "r");
    *cmdFile = openFile(fileName, "cmd", "w+");
    *dataFile = openFile(fileName, "data", "w+");
    /* here we create them only if needed */
    if(status->foundEntry){
        *entFile = openFile(fileName, "ent", "w");
    }
    if(status->foundExtern){
        *extFile = openFile(fileName, "ext", "w");
    }
    
    toBase32(status->finalIC - 100 , ICBase32);
    toBase32(status->finalDC , DCBase32);
    if(status->finalIC - 100 <= 31) { /* removing the leading "!" */
        ICBase32[0] = ICBase32[1];
        ICBase32[1] = '\0';
    }
    if(status->finalDC <= 31) { /* removing the leading "!" */
        DCBase32[0] = DCBase32[1];
        DCBase32[1] = '\0';
    }
    fprintf(*cmdFile, "%.2s\t%.2s\n\n", ICBase32, DCBase32);
}

int encodeAssembly(char* fileName, symbolTable table, flags* status){

    FILE *inputFile = NULL, *cmdFile = NULL, *dataFile = NULL, *entFile = NULL, *extFile = NULL;
    
    char line[MAX_LINE_LENGTH] = {0};
    int numberOfLine = 0;
    char *firstWord = NULL;
    int IC = 99;

    openFiles(fileName, &inputFile, &cmdFile, &dataFile, &entFile, &extFile, status);

    PRINT_WHITE();    
    printf("Started second iteration on the file: %s...\n",  fileName);
    CLEAR_COLOR();

    while (!feof(inputFile)) {

        /* iterating through each line of the input file */
        fgets(line, MAX_LINE_LENGTH, inputFile); /* MAIN:    mov    S1.1 ,LENGTH*/
        line[strcspn(line, "\n")] = 0;
        
        numberOfLine++;
        if (foundEmptySentence(line) || checkFirstCharacter(line, ';')) {/* if line is empty or comment continue to the next line*/
            continue;
        }

        firstWord = strtok(line, " \t\n\v\f\r");/*XYZ:*/
        if(isLabel(firstWord)){
            firstWord = strtok(NULL, " \t\n\v\f\r,");
        }
        if(firstCharIsDot(firstWord)){
            
            if(!handleEntryAndExtern(firstWord, table,  numberOfLine,entFile , status)){ /* if its not an extern nor entry instruction */
                handleInstructions(table, firstWord, &IC, numberOfLine, dataFile);
            }
        }
        else{
             if(isOperationName(firstWord)){
                status->error = encodeCommandSentence(table,  firstWord, &IC, numberOfLine, cmdFile, extFile);
             }
        }
        
        if(status->error){
            
            terminateSecondPhase(fileName, table, inputFile , entFile ,extFile, cmdFile, dataFile);
            deleteFile(fileName, "ent");
            deleteFile(fileName, "ext");
            deleteFile(fileName, "am");
            return 1;

        }
        memset(line, 0, MAX_LINE_LENGTH);
    }
    PRINT_GREEN();
    printf("Second pass has been finished successfully.\n");
    CLEAR_COLOR();
    handleFinalOutputFiles(fileName, cmdFile, dataFile, status);
    terminateSecondPhase(fileName, table, inputFile, entFile  ,extFile, cmdFile, dataFile);
    return 0;
}
