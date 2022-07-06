#include "file_handler.h"

FILE* openFile(char* file_name, char* file_extention, char* mode){
    char* fileNameWithExtension = (char*)malloc(sizeof(char) * (strlen(file_name) + strlen(file_extention) + 1)); /* the + 1 is for the "." that is going to be added */
    FILE* fileToOpen;

    strcat(fileNameWithExtension, file_name);
    fileNameWithExtension[strlen(file_name)] = '.';
    strcat(fileNameWithExtension + (strlen(file_name)), file_extention);
    printf("%s\n", fileNameWithExtension);
    fileToOpen = fopen(fileNameWithExtension,mode);
    free(fileNameWithExtension);
    
    return fileToOpen;
}