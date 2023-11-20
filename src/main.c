#include <stdio.h>
#include <allegro5/allegro.h>

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