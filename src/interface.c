#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h> //ToDo: Add ncurses to the include folder
#include <dirent.h>
#include <string.h>

#include "odos.h"
#include "sint.h"
#include "srtf.h"

extern int running;
extern pcb* pcbBuffer;
extern int showMemory;
extern int showProcess;

WINDOW *results;
WINDOW *messages;
WINDOW *menu;

char error_message[10*BUFFER_SIZE];

extern char process_info[10*BUFFER_SIZE];

int start_interface() {
    initscr();  // Inicializa a biblioteca ncurses
    cbreak();   // Desabilita o buffer de linha (lê um caractere por vez)
    noecho();   // Não exibe os caracteres digitados pelo usuário
    nodelay(stdscr, TRUE);  // Torna a função getch() não bloqueante
    curs_set(0); // Remove o cursor

    //gera as janelas
    results = newwin(LINES, 2*COLS/3, 0, 0);
    messages = newwin(LINES/2, COLS/3, 0, 2*COLS/3);
    menu = newwin(LINES/2, COLS/3, LINES/2, 2*COLS/3);

    wtimeout(menu,2000);
    wtimeout(results,50);
    wtimeout(messages,4000);
     // or nodelay(stdscr, TRUE);


    return 1;
}

void listarArquivos() {
    DIR *dir;
    struct dirent *entry;
    int i=0;

    // Especifique o caminho da pasta que você deseja listar
    const char *path = "./programs";

    // Abre o diretório
    dir = opendir(path);
    if (dir == NULL) {
        strcpy(error_message, "Nao foi possivel encontrar o diretorio");
        return;
    }

    // Lê os arquivos do diretório

    i=0;

    wclear(menu);  // Limpa a tela
    box(menu, 0, 0);

    while ((entry = readdir(dir)) != NULL) {
        if(strstr(entry->d_name, ".txt") != NULL){
            mvwprintw(menu, (1+i), 2, "%d- %s", (i+1), entry->d_name);
            wrefresh(menu);

            i++;
        } 
    }

    rewinddir(dir);

    int op = wgetch(menu), j=1;
    char filename[BUFFER_SIZE];

    if(op != ERR) {
        /*for(i=i;i>=0; j++) {
            entry = readdir(dir);

            if(strstr(entry->d_name, ".txt") != NULL){
               
                i--;
            }

            if(j=(op-'0')) {
                sprintf(filename, "./programs/%.60s", entry->d_name);
                strcpy(error_message, filename);
                //read_sint(filename, pcbBuffer);
            }
            
        }*/

        i=0; 

        while ((entry = readdir(dir)) != NULL) {
            if(strstr(entry->d_name, ".txt") != NULL){
                i++;

                if(i == (op-'0')) {
                    sprintf(filename, "./programs/%.60s", entry->d_name);
                   
                   
                    pcbBuffer = (pcb*) malloc(sizeof(pcb));
                    read_sint(filename, pcbBuffer);
                }
            } 
        }
    }

    // Fecha o diretório
    closedir(dir);
}

void newProcess() {
    wclear(menu);  // Limpa a tela
    box(menu, 0, 0);
    mvwprintw(menu, 1, 2, "Voce inseriu o arquivo do novo processo na pasta programs?");
    mvwprintw(menu, 3, 2, "1- Sim"); 
    mvwprintw(menu, 5, 2, "2- Nao"); 
    mvwprintw(menu, 7, 2, "3- Cancelar operacao");
    wrefresh(menu);

    int op = wgetch(menu);

    if (op != ERR) {
        switch(op) {
            case '1': listarArquivos();
                      break;
            
            case '2': strcpy(error_message, "Insira o arquivo na pasta programs antes de continuar");
                      break;

            case '3': break;
        }
    }
}

void processStatus() {
    
    int op;
    if(showProcess==0) {
        
        wclear(results);  // Limpa a tela
        box(results, 0, 0);
        mvwprintw(results, 1, 2, "Digite 4 se voce deseja sair do menu de exibicao dos processos");
        
        //Printa as informações de cada processo
        if(process_info)  
            mvwprintw(results, 3, 2, "%s", process_info);

        wrefresh(results);

        op = wgetch(results); 
    }
     if(showProcess==1) {
        wclear(results);  // Limpa a tela
        box(results, 0, 0);
        mvwprintw(results, 1, 2, "Aguarde...");
        wrefresh(results);
    }
    showProcess = 1;

}

void memoryStatus() {

}

int update_interface(){
    wclear(results);  // Limpa a tela
    box(results, 0, 0);
    wrefresh(results);

    wclear(messages);
    box(messages, 0, 0);
    mvwprintw(messages, 1, 2, "%s", error_message);
    wrefresh(messages);
    
    wclear(menu);  // Limpa a tela
    box(menu, 0, 0);
    mvwprintw(menu, 1, 2, "0- Fechar sistema operacional");
    mvwprintw(menu, 3, 2, "1- Inserir novos processos");
    mvwprintw(menu, 5, 2, "2- Verificar estados dos processos");
    mvwprintw(menu, 7, 2, "3- Verificar estado de ocupacao da memoria");
    wrefresh(menu);

    processStatus();
    int op = wgetch(menu);

    if(op != ERR) {
        switch(op) {
            case '1': 
                newProcess();
                break;
            
            case '2': 
                processStatus();
                break;
            
            case '3': 
                memoryStatus();
                break;

            case '0':
                running=0;
                break;
            
            default: 
                wclear(menu);  // Limpa a tela
                mvwprintw(menu, 1, 0, "Digite um valor valido");
                wrefresh(menu);
        }
    }

    refresh();

    return 0;
}

int end_interface(){
    endwin();
}