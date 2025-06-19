#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aero.h"
#include "frequentes.h"

void cadastrarAeroportos(Aeroporto *A, int *qtdeA){
    Aeroporto novoAeroporto;
    int i, find = 0;

    FILE *arquivo = fopen("aeroportos.txt", "a");

    if (!arquivo) {
        printf("Erro ao abrir o arquivo de aeroportos!\n");
        return;
    }

    // Limpeza de buffer
    limparBuffer();

    printf("\n---- CADASTRO DE AEROPORTOS ----\n");


    while (1) {
        limparBuffer();
        printf("Codigo do aeroporto (3 letras): ");
        fgets(novoAeroporto.codigo, 50, stdin);
        novoAeroporto.codigo[strcspn(novoAeroporto.codigo, "\n")] = '\0';

        // Verifica se o código tem exatamente 3 caracteres
        if (strlen(novoAeroporto.codigo) == 3 &&
            isalpha(novoAeroporto.codigo[0]) &&
            isalpha(novoAeroporto.codigo[1]) &&
            isalpha(novoAeroporto.codigo[2])) {
            break; // Código válido, sai do loop
        }

        printf("Erro: O codigo do aeroporto deve ter exatamente 3 letras.\n");
    }

    printf("Nome do aeroporto: ");
    fgets(novoAeroporto.nome, 50, stdin);
    novoAeroporto.nome[strcspn(novoAeroporto.nome, "\n")] = '\0';

    printf("Cidade: ");
    fgets(novoAeroporto.cidade, 50, stdin);
    novoAeroporto.cidade[strcspn(novoAeroporto.cidade, "\n")] = '\0';

    printf("Estado: ");
    fgets(novoAeroporto.estado, 50, stdin);
    novoAeroporto.estado[strcspn(novoAeroporto.estado, "\n")] = '\0';

    // Verificar se Passageiro já foi cadastrado
    for(i = 0; i < *qtdeA; i++){
        if(strcmp(A[i].codigo, novoAeroporto.codigo) == 0){
            find = 1;
        }
    }

    if(find != 0){
        printf("Erro: Aeroporto já cadastrado.\n");
            return;
        }
        else{
            A[*qtdeA] = novoAeroporto;
            (*qtdeA)++;
    }

    /*
    // Grava os dados no arquivo
    fprintf(arquivo, "%s;%s;%s;%s\n", novoAeroporto.codigo, novoAeroporto.nome, novoAeroporto.cidade, novoAeroporto.estado);

    fclose(arquivo);
    */

    printf("Aeroporto cadastrado com sucesso!\n");
}

int carregarAeroportos(Aeroporto **A, int *tamAe){
    int qtde = 0;
    char linha[300]; // Declaração de string para armazenar cada linha lida do arquivo
    FILE *arq = fopen("aeroportos.txt", "r");

    limparBuffer();

    if(!arq){
        printf("Erro ao abrir arquivo de Passageiros Fidelizados.\n");
        return 0; // Nenhum passageiro carregado
    }

     // Saber a quantidade de passageiros que tem no arquivo
     while(fgets(linha, sizeof(linha), arq)){
        if(qtde >= *tamAe){
            *tamAe *= 2;
            *A = (Aeroporto *)realloc(*A, (*tamAe) * sizeof(Aeroporto));
        }

        // Extração dos dados da string linha, separando cada campo por;
        sscanf(linha, "%[^;];%[^;];%[^;];%[^\n]", (*A)[qtde].codigo, (*A)[qtde].nome, (*A)[qtde].cidade, (*A)[qtde].estado);

        qtde++;
     }

    fclose(arq);
    printf("%d Aeroportos carregados!\n", qtde);

    return qtde;
}

void salvarAeroportos(Aeroporto *A, int qtdeA){
    int i;

    // Abertura do arquivo
    FILE *arq = fopen("Aeroportos.txt", "w");

    // Verificação se o arquivo foi aberto com sucesso
    if(!arq){
        printf("Erro ao abrir arquivo de Aeroportos.\n");
        return;
    }

    for(i = 0; i < qtdeA; i++){
        fprintf(arq, "%s;%s;%s;%s\n", A[i].codigo, A[i].nome, A[i].cidade, A[i].estado);
    }
    // Fechamento do arquivo
    fclose(arq);
    printf("Arquivo Atualizado com sucesso!\n");
}



void listarAeroportos() {
    Aeroporto aeroporto;
    FILE *arquivo = fopen("aeroportos.txt", "r");
    if (!arquivo) {
        printf("Nenhum aeroporto cadastrado.\n");
        return;
    }

     // Limpeza de buffer
    limparBuffer();


    printf("\n=== LISTA DE AEROPORTOS ===\n");
    while (fscanf(arquivo, " %49[^;];%49[^;];%49[^;];%49[^\n]", aeroporto.codigo, aeroporto.nome, aeroporto.cidade, aeroporto.estado) == 4) {
        printf("Codigo: %s\n", aeroporto.codigo);
        printf("Nome: %s\n", aeroporto.nome);
        printf("Cidade: %s\n", aeroporto.cidade);
        printf("Estado: %s\n", aeroporto.estado);
        printf("-----------------------------\n");
    }

    fclose(arquivo);
}
