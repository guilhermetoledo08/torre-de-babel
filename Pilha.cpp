#include "Pilha.h"
#include <iostream>

using namespace std;

Node *Cria(){
  return nullptr;
}

void Empilha(Node **ppilha, string disco){
  Node *novoNo = new Node;
  novoNo->disco = disco;
  novoNo->prox = *ppilha;
  *ppilha = novoNo;
}

string Desempilha(Node **ppilha){
  Node *noExcluido;
  noExcluido = *ppilha;
  string valor = noExcluido->disco;
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

string PegaTopo(Node *pilha){
  string valor = pilha->disco;
  return valor;
}

void transfereDisco(Node **pilhaOrig, Node **pilhaDest){
  string valor = Desempilha(pilhaOrig);
  Empilha(pilhaDest, valor);
}

void imprimePilha(Node *pilha){
  Node *pAux;
  pAux = Cria();
  string x;

  while(Vazia(pilha) != true){
    x = Desempilha(&pilha);
    Empilha(&pAux, x);
    cout << x << endl;
  }
  while(Vazia(pAux) != true){
    x = Desempilha(&pAux);
    Empilha(&pilha, x);
  }
}
