struct Macro{
    char *name;
    int start_macro;
    int end_macro;
};

void file_handler(){
        FILE *asmFile;
        char line[MAX_LINE_LENGTH];
        asmFile = fopen("assembler_test.txt","r");
        

        if(asmFile != NULL) {
            while (!feof(asmFile)) {
                fgets(line, MAX_LINE_LENGTH, asmFile);
                printf("the file data is = %s\n", line);
            }
            fclose(asmFile);
        }
        else{
            printf("\nUnable to open the assembler_test.asm file");
        }


