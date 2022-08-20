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


void throwError(char* errorMsg, int numberOfLine){
    printf("Error occured at line %d: %s\n", numberOfLine, errorMsg);
}



int foundEmptySentence(char* line){
    int i = 0;

    if(line == NULL){
        return 1;
    }
    for(i = 0; i < strlen(line); i++){
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != EOF) return 0;
    }
    return 1;
}


int firstCharIsDot(char *line){

    int i = 0;
    if(line == NULL) return 0;
    for(i = 0; i < strlen(line) && (line[i] == ' ' || line[i] == '\t'); i++);
    return (strlen(line) == 0 || line[i] == '.');

}



void cutColonFromLabel(char *labelName) {

    labelName[strlen(labelName) - 1] = '\0';
}


/*checks if the char is number for doData function*/
int isNumber(char *number){
    char numberCopy[MAX_LINE_LENGTH] = {0};
    char *temp = NULL;
    strcpy(numberCopy, number);
    removeSpacesAndTabs(numberCopy);
    
    strtol(numberCopy,&temp,10);
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



void fixDataInstruction(char *line, char parsedLine[MAX_LINE_LENGTH * 2])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < strlen(line); i++)
    {
        parsedLine[j] = line[i];
        if (line[i] == ',')
        {

            parsedLine[j + 1] = ' ';
            j++;
        }

        j++;
    }
}

void *checkMalloc(size_t size) {
    void* ptr = NULL;
    ptr = malloc(size);
    if (ptr == NULL) {
        printf("Error: Fatal: Memory allocation failed.");
        exit(1);
    }
    return ptr;
}
