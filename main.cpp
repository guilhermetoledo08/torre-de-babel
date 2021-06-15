#include <iostream>
#include <string>
#include "Jogo.h"
#include "Pilha.h"
using namespace std;

int main() {
  Node *pilha1, *pilha2, *pilha3;
  int orig, dest;

  criaJogo(&pilha1, &pilha2, &pilha3);
  
  while(!fimJogo(pilha3)){
    cout << endl << endl;
    imprimePilha(pilha1, pilha2, pilha3);
    
    // Exibição pelo terminal
    // pedir transferencia
    cout << "Origem: ";
    cin >> orig;
    cout << "Destino: ";
    cin >> dest;
    if(orig != dest){
      switch (orig){
        case 1:
          switch (dest){
            case 2:
              transfereDisco(&pilha1, &pilha2);
              break;
            case 3:
              transfereDisco(&pilha1, &pilha3);
              break;
            default:
              cout << "Pilha nao existe! Deve ser 1, 2 ou 3." <<endl;
              break;
          }
          break;
        case 2:
          switch (dest){
            case 1:
              transfereDisco(&pilha2, &pilha1);
              break;
            case 3:
              transfereDisco(&pilha2, &pilha3);
              break;
            default:
              cout << "Pilha nao existe! Deve ser 1, 2 ou 3." <<endl;
              break;
          }
          break;
        case 3:
          switch (dest){
            case 1:
              transfereDisco(&pilha3, &pilha1);
              break;
            case 2:
              transfereDisco(&pilha3, &pilha2);
              break;
            default:
              cout << "Pilha nao existe! Deve ser 1, 2 ou 3." <<endl;
              break;
          }
          break;
          default:
            cout << "Pilha nao existe! Deve ser 1, 2 ou 3." <<endl;
            break;
      }
    }else{
      cout << "As pilhas devem ser diferentes!!" <<endl;
    }
  }
  cout <<endl << "Parabens, voce ganhou!!";
  return 0;
}
