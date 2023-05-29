#ifndef SRTF
#define SRTF

#include <stdlib.h>
#include "odos.h"
//ToDo:Implementar um heap mínimo

typedef struct srtf_queue{
    pcb* process_pointer;
    int remaining_time;
}s_queue;

int init_queue();
int queue_process(pcb* process);
int get_next_running_process(pcb** process_pointer);
int update_queue();

#endif //SRTF