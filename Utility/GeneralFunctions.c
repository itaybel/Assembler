#include "GeneralFunctions.h"

void getFileWithExtension(char* fileName, char* extension, char* fileWithExtension){
    strcat(fileWithExtension, fileName);
    fileWithExtension[strlen(fileName)] = '.';
    strcat(fileWithExtension + (strlen(fileName)) + 1, extension);
}

FILE* openFile(char* file_name, char* file_extention, char* mode){
    char fileNameWithExtension[MAX_FILE_NAME_LENGTH] = {0};
    FILE* fileToOpen;

    getFileWithExtension(file_name, file_extention, fileNameWithExtension);
    
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
    for (i = strlen(line) - 1; (line[i] == ' ' || line[i] == '\t' || line[i] == EOF || line[i] == '\n') && i > 0; i--); /* removing all the spaces from the right */
        
    line[i + 1] = '\0';
    for(i = 0;  (line[i] == ' ' || line[i] == '\t'|| line[i] == EOF || line[i] == '\n') && i < strlen(line) ; i++);
    j = i;
    for(i = 0; j <= strlen(line); i++){ /* shifting all the chars to the left */
        line[i] = line[j];
        j++;
    }
    
    line[j] = '\0';
   
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



/*
This function checks how many consestive commas are there at the beginning of a string
@param input: the input the user has written after some configurtions
@return 
0 - if no commas were found
1 - if one commas were found
2 - if 2 commas were found
*/
int consestiveCommasFound(char* input){
    removeSpacesAndTabs(input);
    if(input[0] == ','){
        input++;
        removeSpacesAndTabs(input);
        if(input[0] == ','){
            return 2;
        }
        return 1;

    }
    return 0;
}


/*
This function checks wether the commas at the beginning of a string are valid, and prints responses to the user
@param input: the input the user has written after some configurtions
@param numberOfLine - the current line in the input file
@return wether its valid or not
*/
int areCommasValid(char* input, int isFirst, int numberOfLine){
    
    int res = consestiveCommasFound(input);
    if(isFirst && res > 0){
        throwError("Invalid commas before first number", numberOfLine);
        return 0;
    }
    if(res == 0){
        if(!isFirst){
            throwError("Missing comma", numberOfLine);
            return 0;
        }
        return 1;
    }
    if(res == 1) {
        if(strlen(input) == 1){ /* if its only a comma, it means the input ends with one*/
            throwError("Extraneous text after end of command", numberOfLine);
            return 0;
        }
        return 1;
    }    
    if(res >= 2){
        throwError("Multiple consecutive commas", numberOfLine);
        return 0;
    }
    return 0;
}



int isBlank(char c){
    return c == ' ' || c == '\t';
}

int containsBlank(char* string){
    int i = 0;
    for(i = 0; i < strlen(string); i++) {
        if(isBlank(string[i])) return 1;
    }
    return 0;
}

void getNextWord(char line[MAX_LINE_LENGTH], char word[MAX_LINE_LENGTH]){
    int i = 0;
    int j = 0;
    for(i = 0; i < strlen(line) && isBlank(line[i]); i++);
    for(; i < strlen(line); i++){
        word[j] = line[i];
    }
}

void throwError(char* errorMsg, int numberOfLine){
    printf("Error occured at line %d: %s\n", numberOfLine, errorMsg);
}

int containsOnlyBlanks(char line[MAX_LINE_LENGTH]){

    int i = 0;
    if(line == NULL){ 
    	return 1;
    }
    for(i = 0; i < strlen(line); i++){
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n') return 0;
    }
    return 1;
}


int firstCharIsDot(char *line){

    int i = 0;
    if(line == NULL) return 0;
    for(i = 0; i < strlen(line) && (line[i] == ' ' || line[i] == '\t'); i++);
    return (strlen(line) == 0 || line[i] == '.');

}



char* cutColonFromLabel(char *line, char *firstWord) {

    line[strlen(firstWord) - 1] = '\0';
    return line;
}


/*checks if the char is number for doData function*/
int isNumber(char *number){
    
    char *temp = NULL;
    removeSpacesAndTabs(number);
    strtol(number,&temp,10);
    if(*temp == '\0'){
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


void *checkMalloc(int size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("Error: Fatal: Memory allocation failed.");
        exit(1);
    }
    return ptr;
}