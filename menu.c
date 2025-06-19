#include <stdio.h>
#include <locale.h>
#include "menu.h"
#include "aero.h"
#include "rotas.h"
#include "passageiros.h"
//#include "funcionarios.h"
//#include "vendas.h"
#include "voo.h"
#include "frequentes.h"

void menuPrincipal(){
    int opc = 0;

    do{
        printf("\n");
        printf("------Menu Principal------\n");
        printf("1. Configuracoes.\n");
        printf("2. Vendas.\n");
        printf("3. Sair.\n");
        printf("Escolha umas opcao: ");
        scanf("%d", &opc);

        // Limpeza de Buffer
        limparBuffer();

        switch (opc){
            case 1:
                menuConfiguracoes();
                break;
            case 2:
                menuVendas();
                break;
            case 3:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while( opc != 3);
}

void menuConfiguracoes(){
    int opc1, opc2;
    int tamPF = 1, tamAe = 1, tamVoo = 1;
    int qtde1 = 0, qtde2 = 0, qtde3 = 0;
    Passageiro *VetFidelizado = NULL;
    Aeroporto *VetAeroporto = NULL;
    Voo *VetVoo = NULL;
    Rota *VetRota = NULL;

    
    VetFidelizado = (Passageiro *)malloc(tamPF * sizeof(Passageiro));
    VetAeroporto = (Aeroporto *)malloc(tamAe * sizeof(Aeroporto));
    VetVoo = (Voo *)malloc(tamVoo * sizeof(Voo));

    
    carregarVoos(&VetVoo, &tamVoo);
    qtde2 = carregarRotas(&VetRota, &tamVoo); 
    carregarVoos(&VetVoo, &tamVoo);
    qtde3 = carregarFidelizados(&VetFidelizado, &tamPF);

    do{
        printf("\n");
        printf("------Menu Configuracoes------\n");
        printf("4. Cadastrar aeroportos.\n");
        printf("5. Cadastrar voos/trechos.\n");
        printf("6. Cadastrar passageiros fidelizados.\n");
        printf("7.  Pesquisar/alterar dados de passageiros fidelizados .\n");
        printf("8.  Cadastrar funcionários.\n");
        printf("9.  Pesquisar/Alterar funcionários .\n");
        printf("10. Voltar.\n");

        printf("Escolha umas opcao: ");
        scanf("%d", &opc1);

        // Limpeza de Buffer
        limparBuffer();

        switch (opc1){
            case 4:
                if(qtde1 >= tamPF){
                    tamPF++;
                    VetAeroporto = (Aeroporto *)realloc(VetAeroporto, tamAe * sizeof(Aeroporto));
                }
                cadastrarAeroportos(VetAeroporto, &qtde1);
                break;
            case 5:
                if(qtde2 >= tamVoo){
                    tamVoo++;
                    VetVoo = (Voo *)realloc(VetVoo, tamVoo * sizeof(Voo));
                }
                cadastrarVoos(VetVoo, &qtde2, VetAeroporto, qtde1);
                break;
            case 6:
                if(qtde3 >= tamPF){
                    tamPF++;
                    VetFidelizado = (Passageiro *)realloc(VetFidelizado, tamPF * sizeof(Passageiro));
                }
                cadastrarFidelizados(VetFidelizado, &qtde3);
                break;

            case 7:
                // Menu
                do{
                    printf("\n");
                    printf("------Menu Busca/Alteracao de Passageiro Fidelizado------\n"); // Não sou criativa com nomes, pode mudar
                    printf("13. Pesquisar Passageiro .\n");
                    printf("14. Alterar dados.\n");
                    printf("15. Voltar.\n");

                    printf("Escolha umas opcao: ");
                    scanf("%d", &opc2);

                    // Limpeza de Buffer
                    limparBuffer();

                    switch(opc2){
                        case 13:
                            pesquisarFidelizados(VetFidelizado, qtde3);
                            break;
                        case 14:
                            alterarFidelizados(VetFidelizado, qtde3);
                            break;
                        case 15:
                            printf("Voltando ao menu principal\n");
                            break;
                        default:
                            printf("Opcao Invalida\n");
                    }

                }while(opc2 != 15);
                break;
            /*
            case 8:
                cadastrarFuncionarios();
                break;
            case 9:
                pesquisarAlterarFuncionarios();
                break;
            */
            case 10:
                printf("Salvando rotas antes de sair...\n");
                salvarRotas(VetRota, qtde2);

                printf("Salvando passageiros fidelizados antes de sair...\n");
                salvarFidelizados(VetFidelizado, qtde3);

                printf("Salvando voos antes de sair...\n");
                salvarVoos(VetVoo, qtde2);

                printf("Voltando ao menu principal\n");
                break;
            default:
                printf("Opcao Invalida\n");
        }

    } while( opc1 !=10);

    free(VetAeroporto);
    free(VetFidelizado);
    free(VetVoo);
}



void menuVendas(){
    int opc;


    do{
        printf("\n");
        printf("------Menu Vendas------\n");
        printf("11. Selecionar origem e destino .\n");
        printf("12. Voltar.\n");

        printf("Escolha umas opcao: ");
        scanf("%d", &opc);
        // Limpeza de Buffer
            limparBuffer();

        switch(opc){
            /*case 11:
                S_OrigemDestino();
                break;
            case 12:
                printf("Voltando ao menu principal\n");
                break;*/
            //default:
                //printf("Opcao Invalida\n");
        }

    }while(opc != 12 );
}
