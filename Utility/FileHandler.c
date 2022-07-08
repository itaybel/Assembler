#include "FileHandler.h"

FILE* openFile(char* file_name, char* file_extention, char* mode){
    char fileNameWithExtension[MAX_FILE_NAME_LENGTH] = {0};
    FILE* fileToOpen;

    strcat(fileNameWithExtension, file_name);
    fileNameWithExtension[strlen(file_name)] = '.';
    strcat(fileNameWithExtension + (strlen(file_name)) + 1, file_extention);
    fileToOpen = fopen(fileNameWithExtension,mode);
    
    return fileToOpen;
}