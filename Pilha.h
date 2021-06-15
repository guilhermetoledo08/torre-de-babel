#pragma once

#include <string>
using namespace std;

typedef struct node{
  string disco;
  struct node *prox;
}Node;

// Cria a pilha
Node *Cria();
// Empilha o disco na pilha
void Empilha(Node **, string);
// Desempilha o disco no topo da pilha
string Desempilha(Node **);
// Verifica se a pilha está vazia
bool Vazia(Node *);
// Retorna o topo da Pilha
string PegaTopo(Node *);

// Transfere o disco de uma pilha para outra
void transfereDisco(Node**, Node**);

// Imprime as pilhas
void imprimePilha(Node *);
