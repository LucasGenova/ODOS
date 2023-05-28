/*
Esse é o arquivo de header de odos.c
Contém as definições das representações internas do simulador e as definições das funções do simulador
*/

#ifndef ODOS
#define ODOS

#define BUFFER_SIZE 100 //ToDo: as estruturas de dados devem crescer dinâmicamente sem a necessidade de um limite maximo

typedef enum proc_state{ // Estados previstos para um processo.
    RUNNING,
    READY,
    WAITING,
    BLOCKED,
    KILLED,
    //INACTIVE
}p_stt;

typedef enum inst_type{ // Instruções previstas para os programas sintéticos
    EXEC,
    READ,
    WRITE,
    P,
    V,
    PRINT
 
}inst_type;

typedef enum sys_call{
    processInterrupt = 1, //#interrupção gerada pela execução da função processCreate e pelo término de operações de E/S
    semaphoreP = 10,      //#tratamento de bloqueio de processo
    semaphoreV = 11,      //#tratamento de desbloqueio de processo
    DiskRequest = 4,      //chamada de operação de entrada/saída para disco
    DiskFinish = 5,       //sinalização de final de E/S para disco
    PrintRequest = 14,    //chamada de operação de entrada/saída para impressão
    PrintFinish = 15,     //sinalização de final de E/S para impressão
    memLoadReq = 6,       //#chamada de operação de carregamento na memória
    memLoadFinish = 7,    //#sinalização de final de carregamento
    fsRequest = 8,        //chamada para operação no sistema de arquivos
    fsFinish = 9,         //sinalização de final de operação no sistema de arquivos
    processCreate = 2,    //#chamada para iniciar a criação de um processo no BCP *
    processFinish = 3,    //#chamada para terminar a existência de um processo no BCP *
}

typedef struct instruction{
    inst_type instruction_type;
    int remaining_time;
}inst;

typedef struct operand{
    char value;
}opnd;

typedef union instruction_word{
    inst instruction;
    opnd operand;
}word;

typedef struct program{
    int pc;
    word* instruction_words;
    int word_count;
}prog;

typedef struct process_control_block{ //Esta struct representa uma linha do BCP
    char* process_name;
    int process_id;
    p_stt process_state;

    //program
    prog* program;
    //memory 
    int used_memory;
}pcb;

int init_odos();
int init_pcb_line(pcb* pcb_line);

int processInterrupt();
int processCreate(pcb* system_pcb, pcb* read_process);
int processFinish(pcb* finished_process);

#endif //ODOS