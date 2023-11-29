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
void analizar_fecha_habitos();
void verificarREGISTROS();
void rellenarRegistrosHabitos(int);
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
USUARIO usuario ={1,""},usuarioprueba={0};
struct APP app_recibe = {0};
struct APP reseteoAPP = {0,1};
//ESTRUCTURAS VACIAS (Para DELETE y otros):
HABITO habNULL={0};
USUARIO usuNULL={0};
HORARIO  horarioNULL={0};
RECORDATORIOS recordNULL={0};
DIFICULTAD difNULL = {0};
TIPO tipoNULL = {0};
REGISTRO_HABITOS reg_habNULL = {0};
HORA_HORARIO hor_horarioNULL = {0};
PRODUCTIVIDAD productNULL = {0};
//ESTRUCTURAS GLOBALES
//TODOS LOS REGISTROS:
DIFICULTAD * Dificultades;
TIPO * Tipos;
HABITO * Habitos, * habitosNULL ;
REGISTRO_HABITOS * Reg_habitos, * Numero_Registros;
HORARIO * Horarios;
HORA_HORARIO * Hora_horarios;
RECORDATORIOS * Recordatorios;
PRODUCTIVIDAD * Productividad;
FECHA miFecha;
int n_reg_dificultades;
int n_reg_tipo;
int n_reg_habitos;
//int n_reh_habitos2;/*PRUEBA LUILLILOL*/
int cantidadREGISTROS_HABITOS;
int n_reg_reg_hab;
int n_reg_horario;
int n_reg_hora_horario;
int n_reg_recordatorios;
int n_reg_productividad;

/* ---- termina; ---- */

/* ----> VARIABLES GLOBALES <---- */
int fin=0;
int momento=0, estado=0; /*0: Inicio primera vez*/
int tamArrPos=6, loc=0;
int * arrPos, * arrHab;
int registrosInicializados = 0;
 //Nos permiten navegar en el momento 1
