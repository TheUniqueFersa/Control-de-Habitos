typedef struct tm FECHA;
typedef struct {
        int ID_dificultad;
        char dificultad[11];
} DIFICULTAD;
typedef struct {
    int ID_usuario;
    char nombre[30];
} USUARIO;
typedef struct {
    int ID_tipo;
    char tipo[50];
} TIPO;
typedef struct {
    int ID_habito;
    char nombre[40];
    char nota[180];
    char repeticion_semanal[7];
    int repeticion;
    TIPO *ptr_fk_tipo;
    TIPO fk_tipo;//-----
    DIFICULTAD *ptr_fk_difi;
    DIFICULTAD fk_dif1;//-----
    int racha;
    time_t tiempo;
    FECHA fecha_ini;
} HABITO;
typedef struct {
    int ID_RH;
    HABITO *ptr_fk_habito;
    time_t tiempo;
    FECHA fecha;
    int completado;
    int no_completado;
} REGISTRO_HABITOS;
typedef struct {
    int ID_horario;
    char nombre[40];
    char repeticion_semanal[7];
    TIPO *ptr_fk_tipo;
    time_t tiempo;
    FECHA fecha_ini;
    FECHA fecha_final;
    FECHA alerta;
} HORARIO;
typedef struct {
    int ID_HH;
    HORARIO *ptr_fk_horario;
    time_t tiempo;
    FECHA dia_h_ini;
    FECHA h_final;
} HORA_HORARIO;
typedef struct {
    int ID_recordatorio;
    char recordatorio[180];
    TIPO *ptr_fk_tipo;
    time_t tiempo;
    FECHA fecha;
    short int estado_comp;
} RECORDATORIOS;
typedef struct {
    int ID_product;
    time_t tiempo;
    FECHA fecha;
    int habit;
    int racord;
} PRODUCTIVIDAD;

typedef struct {
    char ejemplo[20];
    int intej;
} EJEMPLO;
typedef struct{
    int origenX;
    int origenY;
    //
    //void * estructura;
} VISUALES;
/*
RECORDATORIOS recordatorio[56];

VISUALES recordatorios = {0,0, &recordatorio[0]};
int hola(){
    recordatorios.estructura->
}
VISUALES recordatorios_visuales[56];
 */