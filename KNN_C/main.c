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

    PrintArray(pontos, maxLinhas);
    PrintArray(testes, maxLinhasTestes);

    return 0;
}
