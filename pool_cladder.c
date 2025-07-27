#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define PATH_JOGOS "jogos.txt" 
#define PATH_ID "jogos_id.txt" 
#define QTD_RODADAS 5

typedef struct {
    char palavra[7];
    char dica[256];
} Rodada;


void get_rodada(Rodada *r, char id[]);
int menu();
void jogar_rodada(Rodada *r);
char* arquivo();
char* random_id();
void comojogar();

int main(){

    Rodada rodadas[QTD_RODADAS];

    FILE *arqv;
    arqv = fopen (PATH_JOGOS, "r");
    if( arqv == NULL ) {
        printf("ERRO arquivo nao encontrado\n");
        exit(1);
    }
    
    fclose(arqv);
    
    int res;
    do{
        res = menu();
        if(res == 1){
            get_rodada(rodadas, random_id());
            jogar_rodada(rodadas);
        }else if(res == 2){
            char id[3];
            strcpy(id, arquivo());
            if(strcmp(id, "0") == 0)
                continue;
            get_rodada(rodadas, id);
            jogar_rodada(rodadas);
        }else if(res == 3){
            comojogar();
        }
        
    }while(res);
    
    
}

void get_rodada(Rodada *r, char id[]){
    
    int isrodada = 0;
    FILE *arqv = fopen(PATH_JOGOS, "r");
    
    int i = 0;
    char line[266];
    while(fgets(line, 266, arqv)){
        line[strcspn(line, "\n")] = 0;
        
        if(isrodada){
            const char *delimitier = "|";
            char *token; 
            token = strtok(line, delimitier);
            strcpy(r[i].palavra, token);
            token = strtok(NULL, delimitier);
            strcpy(r[i].dica, token);
            i++;
        }
        
        if(strcmp(line, id) == 0)
        isrodada = 1;
        
        if(i == QTD_RODADAS)
        break;
    }
    
    fclose(arqv);
}

int menu(){
    printf("------------------------------\n");
    printf("-----CLADDER VERSAO POBRE-----\n");
    printf("---------1.JOGAR--------------\n");
    printf("---------2.ARQUIVO------------\n");
    printf("---------3.COMO-JOGAR---------\n");
    printf("---------0.SAIR---------------\n");
    printf("------------------------------\n");
    printf("\n");
    
    int res;
    scanf("%d", &res);
    printf("\033[2J\033[1;1H");
    return res;
}

void jogar_rodada(Rodada *r){

    int status = 1;
    int i = 1;
    for (; i<QTD_RODADAS ; i++){
        
        printf("Palavra atual: %s\n", r[i-1].palavra);
        printf("Dica para a proxima palavra: %s\n", r[i].dica);
        printf("Digite a palavra: ");
        char v[7];
        scanf("%s",v);
        printf("\n");
        
        if(v[0] == '0'){
            status = 0;
            break;
        }

        if( strcmp( v , r[i].palavra ) != 0 ){
            printf("voce errou, tente novamente!\n");
            i--;
            sleep(1);
        }
        printf("\033[2J\033[1;1H");
    }

    printf(status ? "Voce venceu, parabens!" : "Voce perdeu, fica pra proxima");
    printf("\nA palavra correta era %s\n", r[(status ? i-1 : i)].palavra);
    sleep(2);
    printf("\033[2J\033[1;1H");
}

char* random_id(){
    srand(time(NULL));
    FILE *arqv;
    char line[3];
    int menor = 100, maior = 0;

    arqv = fopen(PATH_ID, "r");
    while(fgets(line, 3, arqv)){
        if(line != NULL){
            int num = atoi(line);
            if(num < menor)
                menor = num;
            if(num > maior)
                maior = num;

        }
    }
    fclose(arqv);

    int random_num = (rand() % (maior - menor + 1)) + menor;
    static char id[3];
    sprintf(id, "%d", random_num);
    return id;
}

char* arquivo(){
    FILE *arqv;
    char line[3];
    int menor = 100, maior = 0;
    
    printf("------------------------------\n");
    printf("-----CLADDER VERSAO POBRE-----\n");
    printf("------ARQUIVO-----------------\n");
    arqv = fopen(PATH_ID, "r");
    while(fgets(line, 3, arqv)){
        if(line != NULL){
            int num = atoi(line);
            if(num < menor)
                menor = num;
            if(num > maior)
                maior = num;
    
            line[strcspn(line, "\n")] = 0;
            printf("#%s ", line);
            if(num % 6 == 0)
                printf("\n");

        }
    }
    fclose(arqv);
    
    printf("\n");
    printf("------------------------------\n");
    printf("\n");
    

    int res;
    do{
        scanf("%d", &res);
        if(res == 0){
            res = 0;
            break;
        }

    }while(res < menor || res > maior);

    static char id[3];
    sprintf(id, "%d", res);
    printf("\033[2J\033[1;1H");
    return id;
}

void comojogar(){
    printf("-------------------------------------\n");
    printf("-----CLADDER VERSAO POBRE------------\n");
    printf("-----*Comece com uma palava base-----\n");
    printf("-----*Descubra a proxima palavra-----\n");
    printf("-----*Siga a dica--------------------\n");
    printf("-----*Cada palavra muda uma letra----\n");
    printf("-----*Joque jogos aleatórios com 1---\n");
    printf("-----*Escolha seu jogo com 2---------\n");
    printf("-----*Voce sempre pode sair com 0----\n");
    printf("-------------------------------------\n");
    printf("\n");   

    int res;
    do{
        scanf("%d", &res);
        if(res != 0)
            printf("Vai sair!?, tente 0!\n");
    }while(res != 0);
    printf("\033[2J\033[1;1H");
}