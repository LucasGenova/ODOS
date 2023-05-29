#ifndef SEMAPHORE
#define SEMAPHORE

#include "odos.h"

typedef struct semaphore{
    char sem_name;
    pcb* cur_user;
    pcb** requests;
}semaphore;

extern semaphore semaphore_list[BUFFER_SIZE];

int init_semaphore_list();
int create_semaphore(char sem_name);

int semaphore_P();
int semaphore_V();

#endif //SEMAPHORE