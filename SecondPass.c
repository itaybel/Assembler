#include "AssemblySentence.h"
#include <stdio.h>
#include <string.h>
#include "SecondPass.h"

void writeToFile(char* content, FILE* file, int IC){
    char base32Address[2] = {0};
    toBase32(IC, base32Address);
    fprintf(file, "%s\t%s", base32Address, content);
    
}

void toBase32(int num, char *base)
{
    const char base32chars[] = "!@#$%^&*<>abcdefghijklmnopqrstuv";
    (base)[0] = base32chars[num / 32];
    (base)[1] = base32chars[num % 32];
    /* todo: make it work for negative numbers */
}

void encodeData(symbolTable table, char* line , int* IC, int numberOfLine, FILE* obFile){
    char* nextNumber = NULL;
    char inBase32[2] = {0};
    printf("got line: %s\ndc: %d\nnumber of line: %d\n", line, *IC, numberOfLine);
    nextNumber = strtok(line, " \t\n\v\f\r,");
    printf("next is: -%s-", nextNumber);
    while(nextNumber){
        
        printf("%s,", nextNumber);
        nextNumber = strtok(NULL, " \t\n\v\f\r,");
        toBase32(atoi(nextNumber), inBase32);
        writeToFile(inBase32, obFile, *IC);
        *IC = *IC + 1;
        

    }

}

void encodeString(symbolTable table, char* command , int* IC, int numberOfLine, FILE* obFile)
{





    int i = 0;
    int string_length = 0;
    int found_valid_string = 0;
    char *token = NULL;
    char inBase32[2] = {0};
    token = strtok(NULL," \t\n\v\f\r,");
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
                toBase32(command[i], inBase32);
                *IC = *IC + 1;
                writeToFile(inBase32, obFile, *IC);
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






struct encodeInst
{
    const char *name;
    void(*encodeInstructions)(/*SymbolTable *, char */symbolTable table,char *line, int *DC, int numberOfLine, FILE* obFile);
};
void handleInstructions(symbolTable table, char *instruction, int *DC, int numberOfLine, FILE* obFile){
    struct encodeInst instructionFunc[] = {{".data", encodeData}, {".string", encodeString}, {".struct", encodeData}, {".extern",encodeData}};
    int i = 0;



    for(i = 0; i < sizeof(instructionFunc)/sizeof(instructionFunc[0]); ++i)
    {
        if(strcmp(instructionFunc[i].name, instruction) == 0){
            instruction = strtok(NULL," ");
            instructionFunc[i].encodeInstructions(table, instruction, DC, numberOfLine, obFile);
        }

    }
}

void parseCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine) {

}
int encodeAssembly(char* fileName, symbolTable table){

    FILE *inputFile = NULL;
    FILE* obFile = NULL;
    char line[MAX_LINE_LENGTH] = {0};
    int numberOfLine = 0;
    char *firstWord = NULL;
    int IC = 100;
    int DC = 0;
    int instructionIndex = 0;
    inputFile = openFile(fileName, "am", "r");
    obFile = openFile(fileName, "ob", "w");

    while (!feof(inputFile)) {

        /* iterating through each line of the input file */
        fgets(line, MAX_LINE_LENGTH, inputFile); /* MAIN:    mov    S1.1 ,LENGTH*/
        numberOfLine++;
        if (foundEmptySentence(line) || foundCommendSentence(line)) {/* if line is empty or commend continue to the next line*/
            continue;
        }

        firstWord = strtok(line, " \t\n\v\f\r");/*XYZ:*/
        if(isLabel(firstWord)){
            firstWord = strtok(NULL, " \t\n\v\f\r,");
        }
    /*    instructionIndex = validInstructions(*head, firstWord, &DC, numberOfLine, symbol); */
        if(firstCharIsDot(firstWord)){
            
            if(instructionIndex == ENTRY_INDEX){
                firstWord = strtok(NULL, " \t\n\v\f\r,");
                if(!isIsSymbolTable(table, firstWord)){
                    throwError("Found an entry declaration of an undefined label", numberOfLine);
                    continue;
                }else{
                    /* todo: write the label into the .ent file */
                }
            }else{
                handleInstructions(table, firstWord, &DC, numberOfLine, obFile);
            }
        }else{
             if(isOperationName(firstWord)){
                parseCommandSentence(table,  firstWord, &IC, numberOfLine);
             }
        }
        printf("first word is: %s\n", firstWord);

    }
    return 0;
}