#include "input_handler.h"

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


int startWith(char* str1, char* str2){
    return strncmp(str1, str2, strlen(str2)) == 0;
}

char* getNextField(char* string){
    int i = 0;
    int j = 0;
    char* firstField;
    firstField = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
    for(i = 0; i < strlen(string) && (string[i] == ' ' || string[i] == '\t'); i++); /* iterating until a letter was found */
    for(; i < strlen(string) && (string[i] != ' ' && string[i] != '\t'); i++, j++){ /* iterating until a space/tab was found */
        firstField[j] = string[i];
    }
    firstField[j] = '\0';
    return firstField;
}
