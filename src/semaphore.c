
#include <stdio.h>
#include <stdlib.h>
#include "semaphore.h"
//#include "disk.h"

int init_semaphore_list(){
    for(int i=0; i<BUFFER_SIZE; i++){
        semaphore_list[i].sem_name = 0;
        semaphore_list[i].requests = NULL;
        semaphore_list[i].cur_user = NULL;
    }
}

int create_semaphore(char sem_name){
    int i;
    for(i=0; i<BUFFER_SIZE && semaphore_list[i].sem_name; i++)
        if(semaphore_list[i].sem_name == sem_name) return 0;

    if(i<BUFFER_SIZE){
        semaphore_list[i].sem_name=sem_name;
        semaphore_list[i].cur_user=NULL;
        semaphore_list[i].requests=(pcb**) calloc(BUFFER_SIZE, sizeof(pcb*));
    }

}

int semaphore_P(){
    
}

int semaphore_V(){

}