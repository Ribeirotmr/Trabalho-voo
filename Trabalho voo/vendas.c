#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "vendas.h"
#include "frequentes.h"
#include "aero.h"
#include "rotas.h"
#include "passageiros.h"

typedef struct {
    char codigoVenda[20];
    char cpfPassageiro[15];
    char codigoRota[50];
    int hora;
    int min;
    char data[11];
    char assento[5];
    float valor;
    char formaPagamento[10];
} Venda;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

float calcularPrecoPassagem(float distancia, int diasParaViagem, int diaSemana, int poltronasVagas) {
    float precoMilha;
    if (distancia <= 500) precoMilha = 0.36;
    else if (distancia <= 800) precoMilha = 0.29;
    else precoMilha = 0.21;

    float fatorPeriodo;
    if (diasParaViagem <= 3) fatorPeriodo = 4.52;
    else if (diasParaViagem <= 6) fatorPeriodo = 3.21;
    else if (diasParaViagem <= 10) fatorPeriodo = 2.25;
    else if (diasParaViagem <= 15) fatorPeriodo = 1.98;
    else if (diasParaViagem <= 20) fatorPeriodo = 1.78;
    else if (diasParaViagem <= 30) fatorPeriodo = 1.65;
    else fatorPeriodo = 1.45;

    float fatorDia;
    if (diaSemana == 0) fatorDia = 3.56; 
    else if (diaSemana == 6 || diaSemana == 7) fatorDia = 1.21; 
    else fatorDia = 1.00; 

    float fatorProcura;
    float ocupacao = (1.0 - ((float)poltronasVagas / 100.0)) * 100;
    if (ocupacao > 90) fatorProcura = 0.75;
    else if (ocupacao > 70) fatorProcura = 0.85;
    else if (ocupacao > 60) fatorProcura = 0.95;
    else if (ocupacao > 40) fatorProcura = 1.00;
    else if (ocupacao > 20) fatorProcura = 1.15;
    else if (ocupacao > 10) fatorProcura = 1.20;
    else fatorProcura = 1.35;

    return distancia * precoMilha * fatorPeriodo * fatorDia * fatorProcura;
}

void gerarCodigoVenda(char *codigo) {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    int num = rand() % 10000;
    snprintf(codigo, 20, "VND-%04d", num);
}

int salvarVenda(Venda venda) {
    FILE *arquivo = fopen("vendas.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return 1;
    }
    fprintf(arquivo, "%s;%s;%s;%02d:%02d;%s;%s;%.2f;%s\n", 
            venda.codigoVenda, venda.cpfPassageiro, venda.codigoRota,
            venda.hora, venda.min, venda.data, venda.assento, 
            venda.valor, venda.formaPagamento);
    fclose(arquivo);
    return 0;
}

void listarVendas() {
    FILE *arquivo = fopen("vendas.txt", "r");
    if (!arquivo) {
        printf("Nenhuma venda registrada.\n");
        return;
    }
    
    Venda venda;
    printf("\n=== LISTA DE VENDAS ===\n");
    while (fscanf(arquivo, "%19[^;];%14[^;];%49[^;];%d:%d;%10[^;];%4[^;];%f;%9[^\n]\n", 
                  venda.codigoVenda, venda.cpfPassageiro, venda.codigoRota,
                  &venda.hora, &venda.min, venda.data, venda.assento, 
                  &venda.valor, venda.formaPagamento) == 9) {
        printf("Código: %s | Passageiro: %s | Rota: %s\n", venda.codigoVenda, venda.cpfPassageiro, venda.codigoRota);
        printf("Horário: %02d:%02d | Data: %s | Assento: %s\n", venda.hora, venda.min, venda.data, venda.assento);
        printf("Valor: R$ %.2f | Pagamento: %s\n", venda.valor, venda.formaPagamento);
        printf("----------------------------------\n");
    }
    fclose(arquivo);
}