/*
 *
 * //Estado: 0-> Leer, 1 -> Crear, 2-> Modificar, 3-> Eliminar
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
char frag_2rutaHORA_HORARIO[100] = {"/hora_horario.dat"};
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

char nombre[30] = {0};
char Titulo[30] = {0};
char notas[30] = {0};
char semana[7]="0000000";
int y=400,y2=400,x3=475,y3=305;
void colorearDia(int x, int y, char valor) {
    if(valor==1){
        al_draw_filled_rectangle(x,y,x+20,y+20,principal_pale_chestnut);
    }else{
        al_draw_filled_rectangle(x,y,x+20,y+20,neutro1_tinta_de_pulpo);
    }
}
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
void calendario(int dia_semana, int mes,int primero,int anio){
    int FILAS = 6;
    int COLUMNAS = 7;
    int CELDA=25;
    int tipomes=mes%2;
    int dias_en_mes;
    int primerafila=0;
    int bisiesto=anio%4;
    if(mes==2){
        if(bisiesto!=0){
            dias_en_mes=28;
        }else{
            dias_en_mes=29;
            printf("dias en mes: %d",dias_en_mes);
        }
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
            int dia_calendario = fila * COLUMNAS + columna + 1 - primero;
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
    calendario(dia_semana,mes,primero,anio);
    al_draw_text(lexend_regular[59], texto_black, 1100, 310, ALLEGRO_ALIGN_CENTER, hora_formateada);
    al_draw_text(lexend_regular[20], texto_black, 1100, 420, ALLEGRO_ALIGN_CENTER, dia_formateado);
}
void ventanaActual(){
    int i=0;

    switch (momento) {
        case 0:
            if(estado==0){
                al_draw_filled_rectangle(0,0,1200,700, fondo_principal_oscuro);
                al_draw_text(lexend_regular[40], texto_white,600,300,ALLEGRO_ALIGN_CENTER,"Parece que es tu primera vez abriendo Habitus");
                al_draw_text(lexend_regular[30], texto_white,600,350,ALLEGRO_ALIGN_CENTER,"Presiona cualquier tecla para continuar");
            }
            else{
                al_draw_filled_rectangle(0,0,1200,700, fondo_principal_oscuro);
                al_draw_text(lexend_regular[25], texto_white, 600, 300, ALLEGRO_ALIGN_CENTER, "Ingresa tu nombre:");
                al_draw_rectangle(280,340,920,380,texto_white,5);
                al_draw_text(lexend_regular[30], texto_white, 600, 340, ALLEGRO_ALIGN_CENTER, nombre);
            }
            break;
        case 1:
            al_draw_scaled_bitmap(HABITOSROSA, 0, 0, 100, 300, 0, 0,100, 300, 0);
            al_draw_scaled_bitmap(CALENDARIOBLANCO, 0, 0, 100, 300, 0, 175,100, 300, 0);
            al_draw_scaled_bitmap(RECORDS, 0, 0, 100, 300, 0, 350,100, 300, 0);
            al_draw_scaled_bitmap(AJUSTES, 0, 0, 100, 300, 0, 525,100, 300, 0);

            al_draw_filled_rectangle(100,0,1000,700, fondo_principal_oscuro);
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,0,ALLEGRO_ALIGN_CENTER,"1");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,175,ALLEGRO_ALIGN_CENTER,"2");

            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,320,ALLEGRO_ALIGN_CENTER,"3");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,490,ALLEGRO_ALIGN_CENTER,"4");
            al_draw_filled_rectangle(1000, 0, 1200, 700, al_map_rgb(255, 255, 255));

            al_draw_filled_rectangle(100, 0, 1000, 700, fondo_principal_oscuro);
            creacionEstructuras();
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,335,ALLEGRO_ALIGN_CENTER,"3");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,503,ALLEGRO_ALIGN_CENTER,"4");
            /*Interfaz integrada para cada estado*/

            if(estado==1){
                al_draw_filled_rectangle(200,0,900,550, al_map_rgba(74, 63, 75 , 220));/*Ventana emergente*/
                al_draw_filled_rectangle(360,170,730,215, texto_white);
                al_draw_text(lexend_regular[30],texto_black,540,175,ALLEGRO_ALIGN_CENTER,"HABITUS");




            //al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,335,ALLEGRO_ALIGN_CENTER,"3");
            //al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,503,ALLEGRO_ALIGN_CENTER,"4"); ---VERIFICAR

            al_draw_filled_rectangle(100, 0, 1000, 150, fondo_principal_oscuro);
            al_draw_scaled_bitmap(LOGO, 0, 0, 516, 484, 488, 0,125, 125, 0);
            al_draw_filled_rectangle(300, 90, 500, 120, al_map_rgb(214, 164, 226));//Cuadro Hoy
            al_draw_filled_rectangle(600, 90, 800, 120, al_map_rgb(214, 164, 226));//Cuadro Todos
            al_draw_text(lexend_regular[28],texto_black,400,85,ALLEGRO_ALIGN_CENTER,"Hoy");
            al_draw_text(lexend_regular[28],texto_black,700,85,ALLEGRO_ALIGN_CENTER,"Todos");
            //l_draw_filled_rectangle(150, 150, 950, 600, al_map_rgb(119, 86, 122));
            al_draw_filled_rounded_rectangle(100, 496, 225, 700, 25, 25, al_map_rgb(255, 255, 255));//222, 186, 192, 1
            al_draw_filled_rounded_rectangle(890, 496, 1110, 700, 25, 25, al_map_rgb(255, 255, 255));//222, 186, 192, 1

            //texto de los bitmaps nuevo, editar, borrar
            al_draw_text(lexend_regular[30],texto_black,195,508,ALLEGRO_ALIGN_CENTER,"A");
            al_draw_text(lexend_regular[30],texto_black,195,574,ALLEGRO_ALIGN_CENTER,"E");
            al_draw_text(lexend_regular[30],texto_black,195,642,ALLEGRO_ALIGN_CENTER,"B");
            al_draw_scaled_bitmap(NUEVOHABITO, 0, 0, 738, 740, 100, 496,75, 68, 0);
            al_draw_scaled_bitmap(EDITARHABITO, 0, 0, 740, 744, 100, 564,75, 68, 0);
            al_draw_scaled_bitmap(BORRARHABITO, 0, 0, 744, 740, 100, 632,75, 68, 0);
            al_draw_scaled_bitmap(FLECHAS, 0, 0, 360, 360, 850, 496,210, 210, 0);
            if(estado==1){
                al_draw_filled_rectangle(100,0,1000,700, al_map_rgba(47,50,58,200));
                al_draw_filled_rectangle(200,100,900,550, al_map_rgba(74, 63, 75 , 220));/*Ventana emergente*/
                al_draw_text(lexend_regular[20], texto_white, 550, 120, ALLEGRO_ALIGN_CENTER, "Escribe el nombre de tu habito");
                al_draw_filled_rectangle(250,150,850,200, texto_white);
                al_draw_text(lexend_regular[30], texto_black, 550, 160, ALLEGRO_ALIGN_CENTER, Titulo);
                al_draw_text(lexend_regular[20], texto_white, 550, 220, ALLEGRO_ALIGN_CENTER, "Escribe una nota para tu habito(Puedes dejarlo en blanco)");
                al_draw_filled_rectangle(250,250,850,300, texto_white);
                al_draw_text(lexend_regular[18], texto_white, 550, 320, ALLEGRO_ALIGN_CENTER, "1      2      3      4       5       6      7");
                al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, "Do  Lu  Ma  Mi   Ju   Vi   Sa");
                int CalX=422,CalY=365;
                for (int i = 0; i < 4; ++i) {
                    for(int j=0;i<7;i++){
                        int valor=semana[i]-48;
                        colorearDia(CalX,CalY,valor);
                        CalX+=40;
                    }
                }
            }else if(estado==2){
                al_draw_filled_rectangle(100,0,1000,700, al_map_rgba(47,50,58,200));
                al_draw_filled_rectangle(200,100,900,550, al_map_rgba(74, 63, 75 , 220));/*Ventana emergente*/
                al_draw_text(lexend_regular[20], texto_white, 550, 120, ALLEGRO_ALIGN_CENTER, "Escribe el nombre de tu habito");
                al_draw_filled_rectangle(250,150,850,200, texto_white);
                al_draw_text(lexend_regular[30], texto_black, 550, 160, ALLEGRO_ALIGN_CENTER, Titulo);
                al_draw_text(lexend_regular[20], texto_white, 550, 220, ALLEGRO_ALIGN_CENTER, "Escribe una nota para tu habito(Puedes dejarlo en blanco)");
                al_draw_filled_rectangle(250,250,850,300, texto_white);
                al_draw_text(lexend_regular[30],texto_black,550,260,ALLEGRO_ALIGN_CENTER,notas);
                al_draw_text(lexend_regular[18], texto_white, 550, 320, ALLEGRO_ALIGN_CENTER, "1      2      3      4       5       6      7");
                al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, "Do  Lu  Ma  Mi   Ju   Vi   Sa");
                int CalX=422,CalY=365;
                for (int i = 0; i < 4; ++i) {
                    for(int j=0;i<7;i++){
                        int valor=semana[i]-48;
                        colorearDia(CalX,CalY,valor);
                        CalX+=40;
                    }
                }
            }else if(estado==3){
                al_draw_filled_rectangle(100,0,1000,700, al_map_rgba(47,50,58,200));
                al_draw_filled_rectangle(200,100,900,550, al_map_rgba(74, 63, 75 , 220));/*Ventana emergente*/
                al_draw_text(lexend_regular[20], texto_white, 550, 120, ALLEGRO_ALIGN_CENTER, "Escribe el nombre de tu habito");
                al_draw_filled_rectangle(250,150,850,200, texto_white);
                al_draw_text(lexend_regular[30], texto_black, 550, 160, ALLEGRO_ALIGN_CENTER, Titulo);
                al_draw_text(lexend_regular[20], texto_white, 550, 220, ALLEGRO_ALIGN_CENTER, "Escribe una nota para tu habito(Puedes dejarlo en blanco)");
                al_draw_filled_rectangle(250,250,850,300, texto_white);
                al_draw_text(lexend_regular[30],texto_black,550,260,ALLEGRO_ALIGN_CENTER,notas);
                al_draw_text(lexend_regular[18], texto_white, 550, 320, ALLEGRO_ALIGN_CENTER, "1      2      3      4       5       6      7");
                al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, "Do  Lu  Ma  Mi   Ju   Vi   Sa");
                int CalX=422,CalY=365;
                for (int i = 0; i < 4; ++i) {
                    for(int j=0;i<7;i++){
                        int valor=semana[i]-48;
                        colorearDia(CalX,CalY,valor);
                        CalX+=40;
                    }
                }
            }else if(estado==4) {

                //interfaz de dificultad
                al_draw_filled_rectangle(100, 0, 1000, 1200, al_map_rgba(47, 50, 58,200)); //rectangulo que tapa lo de Arias
                al_draw_filled_rounded_rectangle(325, 150, 800, 720, 100, 100, al_map_rgb(227, 218, 201));
                al_draw_filled_circle(562, 400, 238, al_map_rgb(227, 218, 201));//255, 134, 0, 1
                //al_draw_filled_pieslice(0,0,40, al_map_rgb(74, 63, 75));
                al_draw_pieslice(475, 400, 120, 2.9, 3.6, al_map_rgb(255, 255, 255), 4);

                //texto de los bitmaps nuevo, editar, borrar

                al_draw_arc(475, 400, 120, 2.95, 0.55, al_map_rgba(22, 82, 1, 244), 20);//22,82,1
                al_draw_arc(475, 400, 120, 3.6, 0.6, al_map_rgba(69, 183, 30, 244), 20);//255, 134, 0, 1
                al_draw_arc(475, 400, 120, 4.3, 0.8, al_map_rgba(255, 255, 0, 244), 20);
                al_draw_arc(475, 400, 120, 5.2, 0.7, al_map_rgba(255, 134, 0, 244), 20);//69,183,30
                al_draw_arc(475, 400, 120, 5.95, 0.5, al_map_rgba(255, 0, 0, 244), 20);//255,0,0
                al_draw_filled_circle(475, 400, 15, al_map_rgb(0, 0, 0));//255, 134, 0, 1
                al_draw_filled_triangle(470, y, 480, y2, x3, y3, al_map_rgb(0, 0, 0));
                //muy facil:yvar:405,x3:400,y3:385,facil:x3:400,y3:315,normal:x3:475,y3:300,dificil:x3:550,y:315,muy dificil:yvar:405,x3:550,y3:385
                al_draw_filled_rounded_rectangle(450, 175, 675, 250, 25, 25,
                                                 al_map_rgb(222, 186, 201));//222, 186, 192, 1
                al_draw_scaled_bitmap(LOGO, 0, 0, 516, 484, 360, 175, 80, 80, 0);
                al_draw_filled_rounded_rectangle(625, 270, 780, 635, 25, 25,
                                                 al_map_rgb(222, 186, 201));//222, 186, 192, 1
                al_draw_filled_rounded_rectangle(650, 290, 755, 330, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
                al_draw_filled_rounded_rectangle(650, 335, 755, 403, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
                al_draw_filled_rounded_rectangle(650, 408, 755, 476, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
                al_draw_filled_rounded_rectangle(650, 481, 755, 549, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
                al_draw_filled_rounded_rectangle(650, 554, 755, 622, 10, 10, al_map_rgb(146, 98, 107));//146, 98, 107, 1
                // texto de los rectángulos de dificultad
                al_draw_text(lexend_regular[15], texto_white, 700, 300, ALLEGRO_ALIGN_CENTER, "1. Muy facil");
                al_draw_text(lexend_regular[20], texto_white, 700, 350, ALLEGRO_ALIGN_CENTER, "2. Facil");
                al_draw_text(lexend_regular[16], texto_white, 703, 423, ALLEGRO_ALIGN_CENTER, "3. Intermedio");
                al_draw_text(lexend_regular[20], texto_white, 700, 500, ALLEGRO_ALIGN_CENTER, "4. Difícil");
                al_draw_text(lexend_regular[16], texto_white, 700, 574, ALLEGRO_ALIGN_CENTER, "5. Muy difícil");
                al_draw_text(lexend_regular[45], texto_white, 565, 185, ALLEGRO_ALIGN_CENTER, "Dificultad");
            }
            break;
        case 2:
            al_draw_scaled_bitmap(HABITOS, 0, 0, 100, 300, 0, 0,100, 300, 0);
            al_draw_scaled_bitmap(CALENDARIOROSA, 0, 0, 100, 300, 0, 175,100, 300, 0);
            al_draw_scaled_bitmap(RECORDS, 0, 0, 100, 300, 0, 350,100, 300, 0);
            al_draw_scaled_bitmap(AJUSTES, 0, 0, 100, 300, 0, 525,100, 300, 0);
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,0,ALLEGRO_ALIGN_CENTER,"1");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,175,ALLEGRO_ALIGN_CENTER,"2");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,335,ALLEGRO_ALIGN_CENTER,"3");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,503,ALLEGRO_ALIGN_CENTER,"4");
            break;
        case 3:
            al_draw_scaled_bitmap(HABITOS, 0, 0, 100, 300, 0, 0,100, 300, 0);
            al_draw_scaled_bitmap(CALENDARIOBLANCO, 0, 0, 100, 300, 0, 175,100, 300, 0);
            al_draw_scaled_bitmap(RECORDSROSA, 0, 0, 100, 300, 0, 350,100, 300, 0);
            al_draw_scaled_bitmap(AJUSTES, 0, 0, 100, 300, 0, 525,100, 300, 0);
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,0,ALLEGRO_ALIGN_CENTER,"1");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,175,ALLEGRO_ALIGN_CENTER,"2");
            //al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,335,ALLEGRO_ALIGN_CENTER,"3");--CONFLICTO
            //al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,503,ALLEGRO_ALIGN_CENTER,"4"); --CONFLICTO
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,320,ALLEGRO_ALIGN_CENTER,"3");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,490,ALLEGRO_ALIGN_CENTER,"4");
            al_draw_filled_rectangle(100,0,1000,700, fondo_principal_oscuro);
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,0,ALLEGRO_ALIGN_CENTER,"1");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,175,ALLEGRO_ALIGN_CENTER,"2");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,320,ALLEGRO_ALIGN_CENTER,"3");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,490,ALLEGRO_ALIGN_CENTER,"4");

            al_draw_filled_rectangle(1000, 0, 1200, 700, al_map_rgb(255, 255, 255));
            al_draw_filled_rectangle(100, 0, 1000, 700, fondo_principal_oscuro);
            al_draw_filled_rectangle(100, 0, 1000, 150, fondo_principal_oscuro);
            al_draw_scaled_bitmap(LOGO, 0, 0, 516, 484, 488, 0,125, 125, 0);
            //l_draw_filled_rectangle(150, 150, 950, 600, al_map_rgb(119, 86, 122));
            al_draw_filled_rounded_rectangle(100, 496, 225, 700, 25, 25, al_map_rgb(255, 255, 255));//222, 186, 192, 1
            al_draw_filled_rounded_rectangle(890, 496, 1110, 700, 25, 25, al_map_rgb(255, 255, 255));//222, 186, 192, 1

            //texto de los bitmaps nuevo, editar, borrar
            al_draw_text(lexend_regular[30],texto_black,195,508,ALLEGRO_ALIGN_CENTER,"A");
            al_draw_text(lexend_regular[30],texto_black,195,574,ALLEGRO_ALIGN_CENTER,"E");
            al_draw_text(lexend_regular[30],texto_black,195,642,ALLEGRO_ALIGN_CENTER,"B");
            al_draw_scaled_bitmap(NUEVOHABITO, 0, 0, 738, 740, 100, 496,75, 68, 0);
            al_draw_scaled_bitmap(EDITARHABITO, 0, 0, 740, 744, 100, 564,75, 68, 0);
            al_draw_scaled_bitmap(BORRARHABITO, 0, 0, 744, 740, 100, 632,75, 68, 0);
            al_draw_scaled_bitmap(FLECHAS, 0, 0, 360, 360, 850, 496,210, 210, 0);
            break;
        case 4:
            al_draw_scaled_bitmap(HABITOS, 0, 0, 100, 300, 0, 0,100, 300, 0);
            al_draw_scaled_bitmap(CALENDARIOBLANCO, 0, 0, 100, 300, 0, 175,100, 300, 0);
            al_draw_scaled_bitmap(RECORDS, 0, 0, 100, 300, 0, 350,100, 300, 0);
            al_draw_scaled_bitmap(AJUSTESROSA, 0, 0, 100, 300, 0, 525,100, 300, 0);
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,0,ALLEGRO_ALIGN_CENTER,"1");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,175,ALLEGRO_ALIGN_CENTER,"2");

            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,320,ALLEGRO_ALIGN_CENTER,"3");
            al_draw_text(lexend_regular[40],al_map_rgba(0, 0, 0, 100),12,490,ALLEGRO_ALIGN_CENTER,"4");

            al_draw_filled_rectangle(100,0,1000,700, fondo_principal_oscuro);
            al_draw_text(lexend_regular[15], texto_white, 550, 310, ALLEGRO_ALIGN_CENTER, "Ingresa tu nombre:");
            al_draw_rectangle(300,340,800,365,texto_white,5);
            al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, nombre);
            break;
        default:
            break;
    }
    if(momento!=0){
        al_draw_filled_rectangle(1000, 0, 1200, 700, al_map_rgb(255, 255, 255));
        ObtenerHora();
        al_draw_line(100,25,100,675,fondo_gris1,2);
    }
}
void actualizar_display(){
    //FIGURAS PRIMITAVAS
    //al_draw_text(lexend_regular[10],al_map_rgba(255, 255, 255, 10),199,500,ALLEGRO_ALIGN_CENTER,"1");
    //al_draw_filled_rectangle(1000, 0, 1200, 700, al_map_rgb(255, 255, 255)); --CONFLICTO
    //al_draw_filled_rectangle(101, 0, 1000, 720, al_map_rgb(47, 50, 58)); --CONFLICTO
    //al_draw_filled_rectangle(300, 90, 500, 120, al_map_rgb(214, 164, 226)); --CONFLICTO
    //al_draw_filled_rectangle(600, 90, 800, 120, al_map_rgb(214, 164, 226)); --CONFLICTO
    //l_draw_filled_rectangle(150, 150, 950, 600, al_map_rgb(119, 86, 122));
    /*al_draw_filled_rectangle(175, 175, 925, 400, al_map_rgb(74, 63, 75));
    al_draw_filled_rectangle(190, 190, 910, 235, al_map_rgb(227, 158, 193));//227, 158, 193, 1
    al_draw_filled_rectangle(190, 250, 540, 370, al_map_rgb(227, 158, 193)); //(225, 0, 129));
    al_draw_filled_rectangle(550, 250, 910, 370, al_map_rgb(227, 158, 193));
    //al_draw_filled_rectangle(550, 250, 910, 290, al_map_rgb(225, 0, 129));

    //texto para los recuadros


    //recuadro con transparencia y mensaje deseas eliminar yes or no
    /*al_draw_filled_rounded_rectangle(225, 100, 890, 675, 25, 25, al_map_rgba(0, 0,0, 160));//222, 186, 192, 1
    al_draw_text(lexend_regular[40],al_map_rgb(255, 255, 255),560, 300, ALLEGRO_ALIGN_CENTER,"¿Estás seguro que");//deseas eliminar este elemento?
    al_draw_text(lexend_regular[40],al_map_rgb(255, 255, 255),560,340,ALLEGRO_ALIGN_CENTER,"deseas eliminar este elemento?");

    al_draw_filled_rounded_rectangle(425, 425, 525, 525, 25, 25, al_map_rgba(0, 0,0, 160));//222, 186, 192, 1
    al_draw_filled_rounded_rectangle(625, 425, 725, 525, 25, 25, al_map_rgba(0, 0,0, 160));//222, 186, 192, 1
    al_draw_text(lexend_regular[20],al_map_rgb(255, 255, 255),475, 450, ALLEGRO_ALIGN_CENTER,"Sí");
    al_draw_text(lexend_regular[20],al_map_rgb(255, 255, 255),475, 475, ALLEGRO_ALIGN_CENTER,"(Enter)");

    al_draw_text(lexend_regular[20],al_map_rgb(255, 255, 255),675, 450, ALLEGRO_ALIGN_CENTER,"No");
    al_draw_text(lexend_regular[20],al_map_rgb(255, 255, 255),675, 475, ALLEGRO_ALIGN_CENTER,"(Esc)");*/
//confirma la acción
    al_draw_filled_rounded_rectangle(225, 100, 890, 675, 25, 25, al_map_rgba(0, 0,0, 160));//222, 186, 192, 1
    al_draw_text(lexend_regular[40],al_map_rgb(255, 255, 255),560, 300, ALLEGRO_ALIGN_CENTER,"¿Quieres confirmar la acción?");//deseas eliminar este elemento?

    al_draw_filled_rounded_rectangle(425, 425, 525, 525, 25, 25, al_map_rgba(0, 0,0, 160));//222, 186, 192, 1
    al_draw_filled_rounded_rectangle(625, 425, 725, 525, 25, 25, al_map_rgba(0, 0,0, 160));//222, 186, 192, 1
    al_draw_text(lexend_regular[20],al_map_rgb(255, 255, 255),475, 450, ALLEGRO_ALIGN_CENTER,"Sí");
    al_draw_text(lexend_regular[20],al_map_rgb(255, 255, 255),475, 475, ALLEGRO_ALIGN_CENTER,"(Enter)");

    al_draw_text(lexend_regular[20],al_map_rgb(255, 255, 255),675, 450, ALLEGRO_ALIGN_CENTER,"No");
    al_draw_text(lexend_regular[20],al_map_rgb(255, 255, 255),675, 475, ALLEGRO_ALIGN_CENTER,"(Esc)");
    ObtenerHora();
    ventanaActual();
    //IMPRIME NOMBRE USUARIO:
    al_draw_text(lexend_regular[10],fondo_gris1,1100,645,ALLEGRO_ALIGN_CENTER,"USUARIO");
    al_draw_text(lexend_regular[14],texto_black,1100,655,ALLEGRO_ALIGN_CENTER,usuario.nombre);


    al_flip_display();
}
void inicializar_rutas_usuario(char * id_string_usuario){
    strcat(rutaDIFICULTAD, id_string_usuario);
    strcat(rutaDIFICULTAD, frag_2rutaDIFICULTAD);

    strcat(rutaTIPO, id_string_usuario);
    strcat(rutaTIPO, frag_2rutaTIPO);

    strcat(rutaHABITO, id_string_usuario);
    strcat(rutaHABITO, frag_2rutaHABITO);

    strcat(rutaREGISTROHABITO, id_string_usuario);
    strcat(rutaREGISTROHABITO, frag_2rutaREGISTROHABITO);

    strcat(rutaHORARIO, id_string_usuario);
    strcat(rutaHORARIO, frag_2rutaHORARIO);

    strcat(rutaHORA_HORARIO, id_string_usuario);
    strcat(rutaHORA_HORARIO, frag_2rutaHORA_HORARIO);

    strcat(rutaRECORDATORIO, id_string_usuario);
    strcat(rutaRECORDATORIO, frag_2rutaRECORDATORIO);

    strcat(rutaPRODUCTIVIDAD, id_string_usuario);
    strcat(rutaPRODUCTIVIDAD, frag_2rutaPRODUCTIVIDAD);
}
typedef struct {
    HABITO * ptr_ID_habito;
    ALLEGRO_FONT *para_nombre;
    int coord_x_nombre;
    int coord_y_nombre;
    ALLEGRO_FONT *para_nota;
    int coord_x_nota;
    int coord_y_nota;
    int coord_x_repet_s;
    int coord_y_repet_s;
    int coord_x_repet;
    int coord_y_repet;
    int coord_x_tipo;
    int coord_y_tipo;
    int coord_x_dif;
    int coord_y_dif;
    int coord_x_racha;
    int coord_y_racha;
    int coord_x_fecha;
    int coord_y_fecha;
}HABITO_VISUAL;
typedef struct {
    HORARIO * ptr_ID_horario;
    ALLEGRO_FONT *para_nombre;
    int coord_x_nombre;
    int coord_y_nombre;
    int coord_x_repet_s;
    int coord_y_repet_s;
    int coord_x_tipo;
    int coord_y_tipo;
    int coord_x_fecha;
    int coord_y_fecha;
}HORARIO_VISUAL;
typedef struct {
    RECORDATORIOS * ptr_ID_recordatorio;
    ALLEGRO_FONT *para_nombre;
    int coord_x_nombre;
    int coord_y_nombre;
    int coord_x_tipo;
    int coord_y_tipo;
    int coord_x_fecha;
    int coord_y_fecha;
    int coord_x_ecomple;
    int coord_y_ecomple;
}RECORDATORIO_VISUAL;
void CONTAR_REGISTROS(){

}


