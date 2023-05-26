/*
Esse arquivo deve conter a logica do simulador.
*/

#include <stdio.h>
#include <stdlib.h>
#include "odos.h"

//Os buffers and global variables
pcb process_control_block[BUFFER_SIZE];

int init_pcb_line(pcb* pcb_line){
    pcb_line->process_name = (char*) calloc(BUFFER_SIZE, sizeof(char));
    
    pcb_line->program = (prog*) calloc(1, sizeof(prog));
    pcb_line->program->instruction_words = (word*) calloc(BUFFER_SIZE, sizeof(word));


    if(!pcb_line->process_name || !pcb_line->program || !pcb_line->program->instruction_words) return 0;

    return 1;
}
