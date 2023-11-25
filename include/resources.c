#include <allegro5/allegro.h>
ALLEGRO_COLOR principal_pale_chestnut;
ALLEGRO_COLOR secundario_pastel_magenta;
ALLEGRO_COLOR neutro1_tinta_de_pulpo;
ALLEGRO_COLOR neutro2_african_violet;
ALLEGRO_COLOR neutro3_french_lilac;
int init_resources(){
    int inicializado_correctamente=1;
    principal_pale_chestnut = al_map_rgb(222, 186, 192);
    secundario_pastel_magenta = al_map_rgb(227,158,193);
    neutro1_tinta_de_pulpo = al_map_rgb(47,50,58);
    neutro2_african_violet = al_map_rgb(222, 186, 192);
    neutro3_french_lilac = al_map_rgb(222, 186, 192);
    return inicializado_correctamente;
}