int obtenerNumeroRegistros(char * ruta, size_t tamanio){
    long int entero = sizeof(int);
    int bytesSoloRegistro = contadorBytesArch(ruta) - entero, registros=0;
    return registros = bytesSoloRegistro/tamanio;
}
void *crearArreglo(size_t tamanioElemento, int cantidadElementos) {
    int retorno=0;
    void *arreglo = malloc(tamanioElemento * cantidadElementos);
    printf("Direccion asignada en malloc: %p\n", malloc(tamanioElemento * cantidadElementos));
    if (arreglo == NULL) {
        printf("Error: No se pudo asignar memoria para el arreglo.\n");
        retorno = 1;
    }
    return arreglo;
}
void *aumentarArreglo(void *arreglo, size_t tamanioElemento, int nuevoTamano) {
    int retorno = 0;
    void *temp = realloc(arreglo, tamanioElemento * nuevoTamano);
    if (temp == NULL) {
        printf("Error: No se pudo ajustar el tamaño del arreglo.\n");
        free(arreglo); // Liberar el arreglo original si realloc falló
        retorno = 1;
    }
    return temp;
}
int * arrIndicesRegistrosNoVacios;
void cargar_registros_no_vacios(){
    int n_cantidad_registros_disponibles=0;


    cantidadREGISTROS_HABITOS = obtenerNumeroRegistros(rutaREGISTROHABITO, sizeof (REGISTRO_HABITOS));
    printf("\nREGISTRO HABITOS TAMAniO:%i\n", cantidadREGISTROS_HABITOS);
    for(int i=0; i<n_reg_habitos; i++){
        if(Habitos->ID_habito == 0){
            n_cantidad_registros_disponibles++;
        }
        printf("------------------>Habitos: %i, %s, %s, %s, %i, %p, %s, %p, %s, %i, %lli, %d/%d/%d\n",
               Habitos[i].ID_habito, Habitos[i].nombre, Habitos[i].nota, Habitos[i].repeticion_semanal, Habitos[i].repeticion, Habitos[i].ptr_fk_tipo,
               Habitos[i].fk_tipo.tipo, Habitos[i].ptr_fk_difi, Habitos[i].fk_difi.dificultad, Habitos[i].racha, Habitos[i].tiempo, Habitos[i].fecha_ini.tm_mday, Habitos[i].fecha_ini.tm_mon, Habitos[i].fecha_ini.tm_year);
    }
}


