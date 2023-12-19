#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

int main() {

    char xtrainFileName[] = "../data/xtrain.txt";
    char ytrainFileName[] = "../data/ytrain.txt";
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

    int k = 1;
    int numThreads = 1;

    printf("Digite o numero do k: ");
    scanf("%d", &k);
    printf("Digite o numero de Threads: ");
    scanf("%d", &numThreads);

    double time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, numThreads);
    printf("Tempo de Execucao(1): %.3fs\n", time);

    //PrintArray(pontos, maxLinhas);
    //PrintArray(testes, maxLinhasTestes);

    //int tmp = ordena(3, xtrain, ytrain, xtest);

    return 0;
}
