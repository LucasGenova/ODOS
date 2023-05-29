/*
Esse arquivo deve conter a logica do simulador.
*/

#include <stdio.h>
#include <stdlib.h>
#include "odos.h"
#include "sint.h"
#include "srtf.h"
#include "semaphore.h"
#include "memory.h"

//Os buffers and global variables
pcb process_control_block[BUFFER_SIZE]; //pcb buffer

pcb* running_process = NULL;

int t=0;
//srtf.h
s_queue queue[BUFFER_SIZE];
int queue_size;
int srtf_process;

//semaphore.h
semaphore semaphore_list[BUFFER_SIZE];


//main.c
extern pcb* pcbBuffer;
extern int showProcess;
extern char process_info[10*BUFFER_SIZE];

extern int showMemory;
extern char memory_info[10*BUFFER_SIZE];

extern FILE* debug;

/*
semaphoreP (10) -- tratamento de bloqueio de processo
semaphoreV (11) -- tratamento de desbloqueio de processo
memLoadReq (6) -- chamada de operação de carregamento na memória
memLoadFinish (7) -- sinalização de final de carregamento
*/

int init_odos(){
    for(int i=0; i<BUFFER_SIZE; i++){
        process_control_block[i].process_id=-1;
        process_control_block[i].process_state = KILLED;
    }
    init_queue();
    init_semaphore_list();

    return 1;
}

int init_pcb_line(pcb* pcb_line){
    if(pcb_line->process_name)
        free(pcb_line->process_name);

    pcb_line->process_name = (char*) calloc(BUFFER_SIZE, sizeof(char));
    
    pcb_line->program = (prog*) calloc(1, sizeof(prog));
    pcb_line->program->instruction_words = (word*) calloc(BUFFER_SIZE, sizeof(word));


    if(!pcb_line->process_name || !pcb_line->program || !pcb_line->program->instruction_words) return 0;

    return 1;
}

int process_create(pcb* system_pcb, pcb* read_process){
    int i;
    for(i=0; i<BUFFER_SIZE && system_pcb[i].process_id>=0 && system_pcb[i].process_state != KILLED; i++);

    if(!read_process->process_name) return 0;
    system_pcb[i].process_name = read_process->process_name;
    read_process->process_name = NULL;

    if(read_process->process_id<0) return 0;
    system_pcb[i].process_id = read_process->process_id;
    read_process->process_id = -1;

    system_pcb[i].process_state = READY;

    if(!read_process->program) return 0;    
    system_pcb[i].program = read_process->program;
    read_process->program = NULL;

    return 1;
}

int process_finish(pcb* finished_process){
    if(finished_process->process_name)
        free(finished_process->process_name);
    
    finished_process->process_id = -1;

    finished_process->process_state = KILLED;

    if(finished_process->program)
        free(finished_process->program);

    //ToDo: liberar memoria usada

    return 1;
}

int process_interrupt(){
    if(!running_process) return 1;

    running_process->process_state = READY;

    update_queue();

    running_process = NULL;

    return 1;
}

int run_odos(){
    //confere o buffer de novos processos
    
    fprintf(debug, "hi\n");
    if(pcbBuffer){
        process_create(process_control_block, pcbBuffer);
        
        free(pcbBuffer);
        pcbBuffer = NULL;
    }

    if(showProcess && running_process){
        sprintf(process_info, "%s - %d", running_process->process_name, queue[srtf_process].remaining_time);

        showProcess=0;
    }

    return 1;
}