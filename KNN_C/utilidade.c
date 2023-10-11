#include <stdio.h>
#include <stdlib.h>
#include "utilidade.h"

void PrintArray(Ponto lista[], int max){
    for (int i = 0; i < max; i++) {
        printf("Ponto(%d): ", i + 1);
        printf("x: [");
        for (int j = 0; j < 8; j++) {
            printf("%.3f", lista[i].x[j]);
            if (j < 7) {
                printf(", ");
            }
        }
        printf("], ");
        printf("Classe: %.0f\n", lista[i].classe);
    }
}

int CountFileLines(char filePath[]){

    FILE *arquivo;
    arquivo = fopen(filePath, "r");
    if (arquivo == NULL) { perror("Erro ao abrir o arquivo"); return -1; }

    int contadorLinhas = 0;
    char linha[60]; //Qualquer arquivo que tenha uma linha com mais char do que esse array suporta resultará em problemas para a contagem.

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        contadorLinhas++;
    }

    fclose(arquivo);

    return contadorLinhas;
}