void CARGAR_TODOS_LOS_REGISTROS(){
    int retorno = 0, i=0;
    if(registrosInicializados==0){
        //inicializa arreglos necesarios
        n_reg_dificultades = obtenerNumeroRegistros(rutaDIFICULTAD, sizeof(DIFICULTAD));
        printf("Registros: %i\n", n_reg_dificultades);
        Dificultades = (DIFICULTAD *) crearArreglo(sizeof(DIFICULTAD), n_reg_dificultades);
        for(i = 0; i<n_reg_dificultades; i++){
            SELECT(rutaDIFICULTAD, &Dificultades[i], sizeof(DIFICULTAD), 1, i+1);
            printf("IDDDD: %i, dificultad: %s\n", Dificultades[i].ID_dificultad, Dificultades[i].dificultad);
        }
        n_reg_tipo = obtenerNumeroRegistros(rutaTIPO, sizeof(TIPO));
        printf("Registros: %i\n", n_reg_tipo);
        Tipos = (TIPO *) crearArreglo(sizeof(TIPO), n_reg_tipo);
        for(i = 0; i<n_reg_tipo; i++){
            SELECT(rutaTIPO, &Tipos[i], sizeof(TIPO), 1, i+1);
            printf("IDDDD: %i, tipo: %s\n", Tipos[i].ID_tipo, Tipos[i].tipo);
        }
        //printf("LOLIN.COM: %lli\n", sizeof(Tipos));
        //printf("IDDDD malo: %i, tipo: %s\n", Tipos[2].ID_tipo, Tipos[2].tipo);
        //printf("IDDDD malo: %i, tipo: %s\n", Tipos[6].ID_tipo, Tipos[6].tipo);
        n_reg_habitos = obtenerNumeroRegistros(rutaHABITO, sizeof(HABITO));
        printf("Registros: %i\n", n_reg_habitos);
        Habitos = (HABITO *) crearArreglo(sizeof(HABITO), n_reg_habitos);
        for(i = 0; i<n_reg_habitos; i++){
            SELECT(rutaHABITO, &Habitos[i], sizeof(HABITO), 1, i+1);
            printf("HAB: %i, %s, %s, %s, %i, %p, %s, %p, %s, %i, %lli, %d/%d/%d\n",
                   Habitos[i].ID_habito, Habitos[i].nombre, Habitos[i].nota, Habitos[i].repeticion_semanal, Habitos[i].repeticion, Habitos[i].ptr_fk_tipo,
                   Habitos[i].fk_tipo.tipo, Habitos[i].ptr_fk_difi, Habitos[i].fk_difi.dificultad, Habitos[i].racha, Habitos[i].tiempo, Habitos[i].fecha_ini.tm_mday, Habitos[i].fecha_ini.tm_mon, Habitos[i].fecha_ini.tm_year);
        }
        n_reg_reg_hab = obtenerNumeroRegistros(rutaREGISTROHABITO, sizeof(REGISTRO_HABITOS));
        printf("Registros: %i\n", n_reg_reg_hab);
        Reg_habitos = (REGISTRO_HABITOS *) crearArreglo(sizeof(REGISTRO_HABITOS), n_reg_reg_hab);
        for(i = 0; i<n_reg_reg_hab; i++){
            SELECT(rutaREGISTROHABITO, &Reg_habitos[i], sizeof(REGISTRO_HABITOS), 1, i+1);
            printf("RH: %i, %p, %s, %d, %d, %d, %i, %i, %i\n", Reg_habitos[i].ID_RH, Reg_habitos[i].ptr_fk_habito, Reg_habitos[i].fk_habito.nombre, Reg_habitos[i].fecha.tm_mday,
                   Reg_habitos[i].fecha.tm_mon, Reg_habitos[i].fecha.tm_year, Reg_habitos[i].completado, Reg_habitos[i].no_completado, Reg_habitos[i].fk_habito.ID_habito);
        }
        n_reg_horario = obtenerNumeroRegistros(rutaHORARIO, sizeof(HORARIO));
        printf("Registros: %i\n", n_reg_horario);
        Horarios = (HORARIO *) crearArreglo(sizeof(HORARIO), n_reg_horario);
        for(i = 0; i<n_reg_horario; i++){
            SELECT(rutaHORARIO, &Horarios[i], sizeof(HORARIO), 1, i+1);
            printf("HORARIO: %i, %s, %s, %p, %i, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
                   Horarios[i].ID_horario, Horarios[i].nombre, Horarios[i].repeticion_semanal, Horarios[i].ptr_fk_tipo,
                   Horarios[i].fk_tipo.ID_tipo, Horarios[i].fk_tipo.tipo, Horarios[i].fecha_ini.tm_mday, Horarios[i].fecha_ini.tm_mon, Horarios[i].fecha_ini.tm_year,
                   Horarios[i].fecha_final.tm_mday, Horarios[i].fecha_final.tm_mon, Horarios[i].fecha_final.tm_year,
                   Horarios[i].alerta.tm_mday, Horarios[i].alerta.tm_mon, Horarios[i].alerta.tm_year);
        }
        n_reg_hora_horario = obtenerNumeroRegistros(rutaHORA_HORARIO, sizeof(HORA_HORARIO));
        printf("Registros: %i\n", n_reg_hora_horario);
        Hora_horarios = (HORA_HORARIO *) crearArreglo(sizeof(HORA_HORARIO), n_reg_hora_horario);
        for(i = 0; i<n_reg_hora_horario; i++){
            SELECT(rutaHORA_HORARIO, &Hora_horarios[i], sizeof(HORA_HORARIO), 1, i+1);
            printf("HH: %i, %p, %i, %s, %lli, %d/%d/%d, %d/%d/%d\n", Hora_horarios[i].ID_HH, Hora_horarios[i].ptr_fk_horario, Hora_horarios[i].fk_horario.ID_horario,
                   Hora_horarios[i].fk_horario.nombre, Hora_horarios[i].tiempo,
                   Hora_horarios[i].dia_h_ini.tm_mday, Hora_horarios[i].dia_h_ini.tm_mon, Hora_horarios[i].dia_h_ini.tm_year,
                   Hora_horarios[i].h_final.tm_mday, Hora_horarios[i].h_final.tm_mon, Hora_horarios[i].h_final.tm_year);
        }
        n_reg_recordatorios = obtenerNumeroRegistros(rutaRECORDATORIO, sizeof(RECORDATORIOS));
        printf("Registros: %i\n", n_reg_recordatorios);
        Recordatorios = (RECORDATORIOS *) crearArreglo(sizeof(RECORDATORIOS), n_reg_recordatorios);
        for(i = 0; i<n_reg_recordatorios; i++){
            SELECT(rutaRECORDATORIO, &Recordatorios[i], sizeof(RECORDATORIOS), 1, i+1);
            printf("Record: %i, %s, %p, %i, %s, %lli, %d/%d/%d, %i\n", Recordatorios[i].ID_recordatorio, Recordatorios[i].recordatorio, Recordatorios[i].ptr_fk_tipo,
                   Recordatorios[i].fk_tipo.ID_tipo, Recordatorios[i].fk_tipo.tipo, Recordatorios[i].tiempo,
                   Recordatorios[i].fecha.tm_mday, Recordatorios[i].fecha.tm_mon, Recordatorios[i].fecha.tm_year, Recordatorios[i].estado_comp);
        }
        n_reg_productividad = obtenerNumeroRegistros(rutaPRODUCTIVIDAD, sizeof(PRODUCTIVIDAD));
        printf("Registros: %i\n", n_reg_productividad);
        Productividad = (PRODUCTIVIDAD *) crearArreglo(sizeof(PRODUCTIVIDAD), n_reg_productividad);
        for(i = 0; i<n_reg_productividad; i++){
            SELECT(rutaPRODUCTIVIDAD, &Productividad[i], sizeof(PRODUCTIVIDAD), 1, i+1);
            printf("PRODUCT: %i, %lli, %d/%d/%d, %i, %i\n", Productividad[i].ID_product, Productividad[i].tiempo,
                   Productividad[i].fecha.tm_mday, Productividad[i].fecha.tm_mon, Productividad[i].fecha.tm_year, Productividad[i].habit, Productividad[i].racord);
        }

    }else{

    }

    cargar_registros_no_vacios();
}
void verificarREGISTROS(){
    int contadorHabito=3, i=3, difDias, habInd=3, diaCONREGISTRO=0;
    double difSegundos;
    // Obtener la fecha y hora actuales
    time_t tiempoActual;
    struct tm *infoTiempo;
    time(&tiempoActual);
    infoTiempo = localtime(&tiempoActual);
    FECHA fechaActual = *infoTiempo;

    printf("\n********ID HABITO 3: %i\n", Habitos[contadorHabito].ID_habito);
    printf("\n**********ID REGISTRO_ HABITO 3: %i\n", Reg_habitos[contadorHabito].ID_RH);
    while(Reg_habitos[i].fk_habito.ID_habito!=1) {
        printf("\ndebug i=%i\n", i);
        i++;
    }
    printf("RH: %i, %p, %s, %d, %d, %d, %i, %i, %i, %d\n", Reg_habitos[i].ID_RH, Reg_habitos[i].ptr_fk_habito, Reg_habitos[i].fk_habito.nombre, Reg_habitos[i].fecha.tm_mday,
           Reg_habitos[i].fecha.tm_mon, Reg_habitos[i].fecha.tm_year, Reg_habitos[i].completado, Reg_habitos[i].no_completado, Reg_habitos[i].fk_habito.ID_habito, Reg_habitos[i].fk_habito.fecha_ini.tm_mday);

    /*Comparar si los nombres coinciden de habito y reg habito*/

    for(int indHabito=0;indHabito<cantidadREGISTROS_HABITOS;indHabito++){
//        difSegundos = difftime(mktime(&fechaActual), mktime(&Habitos[3].fecha_ini));
//        int diferenciaDias = (int)(difSegundos / (60 * 60 * 24));
//        printf("\n\nDIFERENCIAS DIAS: %i\n\n", diferenciaDias);

        printf("\nhabitos: %s, registro: %s\n", Habitos[habInd].nombre, Reg_habitos[indHabito].fk_habito.nombre);
        if(strcmp(Habitos[habInd].nombre, Reg_habitos[indHabito].fk_habito.nombre)==0){
            int diferenciaDias = fechaActual.tm_mday - Habitos[habInd].fecha_ini.tm_mday;
            int diasParaRegistro[diferenciaDias];
            for(int j=0;j<diferenciaDias;j++){/*for para llenar los espacios con numeros consecutivos*/
                diasParaRegistro[j]=(j+1);
                printf("VALOR DE J:%i\n\n", j);
            }
            printf("Regdia. %i", Reg_habitos[indHabito].fecha.tm_mday);
//            difSegundos = difftime(mktime(&fechaActual), mktime(&Habitos[3].fecha_ini.tm_mday));
//            int diferenciaDias = (int)(difSegundos / (60 * 60 * 24));


            printf("\n\nDIFERENCIAS DIAS: %i\n\n", diferenciaDias);
            printf("\n\nCOINCIDE EL NOMBRE\n\n");
            rellenarRegistrosHabitos(indHabito);
        }
    }
//    printf("\n**********ID REGISTRO_ HABITO FK i1 %i\n", Reg_habitos[0].fk_habito.ID_habito);
//    printf("\n**********ID REGISTRO_ HABITO FK i: %i\n", Reg_habitos[1].fk_habito.ID_habito);
//    printf("\n**********ID REGISTRO_ HABITO FK i: %i\n", Reg_habitos[2].fk_habito.ID_habito);
//    printf("\n**********ID REGISTRO_ HABITO FK i: %i\n", Reg_habitos[3].fk_habito.ID_habito);
//    printf("\n**********ID REGISTRO_ HABITO FK i5: %i\n", Reg_habitos[4].fk_habito.ID_habito);
}
//DIFICULTAD Dificultad[obtenerNumeroRegistros(rutaDIFICULTAD, sizeof(DIFICULTAD))];
void rellenarRegistrosHabitos(int indice){

}


