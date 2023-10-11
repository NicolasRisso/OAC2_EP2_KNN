#ifndef LEITURA_H
#define LEITURA_H

struct Ponto {
    float x[8];  //x, y, z, w, ...
    float classe;
};
typedef struct Ponto Ponto;

void Leitura(struct Ponto matrizPonto[], int numElementos);

#endif
