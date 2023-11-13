#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

int main() {

    char xtrainFileName[] = "../data/xtrain.txt";
    char ytrainFileName[] = "../data/ytrain.txt";

    int maxLinhas = CountFileLines(xtrainFileName);
    struct Ponto pontos[maxLinhas];

    int maxLinhasTestes = CountFileLines("../data/xtest.txt");
    struct Ponto testes[maxLinhasTestes];

    LeituraTrain(pontos, xtrainFileName, ytrainFileName);
    LeituraTest(testes, maxLinhasTestes);

    // PrintArray(pontos, maxLinhas);
    // PrintArray(testes, maxLinhasTestes);

    //KNN(pontos, testes, 1, maxLinhas, maxLinhasTestes);

    PrintArray(pontos, maxLinhas);
    PrintArray(testes, maxLinhasTestes);

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

    //int tmp = ordena(3, xtrain, ytrain, xtest);

    return 0;
}
