/*
Esse arquivo deve contar o loop principal: A integração entre a lógica do simulador e a interface gráfica
*/
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h> //para as threads
#include <unistd.h> //para o sleep
#include <stdint.h> //para o casting

#include "odos.h"
#include "sint.h"
#include "srtf.h"
#include "threads.h"
#include "memory.h"
#include "interface.h"
//#include "disk.h"

int running = 1;

int showProcess = 1;
char process_info[10*BUFFER_SIZE];
char process_action[10*BUFFER_SIZE];

int showMemory = 1;
char memory_info[10*BUFFER_SIZE];

pcb* pcbBuffer;


int main(){
    start_interface();
    init_odos();

    //disparar interface e odos em threads diferentes
    while(running){
        
        update_interface();
        run_odos();
        usleep(20000);
    }

    end_interface();
    return 0;
}
