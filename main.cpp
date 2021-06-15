#include <iostream>
#include <string>
#include "Pilha.h"
using namespace std;


int main() {
  Node *pilha1, *pilha2, *pilha3;
  pilha1 = Cria();
  pilha2 = Cria();
  pilha3 = Cria();
  Empilha(&pilha1, "========= ");
  Empilha(&pilha1, " ======= ");
  Empilha(&pilha1, "  ===== ");
  Empilha(&pilha1, "   === ");
  Empilha(&pilha1, "    = ");
  imprimePilha(pilha1);
  transfereDisco(&pilha1, &pilha2);
  cout << endl << endl << endl;
  imprimePilha(pilha1);
  cout << endl << endl << endl;
  imprimePilha(pilha2);
  //cout << PegaTopo(pilha2);
}
