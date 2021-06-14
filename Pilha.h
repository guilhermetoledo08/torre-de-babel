#pragma once

typedef struct node{
  char disco;
  struct node *prox;
}Node;

// Cria a pilha
Node *Cria();
// Empilha o disco na pilha 
void Empilha(Node **, char);
// Desempilha o disco no topo da pilha 
char Desempilha(Node **);
// Verifica se a pilha está vazia 
bool Vazia(Node *);
// Retorna o topo da Pilha 
char PegaTopo(Node *);
