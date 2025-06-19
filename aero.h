#ifndef AERO_H
#define AERO_H

typedef struct {
    char codigo[50];
    char nome[50];
    char cidade[50];
    char estado[50];
} Aeroporto;

void cadastrarAeroportos(Aeroporto *A, int *qtdeA);
int carregarAeroportos(Aeroporto **A, int *tamAe);
void salvarAeroportos(Aeroporto *A, int qtdeA);
void listarAeroportos();

#endif
