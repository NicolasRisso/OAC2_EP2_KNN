#ifndef LEITURA_H
#define LEITURA_H

struct Ponto {
    float x[8];  //x, y, z, w, u, v, s, t
    float classe;
};
typedef struct Ponto Ponto;

void Leitura(struct Ponto matrizPonto[], int numElementos);
void LeituraTest(Ponto matrizPonto[], int maxLinhas);

#endif
