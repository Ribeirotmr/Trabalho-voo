#ifndef VOO_H_INCLUDED
#define VOO_H_INCLUDED
#include "aero.h"
#define MAX_VOOS 50
#define MAX_POLTRONAS 100
#define MAX_HORARIOS 5

typedef struct {
    int hora;
    int minuto;
} Horario;

typedef struct {
    int disponivel;
    int idAssento;
    int disponibilidade;
} Poltrona;

typedef struct {
    char codigoRota[10];
    Aeroporto origem;
    Aeroporto destino;
    Horario horarios[MAX_HORARIOS];
    int numHorarios;
    int numPoltronas;
    Poltrona *poltronas;
    int poltronasDisponiveis;
} Voo;

// Funções
void cadastrarVoos(Voo *voos, int *totalVoos, Aeroporto *aeroportos, int totalAeroportos);
void inicializarAssentos(Poltrona *poltrona, int numPoltronas);
void escolherAssento(Voo *voos);
void carregarVoos(Voo **voos, int *totalVoo);
void salvarVoos(Voo *voos, int qtdeVoo);

#endif // VOO_H_INCLUDED
