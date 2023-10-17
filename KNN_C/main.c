#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "utilidade.h"
#include "knn.h"

int main() {

    int maxLinhas = CountFileLines("../data/xtrain.txt");
    struct Ponto pontos[maxLinhas];

    int maxLinhasTestes = CountFileLines("../data/xtest.txt");
    struct Ponto testes[maxLinhasTestes];

    Leitura(pontos, maxLinhas);
    LeituraTest(testes, maxLinhasTestes);

    // PrintArray(pontos, maxLinhas);
    // PrintArray(testes, maxLinhasTestes);

    KNN(pontos, testes, 2, maxLinhas, maxLinhasTestes);

    float xtrain[maxLinhas * 8];
    float ytrain[maxLinhas];
    float xtest[maxLinhasTestes * 8];

    for (int i = 0; i < maxLinhas; i++){
        for (int j = 0; j < 8; j++){
            xtrain[i * 8 + j] = pontos[i].x[j];
        }
    }
    for (int i = 0; i < maxLinhas; i++) ytrain[i] = pontos[i].classe;
    for (int i = 0; i < maxLinhasTestes; i++){
        for (int j = 0; j < 8; j++){
            xtest[i * 8 + j] = testes[i].x[j];
        }
    }

    int tmp = ordena(3, xtrain, ytrain, xtest);

    return 0;
}
