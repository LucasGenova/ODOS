#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h> //ToDo: Add ncurses to the include folder

#include "../include/odos.h"
#include "../include/sint.h"
#include "../include/srtf.h"

void newProcess() {
    int running =1;
    
    do {
        clear();  // Limpa a tela
        mvprintw(5, 0, "Voce inseriu o arquivo do novo processo na pasta programs?"); 
        mvprintw(6, 0, "1- Sim"); 
        mvprintw(7, 0, "2- Nao"); 
        mvprintw(8, 0, "3- Cancelar operacao");
        refresh();
        
        int op = getch();

        if (op != ERR) {
            switch(op) {
                case '1': /*pcb new_line;
                          read_sint("./programs/sint2.txt", &new_line);*/
                          running=0;
                          break;
                
                case '2': clear();  // Limpa a tela
                          mvprintw(5, 0, "Insira o arquivo na pasta correta antes de prosseguir");
                          refresh();
                          break;

                case '3': running=0;
                          break;
            }
        }

        sleep(1); 
    }while(running==1);
}

void processStatus() {

}

void memoryStatus() {

}

int start_interface() {
    initscr();  // Inicializa a biblioteca ncurses
    cbreak();   // Desabilita o buffer de linha (lê um caractere por vez)
    noecho();   // Não exibe os caracteres digitados pelo usuário
    nodelay(stdscr, TRUE);  // Torna a função getch() não bloqueante

    int running =1;

    do {
        clear();  // Limpa a tela
        mvprintw(4, 0, "--------------------");
        mvprintw(5, 0, "| 1- Inserir novos |");
        mvprintw(6, 0, "|    processos     |");
        mvprintw(7, 0, "--------------------"); 

        mvprintw(4, 25, "------------------------");
        mvprintw(5, 25, "| 2- Verificar estados |");
        mvprintw(6, 25, "|    dos processos     |");
        mvprintw(7, 25, "------------------------");

        mvprintw(4, 54, "-----------------------");
        mvprintw(5, 54, "| 3- Verificar estado |");
        mvprintw(6, 54, "|    de ocupacao da   |");
        mvprintw(6, 54, "|    memoria          |");
        mvprintw(7, 54, "-----------------------");
        refresh();
        
        int op = getch();

        if (op != ERR) {
            switch(op) {
                case '1': newProcess();
                          break;
                
                case '2': processStatus();
                          break;
                
                case '3': memoryStatus();
                          break;
                
                default: printf("\n\nDigite um valor valido\n\n");
            }
        }

        sleep(1); 
    }while(running==1);

    endwin();  // Encerra a biblioteca ncurses

    return 0;
}