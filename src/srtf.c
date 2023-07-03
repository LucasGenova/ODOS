/*
Esse arquivo deve conter a logica do scheduler
*/

#include <stdio.h>
#include <stdlib.h>
#include "srtf.h"
//#include "disk.h"

extern s_queue queue[BUFFER_SIZE];
extern int queue_size;
extern int srtf_process;


int init_queue(){
    for(int i=0; i<BUFFER_SIZE; i++){
        queue[i].process_pointer=NULL;
        queue[i].remaining_time=0;
    }
}

int queue_process(pcb* process){
    if(queue_size>BUFFER_SIZE) return 0;

    queue[queue_size].process_pointer = process;
    
    queue[queue_size].remaining_time=0;
    for(int i=process->program->pc; i<process->program->word_count-process->program->pc; i++){
        switch(process->program->instruction_words[i].instruction.instruction_type){
            case EXEC:
            case PRINT:
                queue[queue_size].remaining_time+=process->program->instruction_words[i].instruction.remaining_time;
                break;

            case P:
            case V:
                queue[queue_size].remaining_time+=process->program->instruction_words[i].instruction.remaining_time;
                i++;
                break;

            default:
                break;
        }
    }

    queue_size++;
    return 1;
}

int get_next_running_process(pcb** process_pointer){
    srtf_process=0;
    int i;

    for(i=0; i<queue_size; i++){
        if(queue[i].process_pointer->process_state==READY){
            srtf_process=i;
            break;
        }
    }

    if(i==queue_size) return 0; //nenhum processo disponível (não acho que deva entrar aqui nunca)

    
    for(i++; i<queue_size; i++){
        if(queue[i].remaining_time && queue[i].process_pointer->process_state == READY && queue[i].remaining_time<queue[srtf_process].remaining_time)
            srtf_process=i;
    }

    (*process_pointer)=queue[srtf_process].process_pointer; 
    return srtf_process;
}

int update_queue(){
    //Após processamento, o remaining_time na queue muda, e quando um processo termina, ele se torna INACTIVE, não sendo mais selecionado. 

    queue[0].remaining_time=0;
    for(int i=queue[0].process_pointer->program->pc; i<queue[0].process_pointer->program->word_count-queue[0].process_pointer->program->pc; i++){
        switch(queue[0].process_pointer->program->instruction_words[i].instruction.instruction_type){
            case EXEC:
            case PRINT:
                queue[0].remaining_time+=queue[0].process_pointer->program->instruction_words[i].instruction.remaining_time;
                break;
            
            case P:
            case V:
                queue[0].remaining_time+=queue[0].process_pointer->program->instruction_words[i].instruction.remaining_time;
                i++;
                break;

            default:
                break;
        }
    }

    return 1;
}
