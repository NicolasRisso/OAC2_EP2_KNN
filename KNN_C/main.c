#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"

int main() {

    int maxLinhas = 576; // Defina o tamanho máximo da matriz
    struct Ponto pontos[maxLinhas]; // Cada linha representa 4 pontos

    Leitura(pontos, maxLinhas);

    for (int i = 0; i < 576; i++) {
        printf("Ponto %d: ", i + 1);
        printf("x: [");
        for (int j = 0; j < 8; j++) {
            printf("%.2f", pontos[i].x[j]);
            if (j < 7) {
                printf(", ");
            }
        }
        printf("] ");
        printf("Classe: %.2f\n", pontos[i].classe);
    }

    return 0;
}
