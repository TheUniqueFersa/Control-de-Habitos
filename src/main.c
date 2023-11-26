#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "../include/structs.c"
#include "../include/CRUD.c"
#include "../include/resources.c"
/* ---->  <---- */
/* ----> Prototipos <---- */
int inicializar_allegro();//INICIALIZA TODO LO NECESARIO PARA QUE ALLEGRO FUNCIONÉ
void main_habitus(int);
void actualizar_display();
int init_resources();
//termina;
/* ----> ALLEGRO {TIPO DE DATOS} <---- */
// Displays
ALLEGRO_DISPLAY *disp;

// Eventos
ALLEGRO_EVENT_QUEUE *cola_eventos;
ALLEGRO_EVENT evento;

//SONIDO
ALLEGRO_SAMPLE_ID id_SAMPLE;
ALLEGRO_SAMPLE *SAMPLE;

//BITMAPS:
ALLEGRO_BITMAP *BITMAP;

//TIMERS
ALLEGRO_TIMER *timer_0_01;
//COLORES
ALLEGRO_FONT *fuente1;





/* ---- termina; ---- */

/* ----> VARIABLES GLOBALES <---- */
/* ----> General <---- */
int fin=0;
int momento=0; /*0: Inicio primera vez
 *              1:
 *
 *
 *
 *              */
/* ----> Nombres de archivos que manejar <---- */


char N_T_DIFICULTAD[100] = {"./../data/"};
//termina;


/* ----> ARCHIVOS <---- */
//termina;

void actualizar_display(){
    //FIGURAS PRIMITAVAS
    //al_draw_rectangle(30, 250, 150, 300, al_map_rgb(255, 0, 0), 3);
    al_draw_filled_rectangle(0, 0, 100, 700, al_map_rgb(255, 0, 0));
    al_draw_filled_rectangle(1000, 0, 1200, 700, al_map_rgb(255, 0, 0));
    al_flip_display();
}


void main_habitus(int verif_iniciador_primera_vez){
    int pantalla_requiere_actualizacion=1;
    momento=verif_iniciador_primera_vez;//Si es 0, es que no se ha iniciado la aplicacion ni una vez
    while(fin!=1){
        if(al_event_queue_is_empty(cola_eventos) && pantalla_requiere_actualizacion){
            pantalla_requiere_actualizacion=0;
            actualizar_display();
        }
        else if(!al_event_queue_is_empty(cola_eventos)){
            pantalla_requiere_actualizacion = 1;
        }

        //EVENTOS SUCEDIENDO:
        al_wait_for_event(cola_eventos, &evento);
        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            //funcion de confirmacion() --TODO
            fin = 1;
        }
        else if(evento.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT){//Evento de que perdiste el foco de la ventana
            printf("PERDISTE EL FOCO\n");
            contadorBytesArch("./data/app.dat");
            FILE *archh = fopen("./data/app.dat", "rb+");
            moverNLastId(archh);
            manejarNLastId("./data/app.dat");
        }
        else if(evento.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN){//Evento de que retomaste el foco de la ventana
            printf("RECUPERASTE EL FOCO\n");
        }
        else{//Si no fueron eventos generales de la ventana:
            switch (momento) {
                case 0:
                    switch (evento.type) {

                    }
                    break;
                case 1:
                    switch (evento.type) {

                    }
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    break;


            }
        }
    }
}
int main() {
    int acceso;

    if(inicializar_allegro()){

        disp = al_create_display(1200, 700);
        al_set_window_title(disp, "Hábitus");
        //al_set_display_icon(disp, n); // --TODO
        cola_eventos = al_create_event_queue();

        al_register_event_source(cola_eventos, al_get_display_event_source(disp)); // FUENTE: eventos de la ventana
        al_register_event_source(cola_eventos, al_get_keyboard_event_source()); // FUENTE: eventos del teclado
        //al_register_event_source(cola_eventos, al_get_timer_event_source(timer_0_01)); // FUENTE: eventos de tipo temporizador

        //ACCEDE AL ARCHIVO QUE TIENE LA INFORMACION DE INICIO DE APP POR PRIMERA VEZ
        // = acceso --TODO
        main_habitus(0);

//
        //al_destroy_timer( n );
        al_destroy_event_queue(cola_eventos);
        al_destroy_display(disp);
    }
    else{
        printf("\nOcurrio un error");// --TODO hacer un archivo txt que registre todos los errores
    }
    return 0;
}
int inicializar_allegro(){
    int verif_todo_ok=1;
    if(!al_init()) {
        printf("No se pudo iniciar Allegro");
    }
    if(!al_init_primitives_addon()){
        printf("No se iniciaron las primitivas");
        verif_todo_ok = 0;
    }
    if(!al_install_keyboard()){
        printf("No se instalo el teclado");
        verif_todo_ok = 0;
    }
    if(!al_init_image_addon()){
        printf("No se inicio image addon");
        verif_todo_ok = 0;
    }
    if(!al_install_audio()){//SONIDO
        printf("No se cargo el complemento de audio");
        verif_todo_ok = 0;
    }
    if(!al_init_acodec_addon()){//SONIDO
        printf("No se pudo cargar el complemento de codex");
        verif_todo_ok = 0;
    }
    if(!al_init_font_addon() || !al_init_ttf_addon()){
        printf("No se pudo cargar el complemento de fuentes");
        verif_todo_ok = 0;
    }
    if(!init_resources()){
        printf("Error al iniciar los recursos fuentes");
        verif_todo_ok = 0;
    }
    return verif_todo_ok;
}

