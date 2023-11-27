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
#include "../include/CRUD.c"
#include "../include/resources.c"
#include "../tests/depuracion.c"
/* ---->  <---- */
/* ----> Prototipos <---- */
int inicializar_allegro();//INICIALIZA TODO LO NECESARIO PARA QUE ALLEGRO FUNCIONÉ
void main_habitus(int, int);
void actualizar_display();
int init_resources();
void IUSD();
void llamarINSERT();
void llamarUPDATE();
void llamarSELECT();
void llamarDELETE();
void creacionEstructuras();
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
ALLEGRO_TIMER *AFK;

//COLORES
ALLEGRO_FONT *fuente1;





/* ---- termina; ---- */
/* ----> ESTRUCTURAS GLOBALES <---- */
struct APP{
    int init;
    int ID_last_user;
};
struct APP appp = {0, 1}, app_recibe = {0};
HABITO habNULL={0};
USUARIO usuNULL={0};
HORARIO  horNULL={0};
RECORDATORIOS recNULL={0};
DIFICULTAD difNULL = {0};
/* ---- termina; ---- */

/* ----> VARIABLES GLOBALES <---- */
int fin=0;
int momento=0; /*0: Inicio primera vez
 *              1:
 *
 *
 *
 *              */
/* ----> Nombres/RUTAS de archivos que manejar <---- */
char rutaAPP[100] = {"./data/app.dat"};
char rutaUSUARIO[100] = {"./data/usuario.dat"};

//char frag_1rutas[100] = {""};
char frag_2rutaDIFICULTAD[100] = {"/dificultad.dat"};
char frag_2rutaTIPO[100] = {"/tipo.dat"};
char frag_2rutaHABITO[100] = {"/habito.dat"};
char frag_2rutaREGISTROHABITO[100] = {"/registro_habito.dat"};
char frag_2rutaHORARIO[100] = {"/horario.dat"};
char frag_2rutaHORA_HORARIO[100] = {"/horario.dat"};
char frag_2rutaRECORDATORIO[100] = {"/recordatorio.dat"};
char frag_2rutaPRODUCTIVIDAD[100] = {"/productividad.dat"};


char rutaDIFICULTAD[100] = {"./data/usuarios/"};
char rutaTIPO[100] = {"./data/usuarios/"};
char rutaHABITO[100] = {"./data/usuarios/"};
char rutaREGISTROHABITO[100] = {"./data/usuarios/"};
char rutaHORARIO[100] = {"./data/usuarios/"};
char rutaHORA_HORARIO[100] = {"./data/usuarios/"};
char rutaRECORDATORIO[100] = {"./data/usuarios/"};
char rutaPRODUCTIVIDAD[100] = {"./data/usuarios/"};
/*
char rutaDIFICULTAD[100] = {"./data/usuarios/1/dificultad.dat"};
char rutaTIPO[100] = {"./data/usuarios/1/tipo.dat"};
char rutaHABITO[100] = {"./data/usuarios/1/habito.dat"};
char rutaREGISTROHABITO[100] = {"./data/usuarios/1/registro_habito.dat"};
char rutaHORARIO[100] = {"./data/usuarios/1/horario.dat"};
char rutaHORA_HORARIO[100] = {"./data/usuarios/1/horario.dat"};
char rutaRECORDATORIO[100] = {"./data/usuarios/1/recordatorio.dat"};
char rutaPRODUCTIVIDAD[100] = {"./data/usuarios/1/productividad.dat"};
 */
/* ---- termina; ---- */

