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
//#include "../include/structs.c"
//#include "../include/CRUD.c"
#include "../include/resources.c"

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

void ObtenerHora(){
    char hora_formateada[9];
    time_t HoraActual = time(NULL);
    char dia_formateado[60];
    struct tm *info_tiempo = localtime(&HoraActual);
    strftime(hora_formateada, sizeof(hora_formateada), "%H:%M", info_tiempo);
    int dia = info_tiempo->tm_mday;
    int mes = info_tiempo->tm_mon + 1;  // tm_mon es 0-indexado, por lo que se suma 1
    int anio = info_tiempo->tm_year + 1900;
    al_draw_filled_rectangle(1000, 0, 1200, 700, al_map_rgb(255, 255, 255));
    al_draw_text(lexend_regular[59], texto_black, 1100, 300, ALLEGRO_ALIGN_CENTER, hora_formateada);
    al_draw_text(lexend_regular[20], texto_black, 1100, 400, ALLEGRO_ALIGN_CENTER, "%02d/%02/%d");
    al_flip_display();
}

void actualizar_display(){
    //FIGURAS PRIMITAVAS
    //al_draw_rectangle(30, 250, 150, 300, al_map_rgb(255, 0, 0), 3);
    al_draw_filled_rectangle(0, 0, 100, 700, al_map_rgb(255, 0, 0));
    al_draw_scaled_bitmap(HABITOSROSA, 0, 0, 100, 175, 0, 0,100, 175, 0);
    al_draw_scaled_bitmap(CALENDARIO, 0, 0, 100, 175, 0, 175,100, 175, 0);
    al_draw_scaled_bitmap(RECORDS, 0, 0, 100, 175, 0, 350,100, 175, 0);
    al_draw_scaled_bitmap(AJUSTES, 0, 0, 100, 175, 0, 525,100, 175, 0);
    al_flip_display();
    ObtenerHora();
}
void main_habitus(int verif_iniciador_primera_vez){
    int pantalla_requiere_actualizacion = 1;
    momento=verif_iniciador_primera_vez;//Si es 0, es que no se ha iniciado la aplicacion ni una vez
    while(fin!=1){
        if(al_event_queue_is_empty(cola_eventos) && pantalla_requiere_actualizacion){
            pantalla_requiere_actualizacion = 0;
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
            //contadorBytesArch("./data/app.dat");
            FILE *archh = fopen("./data/app.dat", "rb");
            //moverNLastId(archh);
            //manejarNLastId("./data/app.dat");
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

            }
        }
    }
}
int main() {
    ALLEGRO_DISPLAY *disp;
    int i;
    if(!al_init()) {
        printf("No se pudo iniciar Allegro");
    }
    disp = al_create_display(1200, 600);
    al_set_window_title(disp, "Hábitos");

    for(i=0; i<=2500; i++){
        printf("\n%i", i);
    }
    al_destroy_display(disp);
    printf("Ventana cerrada");
    return 0;
}