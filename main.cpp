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

void calculaPosicao(ALLEGRO_EVENT ev, ponto retangulos[], int selectedRetangulo)
{
    bool permitir = retangulos[selectedRetangulo].topo;
    ponto * ret;
    int quant = 0;

    if(abs(ev.mouse.x-bloco_l) < abs(ev.mouse.x-(largura_t/2)) &&
            abs(ev.mouse.x-bloco_l) < abs(ev.mouse.x-(largura_t-bloco_l)))
    {
        for(int i = 0; i < n; i++)
        {
            if(retangulos[i].torre == 1)
            {
                if(selectedRetangulo != i) quant++;
                if((retangulos[i].largura < retangulos[selectedRetangulo].largura) ||
                        (retangulos[selectedRetangulo].topo == false))
                    permitir = false;
            }
        }
        if(permitir)
        {
            for(int i = 0; i < n; i++)
            {
                if(retangulos[i].torre == 1 && selectedRetangulo != i)
                    retangulos[i].topo = false;
            }
            if(retangulos[selectedRetangulo].torre != 1)
            {
                for(int i = 0; i < n; i++)
                {
                    if(retangulos[i].torre == retangulos[selectedRetangulo].torre &&
                       i != selectedRetangulo)
                        ret = &retangulos[i];
                }
                ret->topo = true;
            }
            retangulos[selectedRetangulo].x = (bloco_l)-(retangulos[selectedRetangulo].largura/2);
            retangulos[selectedRetangulo].torre = 1;
            retangulos[selectedRetangulo].y = pos_y-(quant*30);
        }
    }
    else if(abs(ev.mouse.x-(largura_t/2)) < abs(ev.mouse.x-bloco_l) &&
            abs(ev.mouse.x-(largura_t/2)) < abs(ev.mouse.x-(largura_t-bloco_l)))
    {
        for(int i = 0; i < n; i++)
        {
            if(retangulos[i].torre == 2)
            {
                if(selectedRetangulo != i) quant++;
                if((retangulos[i].largura < retangulos[selectedRetangulo].largura) ||
                        (retangulos[selectedRetangulo].topo == false))
                    permitir = false;
            }
        }
        if(permitir)
        {
            for(int i = 0; i < n; i++)
            {
                if(retangulos[i].torre == 2 && selectedRetangulo != i)
                    retangulos[i].topo = false;
            }
            if(retangulos[selectedRetangulo].torre != 2)
            {
                for(int i = 0; i < n; i++)
                {
                    if(retangulos[i].torre == retangulos[selectedRetangulo].torre &&
                       i != selectedRetangulo)
                        ret = &retangulos[i];
                }
                ret->topo = true;
            }
            retangulos[selectedRetangulo].x = (largura_t/2)-(retangulos[selectedRetangulo].largura/2);
            retangulos[selectedRetangulo].torre = 2;
            retangulos[selectedRetangulo].y = pos_y-(quant*30);
        }
    }
    else if(abs(ev.mouse.x-(largura_t-bloco_l)) < abs(ev.mouse.x-bloco_l) &&
            abs(ev.mouse.x-(largura_t-bloco_l)) < abs(ev.mouse.x-(largura_t/2)))
    {
        for(int i = 0; i < n; i++)
        {
            if(retangulos[i].torre == 3)
            {
                if(selectedRetangulo != i) quant++;
                if((retangulos[i].largura < retangulos[selectedRetangulo].largura) ||
                        (retangulos[selectedRetangulo].topo == false))
                    permitir = false;
            }
        }
        if(permitir)
        {
            for(int i = 0; i < n; i++)
            {
                if(retangulos[i].torre == 3 && selectedRetangulo != i)
                    retangulos[i].topo = false;
            }
            if(retangulos[selectedRetangulo].torre != 3)
            {
                for(int i = 0; i < n; i++)
                {
                    if(retangulos[i].torre == retangulos[selectedRetangulo].torre &&
                       i != selectedRetangulo)
                        ret = &retangulos[i];
                }
                ret->topo = true;
            }
            retangulos[selectedRetangulo].x = (largura_t-bloco_l)-(retangulos[selectedRetangulo].largura/2);
            retangulos[selectedRetangulo].torre = 3;
            retangulos[selectedRetangulo].y = pos_y-(quant*30);
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

    int selectedRetangulo = n-1;

    ponto retangulos[n];

    for(int i = 0; i < n; i++)
    {
        retangulos[i].torre = 1;

        if(i == n-1)
            retangulos[i].topo = true;
        else
            retangulos[i].topo = false;

        if(i == 0)
        {
            retangulos[i].x = pos_x;
            retangulos[i].largura = bloco_l+104;
        }
        else
        {
            retangulos[i].x = pos_x+((25/1.4)*i);
            retangulos[i].largura = bloco_l+104-((50/1.4)*i);
        }
        retangulos[i].y = pos_y-(i*30);
    }

    bool fim = false, mouse = false, ant = false;
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
            fim = true;

        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(ev.mouse.button & 1)
                mouse = true;
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            mouse = false;
            calculaPosicao(ev, retangulos, selectedRetangulo);
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
        al_draw_filled_rectangle(retangulos[2].x, retangulos[2].y, retangulos[2].x+retangulos[2].largura, retangulos[2].y+30, al_map_rgb(121, 82, 179));
        al_draw_filled_rectangle(retangulos[1].x, retangulos[1].y, retangulos[1].x+retangulos[1].largura, retangulos[1].y+30, al_map_rgb(251, 54, 64));
        al_draw_filled_rectangle(retangulos[0].x, retangulos[0].y, retangulos[0].x+retangulos[0].largura, retangulos[0].y+30, al_map_rgb(92, 51, 246));


        /// Demais discos (3,4,5,6,7)
        switch(n)
        {
        case 4:
            al_draw_filled_rectangle(retangulos[3].x, retangulos[3].y, retangulos[3].x+retangulos[3].largura, retangulos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        case 5:
            al_draw_filled_rectangle(retangulos[4].x, retangulos[4].y, retangulos[4].x+retangulos[4].largura, retangulos[4].y+30, al_map_rgb(27, 185, 247));
            al_draw_filled_rectangle(retangulos[3].x, retangulos[3].y, retangulos[3].x+retangulos[3].largura, retangulos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        case 6:
            al_draw_filled_rectangle(retangulos[5].x, retangulos[5].y, retangulos[5].x+retangulos[5].largura, retangulos[5].y+30, al_map_rgb(120, 222, 199));
            al_draw_filled_rectangle(retangulos[4].x, retangulos[4].y, retangulos[4].x+retangulos[4].largura, retangulos[4].y+30, al_map_rgb(27, 185, 247));
            al_draw_filled_rectangle(retangulos[3].x, retangulos[3].y, retangulos[3].x+retangulos[3].largura, retangulos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        case 7:
            al_draw_filled_rectangle(retangulos[6].x, retangulos[6].y, retangulos[6].x+retangulos[6].largura, retangulos[6].y+30, al_map_rgb(255, 191, 0));
            al_draw_filled_rectangle(retangulos[5].x, retangulos[5].y, retangulos[5].x+retangulos[5].largura, retangulos[5].y+30, al_map_rgb(120, 222, 199));
            al_draw_filled_rectangle(retangulos[4].x, retangulos[4].y, retangulos[4].x+retangulos[4].largura, retangulos[4].y+30, al_map_rgb(27, 185, 247));
            al_draw_filled_rectangle(retangulos[3].x, retangulos[3].y, retangulos[3].x+retangulos[3].largura, retangulos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        case 8:
            al_draw_filled_rectangle(retangulos[7].x, retangulos[7].y, retangulos[7].x+retangulos[7].largura, retangulos[7].y+30, al_map_rgb(120, 104, 230));
            al_draw_filled_rectangle(retangulos[6].x, retangulos[6].y, retangulos[6].x+retangulos[6].largura, retangulos[6].y+30, al_map_rgb(255, 191, 0));
            al_draw_filled_rectangle(retangulos[5].x, retangulos[5].y, retangulos[5].x+retangulos[5].largura, retangulos[5].y+30, al_map_rgb(120, 222, 199));
            al_draw_filled_rectangle(retangulos[4].x, retangulos[4].y, retangulos[4].x+retangulos[4].largura, retangulos[4].y+30, al_map_rgb(27, 185, 247));
            al_draw_filled_rectangle(retangulos[3].x, retangulos[3].y, retangulos[3].x+retangulos[3].largura, retangulos[3].y+30, al_map_rgb(251, 122, 252));
            break;
        }

        /// ---- Movimentação ----
        if(mouse)
        {
            if(ev.mouse.x >= retangulos[0].x &&
                    ev.mouse.x <= retangulos[0].x+retangulos[0].largura &&
                    ev.mouse.y >= retangulos[0].y &&
                    ev.mouse.y <= retangulos[0].y+30)
            {
                selectedRetangulo = 0;
            }

            else if(ev.mouse.x >= retangulos[1].x &&
                    ev.mouse.x <= retangulos[1].x+retangulos[1].largura &&
                    ev.mouse.y >= retangulos[1].y &&
                    ev.mouse.y <= retangulos[1].y+30)
            {
                selectedRetangulo = 1;
            }

            else if(ev.mouse.x >= retangulos[2].x &&
                    ev.mouse.x <= retangulos[2].x+retangulos[2].largura &&
                    ev.mouse.y >= retangulos[2].y &&
                    ev.mouse.y <= retangulos[2].y+30)
            {
                selectedRetangulo = 2;
            }

            else if(ev.mouse.x >= retangulos[3].x &&
                    ev.mouse.x <= retangulos[3].x+retangulos[3].largura &&
                    ev.mouse.y >= retangulos[3].y &&
                    ev.mouse.y <= retangulos[3].y+30)
            {
                selectedRetangulo = 3;
            }

            else if(ev.mouse.x >= retangulos[4].x &&
                    ev.mouse.x <= retangulos[4].x+retangulos[4].largura &&
                    ev.mouse.y >= retangulos[4].y &&
                    ev.mouse.y <= retangulos[4].y+30)
            {
                selectedRetangulo = 4;
            }

            else if(ev.mouse.x >= retangulos[5].x &&
                    ev.mouse.x <= retangulos[5].x+retangulos[5].largura &&
                    ev.mouse.y >= retangulos[5].y &&
                    ev.mouse.y <= retangulos[5].y+30)
            {
                selectedRetangulo = 5;
            }

            else if(ev.mouse.x >= retangulos[6].x &&
                    ev.mouse.x <= retangulos[6].x+retangulos[6].largura &&
                    ev.mouse.y >= retangulos[6].y &&
                    ev.mouse.y <= retangulos[6].y+30)
            {
                selectedRetangulo = 6;
            }

            else if(ev.mouse.x >= retangulos[7].x &&
                    ev.mouse.x <= retangulos[7].x+retangulos[7].largura &&
                    ev.mouse.y >= retangulos[7].y &&
                    ev.mouse.y <= retangulos[7].y+30)
            {
                selectedRetangulo = 7;
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
