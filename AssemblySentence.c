
#include "AssemblySentence.h"

void throwError(char* errorMsg, int numberOfLine){
    printf("Error occured at line %d: %s\n", numberOfLine, errorMsg);
}

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


int firstCharIsDot(char *line){
    int i = 0;
    for(i = 0; i < strlen(line) && (line[i] == ' ' || line[i] == '\t'); i++);
    return (line[i] == '.');
   
}



char* cutColonFromLabel(char *line, char *firstWord) {

    line[strlen(firstWord) - 1] = '\0';
    return line;
}


int doData(symbolTable table,char *line, int *DC,int numberOfLine,symbolTable symbol) {
    int i = 0;
    char *curr_line = line;


    while (curr_line[0] != '\n' && curr_line[0] != '\0') {
        if (strcmp(curr_line, line) == 0) { /*this means that it couldn't convert any number*/
            throwError("Couldn't parse one of the numbers!\n", numberOfLine);
            return 1;
        }
        if (curr_line[0] != '\0' && curr_line[0] != ',') {
            throwError("Couldn't find an ',' after a number!", numberOfLine);
            return 1;
        }
        curr_line++; /*shifting the ',' at the beginning*/
        line = curr_line;
        i++;
    }
    *DC = *DC + i;
    if (symbol != NULL) {
        setType(symbol, DATA_SYMBOL);
    }

    return 0;
}

int doString(symbolTable table,char *line, int *DC,int numberOfLine,symbolTable symbol)
{
    int i = 0;
    int string_length = 0;
    int found_valid_string = 0;
    while (line[i] != '\n' && line[i] != '\0' && !found_valid_string)
    {
        if (line[i] != '\t' && line[i] != ' ')
        {
            throwError("Found invalid text before string", numberOfLine);
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
        if (symbol != NULL) {
            setType(symbol, DATA_SYMBOL);
        }
        return 0;
    }
    return 1;
}


int doStruct(symbolTable table,char *line, int *DC,int numberOfLine,symbolTable symbol)
{
    int i = 0;
    /*int ret = 0;*/
    int string_length = 0;
    int found_valid_string = 0;
    char *curr_line = line;

    /*ret = strtol(line, &curr_line, 10);*/
    if (strcmp(curr_line, line) == 0)
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

    while (line[i] != '\n' && line[i] != '\0' && !found_valid_string)
    {
        if (line[i] != '\t' && line[i] != ' ')
        {
            throwError("Found invalid text after ','", numberOfLine);
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

    if(validLabelName(label)){
        InsertSymbolNode(&table, (char *) symbol,*DC);
        return 1;
    }
    return 0;
}




int getSpacesAtBegining(char* substring){
    int i = 0;

    for(i = 0; i < strlen(substring) && (substring[i] == ' ' || substring[i] == '\t'); i++); /* shifting the spaces */
    return i;
}

int doCommandSentence(char *line, int *IC,int numberOfLine,symbolTable symbol) {
    int opNumber = 0;
    int i = 0;
    char *nextWord = NULL;
    char* originalLine;
    addressingMode prevOperand = immediateAddress;
    addressingMode curr = immediateAddress;

    originalLine = (char*)malloc(sizeof(char) * (strlen(line) + 1));
    strcpy(originalLine, line);
    printf("line is: %s\n", line);
    nextWord = strtok(originalLine, " \t\n\v\f\r");/*XYZ:*/
    printf("line is: %s\n", originalLine);
    removeSpacesAndTabs(nextWord);
    if (!isOperationName(nextWord)) {
        throwError("Invalid OperationName", numberOfLine);
        return 0;
    }

    opNumber = getOperandNum(nextWord);
    
    nextWord = strtok(line, " \t\n\v\f\r");/*XYZ:*/

    printf("opnumber: %d-next word is: %s\n", opNumber, nextWord);
    for (i = 0; i < opNumber; i++) {
        
        printf("nextWord is: -%s-\n", nextWord);
        curr = getAddressingMode(nextWord, numberOfLine);
        iCCounter(curr, prevOperand, IC);
        prevOperand = curr;
        nextWord = strtok(NULL, ",");
    }

    return 1;
}


struct inst
{
    const char *name;
    int(*doInstructions)(/*SymbolTable *, char */symbolTable table,char *line, int *DC, int numberOfLine,symbolTable symbol);
};

void validInstructions(symbolTable table,char *instruction,int *DC, int numberOfLine,symbolTable symbol)
{
    struct inst instructionFunc[] = {{".data", doData}, {".string", doString}, {".struct", doStruct}, {".entry",doEntry}, {".extern",doExtern}};
    int i = 0;



    for(i = 0; i < sizeof(instructionFunc)/sizeof(instructionFunc[0]); ++i)
    {
        if(strcmp(instructionFunc[i].name, instruction) == 0){
            instruction = strtok(NULL," ");
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


int createSymbolTable(char* fileName) {

    FILE *inputFile = NULL;
    char line[MAX_LINE_LENGTH] = {0};
    char *firstWord = NULL;
    char *label = NULL;
    symbolTable symbol = NULL;
    symbolTable table = NULL;
    int numberOfLine = 0;

    int IC = 100;
    int DC = 0;

    inputFile = openFile(fileName, "am", "r");


    while (!feof(inputFile)) {

        /* iterating through each line of the input file */
        fgets(line, MAX_LINE_LENGTH, inputFile); /* XYZ: .data 7, -57, +17, 9*/
        numberOfLine++;
        /* storing a copy of the line, since strtok will be changing it */
        /* subString recives the first string*/
        firstWord = strtok(line, " \t\n\v\f\r");/*XYZ:*/

        if (foundEmptySentence(line) || foundCommendSentence(line)) {/* if line is empty or commend continue to the next line*/
            continue;
        }

        if (isLabel(firstWord)) {/* if subString is label XYZ: we cuting the colon(:) from it,*/
        
            label = cutColonFromLabel(line, firstWord); 
            printf("first word is %s-\n", firstWord);
            InsertSymbolNode(&table, label, IC);
            firstWord = strtok(NULL, "");
        }
        
        if (firstCharIsDot(firstWord)) {
            validInstructions(table, firstWord, &DC, numberOfLine, symbol);
        } else {
            printf("fw is: %s\n", firstWord);
            doCommandSentence(firstWord, &IC, numberOfLine, symbol);
        }


    }

    fclose(inputFile);
    return 1;
}
