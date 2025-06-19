#ifndef ROTAS_H
#define ROTAS_H

typedef struct {
    char codigo[50];
    char nome[100];
    int tipo;
    int hora;
    int min;
    char diaSemana[20];
    int poltronasDis;
    float distancia;
    char origem[50];
    char destino[50];
    int totalPoltronas; 
} Rota;

float distanciaMilhas(char *origem, char *destino);
void cadastrarRotas(Rota *R, int *qtdeRo);
void listarRotas();
void salvarRotas(Rota *R, int qtdeRo);
int carregarRotas(Rota **R, int *qtdeRo);
Rota selecionarVoo();
#endif