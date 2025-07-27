#include <stdio.h>
#include <stdlib.h>

#define MAX_GRUPOS 5
#define MAX_PALAVRAS 5
#define TAM_PALAVRA 7
#define TAM_DICA 256
#define PATH "jogos.txt"
#define PATH_ID "jogos_id.txt"

typedef struct {
    char palavra[TAM_PALAVRA];
    char dica[TAM_DICA];
} Rodada;

int main() {
    Rodada grupos[MAX_GRUPOS][MAX_PALAVRAS] = {
        { 
            {"bola", "inicial"},
            {"cola", "gruda"},
            {"mola", "quica"},
            {"moda", "matematica"},
            {"poda", "corte de uma arvore"}
        },
        {
            {"bola", "inicial"},
            {"cola", "gruda"},
            {"mola", "quica"},
            {"dola", "juridico"},
            {"doca", "barcos"}
        },
        {
            {"joga", "inicial"},
            {"roga", "crente"},
            {"roda", "carro"},
            {"roma", "coliseu"},
            {"soma", "operacao matematica"}
        },
        { 
            {"fama", "inicial"},
            {"cama", "dormir"},
            {"dama", "muie rica"},
            {"data", "calendario"},
            {"mata", "floresta"}
        },
        { 
            {"galo", "inicial"},
            {"ralo", "banheiro"},
            {"ramo", "plantas e ervas"},
            {"rumo", "para onde esta indo"},
            {"fumo", "cancer nos pulmoes"}
        }
    };

    FILE *path = fopen(PATH, "a");
    FILE *path_id = fopen(PATH_ID, "a");
    for (int i = 0; i < MAX_GRUPOS; i++) {
        char id[3];
        sprintf(id, "%d", i+1);
        fprintf(path, "%s\n", id);    
        fprintf(path_id, "%s\n", id);
        
        for (int j = 0; j < MAX_PALAVRAS; j++) {
            fprintf(path, "%s|%s\n", grupos[i][j].palavra, grupos[i][j].dica);
        }
        
    }
    fclose(path);
    fclose(path_id);

}
