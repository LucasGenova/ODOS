/*
Esse arquivo deve contar o loop principal: A integração entre a lógica do simulador e a interface gráfica
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //para as threads
#include <unistd.h> //para o sleep
#include <stdint.h> //para o casting
#include "../include/odos.h"
#include "../include/sint.h"
#include "../include/srtf.h"
#include "../include/threads.h"
#include "../include/memoria.h"
#define NUM_THREADS 16

int main(){

    pcb new_line;

    read_sint("./programs/sint2.txt", &new_line);
    
    //inicialização dos segmentos
    int num_segments = TOTAL_MEMORY_SIZE / PAGE_SIZE;
    Segment** segments = (Segment**)malloc(num_segments * sizeof(Segment*));

    //inicialização das threads
    pthread_t threads[NUM_THREADS];
    int i;
    int status;

    for (i = 0; i < NUM_THREADS; i++) {
        printf("Main: criando a thread %d\n", i + 1);
        //int status = pthread_create(&threads[i], NULL, thread_function, (void *)i);
        //int status = pthread_create(&threads[i], NULL, thread_function, (void *)(intptr_t)i);
        status = pthread_create(&threads[i], NULL, thread_function, (void *)(intptr_t)(i + 1));

        if (status) {
            printf("Erro ao criar a thread %d: %d\n", i, status);
            return -1;
        }
    }

    printf("Main: Todas as threads foram criadas com sucesso.\n");

    // Aguarda todas as threads terminarem
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: Todas as threads terminaram. Saindo do programa.\n");


    //Gerenciamento de Memória
    // Aloca os segmentos
    for (int i = 0; i < num_segments; i++) {
        segments[i] = allocateSegment(i, PAGE_SIZE);
    }

    // Desaloca os segmentos
    for (int i = 0; i < num_segments; i++) {
        deallocateSegment(segments[i]);
    }
    free(segments);


    //pequeno teste: escalonador funciona
    /**
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
