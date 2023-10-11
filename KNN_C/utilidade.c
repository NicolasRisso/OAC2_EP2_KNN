#include <stdio.h>
#include <stdlib.h>
#include "utilidade.h"
#include "leitura.h"

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