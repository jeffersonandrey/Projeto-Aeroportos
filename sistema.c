#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#include <ctype.h>

#define MAX_AEROPORTOS 100

static Aeroporto* aeroportos[MAX_AEROPORTOS];
static int** matrizAdjacencia = NULL;
static int totalAeroportos = 0;

void inicializarSistema() {
    matrizAdjacencia = (int**) malloc(sizeof(int*) * MAX_AEROPORTOS);
    for (int i = 0; i < MAX_AEROPORTOS; i++) {
        matrizAdjacencia[i] = (int*) calloc(MAX_AEROPORTOS, sizeof(int));
        aeroportos[i] = NULL;
    }

    Aeroporto* a1 = malloc(sizeof(Aeroporto));
    strcpy(a1->codigo, "BSB");
    strcpy(a1->nome, "Brasilia");
    aeroportos[0] = a1;

    Aeroporto* a2 = malloc(sizeof(Aeroporto));
    strcpy(a2->codigo, "CNF");
    strcpy(a2->nome, "Belo Horizonte");
    aeroportos[1] = a2;

    Aeroporto* a3 = malloc(sizeof(Aeroporto));
    strcpy(a3->codigo, "GIG");
    strcpy(a3->nome, "Rio de Janeiro");
    aeroportos[2] = a3;

    Aeroporto* a4 = malloc(sizeof(Aeroporto));
    strcpy(a4->codigo, "GRU");
    strcpy(a4->nome, "Guarulhos");
    aeroportos[3] = a4;

    Aeroporto* a5 = malloc(sizeof(Aeroporto));
    strcpy(a5->codigo, "SSA");
    strcpy(a5->nome, "Salvador");
    aeroportos[4] = a5;

    totalAeroportos = 5;

    matrizAdjacencia[0][4] = 107;
    matrizAdjacencia[1][2] = 555;
    matrizAdjacencia[1][3] = 101;
    matrizAdjacencia[1][4] = 214;
    matrizAdjacencia[2][1] = 554;
    matrizAdjacencia[2][3] = 90;
    matrizAdjacencia[3][0] = 50;
    matrizAdjacencia[3][1] = 102;
    matrizAdjacencia[3][2] = 89;
    matrizAdjacencia[4][1] = 215;

}


int desejaContinuar(const char* mensagem) {
    char resposta;
    int c;

    do {
        printf("%s (S/N): ", mensagem);
        if (scanf(" %c", &resposta) != 1) { 
            printf("Entrada invalida.\n");
            while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer até o final da linha
            continue;
        }

        resposta = toupper(resposta);  // Converte para maiúsculo

        // Se o caractere não for 'S' ou 'N', solicita nova entrada
        if (resposta != 'S' && resposta != 'N') {
            printf("Opcao invalida. Digite apenas S ou N.\n");
            while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer até o final da linha
            continue;
        }

        // Limpa o resto da linha caso o usuário tenha digitado mais de um caractere
        while ((c = getchar()) != '\n' && c != EOF); 

    } while (resposta != 'S' && resposta != 'N'); // Repete até uma opção válida

    return (resposta == 'S') ? 1 : 0;
}


int validarCodigo(const char* codigo) {
    if (codigo[0] == '\0') return 0; // código vazio

    for (int i = 0; codigo[i] != '\0'; i++) {
        if (!isalpha(codigo[i])) return 0; // caractere inválido
    }

    return 1;
}

void cadastrarAeroporto() {
    do {
        if (totalAeroportos >= MAX_AEROPORTOS) {
            printf("Limite de aeroportos atingido.\n");
            return;
        }

        Aeroporto* novo = malloc(sizeof(Aeroporto));

        printf("Codigo do aeroporto (ex: CNF): ");
        scanf("%3s", novo->codigo);
        while (getchar() != '\n'); // Limpa o buffer

        // Verifica se o código já foi cadastrado
        int codigoExistente = 0;
        for (int i = 0; i < totalAeroportos; i++) {
            if (strcmp(aeroportos[i]->codigo, novo->codigo) == 0) {
                printf("Erro: Ja existe um aeroporto com o codigo %s.\n", novo->codigo);
                codigoExistente = 1;
                break;
            }
        }

        if (codigoExistente) {
            free(novo); // Libera a memória do aeroporto não cadastrado
            continue;  // Solicita novo cadastro
        }

        printf("Nome da cidade: ");
        fgets(novo->nome, TAM_NOME, stdin);
        novo->nome[strcspn(novo->nome, "\n")] = '\0';  // Remove a nova linha da entrada

        aeroportos[totalAeroportos++] = novo;  // Adiciona o novo aeroporto
        printf("Aeroporto %s (%s) cadastrado com sucesso.\n", novo->nome, novo->codigo);

    } while (desejaContinuar("Deseja cadastrar outro aeroporto?"));
}

  

