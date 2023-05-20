/*
Esse é o arquivo de header de odos.c
*/

#ifndef ODOS
#define ODOS

#define BUFFER_SIZE 100

typedef enum proc_state{ // Estados previstos para um processo.
    RUNNING,
    READY,
    WAITING,
    BLOCKED,                                                                                                                                                                                          
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

int init_pcb_line(pcb* pcb_line);

#endif //ODOS