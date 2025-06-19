#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

typedef struct {
    char codigo[50];
    char nome[100];
    char cpf[15];
    char dataNasc[11]; // Formato: DD/MM/AAAA
    char telefone[15];

} Passageiro;

void cadastrarFidelizados(Passageiro *F, int *qtdePF);
int carregarFidelizados(Passageiro **F, int *tamPF);
void salvarFidelizados(Passageiro *F, int qtdePF);
void pesquisarFidelizados(Passageiro *F, int qtdePF);
void alterarFidelizados(Passageiro *F, int qtdePF);

#endif
