#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "utilidade.h"

int main() {

    int maxLinhas = 576;
    struct Ponto pontos[maxLinhas];

    int maxLinhasTestes = 192;
    struct Ponto testes[maxLinhasTestes];

    Leitura(pontos, maxLinhas);
    LeituraTest(testes, maxLinhasTestes);

    PrintArray(pontos, maxLinhas);
    PrintArray(testes, maxLinhasTestes);

    return 0;
}
