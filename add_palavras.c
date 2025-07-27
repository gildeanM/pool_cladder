#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PATH_JOGOS "jogos.txt"
#define PATH_ID "jogos_id.txt"
#define QTD_RODADAS 5

char* incrementa_id();
void add_palavra();

int main(){
    
    add_palavra();


}

void add_palavra(){

    int qtd_letras;
    printf("Digite a quantidade de letras que as palavras terao: ");
    scanf("%d", &qtd_letras);
    
    char palavra[qtd_letras+1];
    char dica[250] = "inicial";
    FILE *arqv = fopen(PATH_JOGOS, "a+");
    if(arqv == NULL){
        printf("ERRO arquivo %s nao encontrado.\n", PATH_JOGOS);
        exit(1);
    }
    fprintf(arqv, "%s\n", incrementa_id());
    for(int i = 0; i < QTD_RODADAS; i++){
        
        scanf(" %[^\n]s", palavra);
        if(strlen(palavra) != qtd_letras){
            i--;
            continue;
        }

        if(i != 0)
            scanf(" %[^\n]s", dica);
            
        fprintf(arqv, "%s|%s\n", palavra, dica);
          
    }
    fclose(arqv);

    printf("\033[2J\033[1;1H");
}

char* incrementa_id(){
    
    static char str[3];
    int num = 1;
    
    FILE *arqv = fopen(PATH_ID, "a+");
    if(arqv == NULL){
        printf("ERRO arquivo %s nao encontrado.\n", PATH_ID);
        exit(1);
    }
    while(fgets(str, 3, arqv));
    if(str != NULL)
        num = atoi(str);


    snprintf(str,12, "%d", ++num);
    fprintf(arqv, "%s\n",str);


    fclose(arqv);

    return str;
    
}
