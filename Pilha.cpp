#include "Pilha.h"
#include <iostream>

using namespace std;

Node *Cria(){
  return nullptr;
}

void Empilha(Node **ppilha, int disco){
  Node *novoNo = new Node;
  novoNo->disco = disco;
  novoNo->prox = *ppilha;
  *ppilha = novoNo;
}

int Desempilha(Node **ppilha){
  Node *noExcluido;
  noExcluido = *ppilha;
  int valor = noExcluido->disco;
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

int PegaTopo(Node *pilha){
  if(Vazia(pilha)){
    return QUANT_DISCO;
  }
  int valor = pilha->disco;
  return valor;
}
