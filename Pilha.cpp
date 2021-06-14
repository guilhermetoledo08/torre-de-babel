#include "Pilha.h"

Node *Cria(){
  return nullptr;
}

void Empilha(Node **ppilha, char disco){
  Node *novoNo = new Node;
  novoNo->disco = disco;
  novoNo->prox = *ppilha;
  *ppilha = novoNo;
}

char Desempilha(Node **ppilha){
  Node *noExcluido;
  noExcluido = *ppilha;
  char valor = noExcluido->disco;
  *ppilha = noExcluido->prox;
  delete noExcluido;
  noExcluido = nullptr;
  return valor;
}

bool Vazia(Node *pilha){
  if(pilha == nullptr){
    return true;
  }
  return false;
}

char PegaTopo(Node *pilha){
  char valor = pilha->disco;
  return valor;
}