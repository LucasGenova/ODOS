#include <stdio.h>
#include <stdlib.h>
#include "../include/odos.h"
#include "../include/sint.h"
#include "../include/srtf.h"

void newProcess() {
    int ok=0;

    printf("\n\nVoce inseriu o arquivo do novo processo na pasta programs?\n\n");

    while(ok==0) {
        scanf("");
    }
    read_sint("./programs/sint2.txt", &new_line);
}

void processStatus() {

}

void memoryStatus() {

}

int main() {
    int running = 1, op;

    do {
        printf("\n-------- MENU --------\n\n1- Inserir novo processo\n2- Verificar estados dos processos\n3- Verificar estado de ocupacao da memoria\n\nOpcao: ");
        scanf("%d", &op);

        switch(op) {
            case 1: newProcess();
                    break;
            
            case 2: processStatus();
                    break;
            
            case 3: memoryStatus();
                    break;
            
            default: printf("\n\nDigite um valor valido\n\n");
        }
    }while(running==1);

    return 0;
}