void Dia(int dia){
    al_draw_text(lexend_regular[15], texto_black, 1015, 375, ALLEGRO_ALIGN_LEFT, "Do Lu  Ma Mi  Ju  Vi  Sa");
    for (int i = 0; i < 7; ++i) {
        if (i == dia) {
            al_draw_filled_rectangle(1015 + i * 25, 395, 1035 + i * 25, 415, secundario_pastel_magenta);
        } else {
            al_draw_filled_rectangle(1015 + i * 25, 395, 1035 + i * 25, 415, fondo_gris1);
        }
    }
}
char CantHabitosHoy[2]="10"; //GLOBAL para que se imprima bien
void Pendientes(){
    //-ALLEGRO_PI/2.0 SE UTILIZA PARA INICIAR EN LA PARTE SUPERIOR DE LA CIRCUNFERENCIA
    //theta se trabaja en radianes
    //PasoHabitos=(-2*ALLEGRO_PI)/CantHabitosHoy

    al_draw_line(1000,25,1000,675,fondo_gris1,2);
    //PasoRecordatorios=(-2*ALLEGRO_PI)/CantRecordatoriosHoy
    al_draw_arc(1100,75, 50,-ALLEGRO_PI/2.0,-ALLEGRO_PI,principal_pale_chestnut,15.0);
    al_draw_text(lexend_regular[30],texto_black,1100,55,ALLEGRO_ALIGN_CENTER,CantHabitosHoy);
    al_draw_arc(1100,225, 50,-ALLEGRO_PI/2.0,-ALLEGRO_PI,neutro1_tinta_de_pulpo,15.0);
    al_draw_text(lexend_regular[30], texto_black, 1100, 205, ALLEGRO_ALIGN_CENTER, CantHabitosHoy);
}
void calendario(int dia_semana, int mes,int primero){
    int FILAS = 6;
    int COLUMNAS = 7;
    int CELDA=25;
    int tipomes=mes%2;
    int dias_en_mes;
    int primerafila=0;
    if(mes==2){
        dias_en_mes=28;
    }else if(tipomes==0){
        dias_en_mes=31;
    }else if(tipomes==1){
        dias_en_mes=30;
    }
    float transparencia;
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int columna = 0; columna < COLUMNAS; ++columna) {
            if(primerafila==0){
                columna=primero;
                primerafila=1;
            }
            int dia_calendario = fila * COLUMNAS + columna + 1 - dia_semana-primero;
            //Aqui va la lógica para poder hacer la transparencia en base a la cantidad de actividades que tuvo,solo que ocupo la cantidad
            if(dia_calendario%4==0)transparencia=0;
            else if(dia_calendario%4==1)transparencia=255/2;
            else if(dia_calendario%4==2)transparencia=255*3/4;
            else if(dia_calendario%4==3)transparencia=255*4/5;
            if (dia_calendario >= 1 && dia_calendario <= dias_en_mes) {
                // Dibujar calendario

                    al_draw_filled_rectangle(1012 + columna * CELDA+3, 500 + 3 + fila * CELDA,
                                             1012 + (columna + 1) * CELDA, 500 + (fila + 1) * CELDA,
                                             fondo_gris1);
                if (transparencia != 0) {
                    al_draw_filled_rectangle(1012 + columna * CELDA+3, 500+ 3 + fila * CELDA,
                                             1012 + (columna + 1) * CELDA, 500 + (fila + 1) * CELDA,
                                             al_map_rgba(248,107,234,transparencia));
                }

                // Puedes agregar el número del día del mes
                char texto_dia[3];
                snprintf(texto_dia, sizeof(texto_dia), "%d", dia_calendario);
                al_draw_text(roboto_black[10], texto_black,
                             1012 + 3 + columna * CELDA + CELDA / 2, 495 + fila * CELDA + CELDA / 2,
                             ALLEGRO_ALIGN_CENTER, texto_dia);
            }
        }
    }
}
void ObtenerHora(){
    char hora_formateada[9];
    time_t Hora=time(NULL);
    struct tm *primerdia= localtime(&Hora);
    primerdia->tm_mday = 1;
    primerdia->tm_hour = 0;
    primerdia->tm_min = 0;
    primerdia->tm_sec = 0;
    mktime(primerdia);
    int primero=primerdia->tm_wday;
    time_t HoraActual = time(NULL);
    struct tm *info_tiempo = localtime(&HoraActual);
    char dia_formateado[60];
    strftime(hora_formateada, sizeof(hora_formateada), "%H:%M", info_tiempo);
    int dia = info_tiempo->tm_mday;
    int dia_semana = info_tiempo->tm_wday;
    int mes = info_tiempo->tm_mon + 1;
    int anio = info_tiempo->tm_year + 1900;
    sprintf(dia_formateado,"%02d/%02d/%d",dia,mes,anio);
    Pendientes();
    Dia(dia_semana);
    calendario(dia_semana,mes,(primero));
    al_draw_text(lexend_regular[59], texto_black, 1100, 310, ALLEGRO_ALIGN_CENTER, hora_formateada);
    al_draw_text(lexend_regular[20], texto_black, 1100, 420, ALLEGRO_ALIGN_CENTER, dia_formateado);
}
void ventanaActual(int momento){
    int i=0;
    switch (momento) {
        case 0:
            break;
        case 1:
            al_draw_scaled_bitmap(HABITOSROSA, 0, 0, 100, 300, 0, 0,100, 300, 0);
            al_draw_scaled_bitmap(CALENDARIOBLANCO, 0, 0, 100, 300, 0, 175,100, 300, 0);
            al_draw_scaled_bitmap(RECORDS, 0, 0, 100, 300, 0, 350,100, 300, 0);
            al_draw_scaled_bitmap(AJUSTES, 0, 0, 100, 300, 0, 525,100, 300, 0);
            break;
        case 2:
            al_draw_scaled_bitmap(HABITOS, 0, 0, 100, 300, 0, 0,100, 300, 0);
            al_draw_scaled_bitmap(CALENDARIOROSA, 0, 0, 100, 300, 0, 175,100, 300, 0);
            al_draw_scaled_bitmap(RECORDS, 0, 0, 100, 300, 0, 350,100, 300, 0);
            al_draw_scaled_bitmap(AJUSTES, 0, 0, 100, 300, 0, 525,100, 300, 0);
            break;
        case 3:
            al_draw_scaled_bitmap(HABITOS, 0, 0, 100, 300, 0, 0,100, 300, 0);
            al_draw_scaled_bitmap(CALENDARIOBLANCO, 0, 0, 100, 300, 0, 175,100, 300, 0);
            al_draw_scaled_bitmap(RECORDSROSA, 0, 0, 100, 300, 0, 350,100, 300, 0);
            al_draw_scaled_bitmap(AJUSTES, 0, 0, 100, 300, 0, 525,100, 300, 0);
            break;
        case 4:
            al_draw_scaled_bitmap(HABITOS, 0, 0, 100, 300, 0, 0,100, 300, 0);
            al_draw_scaled_bitmap(CALENDARIOBLANCO, 0, 0, 100, 300, 0, 175,100, 300, 0);
            al_draw_scaled_bitmap(RECORDS, 0, 0, 100, 300, 0, 350,100, 300, 0);
            al_draw_scaled_bitmap(AJUSTESROSA, 0, 0, 100, 300, 0, 525,100, 300, 0);
            break;
        default:
    }
    if(momento!=0){
        al_draw_filled_rectangle(1000, 0, 1200, 700, al_map_rgb(255, 255, 255));
        ObtenerHora();
        al_draw_line(100,25,100,675,fondo_gris1,2);
    }
}
void actualizar_display(){
    //FIGURAS PRIMITAVAS
    al_draw_filled_rectangle(0, 0, 100, 700, al_map_rgb(255, 0, 0));
    al_draw_scaled_bitmap(HABITOSROSA, 0, 0, 100, 175, 0, 0,100, 175, 0);
    al_draw_scaled_bitmap(CALENDARIOBLANCO, 0, 0, 100, 175, 0, 175,100, 175, 0);
    al_draw_scaled_bitmap(RECORDS, 0, 0, 100, 175, 0, 350,100, 175, 0);
    al_draw_scaled_bitmap(AJUSTES, 0, 0, 100, 175, 0, 525,100, 175, 0);

    al_draw_filled_rectangle(1000, 0, 1200, 700, al_map_rgb(255, 255, 255));
    al_draw_filled_rectangle(101, 0, 1000, 720, al_map_rgb(47, 50, 58));
    /*al_draw_filled_rectangle(300, 90, 500, 120, al_map_rgb(214, 164, 226));
    al_draw_filled_rectangle(600, 90, 800, 120, al_map_rgb(214, 164, 226));
    //l_draw_filled_rectangle(150, 150, 950, 600, al_map_rgb(119, 86, 122));
    /*al_draw_filled_rectangle(175, 175, 925, 400, al_map_rgb(74, 63, 75));
    al_draw_filled_rectangle(190, 190, 910, 235, al_map_rgb(227, 158, 193));//227, 158, 193, 1
    al_draw_filled_rectangle(190, 250, 540, 370, al_map_rgb(227, 158, 193)); //(225, 0, 129));
    al_draw_filled_rectangle(550, 250, 910, 370, al_map_rgb(227, 158, 193));
    //al_draw_filled_rectangle(550, 250, 910, 290, al_map_rgb(225, 0, 129));
    al_draw_filled_rectangle(550, 330, 910, 370, al_map_rgb(225, 0, 129));
    al_draw_filled_rectangle(220, 270, 290, 340, al_map_rgb(225, 0, 129));
    al_draw_filled_rectangle(440, 270, 510, 340, al_map_rgb(225, 0, 129));
    al_draw_scaled_bitmap(LOGO, 0, 0, 516, 484, 488, 0,125, 125, 0);
    al_draw_filled_rectangle(340, 285, 390, 330, al_map_rgb(225, 0, 129));
    al_draw_scaled_bitmap(NUEVOHABITO, 0, 0, 738, 740, 100, 496,75, 68, 0);
    al_draw_scaled_bitmap(EDITARHABITO, 0, 0, 740, 744, 100, 564,75, 68, 0);
    al_draw_scaled_bitmap(BORRARHABITO, 0, 0, 744, 740, 100, 632,75, 68, 0);
    //al_draw_filled_circle(100, 510, 50, al_map_rgb(74, 63, 75));*/
    al_draw_filled_rounded_rectangle(325, 150, 800, 720, 100, 100, al_map_rgb(227, 218, 201));
    al_draw_filled_circle(562, 400, 238, al_map_rgb(227, 218, 201));//255, 134, 0, 1
    //al_draw_filled_pieslice(0,0,40, al_map_rgb(74, 63, 75));
    al_draw_pieslice(475, 400, 120,2.9, 3.6, al_map_rgb(255, 255, 255), 4);
    al_draw_scaled_bitmap(NUEVOHABITO, 0, 0, 738, 740, 100, 496,75, 68, 0);
    al_draw_scaled_bitmap(EDITARHABITO, 0, 0, 740, 744, 100, 564,75, 68, 0);
    al_draw_scaled_bitmap(BORRARHABITO, 0, 0, 744, 740, 100, 632,75, 68, 0);
    al_draw_scaled_bitmap(BORRARHABITO, 0, 0, 744, 740, 100, 632,75, 68, 0);


    al_draw_arc(475, 400, 120, 2.95, 0.55, al_map_rgba(255, 0, 0, 500), 20);
    al_draw_arc(475, 400, 120, 3.6, 0.6, al_map_rgba(255, 134, 0, 500), 20);//255, 134, 0, 1
    al_draw_arc(475, 400, 120, 4.3, 0.8, al_map_rgba(255, 255, 0, 500), 20);
    al_draw_arc(475, 400, 120, 5.2, 0.7, al_map_rgba(69, 183, 30, 500), 20);
    al_draw_arc(475, 400, 120, 5.95, 0.5, al_map_rgba(22, 82, 1, 500), 20);//22, 82, 1, 1
    al_draw_filled_circle(475, 400, 15, al_map_rgb(0, 0, 0));//255, 134, 0, 1
    al_draw_filled_triangle(470, 400, 480, 400, 475, 300, al_map_rgb(0, 0, 0));
    al_draw_filled_rounded_rectangle(450, 175, 675, 250, 25, 25, al_map_rgb(222, 186, 201));//222, 186, 192, 1
    al_draw_scaled_bitmap(LOGO, 0, 0, 516, 484, 360, 175,80, 80, 0);
    al_draw_filled_rounded_rectangle(625, 270, 780, 635, 25, 25, al_map_rgb(222, 186, 201));//222, 186, 192, 1
    al_draw_filled_rounded_rectangle(650, 290, 755, 330, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
    al_draw_filled_rounded_rectangle(650, 335, 755, 403, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
    al_draw_filled_rounded_rectangle(650, 408, 755, 476, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
    al_draw_filled_rounded_rectangle(650, 481, 755, 549, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
    al_draw_filled_rounded_rectangle(650, 554, 755, 622, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1

    ObtenerHora();
    al_flip_display();
}
void inicializar_rutas_usuario(char * usuario){
    strcat(rutaDIFICULTAD, usuario);
    strcat(rutaDIFICULTAD, frag_2rutaDIFICULTAD);

    strcat(rutaTIPO, usuario);
    strcat(rutaTIPO, frag_2rutaTIPO);

    strcat(rutaHABITO, usuario);
    strcat(rutaHABITO, frag_2rutaHABITO);

    strcat(rutaREGISTROHABITO, usuario);
    strcat(rutaREGISTROHABITO, frag_2rutaREGISTROHABITO);

    strcat(rutaHORARIO, usuario);
    strcat(rutaHORARIO, frag_2rutaHORARIO);

    strcat(rutaHORA_HORARIO, usuario);
    strcat(rutaHORA_HORARIO, frag_2rutaHORA_HORARIO);

    strcat(rutaRECORDATORIO, usuario);
    strcat(rutaRECORDATORIO, frag_2rutaRECORDATORIO);

    strcat(rutaPRODUCTIVIDAD, usuario);
    strcat(rutaPRODUCTIVIDAD, frag_2rutaPRODUCTIVIDAD);
}
void colorearDia(int x, int y, char valor) {
    if(valor==1){
        al_draw_filled_rectangle(x,y,x+20,y+20,principal_pale_chestnut);
    }else{
        al_draw_filled_rectangle(x,y,x+20,y+20,fondo_gris1);
    }
}
void main_habitus(int verif_iniciador_primera_vez, int ultimo_usuario){
    int pantalla_requiere_actualizacion=1;
    char usuarioString[100], frag_1RutaUsuario;
    momento=verif_iniciador_primera_vez;//Si es 0, es que no se ha iniciado la aplicacion ni una vez
    printf("%i, %i\n", momento, ultimo_usuario);
    itoa(ultimo_usuario, usuarioString, 10);
    inicializar_rutas_usuario(usuarioString);
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", rutaDIFICULTAD, rutaTIPO, rutaHABITO, rutaREGISTROHABITO, rutaHORARIO, rutaHORA_HORARIO, rutaRECORDATORIO, rutaPRODUCTIVIDAD);
    //momento=-1;//DEP
    USUARIO usuario ={1,"Alcantara"},usuarioprueba={0};
    al_draw_filled_rectangle(0,0,1200,700, fondo_principal_comohuesito);
    if(momento==0){
        al_draw_text(lexend_regular[40], texto_black,600,300,ALLEGRO_ALIGN_CENTER,"Parece que es tu primera vez abriendo Habitus");
        al_draw_text(lexend_regular[30], texto_black,600,350,ALLEGRO_ALIGN_CENTER,"Presiona cualquier tecla para continuar");
    }
    char nombre[30] = {0};
    /**/
    USUARIO usNULL = {0};
    HABITO haNULL = {0};
    RECORDATORIOS reNULL= {0};
    DIFICULTAD diNULL ={0};
    TIPO tNULL = {0};
    //SELECT(rutaTIPO, &tNULL, sizeof(TIPO), 1, 2);
//        printf("Nombre: %s\nNota:%s\nID:%i\n", haNULL.nombre, haNULL.nota, haNULL.ID_habito);
//        printf("Nombre: %s\nID:%i", usNULL.nombre, usNULL.ID_usuario);
//    printf("recordatorio: %s\nid:%i\nTIPO:%s\n", reNULL.recordatorio, reNULL.ID_recordatorio, reNULL.ptr_fk_tipo->tipo);
//    printf("Dificultad: %s\nID:%i", diNULL.dificultad, diNULL.ID_dificultad);
//    printf("Tipo:%s\nID:%i\n", tNULL.tipo, tNULL.ID_tipo);
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
        }else if(evento.type == ALLEGRO_EVENT_TIMER){
            actualizar_display();
        }
        else if(evento.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT){//Evento de que perdiste el foco de la ventana
            //printf("PERDISTE EL FOCO\n");
        }
        else if(evento.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN){//Evento de que retomaste el foco de la ventana
            //printf("RECUPERASTE EL FOCO\n");

        }
        else{//Si no fueron eventos generales de la ventana:
            switch (momento) {
                case -1: //Depuracion
                    switch (evento.type) {
                        case ALLEGRO_EVENT_KEY_DOWN:
                            switch (evento.keyboard.keycode) {
                                case ALLEGRO_KEY_F:
                                    printf("\n\n----\n");
                                    /*DIFICULTAD*/
                                    /* --HECHA
                                    DIFICULTAD dif1 = {777, "Muy facil"};
                                    DIFICULTAD dif2 = {2, "Facil"};
                                    DIFICULTAD dif3 = {3, "Intermedio"};
                                    DIFICULTAD dif4 = {4, "Dificil"};
                                    DIFICULTAD dif5 = {5, "Muy dificil"};
                                    DIFICULTAD vacia = {0};
                                    */
                                    /*USUARIO*/
                                    /*
                                    USUARIO usu1 = {1, "Luillilol"};
                                    USUARIO usu2 = {2, "Fersa"};
                                    USUARIO usu3 = {3, "José"};
                                    USUARIO usu4 = {4, "Arias"};
                                    USUARIO usu5 = {5, "Raz"};
                                     */
                                    /*TIPO */
                                    TIPO tip1 = {1, "Personal"};
                                    TIPO tip2 = {2, "Escuela"};
                                    TIPO tip3 = {3, "Salud"};
                                    /*HABITO*/
                                    time_t tiempo= time(NULL);
                                    struct tm *infoTiempo;
                                    time(&tiempo);
                                    infoTiempo = localtime(&tiempo);
                                    FECHA miFecha = *infoTiempo;
                                    printf("Fecha actual: %d/%d/%d %02d:%02d:%02d\n", miFecha.tm_year + 1900, miFecha.tm_mon + 1, miFecha.tm_mday,
                                           miFecha.tm_hour, miFecha.tm_min, miFecha.tm_sec);
                                    /*
                                    HABITO hab1 = {1, "Ir al Gym", "Llevar toalla", "0010110", 1, &tip3, tip3, &dif3, dif3,  12, tiempo, miFecha};
                                    HABITO hab2 = {1, "Krunkear", "Un ratito", "1010010", 5, &tip1, tip1, &dif1, dif1, 35,  tiempo, miFecha};
                                    HABITO hab3 = {1, "Hacer la tarea", "Pa mañana", "0000001", 7, &tip2, tip2, &dif3, dif3, 2,  tiempo, miFecha};
                                    HABITO hab4 = {1, "Una paja a la crema", "Es una buena paja", "1111111", 5, &tip1, tip1, &dif1, dif1, 100,  tiempo, miFecha};
                                      */
                                            //SUPER INSERT TIPO
                                            /*
                                    SUPER_INSERT(&tip1.ID_tipo, rutaTIPO, &tip1, sizeof(TIPO), 1);
                                    SUPER_INSERT(&tip2.ID_tipo, rutaTIPO, &tip2, sizeof(TIPO), 1);
                                    SUPER_INSERT(&tip3.ID_tipo, rutaTIPO, &tip3, sizeof(TIPO), 1);
                                    //SUPERO INSERT HABITO
                                    SUPER_INSERT(&hab1.ID_habito, rutaHABITO, &hab1, sizeof(HABITO), 1);
                                    SUPER_INSERT(&hab2.ID_habito, rutaHABITO, &hab2, sizeof(HABITO), 1);
                                    SUPER_INSERT(&hab3.ID_habito, rutaHABITO, &hab3, sizeof(HABITO), 1);
                                    SUPER_INSERT(&hab4.ID_habito, rutaHABITO, &hab4, sizeof(HABITO), 1);
                                             */

                                    /*REGISTROH-HABITOS*/

                                    /*
                                    time_t tiempo2= time(NULL);
                                    struct tm *infoTiempo2;
                                    time(&tiempo2);
                                    infoTiempo2= localtime(&tiempo2);
                                    FECHA miFecha2 = *infoTiempo2;
                                    printf("Fecha actual: %d/%02d/%02d %02d:%02d:%02d\n",
                                           miFecha2.tm_year + 1900, miFecha2.tm_mon + 1, miFecha2.tm_mday,
                                           miFecha2.tm_hour, miFecha2.tm_min, miFecha2.tm_sec);
                                    REGISTRO_HABITOS reg_hab1 = {1, &hab1, tiempo2, miFecha2, 1, 0};
                                    REGISTRO_HABITOS reg_hab2 = {2, &hab2, tiempo2, miFecha2, 4, 1};
                                    REGISTRO_HABITOS reg_hab3 = {3, &hab3, tiempo2, miFecha2, 1, 0};
                                    REGISTRO_HABITOS reg_hab4 = {4, &hab4, tiempo2, miFecha2, 5, 0};
                                    */
                                    /*HORARIO*/
                                    /*
                                    HORARIO horario1 = {1, "Algebra", "1000100", &tip2, tiempo, miFecha2, miFecha2, miFecha2};
                                    HORARIO horario2 = {2, "Curso Progra", "1010101", &tip2, tiempo, miFecha2, miFecha2, miFecha2};
                                    HORARIO horario3 = {3, "Calculo", "0111000", &tip2, tiempo, miFecha2, miFecha2, miFecha2};
                                    */
                                    /*HORA_HORARIO*/
                                    /*
                                    HORA_HORARIO hor_hor1={1, &horario1, tiempo, miFecha2, miFecha2};
                                    HORA_HORARIO hor_hor2={2, &horario1, tiempo, miFecha2, miFecha2};
                                    HORA_HORARIO hor_hor3={3, &horario2, tiempo, miFecha2, miFecha2};
                                    HORA_HORARIO hor_hor4={4, &horario2, tiempo, miFecha2, miFecha2};
                                     */
                                    /*RECORDATORIOS*/
                                    /*
                                    RECORDATORIOS recor1 = {1, "EXAMEN FINAL PIÑA", &tip2, tiempo, miFecha2, 0};
                                    RECORDATORIOS recor2 = {2, "Serie Algebra", &tip2, tiempo, miFecha2, 1};
                                    RECORDATORIOS recor3 = {3, "Salida con amigos", &tip1, tiempo, miFecha2, 0};
                                    RECORDATORIOS recor4 = {4, "Cita con Doctor", &tip3, tiempo, miFecha2, 1};
                                     */
                                    /*PRODUCTIVIDAD*/
                                    /*
                                    PRODUCTIVIDAD product1= {1, tiempo, miFecha2, 7, 6};
                                    PRODUCTIVIDAD product2= {2, tiempo, miFecha2, 8, 7};
                                    PRODUCTIVIDAD product3= {3, tiempo, miFecha2, 12, 10};
                                    */
/*
                                    //SUPERINSERT DIFICULTAD
                                    SUPER_INSERT(&dif1.ID_dificultad, rutaDIFICULTAD, &dif1, sizeof(DIFICULTAD), 1);
                                    SUPER_INSERT(&dif2.ID_dificultad, rutaDIFICULTAD, &dif2, sizeof(DIFICULTAD), 1);
                                    SUPER_INSERT(&dif3.ID_dificultad, rutaDIFICULTAD, &dif3, sizeof(DIFICULTAD), 1);
                                    SUPER_INSERT(&dif4.ID_dificultad, rutaDIFICULTAD, &dif4, sizeof(DIFICULTAD), 1);
                                    SUPER_INSERT(&dif5.ID_dificultad, rutaDIFICULTAD, &dif5, sizeof(DIFICULTAD), 1);
                                    //SUPER INSERT USUARIO
                                    SUPER_INSERT(&usu1.ID_usuario, rutaUSUARIO, &usu1, sizeof(USUARIO), 1);
                                    SUPER_INSERT(&usu2.ID_usuario, rutaUSUARIO, &usu2, sizeof(USUARIO), 1);
                                    SUPER_INSERT(&usu3.ID_usuario, rutaUSUARIO, &usu3, sizeof(USUARIO), 1);
                                    SUPER_INSERT(&usu4.ID_usuario, rutaUSUARIO, &usu4, sizeof(USUARIO), 1);
                                    SUPER_INSERT(&usu5.ID_usuario, rutaUSUARIO, &usu5, sizeof(USUARIO), 1);

                                    //SUPER INSERT TIPO
                                    SUPER_INSERT(&tip1.ID_tipo, rutaTIPO, &tip1, sizeof(TIPO), 1);
                                    SUPER_INSERT(&tip2.ID_tipo, rutaTIPO, &tip2, sizeof(TIPO), 1);
                                    SUPER_INSERT(&tip3.ID_tipo, rutaTIPO, &tip3, sizeof(TIPO), 1);
                                    //SUPERO INSERT HABITO
                                    SUPER_INSERT(&hab1.ID_habito, rutaHABITO, &hab1, sizeof(HABITO), 1);
                                    SUPER_INSERT(&hab2.ID_habito, rutaHABITO, &hab2, sizeof(HABITO), 1);
                                    SUPER_INSERT(&hab3.ID_habito, rutaHABITO, &hab3, sizeof(HABITO), 1);
                                    SUPER_INSERT(&hab4.ID_habito, rutaHABITO, &hab4, sizeof(HABITO), 1);
                                    //SUÉRINSERT REGISTROHABITO
                                    SUPER_INSERT(&reg_hab1.ID_RH, rutaREGISTROHABITO, &reg_hab1, sizeof(REGISTRO_HABITOS), 1);
                                    SUPER_INSERT(&reg_hab2.ID_RH, rutaREGISTROHABITO, &reg_hab2, sizeof(REGISTRO_HABITOS), 1);
                                    SUPER_INSERT(&reg_hab3.ID_RH, rutaREGISTROHABITO, &reg_hab3, sizeof(REGISTRO_HABITOS), 1);
                                    SUPER_INSERT(&reg_hab4.ID_RH, rutaREGISTROHABITO, &reg_hab4, sizeof(REGISTRO_HABITOS), 1);
                                    //SUPER INSERT HORARIO
                                    SUPER_INSERT(&horario1.ID_horario, rutaHORARIO, &horario1, sizeof(HORARIO), 1);
                                    SUPER_INSERT(&horario2.ID_horario, rutaHORARIO, &horario2, sizeof(HORARIO), 1);
                                    SUPER_INSERT(&horario3.ID_horario, rutaHORARIO, &horario3, sizeof(HORARIO), 1);
                                    //SUPER INSERT HORA-HORARIO
                                    SUPER_INSERT(&hor_hor1.ID_HH, rutaHORA_HORARIO, &hor_hor1, sizeof(HORA_HORARIO), 1);
                                    SUPER_INSERT(&hor_hor2.ID_HH, rutaHORA_HORARIO, &hor_hor2, sizeof(HORA_HORARIO), 1);
                                    SUPER_INSERT(&hor_hor3.ID_HH, rutaHORA_HORARIO, &hor_hor3, sizeof(HORA_HORARIO), 1);
                                    SUPER_INSERT(&hor_hor4.ID_HH, rutaHORA_HORARIO, &hor_hor4, sizeof(HORA_HORARIO), 1);
                                    //SUPER INSERT RECORDATORIO
                                    SUPER_INSERT(&recor1.ID_recordatorio, rutaRECORDATORIO, &recor1, sizeof(RECORDATORIOS), 1);
                                    SUPER_INSERT(&recor2.ID_recordatorio, rutaRECORDATORIO, &recor2, sizeof(RECORDATORIOS), 1);
                                    SUPER_INSERT(&recor3.ID_recordatorio, rutaRECORDATORIO, &recor3, sizeof(RECORDATORIOS), 1);
                                    SUPER_INSERT(&recor4.ID_recordatorio, rutaRECORDATORIO, &recor4, sizeof(RECORDATORIOS), 1);
                                    //SUPER INSERT PRODUCTIVIDAD
                                    SUPER_INSERT(&product1.ID_product, rutaPRODUCTIVIDAD, &product1, sizeof(PRODUCTIVIDAD), 1);
                                    SUPER_INSERT(&product2.ID_product, rutaPRODUCTIVIDAD, &product2, sizeof(PRODUCTIVIDAD), 1);
                                    SUPER_INSERT(&product3.ID_product, rutaPRODUCTIVIDAD, &product3, sizeof(PRODUCTIVIDAD), 1);
*/




                                    
//                                    obtenerTamanioEstructura(sizeof(RECORDATORIOS), "RECORDATORIOS");
//                                    contadorBytesArch(rutaRECORDATORIO);
                                    break;
                                default:
                            }
                            break;
                        default:

                    }
                    break;
                case 0:
                    al_draw_filled_rectangle(0,0,1200,700, fondo_principal_comohuesito);
                    al_draw_text(lexend_regular[25], texto_black, 600, 300, ALLEGRO_ALIGN_CENTER, "Ingresa tu nombre:");
                    al_draw_rectangle(280,340,920,380,texto_black,5);
                    if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                        if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {
                            // Añadir el carácter a la cadena de entrada
                            int len = strlen(nombre);
                            if (len < sizeof(nombre) - 1) {
                                nombre[len] = evento.keyboard.unichar;
                                nombre[len + 1] = '\0';
                            }
                        } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                            // Borrar el último carácter de la cadena de entrada
                            int len = strlen(nombre);
                            if (len > 0) {
                                nombre[len - 1] = '\0';
                            }
                        }else if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){
                            //Aqui se ingresa el nombre del usuario
                            //UPDATE
                            strcpy(usuario.nombre,nombre);
                            UPDATE(rutaUSUARIO,&usuario,sizeof (USUARIO),1,1);
                            printf("%s",usuario.nombre);
                            momento=4;
                        }
                        al_draw_text(lexend_regular[30], texto_black, 600, 340, ALLEGRO_ALIGN_CENTER, nombre);
                    }
                    break;
                case 1:
                    al_draw_filled_rectangle(100,0,1000,700, fondo_principal_comohuesito);
                    creacionEstructuras();
                    al_flip_display();
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    
                    al_draw_filled_rectangle(100,0,1000,700, fondo_principal_comohuesito);
                    al_draw_text(lexend_regular[15], texto_black, 550, 310, ALLEGRO_ALIGN_CENTER, "Ingresa tu nombre:");
                    al_draw_rectangle(300,340,800,365,texto_black,5);
                    if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                        if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {
                            // Añadir el carácter a la cadena de entrada
                            int len = strlen(nombre);
                            if (len < sizeof(nombre) - 1) {
                                nombre[len] = evento.keyboard.unichar;
                                nombre[len + 1] = '\0';
                            }
                        } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                            // Borrar el último carácter de la cadena de entrada
                            int len = strlen(nombre);
                            if (len > 0) {
                                nombre[len - 1] = '\0';
                            }
                        }
                        al_draw_text(lexend_regular[20], texto_black, 550, 340, ALLEGRO_ALIGN_CENTER, nombre);
                        if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){
                            //Aqui se ingresa el nombre del usuario
                            strcpy(usuario.nombre,nombre);
                            UPDATE(rutaUSUARIO,&usuario,sizeof (USUARIO),1,1);
                            printf("%s",usuario.nombre);
                            SELECT(rutaUSUARIO,&usuario,sizeof (USUARIO),1,1);
                            printf("Seleccionando %s",usuario.nombre);
                            al_draw_filled_rectangle(100,0,1000,700, fondo_principal_comohuesito);
                            al_draw_text(lexend_regular[20],texto_black,550,340,ALLEGRO_ALIGN_CENTER,"Se han guardado los cambios");
                            momento=1;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
void IUSD(){
    int opcion;
    printf("1.Insert.\n2.Update\n3.Select\n4.Delete.");
    scanf("%i", &opcion);
    switch (opcion) {
        case 1:
            llamarINSERT();
            break;
        case 2:
            llamarUPDATE();
            break;
        case 3:
            llamarSELECT();
            break;
        case 4:
            llamarDELETE();
            break;
        default:
            break;
    }
}
void llamarINSERT(){}

void pedirDatosUPDATE(int opcion, int id){
    /*HABITO habit1 ={1, "HABITO 4 NUEVO OWO", "NOTA PARA 4", "2", 4, '\0', '\0', 44, '\0', '\0'};
    habit1.ID_habito = manejarAUTOINCREMENT("./data/usuarios/1/habito.dat");*/
    HABITO newHab={0};
    //newHab.ID_habito = manejarAUTOINCREMENT("./data/usuarios/1/habito.dat");
    switch (opcion) {
        case 1:
            getchar();
            printf("NOMBRE DEL HABITO:");
            fgets(newHab.nombre, sizeof(newHab.nombre), stdin);
            printf("Nota del habito:");
            fgets(newHab.nota, sizeof(newHab.nota), stdin);
            printf("Repeticion semanal:");
            fgets(newHab.repeticion_semanal, sizeof(newHab.repeticion_semanal), stdin);

            printf("Racha:");
            char racha[2];
            sprintf(racha,"%c", newHab.racha);
            fgets(racha, sizeof(newHab.racha), stdin);
            newHab.racha = atoi(racha);

            UPDATE("./data/usuarios/1/habito.dat", &newHab, sizeof(HABITO), 1, id);
    }

}
void llamarUPDATE(){
    HABITO habNULL={0};
    USUARIO usuNULL={0};
    HORARIO  horNULL={0};
    RECORDATORIOS recNULL={0};
    int opcion, id;
    char *ruta[] ={};

    printf("Estructura:\n1.Habito\n2.Usuario\n3.Horario\n4.Recordatorio\n");
    scanf("%i", &opcion);

    printf("ID: ");
    scanf("%i", &id);
    switch (opcion) {
        case 1:
//            *ruta = "./data/usuarios/1/habito.dat";
//          DELETE("./data/usuarios/1/habito.dat", &habNULL, sizeof(HABITO), 1, id);
//            SELECT("./data/usuarios/1/habito.dat", &habNULL, sizeof(HABITO), 1, id);
            pedirDatosUPDATE(opcion, id);
            break;
        case 2:
            *ruta = "./data/usuarios/1/usuario.dat";
            break;
        case 3:
            *ruta = "./data/usuarios/1/horario.dat";
            break;
        case 4:
            *ruta = "./data/usuarios/1/recordatorio.dat";
            break;
        default:
            break;
    }
}
void llamarSELECT(){
    HABITO habNULL={0};
    USUARIO usuNULL={0};
    HORARIO  horNULL={0};
    RECORDATORIOS recNULL={0};
    int opcion, id;
    char *ruta[] ={};

    printf("Estructura:\n1.Habito\n2.Usuario\n3.Horario\n4.Recordatorio\n");
    scanf("%i", &opcion);

    printf("ID: ");
    scanf("%i", &id);
    switch (opcion) {
        case 1:
//            *ruta = "./data/usuarios/1/habito.dat";
//            DELETE("./data/usuarios/1/habito.dat", &habNULL, sizeof(HABITO), 1, id);
            //SELECT("./data/usuarios/1/habito.dat", &habNULL, sizeof(HABITO), 1, id);
            //printf("Nombre: %s\nNota:%s\nID:%i\n", habNULL.nombre, habNULL.nota, habNULL.ID_habito);
            break;
        case 2:
            *ruta = "./data/usuarios/1/usuario.dat";
            break;
        case 3:
            *ruta = "./data/usuarios/1/horario.dat";
            break;
        case 4:
            *ruta = "./data/usuarios/1/recordatorio.dat";
            break;
        default:
            break;
    }
}
void llamarDELETE(){
    int opcion, id;
    char *ruta[] ={};

    printf("Estructura:\n1.Habito\n2.Usuario\n3.Horario\n4.Recordatorio\n");
    scanf("%i", &opcion);

    printf("ID: ");
    scanf("%i", &id);
    switch (opcion) {
        case 1:
//            *ruta = "./data/usuarios/1/habito.dat";
            DELETE("./data/usuarios/1/habito.dat", &habNULL, sizeof(HABITO), 1, id);
//            SELECT("./data/usuarios/1/habito.dat", &habNULL, sizeof(HABITO), 1, id);
            break;
        case 2:
            *ruta = "./data/usuarios/1/usuario.dat";
            break;
        case 3:
            *ruta = "./data/usuarios/1/horario.dat";
            break;
        case 4:
            *ruta = "./data/usuarios/1/recordatorio.dat";
            break;
        default:
            break;
    }
}

void creacionEstructuras(){
    /*Dificultad*/
    DIFICULTAD dif1 = {1, "Muy facil"};
    DIFICULTAD dif2 = {2, "Facil"};
    DIFICULTAD dif3 = {3, "Intermedio"};
    DIFICULTAD dif4 = {4, "Dificil"};
    DIFICULTAD dif5 = {5, "Muy dificil"};

    /*USUARIO*/
    USUARIO usu1 = {1, "Luillilol"};
    USUARIO usu2 = {2, "Fersa"};
    USUARIO usu3 = {3, "José"};
    USUARIO usu4 = {4, "Arias"};
    USUARIO usu5 = {5, "Raz"};

    /*TIPO */
    TIPO tip1 = {1, "Personal"};
    TIPO tip2 = {2, "Escuela"};
    TIPO tip3 = {3, "Salud"};

    /*HABITO*/
    time_t tiempo= time(NULL);
    struct tm *infoTiempo;
    time(&tiempo);
    infoTiempo = localtime(&tiempo);
    FECHA miFecha = *infoTiempo;
    printf("Fecha actual: %d/%02d/%02d %02d:%02d:%02d\n",
           miFecha.tm_year + 1900, miFecha.tm_mon + 1, miFecha.tm_mday,
           miFecha.tm_hour, miFecha.tm_min, miFecha.tm_sec);

    //HABITO hab1 = {1, "Ir al Gym", "Llevar toalla", "0010110", 1, &tip3, &dif3, 12, tiempo, miFecha};
    //HABITO hab2 = {1, "Krunkear", "Un ratito", "1010010", 5, &tip1, &dif1, 35,  tiempo, miFecha};
    //HABITO hab3 = {1, "Hacer la tarea", "Pa mañana", "0000001", 7, &tip2, &dif3, 2,  tiempo, miFecha};
    //HABITO hab4 = {1, "Una paja a la crema", "Es una buena paja", "1111111", 5, &tip1, &dif1, 100,  tiempo, miFecha};

    /*REGISTROH-HABITOS*/
    time_t tiempo2= time(NULL);
    struct tm *infoTiempo2;
    time(&tiempo2);
    infoTiempo2= localtime(&tiempo2);
    FECHA miFecha2 = *infoTiempo2;
    printf("Fecha actual: %d/%02d/%02d %02d:%02d:%02d\n",
           miFecha2.tm_year + 1900, miFecha2.tm_mon + 1, miFecha2.tm_mday,
           miFecha2.tm_hour, miFecha2.tm_min, miFecha2.tm_sec);

    //REGISTRO_HABITOS reg_hab1 = {1, &hab1, tiempo2, miFecha2, 1, 0};
    //REGISTRO_HABITOS reg_hab2 = {2, &hab2, tiempo2, miFecha2, 4, 1};
    //REGISTRO_HABITOS reg_hab3 = {3, &hab3, tiempo2, miFecha2, 1, 0};
    //REGISTRO_HABITOS reg_hab4 = {4, &hab4, tiempo2, miFecha2, 5, 0};

    /*HORARIO*/
    HORARIO horario1 = {1, "Algebra", "1000100", &tip2, tiempo, miFecha2, miFecha2, miFecha2};
    HORARIO horario2 = {2, "Curso Progra", "1010101", &tip2, tiempo, miFecha2, miFecha2, miFecha2};
    HORARIO horario3 = {3, "Calculo", "0111000", &tip2, tiempo, miFecha2, miFecha2, miFecha2};

    /*HORA_HORARIO*/
    HORA_HORARIO hor_hor1={1, &horario1, tiempo, miFecha2, miFecha2};
    HORA_HORARIO hor_hor2={2, &horario1, tiempo, miFecha2, miFecha2};
    HORA_HORARIO hor_hor3={3, &horario2, tiempo, miFecha2, miFecha2};
    HORA_HORARIO hor_hor4={4, &horario2, tiempo, miFecha2, miFecha2};

    /*RECORDATORIOS*/
    RECORDATORIOS recor1 = {1, "EXAMEN FINAL PIÑA", &tip2, tiempo, miFecha2, 0};
    RECORDATORIOS recor2 = {2, "Serie Algebra", &tip2, tiempo, miFecha2, 1};
    RECORDATORIOS recor3 = {3, "Salida con amigos", &tip1, tiempo, miFecha2, 0};
    RECORDATORIOS recor4 = {4, "Cita con Doctor", &tip3, tiempo, miFecha2, 1};

    /*PRODUCTIVIDAD*/
    PRODUCTIVIDAD product1= {1, tiempo, miFecha2, 7, 6};
    PRODUCTIVIDAD product2= {2, tiempo, miFecha2, 8, 7};
    PRODUCTIVIDAD product3= {3, tiempo, miFecha2, 12, 10};


    al_draw_textf(lexend_bold[40], texto_black, 500, 10, ALLEGRO_ALIGN_CENTER, "Hábito 1: %s", hab1.nombre);
    al_draw_textf(lexend_regular[15], texto_black, 110, 80, 0, "Notas: %s", hab1.nota);
    int x = 650, y = 80;
    for (int i = 0; i < 4; ++i) {
        char cadena[7]={0};
        strcpy(cadena,hab1.repeticion_semanal);
        for(int j=0;i<7;i++){
            int valor=cadena[i]-48;
            printf("%d\n",valor);
            colorearDia(x,y,valor);
            x+=30;
        }
    }
}
int main() {
    int acceso;

    if(inicializar_allegro()){

        disp = al_create_display(1200, 700);
        AFK= al_create_timer(30);
        al_set_window_title(disp, "Hábitus");
        //al_set_display_icon(disp, n); // --TODO
        cola_eventos = al_create_event_queue();

        al_register_event_source(cola_eventos,al_get_timer_event_source(AFK)); // FUENTE: eventos de tipo temporizador
        al_register_event_source(cola_eventos, al_get_display_event_source(disp)); // FUENTE: eventos de la ventana
        al_register_event_source(cola_eventos, al_get_keyboard_event_source());// FUENTE: eventos del teclado
        al_start_timer(AFK);

        //Prueba función UPDATE
        HABITO habit1 ={1, "HABITO 4 NUEVO OWO", "NOTA PARA 4", "2", 4, '\0', '\0', 44, '\0', '\0'};
        //habit1.ID_habito = manejarAUTOINCREMENT("./data/usuarios/1/habito.dat");
//        UPDATE("./data/usuarios/1/habito.dat", &habit1, sizeof(HABITO), 1, 4);
//      DELETE("./data/usuarios/1/habito.dat", &habit1, sizeof(HABITO), 1, 1);
//      SELECT("./data/usuarios/1/habito.dat", &habit1, sizeof(HABITO), 1, 4);
//        IUSD();




        EJEMPLO ej1 ={"AQUI EJEMPLO", 208};
        //HABITO habit1 ={1, "HABITO PARA REGISTRO 1 ", "NOTITA 1 WOW", "2", 5, '\0', '\0', 85, '\0', '\0'};
        //habit1.ID_habito = manejarAUTOINCREMENT("./data/usuarios/1/habito.dat");


        //UPDATE("./data/usuarios/1/habito.dat", &habit1, sizeof(HABITO), 1, 1);
        //DELETE("./data/usuarios/1/habito.dat", &habit1, sizeof(HABITO), 1, 1);
        //SELECT("./data/usuarios/1/habito.dat", &habit1, sizeof(HABITO), 1, 2);
        //EJEMPLO ej1 ={"AQUI EJEMPLO", 208};
//        UPDATE("./data/usuarios/1/ejemplo.dat", &ej1, sizeof(EJEMPLO), 1);

        /*CREACIÓN DE ESTRUCTURAS*/
        //creacionEstructuras();



        SELECT(rutaAPP, &app_recibe, sizeof(struct APP), 1, 1);
        //printf("main.c: %i, %i\n", app_recibe.init, app_recibe.ID_last_user);
        main_habitus(app_recibe.init, app_recibe.ID_last_user);
        al_destroy_event_queue(cola_eventos);
        al_destroy_display(disp);
        al_destroy_timer(AFK);
    }
    else{
        printf("\nOcurrio un error");// --TODO hacer un archivo txt que registre todos los errores
    }
    return 0;
}
int inicializar_allegro() {
    int verif_todo_ok = 1;
    if (!al_init()) {
        printf("No se pudo iniciar Allegro");
    }
    if (!al_init_primitives_addon()) {
        printf("No se iniciaron las primitivas");
        verif_todo_ok = 0;
    }
    if (!al_install_keyboard()) {
        printf("No se instalo el teclado");
        verif_todo_ok = 0;
    }
    if (!al_init_image_addon()) {
        printf("No se inicio image addon");
        verif_todo_ok = 0;
    }
    if (!al_install_audio()) {//SONIDO
        printf("No se cargo el complemento de audio");
        verif_todo_ok = 0;
    }
    if (!al_init_acodec_addon()) {//SONIDO
        printf("No se pudo cargar el complemento de codex");
        verif_todo_ok = 0;
    }
    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        printf("No se pudo cargar el complemento de fuentes");
        verif_todo_ok = 0;
    }
    if (!init_resources()) {
        printf("Error al iniciar los recursos fuentes");
        verif_todo_ok = 0;
    }
    return verif_todo_ok;
}