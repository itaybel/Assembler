#include "AssemblySentence.h"
#include <stdio.h>
#include <string.h>
#include "SecondPass.h"

void writeToFile(char* content, FILE* file, int IC){
    char base32Address[2] = {0};
    toBase32(IC, base32Address);
    fprintf(file, "%.2s\t%.2s\n", base32Address, content);
    
}

void toBase32(unsigned int num, char* base)
{
   
    const char base32chars[] = "!@#$%^&*<>abcdefghijklmnopqrstuv";
    num &= ((1 << 10) - 1); /* appling bit masking , so that num / 32 will not be bigger than 32 */

    base[0] = base32chars[num / 32];
    base[1] = base32chars[num % 32];

}

void encodeData(symbolTable table, char* line , int* IC, int numberOfLine, FILE* outFile){
    char* nextNumber = NULL;
    char inBase32[2] = {0};
    int number = 0;


    while((nextNumber = strtok(NULL," \t\n\v\f\r,")) != NULL) {

 
        convertToNumber(nextNumber, &number);
        toBase32(number, inBase32);
        writeToFile(inBase32, outFile, *IC);
        *IC = *IC + 1;
    }



}

void encodeString(symbolTable table, char* command , int* IC, int numberOfLine, FILE* outFile)
{

    int i = 0;
    int string_length = 0;
    int found_valid_string = 0;
    char *token = NULL;
    char inBase32[2] = {0};
    token = strtok(NULL," \t\n\v\f\r ");
    while (token[i] != '\n' && token[i] != '\0' && !found_valid_string)
    {

        if (token[i] == '\"')
        {
            while (token[i] != '\n' && token[i] != '\0' && !found_valid_string)
            {
                toBase32(token[i], inBase32);
                *IC = *IC + 1;
                writeToFile(inBase32, outFile, *IC);
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
}



void encodeStruct(symbolTable table, char* command , int* IC, int numberOfLine, FILE* outFile)
{
    int i = 0;
    /*int ret = 0;*/
    int string_length = 0;
    int found_valid_string = 0;
    char* token = NULL;
    char inBase32[2] = {0};
   
    token = strtok(NULL," \t\n\v\f\r,");
    

    if(isNumber(token)){
        toBase32(atoi(token), inBase32);
        writeToFile(inBase32, outFile, *IC);
        (*IC)++;
    }
    token = strtok(NULL," \t\n\v\f\r,");
    while (token[i] != '\n' && token[i] != '\0' && !found_valid_string)
    {

        if (token[i] == '\"')
        {
            while (token[i] != '\n' && token[i] != '\0' && !found_valid_string)
            {
                toBase32(token[i], inBase32);
                *IC = *IC + 1;
                writeToFile(inBase32, outFile, *IC);
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
        *IC = *IC + string_length;
    }
   
}




struct encodeInst
{
    const char *name;
    void(*encodeInstructions)(/*SymbolTable *, char */symbolTable table,char *line, int *DC, int numberOfLine, FILE* outFile);
};


void handleInstructions(symbolTable table, char *instruction, int *DC, int numberOfLine, FILE* outFile){
    struct encodeInst instructionFunc[] = {{".data", encodeData}, {".string", encodeString}, {".struct", encodeStruct}};
    int i = 0;

    for(i = 0; i < sizeof(instructionFunc)/sizeof(instructionFunc[0]); ++i)
    {
        if(strcmp(instructionFunc[i].name, instruction) == 0){
            instructionFunc[i].encodeInstructions(table, instruction, DC, numberOfLine, outFile);
        }

    }
}

int parseNoneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile) {
    char inBase32[2] = {0};

    toBase32(getOperationOpcode(command) << 6, inBase32);
    *IC = *IC + 1;
    writeToFile(inBase32, outFile, *IC);
    return 0;
}   

int handleImmediateAddress(char* operand, int* IC, int numberOfLine, FILE* outFile){
    char inBase32[2] = {0};
    char* end;
    int operandToInt = 0;
    operandToInt = (unsigned int)strtol(operand + 1, &end, 10); /* we need the +1 to shift the # */ 
    if (end == operand + 1 || (*end != ' ' && *end != '\t' && *end != '\n' && *end != '\0')){
        throwError("invalid number", numberOfLine);
        return 1;
    }
    *IC = *IC + 1;
    toBase32(operandToInt, inBase32);
    writeToFile(inBase32, outFile, *IC);
    return 0;
}

int handleDirectAddress(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* outFile){
    char inBase32[2] = {0};
    int ARE = 0;
    symbolTable foundSymbol = NULL;

   
    foundSymbol = findInTable(table, operand);
    if(foundSymbol == NULL){
        throwError("Invalid label found", numberOfLine);
        return 1;
    }else{
      
        /* parsing the extra words */
        if(getType(foundSymbol) == EXTERNAL_SYMBOL) ARE = 1;
        else ARE = 2;
    
        toBase32(getAddress(foundSymbol) << 2 | ARE, inBase32);
        writeToFile(inBase32, outFile, *IC);
        *IC = *IC + 1;
    }
    return 0;
}

int handleAddressAccess(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* outFile){

    char parsedLabel[MAX_LENGTH] = {0};
    int labelEnd = 0;
    char inBase32[2] = {0};
    symbolTable foundSymbol = NULL;

   
    labelEnd = getFirstDelimIndex(operand,'.');
    strncpy(parsedLabel, operand, labelEnd);
    
    foundSymbol = findInTable(table, parsedLabel);
    if(foundSymbol == NULL){
        throwError("Invalid label found", numberOfLine);
        return 1;
    }
  
    toBase32(getAddress(foundSymbol) << 2 | 2, inBase32);
   
    writeToFile(inBase32, outFile, *IC);
    *IC = *IC + 1;
   
    toBase32((operand[labelEnd+1] - '0') << 2, inBase32);
    writeToFile(inBase32, outFile, *IC);
    *IC = *IC + 1;
    return 0;
}

int handleAccesses(addressingMode operandMode, symbolTable table, char* operand, int* IC, int numberOfLine, FILE* outFile){
    char inBase32[2] = {0};

    switch(operandMode){
        case immediateAddress:
            return handleImmediateAddress(operand, IC, numberOfLine, outFile);
            break;
        case directAddress:
            return handleDirectAddress(table, operand, IC, numberOfLine, outFile);
            break;
        case addressAccess:
            return handleAddressAccess(table, operand, IC, numberOfLine, outFile);
        break;

        case directRegisterAddress:
            toBase32(getRegisterNum(operand) << 2, inBase32);
            writeToFile(inBase32, outFile, *IC);
            *IC = *IC + 1;
            return 0;
        break;

        case error:
            throwError("Invalid operand", numberOfLine);
            return 1;
        break;
         
    }
    return 1;
}


int parseOneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile) {
    char inBase32[2] = {0};
    int opCode = 0;
    char* operand = NULL;
    addressingMode operandMode = 0;
    opCode = getOperationOpcode(command);
    operand = strtok(NULL, " \t\n\v\f\r ");
    operandMode = getAddressingMode(operand, numberOfLine);
   
    toBase32(opCode << 6 | operandMode << 4, inBase32);

    writeToFile(inBase32, outFile, *IC);
    *IC = *IC + 1;
    
    return handleAccesses(operandMode, table,  operand, IC,  numberOfLine, outFile);
}   


int parseTwoOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile) {
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
   

    toBase32(opCode << 6 | operand1Mode << 4 | operand2Mode << 2, inBase32);
    writeToFile(inBase32, outFile, *IC);
    *IC = *IC + 1;

    /* we handle this case seperetly */

    if(operand1Mode == directRegisterAddress && operand2Mode == directRegisterAddress){
        toBase32(getRegisterNum(operand1) << 6 | getRegisterNum(operand2) << 2, inBase32);
        writeToFile(inBase32, outFile, *IC);
        *IC = *IC + 1;
        return 0;
    }

    /* if one of them has returned an error, we need to return an error, thats why we use the || operator */
    return handleAccesses(operand1Mode, table,  operand1, IC,  numberOfLine, outFile) || handleAccesses(operand2Mode, table,  operand2, IC, numberOfLine, outFile);
}   


int parseCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile) {
    int opNumber = 0;
    int isErr = 0;
    opNumber = getOperandNum(command);
    if(opNumber == 0){
        isErr = parseNoneOperandsCommand(table, command, IC, numberOfLine, outFile);
    }
    else if(opNumber == 1){
        isErr = parseOneOperandsCommand(table, command, IC, numberOfLine, outFile);
    }else if(opNumber == 2){
        isErr = parseTwoOperandsCommand(table, command, IC, numberOfLine, outFile);
    }else{
        throwError("Error parsing the command!", numberOfLine);
        isErr = 1;
    }
    return isErr;
   

}

void terminateSecondPhase(char* fileName,symbolTable table, FILE* inputFile,  FILE* entFile,  FILE* extFile){
    freeTable(table);
    fclose(inputFile);
    if(entFile != NULL) fclose(entFile);
    if(extFile != NULL) fclose(extFile);

    deleteFile(fileName, "cmd");
    deleteFile(fileName, "data");
}

int handleEntryAndExtern(char* firstWord, symbolTable table, int numberOfLine, FILE* entFile, FILE* extFile , flags* status){
    symbolTable symbol = NULL;
    char* token = NULL;
    char inBase32[2] = {0};
    if(!strcmp(firstWord, ".entry")){
       
        token = strtok(NULL, " \t\n\v\f\r ");
        if((symbol = findInTable(table, token)) == NULL){
            throwError("Found an entry declaration of an undefined label", numberOfLine);
            status->error = 1;
        }else{
            toBase32(getAddress(symbol) , inBase32);
            fprintf(entFile, "%s\t%.2s\n", getSymbol(symbol),inBase32);
        }
        return 1;
    }
    if(!strcmp(firstWord, ".extern")){
       
        token = strtok(NULL, " \t\n\v\f\r ");
        if((symbol = findInTable(table, token)) == NULL){
            throwError("Couldn't find extern symbol in symbol table!", numberOfLine);
            status->error = 1;
        }else{
            toBase32(getAddress(symbol) , inBase32);
            fprintf(extFile, "%s\t%.2s\n", getSymbol(symbol),inBase32);
        }
        return 1;
    }
    return 0;
}

void handleFinalOutputFiles(char* fileName, FILE* cmdFile, FILE* dataFile,  flags* status){
    char c;
    FILE* obFile = openFile(fileName, "ob" , "w");
   
    fseek(cmdFile, 0, SEEK_SET);
     fseek(dataFile, 0, SEEK_SET);
    /* Copy contents of the command instructions to the ob file */
    while ((c = fgetc(cmdFile)) != EOF){
      
        fputc(c, obFile);
    }

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
    /* here we create then only if needed */
    if(status->foundEntry){
        *entFile = openFile(fileName, "ent", "w");
    }
    if(status->foundExtern){
        *extFile = openFile(fileName, "ext", "w");
    }
    toBase32(status->finalIC , ICBase32);
    toBase32(status->finalDC , DCBase32);
    fprintf(*cmdFile, "%.2s\t%.2s\n\n", ICBase32, DCBase32);
}

int encodeAssembly(char* fileName, symbolTable table, flags* status){

    FILE *inputFile = NULL, *cmdFile = NULL, *dataFile = NULL, *entFile = NULL, *extFile = NULL;
    
    char line[MAX_LINE_LENGTH] = {0};
    int numberOfLine = 0;
    char *firstWord = NULL;
    int IC = 100;
    int DC = 0;

    openFiles(fileName, &inputFile, &cmdFile, &dataFile, &entFile, &extFile, status);
    
    printf("Started second phase on the file: %s...\n",  fileName);
    
    while (!feof(inputFile)) {

        /* iterating through each line of the input file */
        fgets(line, MAX_LINE_LENGTH, inputFile); /* MAIN:    mov    S1.1 ,LENGTH*/
        line[strcspn(line, "\n")] = 0;
        
        numberOfLine++;
        if (foundEmptySentence(line) || foundCommentSentence(line)) {/* if line is empty or commend continue to the next line*/
            continue;
        }

        firstWord = strtok(line, " \t\n\v\f\r");/*XYZ:*/
        if(isLabel(firstWord)){
            firstWord = strtok(NULL, " \t\n\v\f\r,");
        }
        if(firstCharIsDot(firstWord)){
            
            if(!handleEntryAndExtern(firstWord, table,  numberOfLine,entFile,extFile , status)){ /* if its not an extern nor entry instruction */
                handleInstructions(table, firstWord, &DC, numberOfLine, dataFile);
            }
        }
        else{
             if(isOperationName(firstWord)){
                status->error = parseCommandSentence(table,  firstWord, &IC, numberOfLine, cmdFile);
             }
        }
        
        if(status->error){
            terminateSecondPhase(fileName, table, inputFile , entFile ,extFile);
            return 1;

        }
        memset(line, 0, MAX_LINE_LENGTH);
    }
    
    handleFinalOutputFiles(fileName, cmdFile, dataFile, status);
    terminateSecondPhase(fileName, table, inputFile, entFile  ,extFile);
    return 0;
}