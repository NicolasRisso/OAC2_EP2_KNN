#include <stdio.h>
#include <stdlib.h>
#include "utilidade.h"
#include "knn.h"

void PrintArray(Ponto lista[], int max){
    for (int i = 0; i < max; i++) {
        printf("Ponto(%d | %d): ", i + 1, lista[i].id);
        printf("x: [");
        for (int j = 0; j < Lenght(lista[i].x); j++) {
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
    char linha[120]; //Qualquer arquivo que tenha uma linha com mais char do que esse array suporta resultará em problemas para a contagem.

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        contadorLinhas++;
    }

    fclose(arquivo);

    return contadorLinhas;
}


int ContarCol(char nomeArquivo[]){
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "r");
    char linha[1000];
    int contador = 0;

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1; // Retorna um valor negativo para indicar erro
    }

    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        for (int i = 0; linha[i] != '\0'; i++) if (linha[i] == ',') contador++;
    } else {
        printf("O arquivo está vazio.\n");
    }

    fclose(arquivo);
    return contador + 1; // Retorna o número de colunas na primeira linha do arquivo

}

int Lenght(float array[]) {
    int comprimento = 0;
    // Itera sobre o array até encontrar o término (assumindo que o término seja zero)
    while (array[comprimento] != -1) {
        comprimento++;
    }
    return comprimento;
}

void alocarEspaco(Ponto *ponto, int numColunas) {
    ponto->x = (float *)malloc((numColunas + 1) * sizeof(float));
    ponto->x[numColunas] = -1.0f;
}


void trocar(DistanciaPonto *a, DistanciaPonto *b) {
    float temp = a->distancia;
    a->distancia = b->distancia;
    b->distancia = temp;
}

void bubbleSort(DistanciaPonto distancias[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (distancias[j].distancia > distancias[j + 1].distancia) {
                trocar(&distancias[j], &distancias[j + 1]);
            }
        }
    }
}