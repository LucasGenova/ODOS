/*
Esse arquivo deve contar o loop principal: A integração entre a lógica do simulador e a interface gráfica
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //para as threads
#include <unistd.h> //para o sleep
#include <stdint.h> //para o casting

#include "odos.h"
#include "sint.h"
#include "srtf.h"
#include "threads.h"
#include "memory.h"
#include "interface.h"

int main(){
    start_interface();
    init_odos();

    //disparar interface e odos em threads diferentes
    while(RUNNING){
        update_interface();
        run_odos();
    }

    endwin();  // Encerra a biblioteca ncurses
    return 0;
}
