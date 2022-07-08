#include "PreAssembler.h"



int createAmFile(char* file_name){
        FILE *asmFile = NULL;
        FILE *amFile = NULL;
        Node** macroTable = NULL;
        MacroNode* newMacroNode =  NULL;
        char line[MAX_LINE_LENGTH] = {0};
        char* lineField = NULL;

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

            removeSpacesAndTabs(line);

            if(strlen(line) == 0) continue;
            lineField = strtok(line, " "); /* get the first word in the line. */
            
            if((newMacroNode = (MacroNode*)(SearchNode(*macroTable, lineField, compareMacro))) != NULL ){ /* if we found a macro call */
                fprintf(amFile, "%s", newMacroNode->content);
            }
            else if(strcmp(lineField, "macro") == 0){ /* if the line starts with "macro" */
                removeSpacesAndTabs(line);
                lineField = strtok(NULL, " "); /* extracting the next field seprated with space, which will be the name of the macro */
                newMacroNode = createMacroNode();
                while(!feof(asmFile)){
                    fgets(line, MAX_LINE_LENGTH, asmFile);
                    removeSpacesAndTabs(line);
                    lineField = strtok(line, " "); /* get the first word in the line. */
                    if(strcmp(lineField, "endmacro") == 0) break;
                    strcpy((newMacroNode->content + newMacroNode->contentLength), line);
                    newMacroNode->contentLength += MAX_LINE_LENGTH;
                    newMacroNode->content = (char*)realloc(newMacroNode->content, newMacroNode->contentLength);
                }
                InsertNode(macroTable, newMacroNode);
            }

            
            printf("the file data is = %s\n", line);
        }
        
        fclose(asmFile);
        return 1;
}




