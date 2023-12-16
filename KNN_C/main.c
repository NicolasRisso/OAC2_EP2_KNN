#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

int main() {

    char xtrainFileName[] = "../data/xtrain200000.txt";
    char ytrainFileName[] = "../data/ytrain200000.txt";
    char xtestFileName[] = "../data/xtest.txt";

    int numCol = ContarCol(xtrainFileName);

    int maxLinhas = CountFileLines(xtrainFileName);
    Ponto *pontos = (Ponto *)malloc(maxLinhas * sizeof(Ponto));
    for (int i = 0; i < maxLinhas; i++) {
        // Supondo que você deseja alocar dinamicamente para o membro 'x'
        pontos[i].x = (float *)malloc(sizeof(float) * 8);
        // Inicializa outros membros
        pontos[i].classe = 0.0;
        pontos[i].id = i + 1;  // Atribui um ID fictício
    }

    int maxLinhasTestes = CountFileLines(xtestFileName);
    Ponto *testes = (Ponto *)malloc(maxLinhas * sizeof(Ponto));
    for (int i = 0; i < maxLinhas; i++) {
        // Supondo que você deseja alocar dinamicamente para o membro 'x'
        pontos[i].x = (float *)malloc(sizeof(float) * numCol);
        // Inicializa outros membros
        pontos[i].classe = 0.0;
        pontos[i].id = i + 1;  // Atribui um ID fictício
    }

    LeituraTrain(pontos, xtrainFileName, ytrainFileName);
    LeituraTest(testes, xtestFileName);

    //PrintArray(pontos, maxLinhas);
    //PrintArray(testes, maxLinhasTestes);

    double time = KNN(pontos, testes, 1, maxLinhas, maxLinhasTestes);
    printf("Tempo de Execucao: %.4fs", time);

    //PrintArray(pontos, maxLinhas);
    //PrintArray(testes, maxLinhasTestes);

    //int tmp = ordena(3, xtrain, ytrain, xtest);

    return 0;
}
