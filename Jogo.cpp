#include "Jogo.h"
#include "Pilha.h"
#include <iostream>

using namespace std;

void criaJogo(Node **pilha1, Node **pilha2, Node **pilha3){
    *pilha1 = Cria();
    *pilha2 = Cria();
    *pilha3 = Cria();
    for(int i = QUANT_DISCO; i>0; i--){
        Empilha(pilha1, i);
    }  
    }

void transfereDisco(Node **pilhaOrig, Node **pilhaDest){
    int tOrig, tDest;
    tOrig = PegaTopo(*pilhaOrig);
    tDest = PegaTopo(*pilhaDest);
    cout << tOrig << endl;
    cout << tDest << endl;
    if(tOrig < tDest){
        int valor = Desempilha(pilhaOrig);
        Empilha(pilhaDest, valor);
    }else{
        cout << "Movimento nao pode ser realizado!!" <<endl;
    }
}

void imprimePilha(Node *pilha){
    Node *pAux;
    pAux = Cria();
    int x;

    while(!Vazia(pilha)){
        x = Desempilha(&pilha);
        Empilha(&pAux, x);
        for(int i=0; i<x; i++){
            cout << "=";
        }
        cout << endl;
    }
    
    while(!Vazia(pAux)){
        x = Desempilha(&pAux);
        Empilha(&pilha, x);
    }
}

void imprimePilha(Node *pilha1, Node *pilha2, Node *pilha3){
    cout << "Pilha 1:" << endl;
    imprimePilha(pilha1);
    cout << "Pilha 2:" << endl;
    imprimePilha(pilha2);
    cout << "Pilha 3:" << endl;
    imprimePilha(pilha3);
}

bool fimJogo(Node *pilha){
    Node *pAux;
    pAux = Cria();
    int qDiscos=0, x;

    while(!Vazia(pilha)){
    x = Desempilha(&pilha);
    Empilha(&pAux, x);
    qDiscos++;
    }
    while(!Vazia(pAux)){
    x = Desempilha(&pAux);
    Empilha(&pilha, x);
    }

    return qDiscos == QUANT_DISCO;
}