#include <stdio.h>
#include <pthread.h> //para as threads
#include <unistd.h> //para o sleep
#include <stdint.h> //para o casting

#define NUM_THREADS 16

int semaphore = 0;

void *thread_function(void *thread_id) {
    long tid = (long)thread_id;

    if (tid == 10) {
        printf("Thread #%ld: Esperando para adquirir o semáforo...\n", tid);
        while (semaphore <= 0) {
            // Aguarda até que o semáforo esteja disponível
        }
        semaphore--; // Adquire o semáforo
        printf("Thread #%ld: Semáforo adquirido! Executando a seção crítica.\n", tid);
        // Simulação da seção crítica
        sleep(2);
        printf("Thread #%ld: Liberando o semáforo.\n", tid);
        semaphore++; // Libera o semáforo
    } else if (tid == 11) {
        printf("Thread #%ld: Liberando o semáforo.\n", tid);
        semaphore++; // Libera o semáforo
    } else {
        printf("Thread #%ld: Executando a tarefa.\n", tid);
        sleep(1);
    }

    pthread_exit(NULL);
}