void convertirFecha(const char *fecha, struct tm *tiempo) {
    // Parsear la fecha
    sscanf(fecha, "%d/%d/%d", &tiempo->tm_mday, &tiempo->tm_mon, &tiempo->tm_year);

    // Ajustar los valores para que coincidan con la estructura tm
    /*
    tiempo->tm_mon -= 1; // Restar 1 al mes porque en la estructura tm, enero es 0, febrero es 1, etc.
    tiempo->tm_year -= 1900; // Restar 1900 al año, ya que en la estructura tm se cuentan los años desde 1900
     */
}
void convertirAFechaYHora(const char *cadenaFecha, struct tm *tiempo) {
    char copiaFecha[strlen(cadenaFecha) + 1];
    strcpy(copiaFecha, cadenaFecha);

    // Usar sscanf para extraer los componentes de la fecha y hora y asignarlos a la estructura tm
    sscanf(copiaFecha, "%d/%d/%d %d:%d:%d", &tiempo->tm_mday, &tiempo->tm_mon, &tiempo->tm_year,
           &tiempo->tm_hour, &tiempo->tm_min, &tiempo->tm_sec);

    // Ajustar los valores para que coincidan con la estructura tm

    tiempo->tm_mon -= 1; // Restar 1 al mes porque en la estructura tm, enero es 0, febrero es 1, etc.
    /*
    tiempo->tm_year += 100; // Sumar 100 al año porque se usa el formato de año de dos dígitos (00-99)
    tiempo->tm_year += 2000; // Sumar 2000 al año para obtener el año completo (si está en formato YY)
     */
}

void reseteatEstadoMomento(int momentoACambiar){
    momento = momentoACambiar;
    estado = 0;
}
time_t convertirAtime_t(const char *cadenaFecha) {
    struct tm tiempo = {0}; // Crear una estructura tm para almacenar la fecha
    char *token;
    char copiaFecha[strlen(cadenaFecha) + 1];
    strcpy(copiaFecha, cadenaFecha);

    // Strtok divide la cadena de texto en tokens utilizando '/'
    token = strtok(copiaFecha, "/");
    tiempo.tm_mday = atoi(token); // Obtener y almacenar el día

    token = strtok(NULL, "/");
    tiempo.tm_mon = atoi(token) - 1; // Obtener y almacenar el mes (restar 1 porque en tm es de 0 a 11)

    token = strtok(NULL, "/");
    tiempo.tm_year = atoi(token) - 1900; // Obtener y almacenar el año (restar 1900 porque tm_year cuenta desde 1900)

    // Configurar otros valores en la estructura tm
    tiempo.tm_hour = 0;
    tiempo.tm_min = 0;
    tiempo.tm_sec = 0;
    tiempo.tm_isdst = -1; // Indicar que la información sobre horario de verano es desconocida

    // Convertir la estructura tm a time_t
    time_t tiempoUnix = mktime(&tiempo);

    return tiempoUnix;
}
//int *nuevoArreglo = (int *)aumentarArreglo(arrPos, sizeof(int), 10);
//arrPos = nuevoArreglo;
void invocarNoVacios(){

    arrPos = (int *) crearArreglo(sizeof(int), n_reg_habitos);
    //printf("Tamaño del arreglo de posicion 1: %lli\n", sizeof(arrPos)); //--Esto devuelve no el tamaño del arreglo que se creó, sino al apuntador, por lo que es incorrecto qu e se intente saber el tamaño con sizeof, NO HACER
    //printf("Tamaño del arreglo de posicion 2: %lli\n", sizeof(*nuevoArreglo));// dEVUELVE el valor del primer indice del arreglo, pues el nombre es [0] y se esta desreferenciando ese valor
    arrHab = (int *) crearArreglo(sizeof(int), n_reg_habitos);
}

void analizar_fecha_habitos(){
    int n=1;
    printf("\nanalizar_fechahabitos\n");
    HABITO habEj = {0};
    cargar_registros_no_vacios();
    printf("\nANALIZAR #registros: %i---------------------------------------------------------\n", n_reg_habitos);
    printf("\nRegistro:");
    printf("RH: %i, %p, %s, %d, %d, %d, %i, %i, %i\n", Reg_habitos[n].ID_RH, Reg_habitos[n].ptr_fk_habito, Reg_habitos[n].fk_habito.nombre, Reg_habitos[n].fecha.tm_mday,
           Reg_habitos[n].fecha.tm_mon, Reg_habitos[n].fecha.tm_year, Reg_habitos[n].completado, Reg_habitos[n].no_completado, Reg_habitos[n].fk_habito.ID_habito);
//    SELECT(rutaHABITO, );
    verificarREGISTROS();
}

