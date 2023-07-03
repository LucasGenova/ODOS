/*
Este arquivo define funções referentes aos programas sintéticos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "odos.h"
#include "sint.h"
//#include "disk.h"

char string_buffer[BUFFER_SIZE];
extern char process_action[10*BUFFER_SIZE];

int read_sint(char* filename, pcb* process_created){
    FILE* sint_file;
    
    sint_file = fopen(filename, "r");
   
    if(!sint_file) return 0; // abertura do arquivo falhou
    
    fseek(sint_file, 0, SEEK_SET);
    //aloca memória para os campos representados por ponteiros
    if(!init_pcb_line(process_created)) return 0;
    fscanf(sint_file, "%s", process_created->process_name);
    fscanf(sint_file, "%d", &process_created->process_id);
    
    fscanf(sint_file, "%*d"); //ignora a prioridade (devido ao srtf)

    fscanf(sint_file, "%d ", &process_created->used_memory); //termina com um espaço para eliminar qualquer \n

    process_created->process_state = READY;

    while(fgetc(sint_file) != '\n'); //ignora a lista de semaforos

    while(!feof(sint_file)){
        parse_word(fgets(string_buffer, BUFFER_SIZE, sint_file), process_created->program);
    }
    /**
    FILE* output = fopen("output.txt", "w");
    fwrite(process_created->program->instruction_words, sizeof(word), process_created->program->word_count, output);
    fflush(output);
    //*/
}

int parse_word(char* instruction_read, prog* current_program){
    switch(instruction_read[0]){
        
        case 'e': //exec
            strcpy(process_action, "Exec");
            
            current_program->instruction_words[current_program->word_count].instruction.instruction_type = EXEC;
            
            sscanf(instruction_read, "%*s%d", &current_program->instruction_words[current_program->word_count++].instruction.remaining_time);
            break;

        case 'r': //read
            strcpy(process_action, "Read");

            current_program->instruction_words[current_program->word_count].instruction.instruction_type = READ;
            
            sscanf(instruction_read, "%*s%d", &current_program->instruction_words[current_program->word_count++].instruction.remaining_time);
            memoryStatus(current_program->instruction_words[current_program->word_count++].instruction.remaining_time);
            //AQUI TBM 
            break;

        case 'w': //write
            strcpy(process_action, "Write");

            current_program->instruction_words[current_program->word_count].instruction.instruction_type = WRITE;
            
            sscanf(instruction_read, "%*s%d", &current_program->instruction_words[current_program->word_count++].instruction.remaining_time);
            memoryStatus(current_program->instruction_words[current_program->word_count++].instruction.remaining_time);
            dRequest(current_program->instruction_words[current_program->word_count++].instruction.remaining_time, 0);
            //AQUI LUIZA -> AQUI LUIZA OQ? -> ONDE EU MUDEI BOBONA
            break;

        case 'p': //print
            strcpy(process_action, "Print");

            current_program->instruction_words[current_program->word_count].instruction.instruction_type = PRINT;
            
            sscanf(instruction_read, "%*s%d", &current_program->instruction_words[current_program->word_count++].instruction.remaining_time);
            pRequest(1, 1, 0);
            break;

        case 'P': //P(s)
            current_program->instruction_words[current_program->word_count].instruction.instruction_type = P;
            
            current_program->instruction_words[current_program->word_count++].instruction.remaining_time = 200;

            sscanf(&instruction_read[2], "%c", &current_program->instruction_words[current_program->word_count++].operand.value); //ToDo: Editar pra ler mais de um caracter

            break;

        case 'V': //V(s)
            current_program->instruction_words[current_program->word_count].instruction.instruction_type = V;
            
            current_program->instruction_words[current_program->word_count++].instruction.remaining_time = 200;

            sscanf(&instruction_read[2], "%c", &current_program->instruction_words[current_program->word_count++].operand.value); //ToDo: Editar pra ler mais de um caracter
            break;

        default:
            return 0;
            break;
    }
    return 1;
}
