#include "Jogo.h"
#include "Pilha.h"
#include <iostream>

using namespace std;

void criaJogo(Node **pilha1, Node **pilha2, Node **pilha3){
    *pilha1 = Cria();
    *pilha2 = Cria();
    *pilha3 = Cria();
    for(int i = QUANT_DISCO; i=1; i--){
        Empilha(pilha1, QUANT_DISCO);
    }  
    }

void transfereDisco(Node **pilhaOrig, Node **pilhaDest){
    int tOrig, tDest;
    tOrig = PegaTopo(*pilhaOrig);
    tDest = PegaTopo(*pilhaDest);
    if(tOrig < tDest){
        int valor = Desempilha(pilhaOrig);
        Empilha(pilhaDest, valor);
    }else{
        printf("Movimento não pode ser realizado!!");
    }
}

void imprimePilha(Node *pilha){
    Node *pAux;
    pAux = Cria();
    int x;

    while(!Vazia(pilha)){
    x = Desempilha(&pilha);
    Empilha(&pAux, x);
    cout << x << endl;
    }
    while(!Vazia(pAux)){
    x = Desempilha(&pAux);
    Empilha(&pilha, x);
    }
}

void imprimePilha(Node *pilha1, Node *pilha2, Node *pilha3){
    imprimePilha(pilha1);
    imprimePilha(pilha2);
    imprimePilha(pilha3);
}

bool verificaTermino(Node *pilha){
    return false;
}