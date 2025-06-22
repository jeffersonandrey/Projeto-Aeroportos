#ifndef AEROPORTO_H
#define AEROPORTO_H

#define TAM_COD 4
#define TAM_NOME 100

typedef struct {
    char codigo[TAM_COD];
    char nome[TAM_NOME];
} Aeroporto;

#endif
