/*
Este é o arquivo de header de sint.c
*/

#ifndef SINT
#define SINT

#include <stdlib.h>
#include "odos.h"

int read_sint(char* filename, pcb* process_created);
int parse_word(char* inst, prog* current_program);

#endif //SINT