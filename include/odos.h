/*
Esse é o arquivo de header de odos.c
*/

#ifndef ODOS
#define ODOS

typedef enum proc_state{ // Estados previstos para um processo.
    RUNNING,
    READY,
    WAITING,
    //INACTIVE
}p_stt;

typedef struct bcp{ //Esta struct representa uma linha do BCP
    char process_name[20];
    int process_id;
    p_stt process_state
    int* process_pages; //lista contendo o numero das paginas usadas em ordem
}bcp;

#endif //ODOS