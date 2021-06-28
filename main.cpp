#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int largura_t = 980;
const int altura_t = 480;
const float bloco_l = largura_t/5;
const float bloco_a = altura_t/5;
float pos_x = bloco_l-150;
float pos_y = 367;

typedef struct rec {
   // al_draw_filled_rectangle(float, float, float, float, al_map_rgb(int, int, int));
    //al_draw_filled_rectangle(pos_x+(5*n), pos_y-(30*n), pos_x+(150+10*n), pos_y-(30*n)+30, al_map_rgb(rand()%255, rand()%255, rand()%255));
} Retangulo;

int main()
{
    bool fim = false, mouse = false;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    BITMAP *ret;

    // This command create a screen
    ALLEGRO_DISPLAY* display;

    // Allegro Setup Error Message
    if(!al_init())
        al_show_native_message_box(NULL,NULL,NULL,"Allegro couldnt initialize",NULL,NULL);

    // Screen Resolution
    display = al_create_display(largura_t,altura_t);

    // Allegro Screen Creating Error
    if(!display)
        al_show_native_message_box(NULL,NULL,NULL,"Couldnt create Screen",NULL,NULL);

    /// Inicializações
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    /// Criação de fila e demais dispositivos
    fila_eventos = al_create_event_queue();

    /// Registro de sources
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    /// Loop principal
    while(!fim)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila_eventos, &ev);

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                fim = true;

            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                pos_y -= 10;
                break;
            case ALLEGRO_KEY_DOWN:
                pos_y += 10;
                break;
            case ALLEGRO_KEY_RIGHT:
                pos_x += (largura_t/2)-bloco_l;
                break;
            case ALLEGRO_KEY_LEFT:
                pos_x -= (largura_t/2)-bloco_l;
                break;
            }
        }

        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            fim = true;

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(ev.mouse.button & 1)
                mouse = !mouse;
        }

        al_draw_line(bloco_l, bloco_a, bloco_l, 400, al_map_rgb(148, 104, 70), 6);
        al_draw_line(largura_t/2, bloco_a, largura_t/2, 400, al_map_rgb(148, 104, 70), 6);
        al_draw_line(largura_t-bloco_l, bloco_a, largura_t-bloco_l, 400, al_map_rgb(148, 104, 70), 6);
        al_draw_line(bloco_l-150, 400, largura_t-bloco_l+150, 400, al_map_rgb(148, 104, 70), 6);

        al_draw_filled_rectangle(bloco_l/1.2, 307, (1.5*bloco_l-(bloco_l*0.32)), 337, al_map_rgb(121, 82, 179));
        al_draw_filled_rectangle(bloco_l/1.5, 337, (1.5*bloco_l-(bloco_l*0.16)), 367, al_map_rgb(251, 54, 64));
        al_draw_filled_rectangle(pos_x, pos_y, pos_x+300, pos_y+30, al_map_rgb(92, 51, 246));

        std::cout << "X: " << ev.mouse.x << " Y: " << ev.mouse.y << std::endl;

        if(mouse)
        {
            if(ev.mouse.x >= 150 && ev.mouse.x <= 830)
                pos_x = -150+(mouse * ev.mouse.x);

            if(ev.mouse.y >= 30 && ev.mouse.y <= 450)
                pos_y = -15+(mouse * ev.mouse.y);
        }

        al_flip_display();
        al_clear_to_color(al_map_rgb(255, 255, 255));
    }





    /// Finalizações
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);

    return 0;
}

/*#include <iostream>
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
}*/
