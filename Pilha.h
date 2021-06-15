#pragma once

#include <string>
using namespace std;

// quantidade de discos utilizados
#define QUANT_DISCO 5

typedef struct node{
    int disco;
    struct node *prox;
}Node;

// Cria a pilha
Node *Cria();
// Empilha o disco na pilha
void Empilha(Node **, int);
// Desempilha o disco no topo da pilha
int Desempilha(Node **);
// Verifica se a pilha está vazia
bool Vazia(Node *);
// Retorna o topo da Pilha
int PegaTopo(Node *);