int buscarIndicePorCodigo(const char* cod) {
    for (int i = 0; i < totalAeroportos; i++) {
        if (strcmp(aeroportos[i]->codigo, cod) == 0)
            return i;
    }
    return -1;
}

void listarAeroportos() {
    if (totalAeroportos == 0) {
        printf("Nenhum aeroporto cadastrado.\n");
    } else {
        printf("==== Aeroportos Cadastrados ====\n");
        for (int i = 0; i < totalAeroportos; i++) {
            printf("%s (%s)\n", aeroportos[i]->nome, aeroportos[i]->codigo);
        }
    }
}

void listarTodosOsVoos() {
    int encontrou = 0;
    printf("Lista de todos os voos cadastrados:\n");
    for (int i = 0; i < totalAeroportos; i++) {
        for (int j = 0; j < totalAeroportos; j++) {
            if (matrizAdjacencia[i][j] != 0) {
                printf("Voo %d: %s (%s) -> %s (%s)\n",
                    matrizAdjacencia[i][j],
                    aeroportos[i]->nome, aeroportos[i]->codigo,
                    aeroportos[j]->nome, aeroportos[j]->codigo);
                encontrou = 1;
            }
        }
    }
    if (!encontrou) {
        printf("Nenhum voo encontrado.\n");
    }
}


void cadastrarVoo() {
    do {
        char origem[TAM_COD], destino[TAM_COD];
        int numero;
        int entradaValida;

        // Código de origem
        do {
            printf("Codigo do aeroporto de origem: ");
            scanf("%s", origem);
            while (getchar() != '\n');
            if (!validarCodigo(origem)) {
                printf("Codigo invalido! Use apenas letras. Tente novamente.\n");
            }
        } while (!validarCodigo(origem));

        // Código de destino
        do {
            printf("Codigo do aeroporto de destino: ");
            scanf("%s", destino);
            while (getchar() != '\n');
            if (!validarCodigo(destino)) {
                printf("Codigo invalido! Use apenas letras. Tente novamente.\n");
            }
        } while (!validarCodigo(destino));

        // Número do voo
        entradaValida = 0;
        while (!entradaValida) {
            printf("Numero do voo: ");
            if (scanf("%d", &numero) != 1) {
                printf("Numero invalido! Digite novamente.\n");
                while (getchar() != '\n');
            } else {
                entradaValida = 1;
            }
        }

        int i = buscarIndicePorCodigo(origem);
        int j = buscarIndicePorCodigo(destino);
        if (i == -1 || j == -1) {
            printf("Aeroporto(s) nao encontrado(s).\n\n");
            continue;
        }

        matrizAdjacencia[i][j] = numero;
        printf("Voo cadastrado com sucesso.\n\n");

    } while (desejaContinuar("Deseja adicionar outro voo?"));
}


void removerVoo() {
    do {
        int numero;
        int entradaValida = 0;

        // Valida número do voo
        while (!entradaValida) {
            printf("Numero do voo a ser removido: ");
            if (scanf("%d", &numero) != 1) {
                printf("Numero invalido!\n");
                while (getchar() != '\n');
            } else {
                entradaValida = 1;
            }
        }

        int encontrado = 0;
        for (int i = 0; i < totalAeroportos; i++) {
            for (int j = 0; j < totalAeroportos; j++) {
                if (matrizAdjacencia[i][j] == numero) {
                    matrizAdjacencia[i][j] = 0;
                    printf("Voo removido com sucesso.\n");
                    encontrado = 1;
                    break;
                }
            }
            if (encontrado) break;
        }

        if (!encontrado)
            printf("Voo nao encontrado.\n");

    } while (desejaContinuar("Deseja remover outro voo?"));
}


