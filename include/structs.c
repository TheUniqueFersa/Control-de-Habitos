struct DIFICULTAD {
        int ID_dificultad;
        char dificultad[11];
};
struct USUARIO {
    int ID_usuario;
    char nombre[30];
};
struct TIPO{
    int ID_tipo;
    char tipo[50];
} tipoxd[2];
struct HORARIO{
    int ID_horario;
    char nombre[40];
    char nota[180];
    char repeticion_semanal[7];
    int repeticion;
    struct TIPO *ptr_ID_tipo;

    //FK
    int racha;

} horario;