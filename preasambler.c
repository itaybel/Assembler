struct Macro{
    char *name;
    int start_macro;
    int end_macro;
};

/*
 * 0) create output file - fopen fclose
 * 1) loop through file - fgets
 * 2) parse each line to fine "macro" - strtok strcmp
 * 3) if macro -> insert to linstlist.
 * 3.1) else copy line to output file - fprintf
 *
 * // need to pay attention to pointers, example to check if name points on another name,
 * // fopen, to check if the name of the file is correct, for example, file name ends with "ps,am",
 * // need to check if we received macro name and ect, for example:
 * "macro m1
 * 1
 * 2
 * 3
 * end macro
 * m1"
 * // functions that could help to implement this algo are: ftell,fseek,
 */