void listarVoos() {
    do {
        char origem[TAM_COD];
        printf("Codigo do aeroporto de origem: ");
        scanf("%s", origem);
        while (getchar() != '\n');

        if (!validarCodigo(origem)) {
            printf("Codigo invalido! Use apenas letras.\n");
            continue;
        }

        int i = buscarIndicePorCodigo(origem);
        if (i == -1) {
            printf("Aeroporto nao encontrado.\n");
            continue;
        }

        printf("Voos saindo de %s (%s):\n", aeroportos[i]->nome, aeroportos[i]->codigo);
        int encontrou = 0;
        for (int j = 0; j < totalAeroportos; j++) {
            if (matrizAdjacencia[i][j] != 0) {
                printf("Voo %d para %s (%s)\n", matrizAdjacencia[i][j], aeroportos[j]->nome, aeroportos[j]->codigo);
                encontrou = 1;
            }
        }

        if (!encontrou) {
            printf("0 voos cadastrados a partir deste aeroporto.\n");
        }

        printf("\n");

    } while (desejaContinuar("Deseja listar voos de outro aeroporto?"));
}


void dfs(int atual, int destino, int* visitado, int* encontrado) {
    if (atual == destino) {
        *encontrado = 1;
        return;
    }
    visitado[atual] = 1;
    for (int i = 0; i < totalAeroportos; i++) {
        if (matrizAdjacencia[atual][i] != 0 && !visitado[i])
            dfs(i, destino, visitado, encontrado);
    }
}

void listarTodosOsCaminhos(int origem, int destino) {
    int visitado[MAX_AEROPORTOS] = {0};
    int caminho[MAX_AEROPORTOS];
    printf("Caminhos possiveis de %s para %s:\n", 
           aeroportos[origem]->codigo, aeroportos[destino]->codigo);
    listarTodosOsCaminhosRec(origem, destino, visitado, caminho, 0);
}

void listarTodosOsCaminhosRec(int atual, int destino, int* visitado, int* caminho, int nivel) {
    visitado[atual] = 1;
    caminho[nivel] = atual;
    nivel++;

    if (atual == destino) {
        // Exibe o caminho
        for (int i = 0; i < nivel; i++) {
            printf("%s (%s)", aeroportos[caminho[i]]->nome, aeroportos[caminho[i]]->codigo);
            if (i < nivel - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        for (int i = 0; i < totalAeroportos; i++) {
            if (matrizAdjacencia[atual][i] != 0 && !visitado[i]) {
                listarTodosOsCaminhosRec(i, destino, visitado, caminho, nivel);
            }
        }
    }

    visitado[atual] = 0;  // backtracking
}

void buscarTrajeto() {
    do {
        char codOrigem[TAM_COD], codDestino[TAM_COD];

        // Entrada do código de origem
        printf("Codigo do aeroporto de origem: ");
        scanf("%s", codOrigem);
        while (getchar() != '\n');
        if (!validarCodigo(codOrigem)) {
            printf("Codigo invalido! Use apenas letras.\n");
            continue;
        }

        // Entrada do código de destino
        printf("Codigo do aeroporto de destino: ");
        scanf("%s", codDestino);
        while (getchar() != '\n');
        if (!validarCodigo(codDestino)) {
            printf("Codigo invalido! Use apenas letras.\n");
            continue;
        }

        // Busca os índices dos aeroportos
        int i = buscarIndicePorCodigo(codOrigem);
        int j = buscarIndicePorCodigo(codDestino);

        if (i == -1 || j == -1) {
            printf("Aeroporto(s) nao encontrado(s).\n");
            continue;
        }

        // Verifica se existe algum trajeto com DFS
        int visitado[MAX_AEROPORTOS] = {0}, existe = 0;
        dfs(i, j, visitado, &existe);

        if (existe) {
            printf("Existe pelo menos um trajeto de %s para %s.\n", codOrigem, codDestino);
            listarTodosOsCaminhos(i, j);  // Exibe todos os caminhos possíveis
        } else {
            printf("Nao ha trajeto de %s para %s.\n", codOrigem, codDestino);
        }

    } while (desejaContinuar("Deseja buscar outro trajeto?"));
}



void liberarMemoria() {
    for (int i = 0; i < MAX_AEROPORTOS; i++) {
        free(matrizAdjacencia[i]);
        if (aeroportos[i] != NULL)
            free(aeroportos[i]);
    }
    free(matrizAdjacencia);
}
