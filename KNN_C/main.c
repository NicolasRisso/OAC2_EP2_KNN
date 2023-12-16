#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

int main() {

    char xtrainFileName[] = "../data/xtrain1000.txt";
    char ytrainFileName[] = "../data/ytrain1000.txt";
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

    int k = 3;
    double time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 100);
    printf("Tempo de Execucao(1): %.3fs\n", time);
    time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 2);
    printf("Tempo de Execucao(2): %.3fs\n", time);
    time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 3);
    printf("Tempo de Execucao(3): %.3fs\n", time);
    time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 4);
    printf("Tempo de Execucao(4): %.3fs\n", time);
    time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 5);
    printf("Tempo de Execucao(5): %.3fs\n", time);
    time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 10);
    printf("Tempo de Execucao(10): %.3fs\n", time);
    time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 20);
    printf("Tempo de Execucao(20): %.3fs\n", time);
    time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 50);
    printf("Tempo de Execucao(50): %.3fs\n", time);
    time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, 100);
    printf("Tempo de Execucao(100): %.3fs\n", time);

    //PrintArray(pontos, maxLinhas);
    //PrintArray(testes, maxLinhasTestes);

    //int tmp = ordena(3, xtrain, ytrain, xtest);

    return 0;
}
