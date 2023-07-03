#include <stdio.h>
#include <stdlib.h>

#include "odos.h"
#include "sint.h"
#include "srtf.h"
#include "threads.h"
#include "memory.h"
#include "interface.h"
#include "disk.h"

extern pcb* pcbBuffer;
int size = 10;
int diskVector[10] = {0};

void setTime(prog* current_program) {
    int i=0;

    while(diskVector[i]>0 && i<=size) {
        i++;
    }

    if(i>size) {
        errorSettingTime();
    }
    else {
        diskVector[i]=current_program->instruction_words[current_program->word_count++].instruction.remaining_time;
    }
}