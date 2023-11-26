#include <allegro5/allegro.h>
ALLEGRO_COLOR principal_pale_chestnut;
ALLEGRO_COLOR secundario_pastel_magenta;
ALLEGRO_COLOR neutro1_tinta_de_pulpo;
ALLEGRO_COLOR neutro2_african_violet;
ALLEGRO_COLOR neutro3_french_lilac;
ALLEGRO_COLOR texto_black;
ALLEGRO_FONT * lexend_regular[100];
ALLEGRO_FONT * lexend_bold[100];
ALLEGRO_FONT * lexend_thin[100];
ALLEGRO_FONT * roboto_bold[100];
ALLEGRO_FONT * roboto_italic[100];
ALLEGRO_FONT * roboto_regular[100];
ALLEGRO_FONT * roboto_thin[100];
ALLEGRO_FONT * roboto_black[100];
ALLEGRO_BITMAP *RECORDS;
ALLEGRO_BITMAP *HABITOS;
ALLEGRO_BITMAP *CALENDARIO;
ALLEGRO_BITMAP *AJUSTES;

ALLEGRO_BITMAP *CALENDARIOROSA;
ALLEGRO_BITMAP *AJUSTESROSA;
ALLEGRO_BITMAP *RECORDSROSA;
ALLEGRO_BITMAP *HABITOSROSA;

int init_resources(){
    int inicializado_correctamente=1;
    principal_pale_chestnut = al_map_rgb(222, 186, 192);
    secundario_pastel_magenta = al_map_rgb(227,158,193);
    neutro1_tinta_de_pulpo = al_map_rgb(47,50,58);
    neutro2_african_violet = al_map_rgb(222, 186, 192);
    neutro3_french_lilac = al_map_rgb(222, 186, 192);
    texto_black = al_map_rgb(0,0,0);
    for(int i; i<60; i++) {
        lexend_regular[i] = al_load_font("./media/fuentes/lexend/Lexend-Regular.ttf", i, 0);
        lexend_bold[i] = al_load_font("./media/fuentes/lexend/Lexend-Bold.ttf", i, 0);
        lexend_thin[i] = al_load_font("./media/fuentes/lexend/Lexend-Thin.ttf", i, 0);
        roboto_bold[i] = al_load_font("./media/fuentes/roboto/Roboto-Bold.ttf", i, 0);
        roboto_italic[i] = al_load_font("./media/fuentes/roboto/Roboto-Italic.ttf", i, 0);
        roboto_regular[i] = al_load_font("./media/fuentes/roboto/Roboto-Regular.ttf", i, 0);
        roboto_thin[i] = al_load_font("./media/fuentes/roboto/Roboto-Thin.ttf", i, 0);
        roboto_black[i] = al_load_font("./media/fuentes/roboto/Roboto-Black.ttf", i, 0);

        if(!lexend_regular[i] || !lexend_bold[i] || !lexend_thin[i]){
            inicializado_correctamente = 0;
            printf("ERROR: %i\n", al_get_errno());
            printf("ERROR: Hubo un problema al cargar las fuentes de lexend\n");
        }
        if(!roboto_regular[i] || !roboto_black[i] || !roboto_bold[i] || !roboto_italic[i] || !roboto_thin[i]){
            inicializado_correctamente = 0;
            printf("ERROR: %i\n", al_get_errno());
            printf("ERROR: Hubo un problema al cargar las fuentes de roboto\n");
        }
    }
    RECORDS = al_load_bitmap("./media/img/recordatorio_blanco.jpg");
    HABITOS = al_load_bitmap("./media/img/habitosblanco.jpg");
    CALENDARIO = al_load_bitmap("./media/img/cal_blanco.jpg");
    AJUSTES = al_load_bitmap("./media/img/ajustes_blanco.jpg");

    CALENDARIOROSA = al_load_bitmap("./media/img/cal_rosa.jpg");
    RECORDSROSA = al_load_bitmap("./media/img/recordatorio_rosa.jpg");
    HABITOSROSA = al_load_bitmap("./media/img/habitosrosa.jpg");
    AJUSTESROSA = al_load_bitmap("./media/img/ajustes_rosa.jpg");
    HABITOSROSA = al_load_bitmap("./media/img/habitosrosa.jpg");

    if(!RECORDS || !HABITOS || !CALENDARIO || !AJUSTES || !CALENDARIOROSA || !RECORDSROSA || !HABITOSROSA || !AJUSTESROSA || !HABITOSROSA){
        inicializado_correctamente = 0;
        printf("ERROR: %i\n", al_get_errno());
        printf("ERROR: Hubo un problema al cargar las imágenes de img\n");
    }

    return inicializado_correctamente;
}