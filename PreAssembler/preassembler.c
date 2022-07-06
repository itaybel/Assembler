#include "preassembler.h"


int createAmFile(char* file_name){
        FILE *asmFile;
        FILE *amFile;
        Node* macroTable;
        char line[MAX_LINE_LENGTH];
        char lineFirstField[MAX_LINE_LENGTH];
        asmFile = openFile(file_name , "as", "r");
        
        if(asmFile == NULL){
            printf("Error - Couldn't open the file: %s\n", file_name);
            return 0;
        }

        amFile = openFile(file_name, "am", "w");
        if(amFile == NULL){
            printf("Error - Couldn't create the am file!\n");
            return 0;
        }


        while (!feof(asmFile)) { /* iterating through each line of the input file */
            fgets(line, MAX_LINE_LENGTH, asmFile);
            line[strcspn(line, "\n")] = 0; 

            strcpy(lineFirstField, getFirstField(line));

            printf("---%s---", lineFirstField);
            
            if(SearchNode(macroTable, lineFirstField, strcmp) != NULL){ /* if we found a macro call */
                printf("line is a macro call!\n");
            }
            if(strcmp(lineFirstField, "macro") == 0){ /* if the line starts with "macro" */
                printf("line is a macro definition!\n");
            }
            printf("the file data is = %s\n", line);
        }
        
        fclose(asmFile);
}




