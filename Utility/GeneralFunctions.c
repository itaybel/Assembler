#include "GeneralFunctions.h"


FILE* openFile(char* file_name, char* file_extention, char* mode){
    char fileNameWithExtension[MAX_FILE_NAME_LENGTH] = {0};
    FILE* fileToOpen;

    strcat(fileNameWithExtension, file_name);
    fileNameWithExtension[strlen(file_name)] = '.';
    strcat(fileNameWithExtension + (strlen(file_name)) + 1, file_extention);
    fileToOpen = fopen(fileNameWithExtension,mode);
    
    return fileToOpen;
}


void removeSpacesAndTabs(char line[MAX_LINE_LENGTH]){
    int i = 0, j = 0;
    for(i = 0;  (line[i] == ' ' || line[i] == '\t') && i < strlen(line) ; i++);
    j = i;
    for(i = 0; j <= strlen(line); i++){ /* shifting all the chars to the left */
        line[i] = line[j];
        j++;
    }
    line[j] = '\0';
}


void throwError(char* errorMsg, int numberOfLine){
    printf("Error occured at line %d: %s\n", numberOfLine, errorMsg);
}

int containsOnlyBlanks(char line[MAX_LINE_LENGTH]){
    int i = 0;
    for(i = 0; i < strlen(line); i++){
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n') return 0;
    }
    return 1;
}


void substring(char* string, int length){
    int i = 0;
    int j = length;
    for(i = 0; j <= strlen(string); i++){
        string[i] = string[j];
        j++;
    }

    string[j] = '\0';
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


/*checks if the char is number for doData function*/
int isNumber(char *number){
    char *temp = NULL;
    strtol(number,&temp,10);
    if(*temp == '\0'){
        return 1;
    }
    return 0;
}