void exibirPoltronas(int totalPoltronas, int poltronasDis) {
    char (*poltronas)[3] = malloc(totalPoltronas * sizeof(*poltronas));
    if (poltronas == NULL) {
        printf("Erro ao alocar memória para as poltronas.\n");
        return;
    }
    int fila = 1;
    int letra = 'A';

    for (int i = 0; i < totalPoltronas; i++) {
        snprintf(poltronas[i], 3, "%d%c", fila, letra);
        letra++;
        if (letra > 'C') {
            letra = 'A';
            fila++;
        }
    }

    printf("\n=== POLTRONAS ===\n");
    for (int i = 0; i < totalPoltronas; i++) {
        if (i % 8 == 0 && i != 0) {
            printf("\n");
        }
        if (i < poltronasDis) {
            printf("\033[0;34m[%s]\033[0m ", poltronas[i]); // Azul para poltronas livres
        } else {
            printf("\033[0;31m[%s]\033[0m ", poltronas[i]); // Vermelho para poltronas ocupadas
        }
    }
    printf("\n");
    free(poltronas);
}

void realizarVenda() {
    Venda novaVenda;
    gerarCodigoVenda(novaVenda.codigoVenda);

    printf("CPF do passageiro: ");
    fgets(novaVenda.cpfPassageiro, 15, stdin);
    novaVenda.cpfPassageiro[strcspn(novaVenda.cpfPassageiro, "\n")] = '\0';

    printf("Código da rota: ");
    fgets(novaVenda.codigoRota, 50, stdin);
    novaVenda.codigoRota[strcspn(novaVenda.codigoRota, "\n")] = '\0';

    printf("Data da viagem (DD/MM/AAAA): ");
    fgets(novaVenda.data, 11, stdin);
    novaVenda.data[strcspn(novaVenda.data, "\n")] = '\0';

    printf("Horário do voo (HH MM): ");
    scanf("%d %d", &novaVenda.hora, &novaVenda.min);
    limparBuffer();

    printf("Assento escolhido: ");
    fgets(novaVenda.assento, 5, stdin);
    novaVenda.assento[strcspn(novaVenda.assento, "\n")] = '\0';

    char origem[50], destino[50];
    FILE *arquivoRotas = fopen("rotas.txt", "r");
    if (!arquivoRotas) {
        printf("Erro ao abrir o arquivo de rotas!\n");
        return;
    }

    // Buscar a origem e destino da rota escolhida
    char linha[200], codigoRota[50], nomeRota[100], diaSemana[20];
    int tipo, hora, min, poltronasDis, totalPoltronas;
    float distancia = -1.0;

    while (fgets(linha, sizeof(linha), arquivoRotas)) {
        sscanf(linha, "%49[^;];%99[^;];%d;%d;%d;%19[^;];%d;%f;%d",
               codigoRota, nomeRota, &tipo, &hora, &min, diaSemana, &poltronasDis, &distancia, &totalPoltronas);
        
        if (strcmp(novaVenda.codigoRota, codigoRota) == 0) {
            sscanf(nomeRota, "%[^-] - %[^\n]", origem, destino);
            break;
        }
    }

    fclose(arquivoRotas);

    if (distancia == -1.0) {
        printf("Erro: Rota não encontrada!\n");
        return;
    }

    distancia = distanciaMilhas(origem, destino);

    if (distancia == -1.0) {
        printf("Erro: Não foi possível calcular a distância para a rota informada.\n");
        return;
    }

    int diasParaViagem = 10; 
    int diaSemanaInt = 3;      
    int poltronasVagas = 50; 

    novaVenda.valor = calcularPrecoPassagem(distancia, diasParaViagem, diaSemanaInt, poltronasVagas);
    printf("Valor calculado da passagem: R$ %.2f\n", novaVenda.valor);

    printf("Forma de pagamento (Dinheiro, Crédito, Débito): ");
    fgets(novaVenda.formaPagamento, 10, stdin);
    novaVenda.formaPagamento[strcspn(novaVenda.formaPagamento, "\n")] = '\0';

    salvarVenda(novaVenda);
    printf("Venda realizada com sucesso! Código: %s\n", novaVenda.codigoVenda);

    exibirPoltronas(totalPoltronas, poltronasDis);
}