#include <stdio.h>

#include "sistema.h"

int main() {
    int opcao;
    printf("BEM VINDO AO SISTEMA NACIONAL DE AEROPORTOS (SNA) \n\nQual sera sua opcao?");
    inicializarSistema();
    do {
        printf("\n================== MENU ===================+\n");
        printf("1. Cadastrar aeroporto                     |\n");
        printf("2. Cadastrar voo                           |\n");
        printf("3. Remover voo                             |\n");
        printf("4. Listar voos a partir de um aeroporto    |\n");
        printf("5. Buscar trajeto entre aeroportos         |\n");
        printf("6. Listar aeroportos cadastrados           |\n");
        printf("7. Listar voos cadastrados                 |\n");
        printf("0. Sair                                    |");
        printf("\n===========================================+\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            while (getchar() != '\n'); // limpa o buffer
            opcao = -1; // força repetir o menu
            continue;
        }

        switch (opcao) {
            case 1: cadastrarAeroporto(); break;
            case 2: cadastrarVoo(); break;
            case 3: removerVoo(); break;
            case 4: listarVoos(); break;
            case 5: buscarTrajeto(); break;
            case 6: listarAeroportos(); break;
            case 7: listarTodosOsVoos(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    liberarMemoria();
    return 0;
}
