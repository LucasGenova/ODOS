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

int running = 1;

int showProcess = 0;
char process_info[10*BUFFER_SIZE];

int showMemory = 0;
char memory_info[10*BUFFER_SIZE];

pcb* pcbBuffer;

FILE* debug;

int main(){
    start_interface();
    init_odos();

    debug = fopen("debug.txt", "w");
    //disparar interface e odos em threads diferentes
    while(running){
        update_interface();
        usleep(20000);
        run_odos();
    }

    end_interface();
    return 0;
}
