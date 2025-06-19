#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiros.h"
#include "frequentes.h"


void cadastrarFidelizados(Passageiro *F, int *qtdePF){
    Passageiro novoFidelizado;
    int i, find = 0;

    // Limpeza de Buffer
    limparBuffer();

    printf("\n---- CADASTRO DE PASAGEIROS FIDELIZADOS ----\n");

    printf("Código do Passageiro: ");
    fgets(novoFidelizado.codigo, 50, stdin);
    novoFidelizado.codigo[strcspn(novoFidelizado.codigo, "\n")] = '\0';

    printf("Nome do Passageiro: ");
    fgets(novoFidelizado.nome, 100, stdin);
    novoFidelizado.nome[strcspn(novoFidelizado.nome, "\n")] = '\0';

    printf("CPF: ");
    fgets(novoFidelizado.cpf, 15, stdin);
    novoFidelizado.cpf[strcspn(novoFidelizado.cpf, "\n")] = '\0';

    printf("Data de nascimento - (Formato: DD/MM/AAAA): ");
    fgets(novoFidelizado.dataNasc, 11, stdin);
    novoFidelizado.dataNasc[strcspn(novoFidelizado.dataNasc, "\n")] = '\0';

    printf("Telefone: ");
    fgets(novoFidelizado.telefone, 15, stdin);
    novoFidelizado.telefone[strcspn(novoFidelizado.telefone, "\n")] = '\0';

    // Verificar se Passageiro já foi cadastrado
    for(i = 0; i < *qtdePF; i++){
        if(strcmp(F[i].cpf, novoFidelizado.cpf) == 0){
            find = 1;
        }
    }

    if(find != 0){
        printf("Erro: Passageiro já cadastrado.\n");
            return;
        }
        else{
            F[*qtdePF] = novoFidelizado;
            (*qtdePF)++;
    }

    printf("\nCadastro de Passageiro Fidelizado realizado com sucesso!\n");

}

int carregarFidelizados(Passageiro **F, int *tamPF){
    int qtde = 0;
    char linha[300]; // Declaração de string para armazenar cada linha lida do arquivo
    FILE *arq = fopen("fidelizados.txt", "r");

    limparBuffer();

    if(!arq){
        printf("Erro ao abrir arquivo de Passageiros Fidelizados.\n");
        return 0; // Nenhum passageiro carregado
    }

     // Saber a quantidade de passageiros que tem no arquivo
     while(fgets(linha, sizeof(linha), arq)){
        if(qtde >= *tamPF){
            *tamPF *= 2;
            *F = (Passageiro *)realloc(*F, (*tamPF) * sizeof(Passageiro));
        }

        // Extração dos dados da string linha, separando cada campo por;
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^\n]", (*F)[qtde].codigo, (*F)[qtde].nome, (*F)[qtde].cpf, (*F)[qtde].dataNasc, (*F)[qtde].telefone);

        qtde++;
     }

    fclose(arq);
    printf("%d passageiros fidelizados carregados!\n", qtde);

    return qtde;
}

void salvarFidelizados(Passageiro *F, int qtdePF){
    int i;

    // Abertura do arquivo
    FILE *arq = fopen("fidelizados.txt", "w");

    // Verificação se o arquivo foi aberto com sucesso
    if(!arq){
        printf("Erro ao abrir arquivo de Passageiros Fidelizados.\n");
        return;
    }

    for(i = 0; i < qtdePF; i++){
        fprintf(arq, "%s;%s;%s;%s;%s\n", F[i].codigo, F[i].nome, F[i].cpf, F[i].dataNasc, F[i].telefone);
    }
    // Fechamento do arquivo
    fclose(arq);
    printf("Arquivo Atualizado com sucesso!\n");
}


void pesquisarFidelizados(Passageiro *F, int qtdePF){
    int i, find = 0;
    char busca_cpf[15];


    // Limpeza de Buffer
    limparBuffer();

    if(qtdePF == 0){
        printf("Não há passageiros fidelizados cadastrados\n");
        return;
    }
    else{
        printf("\n---- BUSCA POR PASSAGEIRO FIDELIZADO ----\n");
        printf("Insira o CPF: ");
        fgets(busca_cpf, 15, stdin);
        busca_cpf[strcspn(busca_cpf, "\n")] = '\0';

        for(i = 0; i < qtdePF; i++){
            if(strcmp(busca_cpf, F[i].cpf) == 0){
                printf("\n---- DADOS DO PASSAGEIRO ----\n");
                printf("NOME: %s\n", F[i].nome);
                printf("CODIGO: %s\n", F[i].codigo);
                printf("DATA DE NASCIMENTO: %s\n", F[i].dataNasc);
                printf("TELEFONE: %s\n", F[i].telefone);
            }
            else{
                printf("Passageiro nao encontrado.\n");
            }
        }
    }

}

void alterarFidelizados(Passageiro *F, int qtdePF){
    int i, opc, find = 0;
    char busca_cpf[15];

    // Limpeza de Buffer
    limparBuffer();

    if(qtdePF == 0){
        printf("Não há passageiros fidelizados cadastrados.\n");
        return;
    }

    printf("\n---- ALTERACAO DE DE PASSAGEIRO FIDELIZADO ----\n");
    printf("Insira o CPF do passageiro que deseja altera: ");
    fgets(busca_cpf, 15, stdin);
    busca_cpf[strcspn(busca_cpf, "\n")] = '\0';

    // Procurar o passageiro
    for(i = 0; i < qtdePF; i++){
        if(strcmp(busca_cpf, F[i].cpf) == 0){
            find = 1;


            printf("\n---- DADOS ATUAIS DO PASSAGEIRO ----\n");
            printf("1. Nome: %s\n", F[i].nome);
            printf("2. Codigo: %s\n", F[i].codigo);
            printf("3. Data de nascimento: %s\n", F[i].dataNasc);
            printf("4. Telefone: %s\n", F[i].telefone);
            printf("0. Para cancelar\n");

            printf("\nQual dos dados deseja alterar? ");
            scanf("%d", &opc);
            limparBuffer();

            switch(opc){
                case 1:
                    printf("Novo nome: ");
                    fgets(F[i].nome, 100, stdin);
                    F[i].nome[strcspn(F[i].nome, "\n")] = '\0';
                    break;
                case 2:
                    printf("Novo codigo: ");
                    fgets(F[i].codigo, 50, stdin);
                    F[i].codigo[strcspn(F[i].codigo, "\n")] = '\0';
                    break;
                case 3:
                    printf("Nova Data de Nascimento: ");
                    fgets(F[i].dataNasc, 11, stdin);
                    F[i].dataNasc[strcspn(F[i].dataNasc, "\n")] = '\0';
                    break;
                case 4:
                    printf("Novo telefone: ");
                    fgets(F[i].telefone, 15, stdin);
                    F[i].telefone[strcspn(F[i].telefone, "\n")] = '\0';
                    break;
                case 0:
                    printf("Alteração cancelada.\n");
                    return;
                default:
                    printf("Opção invalida!\n");
                    return;
            }
            printf("\nAlteração realizada com sucesso!\n");

            // Salvar arquivo novamente
            printf("Arquivo atualizado com novas informações!\n");

            break;
        }
    }
    if(!find){
        printf("Passageiro nao encontrado.\n");
    }
}

