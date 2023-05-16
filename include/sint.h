/*
Este é o arquivo de header de sint.c
*/


#ifndef SINT
#define SINT

#include <stdlib.h>

typedef enum inst_type{ // Instruções previstas para os programas sintéticos
    EXEC,
    READ,
    WRITE,
    P,
    V,
    PRINT
 
}inst_type;

typedef struct instruction{
    inst_type instruction_type;
    int remaining_time;
}inst;

typedef struct program{
    // info about the program

    //instruction list
    //placeholder:
    inst inst_list[1000];
}prog;


int read_sint(char* filename, prog* program_buffer);
#endif //SINT