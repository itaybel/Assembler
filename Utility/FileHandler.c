#include "FileHandler.h"

FILE* OpenFile(char* FileName, char* FileExtention, char* Mode){
    char* FileNameWithExtension = (char*)malloc(sizeof(char) * (strlen(FileName) + strlen(FileExtention) + 1)); /* the + 1 is for the "." that is going to be added */
    FILE* FileToOpen;

    strcat(FileNameWithExtension, FileName);
    FileNameWithExtension[strlen(FileName)] = '.';
    strcat(FileNameWithExtension + (strlen(FileName)), FileExtention);
    printf("%s\n", FileNameWithExtension);
    FileToOpen = fopen(FileNameWithExtension,mode);
    free(FileNameWithExtension);
    
    return FileToOpen;
}
