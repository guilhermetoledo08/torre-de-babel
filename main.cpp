#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>

const int largura_t = 980;
const int altura_t = 480;
const float bloco_l = largura_t/5;
const float bloco_a = altura_t/5;
int n;

float pos_x = bloco_l-150;
float pos_y = 367;

typedef struct
{
    float x;
    float y;
    float largura;
    int torre;
    bool topo;
} ponto;

/// ---- Movimentação ----
void calculaPosicao(ALLEGRO_EVENT ev, ponto discos[], int selectedDisco)
{
    bool permitir = discos[selectedDisco].topo;
    ponto * ret;
    int quant = 0;

    if(abs(ev.mouse.x-bloco_l) < abs(ev.mouse.x-(largura_t/2)) &&
            abs(ev.mouse.x-bloco_l) < abs(ev.mouse.x-(largura_t-bloco_l)))
    {
        for(int i = 0; i < n; i++)
        {
            if(discos[i].torre == 1)
            {
                if(selectedDisco != i) quant++;
                if((discos[i].largura < discos[selectedDisco].largura) ||
                        (discos[selectedDisco].topo == false))
                    permitir = false;
            }
        }
        if(permitir)
        {
            for(int i = 0; i < n; i++)
            {
                if(discos[i].torre == 1 && selectedDisco != i)
                    discos[i].topo = false;
            }
            if(discos[selectedDisco].torre != 1)
            {
                for(int i = 0; i < n; i++)
                {
                    if(discos[i].torre == discos[selectedDisco].torre &&
                       i != selectedDisco)
                        ret = &discos[i];
                }
                ret->topo = true;
            }
            discos[selectedDisco].x = (bloco_l)-(discos[selectedDisco].largura/2);
            discos[selectedDisco].torre = 1;
            discos[selectedDisco].y = pos_y-(quant*30);
        }
    }
    else if(abs(ev.mouse.x-(largura_t/2)) < abs(ev.mouse.x-bloco_l) &&
            abs(ev.mouse.x-(largura_t/2)) < abs(ev.mouse.x-(largura_t-bloco_l)))
    {
        for(int i = 0; i < n; i++)
        {
            if(discos[i].torre == 2)
            {
                if(selectedDisco != i) quant++;
                if((discos[i].largura < discos[selectedDisco].largura) ||
                        (discos[selectedDisco].topo == false))
                    permitir = false;
            }
        }
        if(permitir)
        {
            for(int i = 0; i < n; i++)
            {
                if(discos[i].torre == 2 && selectedDisco != i)
                    discos[i].topo = false;
            }
            if(discos[selectedDisco].torre != 2)
            {
                for(int i = 0; i < n; i++)
                {
                    if(discos[i].torre == discos[selectedDisco].torre &&
                       i != selectedDisco)
                        ret = &discos[i];
                }
                ret->topo = true;
            }
            discos[selectedDisco].x = (largura_t/2)-(discos[selectedDisco].largura/2);
            discos[selectedDisco].torre = 2;
            discos[selectedDisco].y = pos_y-(quant*30);
        }
    }
    else if(abs(ev.mouse.x-(largura_t-bloco_l)) < abs(ev.mouse.x-bloco_l) &&
            abs(ev.mouse.x-(largura_t-bloco_l)) < abs(ev.mouse.x-(largura_t/2)))
    {
        for(int i = 0; i < n; i++)
        {
            if(discos[i].torre == 3)
            {
                if(selectedDisco != i) quant++;
                if((discos[i].largura < discos[selectedDisco].largura) ||
                        (discos[selectedDisco].topo == false))
                    permitir = false;
            }
        }
        if(permitir)
        {
            for(int i = 0; i < n; i++)
            {
                if(discos[i].torre == 3 && selectedDisco != i)
                    discos[i].topo = false;
            }
            if(discos[selectedDisco].torre != 3)
            {
                for(int i = 0; i < n; i++)
                {
                    if(discos[i].torre == discos[selectedDisco].torre &&
                       i != selectedDisco)
                        ret = &discos[i];
                }
                ret->topo = true;
            }
            discos[selectedDisco].x = (largura_t-bloco_l)-(discos[selectedDisco].largura/2);
            discos[selectedDisco].torre = 3;
            discos[selectedDisco].y = pos_y-(quant*30);
        }
    }
}

