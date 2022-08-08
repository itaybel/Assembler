#include "InputHandler.h"


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