void main_habitus(int verif_iniciador_primera_vez, int ultimo_usuario){
    int pantalla_requiere_actualizacion=1;
    char usuarioString[100], frag_1RutaUsuario;
    momento=verif_iniciador_primera_vez;//Si es 0, es que no se ha iniciado la aplicacion ni una vez
    if(verif_iniciador_primera_vez == 1){
        SELECT(rutaUSUARIO, &usuario, sizeof(USUARIO), 1, ultimo_usuario);
        //printf("USERR: %i, %s", usuario.ID_usuario, usuario.nombre);
    }
    printf("Init: %i, Usuario: %i\n", momento, ultimo_usuario);
    itoa(ultimo_usuario, usuarioString, 10);
    inicializar_rutas_usuario(usuarioString);
    //printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", rutaDIFICULTAD, rutaTIPO, rutaHABITO, rutaREGISTROHABITO, rutaHORARIO, rutaHORA_HORARIO, rutaRECORDATORIO, rutaPRODUCTIVIDAD);
    //momento=-1;//DEP


    int resetearCadena=0;

    /*La cantidad de elementos se tiene que ocupar una función para contar las estructuras que
     * no estan vacias del arreglo que almacena estructuras de habitos*/

    /**/
    USUARIO usNULL = {0};
    RECORDATORIOS reNULL= {0};
    DIFICULTAD diNULL ={0};
    TIPO tNULL = {0};
    //SELECT(rutaTIPO, &tNULL, sizeof(TIPO), 1, 2);
//        printf("Nombre: %s\nNota:%s\nID:%i\n", haNULL.nombre, haNULL.nota, haNULL.ID_habito);
//        printf("Nombre: %s\nID:%i", usNULL.nombre, usNULL.ID_usuario);
//    printf("recordatorio: %s\nid:%i\nTIPO:%s\n", reNULL.recordatorio, reNULL.ID_recordatorio, reNULL.ptr_fk_tipo->tipo);
//    printf("Dificultad: %s\nID:%i", diNULL.dificultad, diNULL.ID_dificultad);
//    printf("Tipo:%s\nID:%i\n", tNULL.tipo, tNULL.ID_tipo);
    //printf("N registross: %i\n",obtenerNumeroRegistros(rutaTIPO, sizeof(TIPO)));
    //printf("N registross: %i\n",obtenerNumeroRegistros(rutaDIFICULTAD, sizeof(DIFICULTAD)));

    //RECARGAR(1-2-3-);



    CARGAR_TODOS_LOS_REGISTROS();
    analizar_fecha_habitos();

    while(fin!=1){
        if(al_event_queue_is_empty(cola_eventos) && pantalla_requiere_actualizacion){
            //pantalla_requiere_actualizacion=0;
            actualizar_display();
        }
        else if(!al_event_queue_is_empty(cola_eventos)){
            //pantalla_requiere_actualizacion = 1;
        }

        //EVENTOS SUCEDIENDO:
        printf("Momento: %i", momento);
        printf("Nombre: %s", nombre);
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
                printf("\n\n\nasdasdsad\n");
                    switch (evento.type) {
                        case ALLEGRO_EVENT_KEY_DOWN:
                            switch (evento.keyboard.keycode) {
                                case ALLEGRO_KEY_BACKSPACE:
                                    INSERT(rutaAPP, &reseteoAPP, sizeof(struct APP), 1);
                                    break;
                                case ALLEGRO_KEY_F:
                                    printf("\n\n----\n");
                                    /*DIFICULTAD*/
                                    //--HECHA
                                    DIFICULTAD dif1 = {777, "Muy facil"};
                                    DIFICULTAD dif2 = {2, "Facil"};
                                    DIFICULTAD dif3 = {3, "Intermedio"};
                                    DIFICULTAD dif4 = {4, "Dificil"};
                                    DIFICULTAD dif5 = {5, "Muy dificil"};
                                    SELECT(rutaDIFICULTAD, &difNULL, sizeof(DIFICULTAD), 1, 5);
                                    //printf("DIF: %i, %s\n", difNULL.ID_dificultad, difNULL.dificultad);
                                    //obtenerTamanioEstructura(sizeof(DIFICULTAD), "DIFICULTAD");
                                    contadorBytesArch(rutaDIFICULTAD);

                                    /*TIPO */
                                    TIPO tip1 = {1, "Personal"};
                                    TIPO tip2 = {2, "Escuela"};
                                    TIPO tip3 = {3, "Salud"};
                                    SELECT(rutaTIPO, &tipoNULL, sizeof(TIPO), 1, 2);
                                    //printf("Tipo: %i, %s\n", tipoNULL.ID_tipo, tipoNULL.tipo);
                                    contadorBytesArch(rutaTIPO);

                                    /*
                                    time_t tiempo= time(NULL);
                                    struct tm *infoTiempo;
                                    time(&tiempo);
                                    infoTiempo = localtime(&tiempo);
                                    FECHA miFecha = *infoTiempo;
                                    printf("Fecha actual: %d/%d/%d %02d:%02d:%02d\n", miFecha.tm_year + 1900, miFecha.tm_mon + 1, miFecha.tm_mday,
                                           miFecha.tm_hour, miFecha.tm_min, miFecha.tm_sec);
                                           */

                                    char fecha[5][20] = {"30/11/2023", {"02/12/2023"}, {"16/12/2023"}, {"23/12/2023"},
                                                         {"12/01/2024"}};

                                    FECHA tiempo[5] = {0};
                                    time_t fechaConvertida[5];
                                    for (int i = 0; i < 5; i++) {
                                        convertirFecha(fecha[i], &tiempo[i]);
                                        //printf("%d/%d/%d\n", tiempo[i].tm_mday, tiempo[i].tm_mon, tiempo[i].tm_year);
                                        fechaConvertida[i] = convertirAtime_t(fecha[i]);
                                        //printf("Fecha convertida a time_t: %ld\n", (long) fechaConvertida[i]);
                                    }
                                    HABITO vacioo = {0};
                                    HABITO hab1 = {1, "Ir al Gym", "Llevar toalla", "0010110", 1, &tip3, tip3, &dif3,
                                                   dif3, 12, fechaConvertida[0], tiempo[0]};
                                    HABITO hab2 = {1, "Krunkear", "Un ratito", "1010010", 5, &tip1, tip1, &dif1, dif1,
                                                   35, fechaConvertida[1], tiempo[1]};
                                    HABITO hab3 = {1, "Hacer la tarea", "Pa mañana", "0000001", 7, &tip2, tip2, &dif3,
                                                   dif3, 2, fechaConvertida[2], tiempo[2]};
                                    HABITO hab4 = {1, "Una paja a la crema", "Es una buena paja", "1111111", 5, &tip1,
                                                   tip1, &dif1, dif1, 100, fechaConvertida[3], tiempo[3]};
                                    SELECT(rutaHABITO, &vacioo, sizeof(HABITO), 1, 4);
//Pedir HABITO
                                    //printf("%i, %s, %s, %s, %i, %p, %s, %p, %s, %i, %lli, %d/%d/%d\n",
                                           //vacioo.ID_habito, vacioo.nombre, vacioo.nota, vacioo.repeticion_semanal, vacioo.repeticion, vacioo.ptr_fk_tipo,
                                           //vacioo.fk_tipo.tipo, vacioo.ptr_fk_difi, vacioo.fk_difi.dificultad, vacioo.racha, vacioo.tiempo, vacioo.fecha_ini.tm_mday, vacioo.fecha_ini.tm_mon, vacioo.fecha_ini.tm_year);
                                    //printf("%d/%d/%d\n", vacioo.fecha_ini.tm_mday, vacioo.fecha_ini.tm_mon, vacioo.fecha_ini.tm_year);
                                    contadorBytesArch(rutaHABITO);

                                    REGISTRO_HABITOS reg_hab1 = {1, &hab1, hab1, fechaConvertida[0], tiempo[0], 1, 0};
                                    REGISTRO_HABITOS reg_hab2 = {2, &hab2, hab2,  fechaConvertida[0], tiempo[0], 4, 1};
                                    REGISTRO_HABITOS reg_hab3 = {3, &hab3, hab3, fechaConvertida[0], tiempo[0], 1, 0};
                                    REGISTRO_HABITOS reg_hab4 = {4, &hab4, hab4, fechaConvertida[0], tiempo[0], 5, 0};
                                    SELECT(rutaREGISTROHABITO, &reg_habNULL, sizeof(REGISTRO_HABITOS), 1, 1);
                                    //printf("RH: %i, %p, %s, %d, %d, %d, %i, %i\n", reg_habNULL.ID_RH, reg_habNULL.ptr_fk_habito, reg_habNULL.fk_habito.nombre, reg_habNULL.fecha.tm_mday,
                                           //reg_habNULL.fecha.tm_mon, reg_habNULL.fecha.tm_year, reg_habNULL.completado, reg_habNULL.no_completado);
                                    contadorBytesArch(rutaREGISTROHABITO);
                                    /*
                                    time_t tiempo2= time(NULL);
                                    struct tm *infoTiempo2;
                                    time(&tiempo2);
                                    infoTiempo2= localtime(&tiempo2);
                                    FECHA miFecha2 = *infoTiempo2;
                                    printf("Fecha actual: %d/%02d/%02d %02d:%02d:%02d\n",
                                           miFecha2.tm_year + 1900, miFecha2.tm_mon + 1, miFecha2.tm_mday,
                                           miFecha2.tm_hour, miFecha2.tm_min, miFecha2.tm_sec);

                                    */
                                    /*HORARIO*/

                                    HORARIO horario1 = {1, "Algebra", "1000100", NULL, tip2, fechaConvertida[1], tiempo[1], tiempo[2], tiempo[2]};
                                    HORARIO horario2 = {2, "Curso Progra", "1010101", NULL, tip2, fechaConvertida[0], tiempo[0], tiempo[1], tiempo[1]};
                                    HORARIO horario3 = {3, "Calculo", "0111000", NULL, tip2, fechaConvertida[2], tiempo[2], tiempo[3], tiempo[3]};

                                    //UPDATE(rutaHORARIO, &horario2, sizeof(HORARIO),1, 2);
                                    /*
                                    SELECT(rutaHORARIO, &horarioNULL, sizeof(HORARIO), 1, 2);
                                    printf("HORARIO: %i, %s, %s, %p, %i, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",
                                           horarioNULL.ID_horario, horarioNULL.nombre, horarioNULL.repeticion_semanal, horarioNULL.ptr_fk_tipo,
                                    horarioNULL.fk_tipo.ID_tipo, horarioNULL.fk_tipo.tipo, horarioNULL.fecha_ini.tm_mday, horarioNULL.fecha_ini.tm_mon, horarioNULL.fecha_ini.tm_year,
                                    horarioNULL.fecha_final.tm_mday, horarioNULL.fecha_final.tm_mon, horarioNULL.fecha_final.tm_year,
                                    horarioNULL.alerta.tm_mday, horarioNULL.alerta.tm_mon, horarioNULL.alerta.tm_year);*/
                                    contadorBytesArch(rutaHORARIO);


                                    /*HORA_HORARIO*/
                                    char fecha2[5][30] = {{"29/11/23 09:30:00"}, {"30/11/23 11:15:00"},{"03/12/24 08:45:00"}, {"17/12/23 10:00:00"}, {"08/02/24 09:00:00"}};
                                    struct tm fechaNull[5];
                                    for (int i = 0; i < 5; i++) {
                                        //printf("Entré al for \n");
                                        convertirAFechaYHora(fecha2[i], &fechaNull[i]);
                                        //printf("Fecha y hora convertida: %02d/%02d/%d %02d:%02d:%02d\n",
                                               //fechaNull[i].tm_mday, fechaNull[i].tm_mon + 1, fechaNull[i].tm_year,
                                               //fechaNull[i].tm_hour, fechaNull[i].tm_min, fechaNull[i].tm_sec);
                                        //fechaConvertida[i] = convertirAtime_t(fecha2[i]);
                                        //printf("Fecha convertida a time_t: %ld\n", (long) fechaConvertida[i]);
                                    }

                                    HORA_HORARIO hor_hor1={1, &horario1, horario1, time(NULL), fechaNull[0], fechaNull[1]};
                                    HORA_HORARIO hor_hor2={2, &horario1, horario1, time(NULL), fechaNull[1], fechaNull[2]};
                                    HORA_HORARIO hor_hor3={3, &horario2, horario2, time(NULL), fechaNull[2], fechaNull[3]};
                                    HORA_HORARIO hor_hor4={4, &horario2, horario2, time(NULL), fechaNull[3], fechaNull[4]};
                                    SELECT(rutaHORA_HORARIO, &hor_horarioNULL, sizeof(HORA_HORARIO), 1, 3);
                                    //printf("HH: %i, %p, %i, %s, %lli, %d/%d/%d, %d/%d/%d\n", hor_horarioNULL.ID_HH, hor_horarioNULL.ptr_fk_horario, hor_horarioNULL.fk_horario.ID_horario,
                                           //hor_horarioNULL.fk_horario.nombre, hor_horarioNULL.tiempo,
                                           //hor_horarioNULL.dia_h_ini.tm_mday, hor_horarioNULL.dia_h_ini.tm_mon, hor_horarioNULL.dia_h_ini.tm_year,
                                           //hor_horarioNULL.h_final.tm_mday, hor_horarioNULL.h_final.tm_mon, hor_horarioNULL.h_final.tm_year);
                                    contadorBytesArch(rutaHORA_HORARIO);

                                    /*RECORDATORIOS*/

                                    RECORDATORIOS recor1 = {1, "EXAMEN FINAL PIÑA", &tip2, tip2, time(NULL), fechaNull[2], 0};
                                    RECORDATORIOS recor2 = {2, "Serie Algebra", &tip2, tip3, time(NULL), fechaNull[3], 1};
                                    RECORDATORIOS recor3 = {3, "Salida con amigos", &tip1, tip1, time(NULL), fechaNull[4], 0};
                                    RECORDATORIOS recor4 = {4, "Cita con Doctor", &tip3, tip3, time(NULL), fechaNull[1], 1};
                                    SELECT(rutaRECORDATORIO, &recordNULL, sizeof(RECORDATORIOS), 1, 2);
                                    //printf("Record: %i, %s, %p, %i, %s, %lli, %d/%d/%d, %i\n", recordNULL.ID_recordatorio, recordNULL.recordatorio, recordNULL.ptr_fk_tipo,
                                           //recordNULL.fk_tipo.ID_tipo, recordNULL.fk_tipo.tipo, recordNULL.tiempo,
                                           //recordNULL.fecha.tm_mday, recordNULL.fecha.tm_mon, recordNULL.fecha.tm_year, recordNULL.estado_comp);
                                    /*PRODUCTIVIDAD*/

                                    PRODUCTIVIDAD product1= {1, time(NULL), fechaNull[0],  7, 6};
                                    PRODUCTIVIDAD product2= {2, time(NULL), fechaNull[2], 8, 7};
                                    PRODUCTIVIDAD product3= {3, time(NULL), fechaNull[4], 12, 10};
                                    SELECT(rutaPRODUCTIVIDAD, &productNULL, sizeof(PRODUCTIVIDAD), 1, 1);
                                    //printf("PRODUCT: %i, %lli, %d/%d/%d, %i, %i\n", productNULL.ID_product, productNULL.tiempo,
                                           //productNULL.fecha.tm_mday, productNULL.fecha.tm_mon, productNULL.fecha.tm_year, productNULL.habit, productNULL.racord);
                                    //UPDATE(rutaHORARIO, &horario1, sizeof(HORARIO), 1, 1);
                                    //SUPER_INSERT(&habNULL.ID_habito, rutaHABITO, &habNULL, sizeof(HABITO), 4);
                                    HABITO jijija = {10, "Apoco si tilin", "Lolololol"};
                                    //UPDATE(rutaHABITO, &jijija, sizeof(HABITO), 1, 10);
                                    contadorBytesArch(rutaHABITO);
                                    printf("AAAAA %i",obtenerNumeroRegistros(rutaHABITO, sizeof(HABITO)));
//................................................
/*
                                    //SUPER INSERT TIPO

                                    SUPER_INSERT(&tip1.ID_tipo, rutaTIPO, &tip1, sizeof(TIPO), 1);
                                    SUPER_INSERT(&tip2.ID_tipo, rutaTIPO, &tip2, sizeof(TIPO), 1);
                                    SUPER_INSERT(&tip3.ID_tipo, rutaTIPO, &tip3, sizeof(TIPO), 1);

                                    //SUPER INSERT DIFICULTAD
                                    SUPER_INSERT(&dif1.ID_dificultad, rutaDIFICULTAD, &dif1, sizeof(DIFICULTAD), 1);
                                    SUPER_INSERT(&dif2.ID_dificultad, rutaDIFICULTAD, &dif2, sizeof(DIFICULTAD), 1);
                                    SUPER_INSERT(&dif3.ID_dificultad, rutaDIFICULTAD, &dif3, sizeof(DIFICULTAD), 1);
                                    SUPER_INSERT(&dif4.ID_dificultad, rutaDIFICULTAD, &dif4, sizeof(DIFICULTAD), 1);
                                    SUPER_INSERT(&dif5.ID_dificultad, rutaDIFICULTAD, &dif5, sizeof(DIFICULTAD), 1);
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
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case 0:
                    //al_draw_filled_rectangle(0,0,1200,700, fondo_principal_oscuro);
                    //al_draw_text(lexend_regular[25], texto_white, 600, 300, ALLEGRO_ALIGN_CENTER, "Ingresa tu nombre:");
                    //al_draw_rectangle(280,340,920,380,texto_white,5);
                    //las movi a la funcion ventanaActual();

                    if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                        if(estado==0)
                            estado=1;
                        if(estado==1){
                            if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {
                                // Añadir el carácter a la cadena de entrada
                                int len = strlen(nombre);
                                if (len < sizeof(nombre) - 1) {
                                    nombre[len] = evento.keyboard.unichar;
                                    nombre[len + 1] = '\0';
                                }
                            } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                // Borrar el último carácter de la `cadena` de entrada
                                int len = strlen(nombre);
                                if (len > 0) {
                                    nombre[len - 1] = '\0';
                                }
                            }else if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){
                                //Aqui se ingresa el nombre del usuario
                                //UPDATE
                                strcpy(usuario.nombre,nombre);//Ponerle el nuevo nombre "" -> "nuevo"
                                if(verificarExistenciaDeArchivo(rutaUSUARIO)==0){
                                    SUPER_INSERT(&usuario.ID_usuario, rutaUSUARIO, &usuario, sizeof(USUARIO), 1);
                                } else {
                                    UPDATE(rutaUSUARIO,&usuario,sizeof (USUARIO),1,1);//Por el programa que estamos desarrollando de solo 1 usuario;
                                }
                                //printf("%s",usuario.nombre);
                                //Actualiza archivo de ingresado por primera vez:
                                struct APP appActualizado = {1, usuario.ID_usuario};
                                INSERT(rutaAPP, &appActualizado, sizeof(struct APP), 1);
                                resetearCadena=0;
                                reseteatEstadoMomento(1);
                            }
                        }
                        //al_draw_text(lexend_regular[30], texto_white, 600, 340, ALLEGRO_ALIGN_CENTER, nombre);
                        //al_flip_display();
                    }
                    break;
                case 1: /*Habitos*/

//<<<<<<< Updated upstream --Fersa es tubho áqui 28/11/2023
/*
                    creacionEstructuras();
                    al_flip_display(); */
                    /*Obtener de la variable *habitos en l.464 los registros que no son vacios y
                     * almacenarla en la variable ____*/

                    CONTAR_REGISTROS();
//=======
//>>>>>>> Stashed changes
                    //al_flip_display();
                    /*Flechitas arriba y abajo para cambiar de habito*/
                    if(estado==0){
                        switch(evento.type){
                            case ALLEGRO_EVENT_KEY_DOWN:
                                switch(evento.keyboard.keycode){
                                    //ESTADO 0 -> lectura
                                    case ALLEGRO_KEY_DOWN:
                                        if(loc<tamArrPos && loc>=0){
                                            printf("ENTRA ABAJO\n");
                                            loc++;
                                        }
                                        break;
                                    case ALLEGRO_KEY_UP:
                                        if(loc>0 && loc<=tamArrPos){
                                            printf("ENTRA ARRIBA\n");
                                            loc--;
                                        }
                                        break;
                                    case ALLEGRO_KEY_A:
                                        printf("\nTECLA A\n");
                                        estado = 1;
                                        break;
                                    case ALLEGRO_KEY_E:
                                        printf("\nTECLA E\n");
                                        estado = 2;
                                        break;
                                    case ALLEGRO_KEY_B:
                                        printf("\nTECLA B\n");
                                        estado = 3;
                                        break;
                                    case ALLEGRO_KEY_2:
                                        reseteatEstadoMomento(2);
                                        break;
                                    case ALLEGRO_KEY_3:
                                        reseteatEstadoMomento(3);
                                        break;
                                    case ALLEGRO_KEY_4:
                                        reseteatEstadoMomento(4);
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                    } else if (estado == 1){
                        printf("\nESTADO 1 habitos \n");
                        if(resetearCadena==0){
                            strcpy(Titulo,"");
                            resetearCadena=1;
                        }
                        if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                            if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {
                                int len = strlen(Titulo);
                                if (len < sizeof(Titulo) - 1) {
                                    Titulo[len] = evento.keyboard.unichar;
                                    Titulo[len + 1] = '\0';
                                }
                            } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                int len = strlen(Titulo);
                                if (len > 0) {
                                    Titulo[len - 1] = '\0';
                                }
                            }else if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){
                                resetearCadena=0;
                                estado=2;
                            }else if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                estado = 0;
                            }
                        }
                    }else if (estado == 2){
                        printf("\nESTADO 2 habitos\n");
                        if(resetearCadena==0){
                            strcpy(notas,"");
                            resetearCadena=1;
                        }
                        if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                            if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {
                                int len = strlen(notas);
                                if (len < sizeof(notas) - 1) {
                                    notas[len] = evento.keyboard.unichar;
                                    notas[len + 1] = '\0';
                                }
                            } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                                int len = strlen(notas);
                                if (len > 0) {
                                    notas[len - 1] = '\0';
                                }
                            }else if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){
                                resetearCadena=0;
                                estado=3;
                            }else if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                estado = 0;
                                resetearCadena=0;
                            }
                        }
                    }else if(estado==3){
                        if(evento.type==ALLEGRO_EVENT_KEY_CHAR){
                            if(resetearCadena==0){
                                strcpy(semana,"0000000");
                                resetearCadena=1;
                            }
                            if(evento.keyboard.keycode==ALLEGRO_KEY_1){
                                if(semana[0]=='0') semana[0]='1';
                                else semana[0]='0';
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_2){
                                if(semana[1]=='0')semana[1]='1';
                                else semana[1]='0';
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_3){
                                if(semana[2]=='0')semana[2]='1';
                                else semana[2]='0';
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_4){
                                if(semana[3]=='0')semana[3]='1';
                                else semana[3]='0';
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_5){
                                if(semana[4]=='0')semana[4]='1';
                                else semana[4]='0';
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_6){
                                if(semana[5]=='0')semana[5]='1';
                                else semana[5]='0';
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_7){
                                if(semana[6]=='0')semana[6]='1';
                                else semana[6]='0';
                            }else if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){
                                resetearCadena=0;
                                estado=4;
                            }else if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                estado = 0;
                                resetearCadena = 0;
                                strcpy(semana,"0000000");
                            }
                        }
                    }else if(estado==4){
                        if(evento.type==ALLEGRO_EVENT_KEY_CHAR){
                            if(resetearCadena==0){
                                y=400,y2=400,x3=475,y3=305,resetearCadena=1;
                            }
                            if(evento.keyboard.keycode==ALLEGRO_KEY_1){
                                y=405,y2=400,x3=400,y3=385;
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_2){
                                y=400,y2=400,x3=410,y3=335;
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_3){
                                y=400,y2=400,x3=475,y3=305;
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_4){
                                y=400,y2=400,x3=540,y3=335;
                            }else if(evento.keyboard.keycode==ALLEGRO_KEY_5){
                                y=400,y2=405,x3=550,y3=385;
                            }else if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){
                                resetearCadena=0;
                                y=400;
                                y2=400;
                                x3=400;
                                y3=300;
                                estado=4;
                            }else if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                estado = 0;
                                y=400;
                                y2=400;
                                x3=400;
                                y3=300;
                                resetearCadena = 0;
                                strcpy(semana,"0000000");
                            }
                        }
                    }
                    printf("Tamaño:%i\tLocalización:%i\n", tamArrPos, loc);
                    break;
                case 2:  /*Horario*/
                    if(estado == 0){
                        switch(evento.type){
                            case ALLEGRO_EVENT_KEY_DOWN:
                                switch(evento.keyboard.keycode){
                                    //ESTADO 0 -> lectura
                                    case ALLEGRO_KEY_DOWN:
                                        if(loc<tamArrPos && loc>=0){
                                            printf("ENTRA ABAJO\n");
                                            loc++;
                                        }
                                        break;
                                    case ALLEGRO_KEY_UP:
                                        if(loc>0 && loc<=tamArrPos){
                                            printf("ENTRA ARRIBA\n");
                                            loc--;
                                        }
                                        break;
                                    case ALLEGRO_KEY_1:
                                        reseteatEstadoMomento(1);
                                        break;
                                    case ALLEGRO_KEY_3:
                                        reseteatEstadoMomento(3);
                                        break;

                                    case ALLEGRO_KEY_4:
                                        reseteatEstadoMomento(4);
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                    }  else if (estado == 1){
                        if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                            if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {

                            } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {

                            }
                            //al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, nombre);
                            if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){

                            }
                            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                estado = 0;
                            }
                        }
                    } else if (estado == 2){
                        if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                            if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {

                            } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {

                            }
                            //al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, nombre);
                            if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){

                            }
                            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                estado = 0;
                            }
                        }
                    } else if (estado == 3){
                        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                            if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){

                            }
                            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                estado = 0;
                            }
                        }
                    }
                    break;
                case 3:
                    if(estado == 0){
                        switch(evento.type){
                            case ALLEGRO_EVENT_KEY_DOWN:
                                switch(evento.keyboard.keycode){
                                    //ESTADO 0 -> lectura
                                    case ALLEGRO_KEY_DOWN:
                                        if(loc<tamArrPos && loc>=0){
                                            printf("ENTRA ABAJO\n");
                                            loc++;
                                        }
                                        break;
                                    case ALLEGRO_KEY_UP:
                                        if(loc>0 && loc<=tamArrPos){
                                            printf("ENTRA ARRIBA\n");
                                            loc--;
                                        }
                                        break;
                                    case ALLEGRO_KEY_1:
                                        reseteatEstadoMomento(1);
                                        break;
                                    case ALLEGRO_KEY_2:
                                        reseteatEstadoMomento(2);
                                        break;

                                    case ALLEGRO_KEY_4:
                                        reseteatEstadoMomento(4);
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    }  else if (estado == 1){
                        if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                            if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {

                            } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {

                            }
                            //al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, nombre);
                            if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){

                            }
                            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                estado = 0;
                            }
                        }
                    } else if (estado == 2){
                        if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                            if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {

                            } else if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {

                            }
                            //al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, nombre);
                            if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){

                            }
                            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                estado = 0;
                            }
                        }
                    } else if (estado == 3){
                        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                            if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){

                            }
                            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                                estado = 0;
                            }
                        }
                    }
                case 4:
                    if(resetearCadena==0){
                        strcpy(nombre,usuario.nombre);
                        resetearCadena=1;
                    }
                    //al_draw_filled_rectangle(100,0,1000,700, fondo_principal_oscuro);
                    //al_draw_text(lexend_regular[15], texto_white, 550, 310, ALLEGRO_ALIGN_CENTER, "Ingresa tu nombre:");
                    //al_draw_rectangle(300,340,800,365,texto_white,5);
                    if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
                        if(evento.keyboard.keycode==ALLEGRO_KEY_4){
                            reseteatEstadoMomento(4);
                            resetearCadena=0;
                        }else if(evento.keyboard.keycode==ALLEGRO_KEY_1){
                            reseteatEstadoMomento(1);
                        }
                        else if(evento.keyboard.keycode==ALLEGRO_KEY_2){
                            reseteatEstadoMomento(2);
                        }
                        else if(evento.keyboard.keycode==ALLEGRO_KEY_3){
                            reseteatEstadoMomento(3);
                        }else if (evento.keyboard.unichar >= 32 && evento.keyboard.unichar <= 126) {
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
                        //al_draw_text(lexend_regular[20], texto_white, 550, 340, ALLEGRO_ALIGN_CENTER, nombre);
                        if(evento.keyboard.keycode== ALLEGRO_KEY_ENTER){
                            //Aqui se ingresa el nombre del usuario
                            strcpy(usuario.nombre,nombre);
                            UPDATE(rutaUSUARIO,&usuario,sizeof (USUARIO),1,1);
                            printf("%s",usuario.nombre);
                            SELECT(rutaUSUARIO,&usuario,sizeof (USUARIO),1,1);
                            printf("Seleccionando %s",usuario.nombre);
                            al_draw_filled_rectangle(100,0,1000,700, fondo_principal_oscuro);
                            al_draw_text(lexend_regular[20],texto_white,550,340,ALLEGRO_ALIGN_CENTER,"Se han guardado los cambios");
                            strcpy(nombre,"");
                            resetearCadena=0;
                            reseteatEstadoMomento(1);
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
     miFecha = *infoTiempo;
    printf("Fecha actual: %d/%02d/%02d %02d:%02d:%02d\n",
           miFecha.tm_year + 1900, miFecha.tm_mon + 1, miFecha.tm_mday,
           miFecha.tm_hour, miFecha.tm_min, miFecha.tm_sec);

    //HABITO hab1 = {1, "Ir al Gym", "Llevar toalla", "0010110", 1, &tip3, &dif3, 12, tiempo, miFecha};
    //HABITO hab2 = {1, "Krunkear", "Un ratito", "1010010", 5, &tip1, &dif1, 35,  tiempo, miFecha};
    //HABITO hab3 = {1, "Hacer la tarea", "Pa mañana", "0000001", 7, &tip2, &dif3, 2,  tiempo, miFecha};
    //HABITO hab4 = {1, "Una paja a la crema", "Es una buena paja", "1111111", 5, &tip1, &dif1, 100,  tiempo, miFecha};
    HABITO hab1 = {1, "Ir al Gym", "Llevar toalla", "0010110", 1, &tip3, tip3, &dif3, dif3,  12, tiempo, miFecha};
    HABITO hab2 = {1, "Krunkear", "Un ratito", "1010010", 5, &tip1, tip1, &dif1, dif1, 35,  tiempo, miFecha};
    HABITO hab3 = {1, "Hacer la tarea", "Pa mañana", "0000001", 7, &tip2, tip2, &dif3, dif3, 2,  tiempo, miFecha};
    HABITO hab4 = {1, "Una paja a la crema", "Es una buena paja", "1111111", 5, &tip1, tip1, &dif1, dif1, 100,  tiempo, miFecha};

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

    PRODUCTIVIDAD product1= {1, tiempo, miFecha2, 7, 6};
    PRODUCTIVIDAD product2= {2, tiempo, miFecha2, 8, 7};
    PRODUCTIVIDAD product3= {3, tiempo, miFecha2, 12, 10};

    int x=100,y=180;

    al_draw_filled_rectangle(x+75, y-5, x+825, y+220, al_map_rgb(74, 63, 75));//Cuadro principal habito
    al_draw_filled_rectangle(x+90, y+10, x+810, y+55, al_map_rgb(227, 158, 193));//Cuadro de titulo habito
    al_draw_filled_rectangle(x+90, y+70, x+440, y+190, al_map_rgb(227, 158, 193));//Cuadro contenedor botonera
    al_draw_filled_rectangle(x+450, y+70, x+810, y+190, al_map_rgb(227, 158, 193));//Cuadro contenedor principal notas y semana

    al_draw_filled_rectangle(x+450, y+150, x+810, y+190, al_map_rgb(225, 0, 129));//Cuadro contenedor semana
    al_draw_filled_rectangle(x+120, y+90, x+190, y+160, al_map_rgb(225, 0, 129));//Boton completado
    al_draw_filled_rectangle(x+340, y+90, x+410, y+160, al_map_rgb(225, 0, 129));//Boton No completado
    al_draw_filled_rectangle(x+240, y+105, x+290, y+150, al_map_rgb(225, 0, 129));//Cuadro pendientes

    al_draw_text(lexend_regular[10],texto_black,x+155,y+115,ALLEGRO_ALIGN_CENTER,"Completado");
    al_draw_text(lexend_regular[10],texto_black,x+155,y+125,ALLEGRO_ALIGN_CENTER,"(C)");
    al_draw_text(lexend_regular[9],texto_black,x+375,y+115,ALLEGRO_ALIGN_CENTER,"No completado");
    al_draw_text(lexend_regular[10],texto_black,x+375,y+125,ALLEGRO_ALIGN_CENTER,"(N)");
    al_draw_textf(lexend_bold[40], texto_black, x+450, y+10, ALLEGRO_ALIGN_CENTER, "%s", hab1.nombre);//titulo habito
    al_draw_textf(lexend_regular[15], texto_black, x+630, y+80, ALLEGRO_ALIGN_CENTER, "Notas:");
    al_draw_textf(lexend_regular[15], texto_black, x+630, y+100, ALLEGRO_ALIGN_CENTER, "%s",hab1.nota);
    int CalX = x+540, CalY = y+165;
    al_draw_text(lexend_regular[15], texto_black, CalX, CalY-16, ALLEGRO_ALIGN_LEFT, "Do  Lu   Ma  Mi   Ju    Vi   Sa");
    for (int i = 0; i < 4; ++i) {
        char cadena[7]={0};
        strcpy(cadena,hab1.repeticion_semanal);
        for(int j=0;i<7;i++){
            int valor=cadena[i]-48;
            colorearDia(CalX,CalY,valor);
            CalX+=30;
        }
    }
    y+=300;

    al_draw_filled_rectangle(x+75, y-5, x+825, y+220, al_map_rgb(74, 63, 75));//Cuadro principal habito
    al_draw_filled_rectangle(x+90, y+10, x+810, y+55, al_map_rgb(227, 158, 193));//Cuadro de titulo habito
    al_draw_filled_rectangle(x+90, y+70, x+440, y+190, al_map_rgb(227, 158, 193));//Cuadro contenedor botonera
    al_draw_filled_rectangle(x+450, y+70, x+810, y+190, al_map_rgb(227, 158, 193));//Cuadro contenedor principal notas y semana

    al_draw_filled_rectangle(x+450, y+150, x+810, y+190, al_map_rgb(225, 0, 129));//Cuadro contenedor semana
    al_draw_filled_rectangle(x+120, y+90, x+190, y+160, al_map_rgb(225, 0, 129));//Boton completado
    al_draw_filled_rectangle(x+340, y+90, x+410, y+160, al_map_rgb(225, 0, 129));//Boton No completado
    al_draw_filled_rectangle(x+240, y+105, x+290, y+150, al_map_rgb(225, 0, 129));//Cuadro pendientes

    al_draw_text(lexend_regular[10],texto_black,x+155,y+115,ALLEGRO_ALIGN_CENTER,"Completado");
    al_draw_text(lexend_regular[10],texto_black,x+155,y+125,ALLEGRO_ALIGN_CENTER,"(C)");
    al_draw_text(lexend_regular[9],texto_black,x+375,y+115,ALLEGRO_ALIGN_CENTER,"No completado");
    al_draw_text(lexend_regular[10],texto_black,x+375,y+125,ALLEGRO_ALIGN_CENTER,"(N)");
    al_draw_textf(lexend_bold[40], texto_black, x+450, y+10, ALLEGRO_ALIGN_CENTER, "%s", hab4.nombre);//titulo habito
    al_draw_textf(lexend_regular[15], texto_black, x+630, y+80, ALLEGRO_ALIGN_CENTER, "Notas:");
    al_draw_textf(lexend_regular[15], texto_black, x+630, y+100, ALLEGRO_ALIGN_CENTER, "%s",hab4.nota);
    CalX = x+540;
    CalY = y+165;
    al_draw_text(lexend_regular[15], texto_black, CalX, CalY-16, ALLEGRO_ALIGN_LEFT, "Do  Lu   Ma  Mi   Ju    Vi   Sa");
    for (int i = 0; i < 4; ++i) {
        char cadena[7]={0};
        strcpy(cadena,hab4.repeticion_semanal);
        for(int j=0;i<7;i++){
            int valor=cadena[i]-48;
            colorearDia(CalX,CalY,valor);
            CalX+=30;
        }
    }
}
int main() {
    int acceso;
    if(inicializar_allegro()){
        disp = al_create_display(1200, 700);
        AFK = al_create_timer(30);
        al_set_window_title(disp, "Hábitus");
        //al_set_display_icon(disp, n); // --TODO
        cola_eventos = al_create_event_queue();

        al_register_event_source(cola_eventos,al_get_timer_event_source(AFK)); // FUENTE: eventos de tipo temporizador
        al_register_event_source(cola_eventos, al_get_display_event_source(disp)); // FUENTE: eventos de la ventana
        al_register_event_source(cola_eventos, al_get_keyboard_event_source());// FUENTE: eventos del teclado
        al_start_timer(AFK);

        /*CREACIÓN DE ESTRUCTURAS*/
        //creacionEstructuras();
        if(!verificarExistenciaDeArchivo(rutaAPP)){
            INSERT(rutaAPP, &reseteoAPP, sizeof(struct APP), 1);
        }
        DIFICULTAD diff1 = {777, "Muy facil"};
        TIPO tipp1 = {1, "Personal"};
//        HABITO hab1 = {1, "Ir al Gym", "Llevar toalla", "0010110", 1, &tip3, tip3, &dif3, dif3, 12, fechaConvertida[0], tiempo[0]};
//        HABITO habRapido = {1, "PASEAR AL PERRO", "llevar correa y al toby", "1101001", 2, &tipp1, tipp1, &diff1, diff1, };
//        SUPER_INSERT();
        SELECT(rutaAPP, &app_recibe, sizeof(struct APP), 1, 1);
//        analizar_fecha_habitos();
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