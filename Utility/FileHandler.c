#include "FileHandler.h"

FILE* openFile(char* file_name, char* file_extention, char* mode){
    int fileNameLength = strlen(file_name) + strlen(file_extention) + 2;
    char* fileNameWithExtension = (char*)calloc(fileNameLength, sizeof(char)); /* the + 2 is for the "." that is going to be added and the NULL */
    FILE* fileToOpen;

    strncat(fileNameWithExtension, file_name, fileNameLength);
        printf("\nP:%s\n", fileNameWithExtension);

    fileNameWithExtension[strlen(file_name)] = '.';
    strncat(fileNameWithExtension + (strlen(file_name)) + 1, file_extention, fileNameLength);
    printf("\nP:%s\n", fileNameWithExtension);
    fileToOpen = fopen(fileNameWithExtension,mode);
    free(fileNameWithExtension);
    
    return fileToOpen;
}