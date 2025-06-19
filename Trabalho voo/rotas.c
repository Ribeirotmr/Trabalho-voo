#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rotas.h"
#include "frequentes.h"

float distanciaMilhas(char *origem, char *destino) {
    //abre o arquivo para leitura e procura
    FILE *arquivo = fopen("distanciaMilhas.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo distanciaMilhas.txt.\n");
        return -1.0;
    }

    // Limpeza de buffer
    limparBuffer();

    char linha[150];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char origemArquivo[50], destinoArquivo[50];
        float distancia = -1.0;

        linha[strcspn(linha, "\n")] = '\0';

        // le os dados da linha
        int camposLidos = sscanf(linha, "%[^;];%[^;];%f", origemArquivo, destinoArquivo, &distancia);


        // compara  origemArquivo == origem e destinoArquivo == destino IDA E VOLTA TEM A MSM DISTANCIA!!!
        if ((strcmp(origemArquivo, origem) == 0 && strcmp(destinoArquivo, destino) == 0) ||
            (strcmp(origemArquivo, destino) == 0 && strcmp(destinoArquivo, origem) == 0)) {
            //printf("Rota encontrada: Origem='%s', Destino='%s', Distancia=%.2f\n", origemArquivo, destinoArquivo, distancia);
            fclose(arquivo);
            return distancia; // Retorna a distância
        }
    }

    printf("Rota não encontrada.\n");
    fclose(arquivo);
    return -1.0; //caso não ache
}


void cadastrarRotas(Rota *R, int *qtdeRo) {
    Rota novaRota;

    //abre o arquivo
    FILE *arquivo = fopen("rotas.txt", "a");

    if (!arquivo) {
        printf("Erro ao abrir o arquivo de rotas!\n");
        return;
    }

    printf("\n---- CADASTRO DE ROTAS ----\n");

    // codigo
    limparBuffer();
    printf("Codigo da rota: ");
    fgets(novaRota.codigo, 50, stdin);
    novaRota.codigo[strcspn(novaRota.codigo, "\n")] = '\0';

    // origem
    printf("Origem: ");
    fgets(novaRota.origem, 50, stdin);
    novaRota.origem[strcspn(novaRota.origem, "\n")] = '\0';

    // destino
    printf("Destino: ");
    fgets(novaRota.destino, 50, stdin);
    novaRota.destino[strcspn(novaRota.destino, "\n")] = '\0';

    // nome
    snprintf(novaRota.nome, sizeof(novaRota.nome), "%s - %s", novaRota.origem, novaRota.destino);

    // tipo (DIARIO OU NÃO REGULAR)
    printf("Tipo de voo (1 = diario, 2 = nao regular): ");
    scanf("%d", &novaRota.tipo);
    limparBuffer();

    // horario
    printf("Horario do voo (HH:MM): ");
    while (1) {
        if (scanf("%d:%d", &novaRota.hora, &novaRota.min) == 2) {
            // Verifica se o horário e válido
            if ((novaRota.hora >= 0 && novaRota.hora <= 23) && (novaRota.min >= 0 && novaRota.min <= 59)) {
                break;
            } else {
                printf("Erro: Horario invalido. Tente novamente: ");
            }
        } else {
            limparBuffer();
            printf("Erro: Formato invalido. Tente novamente: ");
        }
    }

    // Dia da semana (se o voo não for diário)
    if (novaRota.tipo == 1) {
        strcpy(novaRota.diaSemana, "Diario");
    } else {
        printf("Dia do voo (Dias da semana): ");
        fgets(novaRota.diaSemana, 50, stdin);
        novaRota.diaSemana[strcspn(novaRota.diaSemana, "\n")] = '\0';
    }

    // Poltronas disponivel
    printf("Poltronas Disponiveis: ");
    scanf("%d", &novaRota.poltronasDis);

    // Total de poltronas
    printf("Total de poltronas: ");
    scanf("%d", &novaRota.totalPoltronas);

    // Distancia
    float distancia = distanciaMilhas(novaRota.origem, novaRota.destino);
    novaRota.distancia = distancia;
    printf("Nova rota distância armazenada: %.1f\n", novaRota.distancia);

    if (novaRota.distancia == -1) {
        printf("Rota não encontrada no arquivo distanciaMilhas.txt!\n");
        printf("Cadastro cancelado.\n");
        fclose(arquivo);
        return;
    }

    // grava a rota no arquivo rota.txt
    fprintf(arquivo, "%s;%s;%d;%d;%d;%s;%d;%.1f;%d\n",
            novaRota.codigo, novaRota.nome, novaRota.tipo,
            novaRota.hora, novaRota.min, novaRota.diaSemana,
            novaRota.poltronasDis, novaRota.distancia, novaRota.totalPoltronas);

    fclose(arquivo);

    printf("Rota cadastrada com sucesso!\n");

    // lista as rotas cadastradas APAGAR DPS
    listarRotas();
}

void listarRotas() {
    Rota rota;
    FILE *arquivo = fopen("rotas.txt", "r");

    if (!arquivo) {
        printf("Nenhuma rota cadastrada.\n");
        return;
    }

    printf("\n-------ROTAS--------\n");

    while (fscanf(arquivo, "%49[^;];%99[^;];%d;%d;%d;%49[^;];%d;%f\n",rota.codigo, rota.nome, &rota.tipo, &rota.hora, &rota.min,
            rota.diaSemana, &rota.poltronasDis, &rota.distancia) == 8) {

        printf("Codigo: %s\n", rota.codigo);
        printf("Nome: %s\n", rota.nome);
        printf("Tipo: %s\n", rota.tipo == 1 ? "Diario" : "Nao Regular");
        printf("Dia da Semana: %s\n", rota.diaSemana);
        printf("Horario: %02d:%02d\n", rota.hora, rota.min);
        printf("Poltronas Disponiveis: %d\n", rota.poltronasDis);
        printf("Distancia: %.1f milhas\n", rota.distancia);
        printf("--------------------------\n");
    }

    fclose(arquivo);
}


void salvarRotas(Rota *R, int qtdeRo){
    if(R == NULL || qtdeRo == 0){
        printf("Nenhuma rota para salva.\n");
        return;
    }

    FILE *arquivo = fopen("rotas.dat", "wb");
    if (!arquivo) {
        printf("Erro ao salvar rotas!\n");
        return;
    }

    fwrite(&qtdeRo, sizeof(int), 1, arquivo);
    fwrite(R, sizeof(Rota), qtdeRo, arquivo);
    fclose(arquivo);
}

int carregarRotas(Rota **R, int *qtdeRo) {
    FILE *arquivo = fopen("rotas.dat", "rb");
    if (!arquivo) {
        return 0;
    }

    fread(qtdeRo, sizeof(int), 1, arquivo);

    if (*qtdeRo > 0) {
        *R = (Rota *)malloc(*qtdeRo * sizeof(Rota*));
        if (*R == NULL) {
            printf("Erro ao alocar a memória.\n");
            fclose(arquivo);
            return 0;
        }
        fread(*R, sizeof(Rota), *qtdeRo, arquivo);
    }
    fclose(arquivo);
    return *qtdeRo;
}
