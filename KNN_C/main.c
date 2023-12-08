#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

int main() {

    char xtrainFileName[] = "../data/xtrain.txt";
    char ytrainFileName[] = "../data/ytrain.txt";
    char xtestFileName[] = "../data/xtest.txt";

    int numCol = ContarCol("../data/xtrain.txt");

    int maxLinhas = CountFileLines(xtrainFileName);
    struct Ponto pontos[maxLinhas];

    int maxLinhasTestes = CountFileLines("../data/xtest.txt");
    struct Ponto testes[maxLinhasTestes];

    LeituraTrain(pontos, xtrainFileName, ytrainFileName);
    LeituraTest(testes, xtestFileName);

    // PrintArray(pontos, maxLinhas);
    // PrintArray(testes, maxLinhasTestes);

    KNN(pontos, testes, 1, maxLinhas, maxLinhasTestes);

    //PrintArray(pontos, maxLinhas);
   // PrintArray(testes, maxLinhasTestes);

    //int tmp = ordena(3, xtrain, ytrain, xtest);

    return 0;
}
