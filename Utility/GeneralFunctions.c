#include <stdlib.h>
#include "string.h"
#include "../AddressingMode.h"
#include "../GeneralFunctions.h"
#include "../OperationTable.h"
#include "../RegisterTable.h"

void getFileWithExtension(char* fileName, char* extension, char* fileWithExtension){
    strcat(fileWithExtension, fileName); /* we copy the file name to the beginning of the string */
    fileWithExtension[strlen(fileName)] = '.'; /* then we add a "." */
    strcat(fileWithExtension + (strlen(fileName)) + 1, extension); /* we add the file extension after the "." */
}

FILE* openFile(char* file_name, char* fileExtention, char* mode){
    char fileNameWithExtension[MAX_FILE_NAME_LENGTH] = {0};
    FILE* fileToOpen;

    getFileWithExtension(file_name, fileExtention, fileNameWithExtension);

    fileToOpen = fopen(fileNameWithExtension,mode);

    return fileToOpen;
}

void deleteFile(char* file_name, char* file_extension){
    char fileNameWithExtension[MAX_FILE_NAME_LENGTH] = {0};

    getFileWithExtension(file_name, file_extension, fileNameWithExtension);
    remove(fileNameWithExtension);
}


void removeSpacesAndTabs(char line[MAX_LINE_LENGTH]){
    int i = 0, j = 0;
    if(line == NULL) return;

    /* removing all the spaces from the right */
    for (i = strlen(line) - 1; (line[i] == ' ' || line[i] == '\t' || line[i] == EOF || line[i] == '\n') && i > 0; i--);
    line[i + 1] = '\0';

    /* removing all the spaces from the left */

    for(i = 0;  (line[i] == ' ' || line[i] == '\t'|| line[i] == EOF || line[i] == '\n') && i < strlen(line) ; i++);
    j = i;
    for(i = 0; j <= strlen(line); i++){ /* shifting all the chars to the left */
        line[i] = line[j];
        j++;
    }

    line[j] = '\0';

}


void throwError(char* errorMsg, int numberOfLine){
    PRINT_RED();
    printf("Error occurred at line %d: %s\n", numberOfLine, errorMsg);
    CLEAR_COLOR();
}
void throwWarning(char* warningMsg, int numberOfLine){
    PRINT_YELLOW();
    printf("Warning occurred at line %d: %s\n", numberOfLine, warningMsg);
    CLEAR_COLOR();
}



int reservedWord(char *word) {

    /*check if register or instructionName or a command */
    return (isRegisterName(word)  || isInstructionName(word) || isOperationName(word));

}

int foundEmptySentence(char* line){
    int i = 0;

    if(line == NULL){
        return 1;
    }
    for(i = 0; i < strlen(line); i++){
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != EOF) return 0; /* if we found a none blank character, it means the ine isn't empty */
    }
    return 1;
}


int firstCharIsDot(char *line){

    int i = 0;
    if(line == NULL) return 0;
    for(i = 0; i < strlen(line) && (line[i] == ' ' || line[i] == '\t'); i++); /* skipping all the blanks at the beginning */
    return (strlen(line) == 0 || line[i] == '.');

}



void cutColonFromLabel(char *labelName) {

    labelName[strlen(labelName) - 1] = '\0';
}


int isNumber(char *number){
    char numberCopy[MAX_LINE_LENGTH] = {0};
    char *temp = NULL;
    strcpy(numberCopy, number);
    removeSpacesAndTabs(numberCopy);


    strtol(numberCopy,&temp,10);
    if(*temp == '\0'){ /* if strtok cut the whole string, it means that the string represents a number */
        return 1;
    }
    return 0;
}

int convertToNumber(char* numberString, int* number){
    char* temp = NULL;
    if(isNumber(numberString)){
        *number = strtol(numberString,&temp,10);
        return 0;
    }else{
        return 1;
    }
}
