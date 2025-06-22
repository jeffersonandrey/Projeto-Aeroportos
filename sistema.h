#ifndef SISTEMA_H
#define SISTEMA_H

#include "aeroporto.h"

void inicializarSistema();
void cadastrarAeroporto();
void cadastrarVoo();
void removerVoo();
void listarVoos();
void buscarTrajeto();
void liberarMemoria();
void listarAeroportos();
void listarTodosOsVoos();
void listarTodosOsCaminhos(int origem, int destino);
void listarTodosOsCaminhosRec(int atual, int destino, int* visitado, int* caminho, int nivel);


#endif