int main()
{
    while(n < 3 || n > 8)
    {
        printf("Numero de discos (de 3 a 8): ");
        scanf("%d", &n);
        if(n < 3 || n > 8)
            std::cout << "Erro: o numero de discos deve estar entrar 3 e 8!\n" << std::endl;
    }

    int selectedDisco = n-1;

    ponto discos[n];

    /// ---- Definindo posições iniciais ----
    for(int i = 0; i < n; i++)
    {
        discos[i].torre = 1;

        if(i == n-1)
            discos[i].topo = true;
        else
            discos[i].topo = false;

        discos[i].x = pos_x+((25/1.4)*i);
        discos[i].y = pos_y-(i*30);
        discos[i].largura = bloco_l+104-((50/1.4)*i);
    }

    bool fim = false, mouse = false;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    /// Cria a tela
    ALLEGRO_DISPLAY* display;

    /// Configura uma mensagem de erro caso o Allegro não consiga inicializar
    if(!al_init())
        al_show_native_message_box(NULL,NULL,NULL,"Allegro couldnt initialize",NULL,NULL);

    /// Define a resolução da tela e adiciona um fundo branco
    display = al_create_display(largura_t,altura_t);
    al_clear_to_color(al_map_rgb(255, 255, 255));

    /// Configura uma mensagem de erro caso a tela não consiga inicializar
    if(!display)
        al_show_native_message_box(NULL,NULL,NULL,"Couldnt create Screen",NULL,NULL);

    /// Inicializações
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    /// Criação da fila de eventos
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
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            fim = true;
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(ev.mouse.button & 1)
                mouse = true;
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            mouse = false;
            calculaPosicao(ev, discos, selectedDisco);
        }

        /// ----- Desenhos -----

        /// Torre 1
        al_draw_line(bloco_l, bloco_a, bloco_l, 400, al_map_rgb(148, 104, 70), 6);

        /// Torre 2
        al_draw_line(largura_t/2, bloco_a, largura_t/2, 400, al_map_rgb(148, 104, 70), 6);

        /// Torre 3
        al_draw_line(largura_t-bloco_l, bloco_a, largura_t-bloco_l, 400, al_map_rgb(148, 104, 70), 6);

        /// Linha horizontal
        al_draw_line(bloco_l-150, 400, largura_t-bloco_l+150, 400, al_map_rgb(148, 104, 70), 6);

        /// Discos (0,1,2)
        al_draw_filled_rectangle(discos[2].x, discos[2].y, discos[2].x+discos[2].largura, discos[2].y+30, al_map_rgb(121, 82, 179));
        al_draw_filled_rectangle(discos[1].x, discos[1].y, discos[1].x+discos[1].largura, discos[1].y+30, al_map_rgb(251, 54, 64));
        al_draw_filled_rectangle(discos[0].x, discos[0].y, discos[0].x+discos[0].largura, discos[0].y+30, al_map_rgb(92, 51, 246));

        /// Demais discos (3,4,5,6,7)
        switch(n)
        {
        case 4:
            al_draw_filled_rectangle(discos[3].x, discos[3].y, discos[3].x+discos[3].largura, discos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        case 5:
            al_draw_filled_rectangle(discos[4].x, discos[4].y, discos[4].x+discos[4].largura, discos[4].y+30, al_map_rgb(27, 185, 247));
            al_draw_filled_rectangle(discos[3].x, discos[3].y, discos[3].x+discos[3].largura, discos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        case 6:
            al_draw_filled_rectangle(discos[5].x, discos[5].y, discos[5].x+discos[5].largura, discos[5].y+30, al_map_rgb(120, 222, 199));
            al_draw_filled_rectangle(discos[4].x, discos[4].y, discos[4].x+discos[4].largura, discos[4].y+30, al_map_rgb(27, 185, 247));
            al_draw_filled_rectangle(discos[3].x, discos[3].y, discos[3].x+discos[3].largura, discos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        case 7:
            al_draw_filled_rectangle(discos[6].x, discos[6].y, discos[6].x+discos[6].largura, discos[6].y+30, al_map_rgb(255, 191, 0));
            al_draw_filled_rectangle(discos[5].x, discos[5].y, discos[5].x+discos[5].largura, discos[5].y+30, al_map_rgb(120, 222, 199));
            al_draw_filled_rectangle(discos[4].x, discos[4].y, discos[4].x+discos[4].largura, discos[4].y+30, al_map_rgb(27, 185, 247));
            al_draw_filled_rectangle(discos[3].x, discos[3].y, discos[3].x+discos[3].largura, discos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        case 8:
            al_draw_filled_rectangle(discos[7].x, discos[7].y, discos[7].x+discos[7].largura, discos[7].y+30, al_map_rgb(120, 104, 230));
            al_draw_filled_rectangle(discos[6].x, discos[6].y, discos[6].x+discos[6].largura, discos[6].y+30, al_map_rgb(255, 191, 0));
            al_draw_filled_rectangle(discos[5].x, discos[5].y, discos[5].x+discos[5].largura, discos[5].y+30, al_map_rgb(120, 222, 199));
            al_draw_filled_rectangle(discos[4].x, discos[4].y, discos[4].x+discos[4].largura, discos[4].y+30, al_map_rgb(27, 185, 247));
            al_draw_filled_rectangle(discos[3].x, discos[3].y, discos[3].x+discos[3].largura, discos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        }

        /// ---- Mapeamento dos discos ----
        if(mouse)
        {
            if(ev.mouse.x >= discos[0].x &&
                    ev.mouse.x <= discos[0].x+discos[0].largura &&
                    ev.mouse.y >= discos[0].y &&
                    ev.mouse.y <= discos[0].y+30)
            {
                selectedDisco = 0;
            }

            else if(ev.mouse.x >= discos[1].x &&
                    ev.mouse.x <= discos[1].x+discos[1].largura &&
                    ev.mouse.y >= discos[1].y &&
                    ev.mouse.y <= discos[1].y+30)
            {
                selectedDisco = 1;
            }

            else if(ev.mouse.x >= discos[2].x &&
                    ev.mouse.x <= discos[2].x+discos[2].largura &&
                    ev.mouse.y >= discos[2].y &&
                    ev.mouse.y <= discos[2].y+30)
            {
                selectedDisco = 2;
            }

            else if(ev.mouse.x >= discos[3].x &&
                    ev.mouse.x <= discos[3].x+discos[3].largura &&
                    ev.mouse.y >= discos[3].y &&
                    ev.mouse.y <= discos[3].y+30)
            {
                selectedDisco = 3;
            }

            else if(ev.mouse.x >= discos[4].x &&
                    ev.mouse.x <= discos[4].x+discos[4].largura &&
                    ev.mouse.y >= discos[4].y &&
                    ev.mouse.y <= discos[4].y+30)
            {
                selectedDisco = 4;
            }

            else if(ev.mouse.x >= discos[5].x &&
                    ev.mouse.x <= discos[5].x+discos[5].largura &&
                    ev.mouse.y >= discos[5].y &&
                    ev.mouse.y <= discos[5].y+30)
            {
                selectedDisco = 5;
            }

            else if(ev.mouse.x >= discos[6].x &&
                    ev.mouse.x <= discos[6].x+discos[6].largura &&
                    ev.mouse.y >= discos[6].y &&
                    ev.mouse.y <= discos[6].y+30)
            {
                selectedDisco = 6;
            }

            else if(ev.mouse.x >= discos[7].x &&
                    ev.mouse.x <= discos[7].x+discos[7].largura &&
                    ev.mouse.y >= discos[7].y &&
                    ev.mouse.y <= discos[7].y+30)
            {
                selectedDisco = 7;
            }
        }

        al_flip_display();
        al_clear_to_color(al_map_rgb(255, 255, 255));
    }

    /// Finalizações
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
/*
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
}*/
