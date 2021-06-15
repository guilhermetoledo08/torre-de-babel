#pragma once

#include "Pilha.h"
#include <string>
using namespace std;


// cria o jogo
void criaJogo(Node**, Node**, Node**); 
// Transfere o disco de uma pilha para outra
void transfereDisco(Node**, Node**);
// Imprime uma pilha
void imprimePilha(Node *);
// Imprime todas as pilhas
void imprimePilha(Node *, Node *, Node *);
// Verifica se a última pilha tem todos os discos (fim de jogo = TRUE)
bool fimJogo(Node *);