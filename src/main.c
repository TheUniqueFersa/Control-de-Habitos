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


int main() {
    ALLEGRO_DISPLAY *disp;
    int i;
    if(!al_init()) {
        printf("No se pudo iniciar Allegro");
    }


    disp = al_create_display(1200, 700);
    al_set_window_title(disp, "Hábitos");

    for(i=0; i<=25000; i++){
        printf("\n%i", i);
    }
    al_destroy_display(disp);
    printf("Ventana cerrada");
    return 0;
}