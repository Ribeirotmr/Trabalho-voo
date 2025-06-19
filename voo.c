#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequentes.h"
#include "voo.h"
#include "aero.h"

void cadastrarVoos(Voo *voos, int *totalVoos, Aeroporto *aeroportos, int totalAeroportos) {
    if (*totalVoos >= MAX_VOOS) {
        printf("N�mero m�ximo de voos cadastrados atingido.\n");
        return;
    }

    Voo voo;
    int origem, destino;

    printf("Digite o c�digo do voo: ");
    scanf("%s", voo.codigoRota);

    printf("Escolha o aeroporto de origem:\n");
    for (int i = 0; i < totalAeroportos; i++) {
        printf("[%d] %s (%s)\n", i + 1, aeroportos[i].nome, aeroportos[i].codigo);
    }

    scanf("%d", &origem);
    if (origem < 1 || origem > totalAeroportos) {
        printf("Aeroporto inv�lido.\n");
        return;
    }
    voo.origem = aeroportos[origem - 1];

    printf("Escolha o aeroporto de destino:\n");
    for (int i = 0; i < totalAeroportos; i++) {
        printf("[%d] %s (%s)\n", i + 1, aeroportos[i].nome, aeroportos[i].codigo);
    }

    scanf("%d", &destino);
    if (destino < 1 || destino > totalAeroportos) {
        printf("Aeroporto inv�lido.\n");
        return;
    }
    voo.destino = aeroportos[destino - 1];

    printf("Quantos hor�rios este voo ter�? ");
    scanf("%d", &voo.numHorarios);

    for (int i = 0; i < voo.numHorarios; i++) {
        printf("Digite o hor�rio %d (hora minuto): ", i + 1);
        int hora, minuto;
        if (scanf("%d %d", &hora, &minuto) == 2) {
            if (hora >= 0 && hora < 24 && minuto >= 0 && minuto < 60) {
                voo.horarios[i].hora = hora;
                voo.horarios[i].minuto = minuto;
            } else {
                printf("Hor�rio inv�lido, tente novamente.\n");
                i--;
            }
        } else {
            printf("Entrada inv�lida para o hor�rio, tente novamente.\n");
            i--;
            while (getchar() != '\n');
        }
    }

    printf("Quantas poltronas dispon�veis? ");
    scanf("%d", &voo.numPoltronas);

    voo.poltronas = (Poltrona *)malloc(voo.numPoltronas * sizeof(Poltrona));
    if (voo.poltronas == NULL) {
        printf("Erro na aloca��o de mem�ria para poltronas.\n");
        return;
    }

    for (int i = 0; i < voo.numPoltronas; i++) {
        voo.poltronas[i].disponivel = 1;
    }

    voos[*totalVoos] = voo;
    (*totalVoos)++;
    printf("Voo cadastrado com sucesso!\n");
}


void inicializarAssentos(Poltrona *poltrona, int numPoltronas){
    for (int i = 0; i < numPoltronas; i++) {
        poltrona[i].idAssento = i + 1;
        poltrona[i].disponibilidade = 1;
    }
}

void escolherAssento(Voo *voos, int vooIndex){
    Voo *voo = &voos[vooIndex];

    printf("\nEscolha um assento para o voo %s (%s -> %s):\n", voo->codigoRota,
           voo->origem.nome, voo->destino.nome);

    // Exibir lista de assentos dispon�vei e ocupados
    for (int i = 0; i < voo->numPoltronas; i++) {
        if(voo->poltronas[i].disponivel == 1){
            printf("%d - Assento %d [Dispin�vel]\n", i+1, voo->poltronas[i].idAssento);
        }else{
            printf("%d - Assento %d [ocupado]\n", i+1, voo->poltronas[i].idAssento);
        }
        }

    int escolha;
    printf("Escolha um assento (0 para cancelar): ");
    scanf("%d", &escolha);

    if (escolha > 0 && escolha <= voo->numPoltronas && voo->poltronas[escolha - 1].disponivel == 1) {
        voo->poltronas[escolha - 1].disponibilidade = 0;
        printf("Assento %d reservado com sucesso!\n", voo->poltronas[escolha - 1].idAssento);
    } else {
        printf("Assento inv�lido ou j� ocupado!\n");
    }
}


void carregarVoos(Voo **voos, int *totalVoo) {
    int i, j, qtde;
    FILE *arq = fopen("voos.txt", "r");

    if (!arq) {
        printf("Erro ao abrir arquivo de Voos.\n");
        return;
    }

    fscanf(arq, "%d", &qtde);
    *totalVoo = qtde;

    // Realocar mem�ria para armazenar os voos lidos
    Voo *temp = (Voo *)realloc(*voos, (*totalVoo) * sizeof(Voo));
    if (temp == NULL) {
        printf("Erro ao alocar mem�ria para voos.\n");
        fclose(arq);
        return;
    }
    *voos = temp; // Atualiza o ponteiro ap�s a realoca��o bem-sucedida

    for (i = 0; i < qtde; i++) {
        fscanf(arq, "%s %d", (*voos)[i].codigoRota, &(*voos)[i].numHorarios);

        for (j = 0; j < (*voos)[i].numHorarios; j++) {
            fscanf(arq, "%d %d", &(*voos)[i].horarios[j].hora, &(*voos)[i].horarios[j].minuto);
        }

        fscanf(arq, "%d", &(*voos)[i].numPoltronas);

        // Alocar mem�ria para as poltronas
        (*voos)[i].poltronas = (Poltrona *)malloc((*voos)[i].numPoltronas * sizeof(Poltrona));
        if ((*voos)[i].poltronas == NULL) {
            printf("Erro ao alocar mem�ria para poltronas do voo %s.\n", (*voos)[i].codigoRota);
            fclose(arq);
            return;
        }

        for (j = 0; j < (*voos)[i].numPoltronas; j++) {
            fscanf(arq, "%d %d", &(*voos)[i].poltronas[j].idAssento, &(*voos)[i].poltronas[j].disponivel);
        }
    }

    fclose(arq);
    printf("%d voos carregados com sucesso!\n", qtde);
}

void salvarVoos(Voo *voos, int qtdeVoos) {
    FILE *arquivo = fopen("voos.dat", "wb");
    if (!arquivo) {
        printf("Erro ao salvar voos!\n");
        return;
    }

    fwrite(&qtdeVoos, sizeof(int), 1, arquivo);
    for (int i = 0; i < qtdeVoos; i++) {
        fwrite(&voos[i], sizeof(Voo), 1, arquivo);
        for (int j = 0; j < voos[i].numPoltronas; j++) {
            fwrite(&voos[i].poltronas[j], sizeof(Poltrona), 1, arquivo);
        }
    }
    fclose(arquivo);
}
