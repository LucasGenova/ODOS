
/*
Esse arquivo deve contar o loop principal: A integração entre a lógica do simulador e a interface gráfica
*/
#include <stdio.h>
#include <stdio.h>
#include "odos.h"
#include "sint.h"
#include "srtf.h"

int main(){
    //pequeno teste: escalonador funciona
    /**/
    pcb new_line[BUFFER_SIZE];
    pcb* prox;

    read_sint("./programs/sint1.txt", &new_line[0]);
    read_sint("./programs/sint2.txt", &new_line[1]);
    read_sint("./programs/sint3.txt", &new_line[2]);

    queue_process(&new_line[0]);
    queue_process(&new_line[1]);
    queue_process(&new_line[2]);

    get_next_running_process(&prox);

    printf("\n%d\n%d\n%d\n%d", new_line[0].process_id, new_line[1].process_id, new_line[2].process_id, prox->process_id);

    //*/

    

    return 0;
}