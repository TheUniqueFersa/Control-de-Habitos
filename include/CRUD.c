/* COMANDOS PARA MANEJAR CRUD EN LOS ARCHIVOS
 *
 * */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "structs.c"
/*OTRAS COSAS*/

int contadorBytesArch(char *ruta){
    printf("Ruta: %s\n", ruta);
    FILE *archi = fopen(ruta, "rb");
    int retorno = 0, n_bytes;
    if(archi != NULL){
        fseek(archi, 0, SEEK_END);
        n_bytes = ftell(archi);
        printf("Numero de bytes del archivo: %i\n", n_bytes);
        rewind(archi);
        fclose(archi);
        retorno = n_bytes;
    }
    else{
        printf("El archivo no fue encontrado (contadosBytesArch)\n");
        retorno = -1; //ERROR
    }
    return retorno;
}
int desplazarAUTOINCREMENT(FILE *arch){ //requiere de la apertura en el modo: rb ||
    int variableDestino=0, retorno;
    //printf("AAlectura: %li\n", ftell(arch));
    fseek(arch, 0, SEEK_SET);
    printf("DDlectura: %li\n", ftell(arch));
    fread(&variableDestino, sizeof(int), 1, arch);
    printf("DaDlectura: %li\n", ftell(arch));
    printf("-- AUTO_INCREMENT leido: %i --\n", variableDestino);
    retorno = (variableDestino > 0)? variableDestino: -1;
    return retorno;
}

int INSERT(char *, void *, size_t, size_t);
int SELECT(char *, void *, size_t, size_t, int id);
int UPDATE(char *, void *, size_t, size_t, int id);
int DELETE(char *, void *, size_t, size_t, int id);

int manejarAUTOINCREMENT(char *ruta){//Solamente ejecutable dentro de INSERT,
    int AUTO_INCREMENT=0;
    FILE *arch = fopen(ruta, "ab+");
    if(arch != NULL){
        if(contadorBytesArch(ruta)==0){
            printf("\tEl archivo esta vacío\n");
            AUTO_INCREMENT=1;
            fwrite(&AUTO_INCREMENT, sizeof(int), 1, arch);
        }
        else{
            fclose(arch);
            FILE *archi2 = fopen(ruta, "rb+");
            //rewind(arch),
            AUTO_INCREMENT = desplazarAUTOINCREMENT(archi2);
            if(AUTO_INCREMENT > 0){
                AUTO_INCREMENT++;
                rewind(archi2);
                //fseek(arch, 0, SEEK_SET);
                printf("Posicion: %li\n", ftell(archi2));
                //printf("INT LOL %lli", sizeof(AUTO_INCREMENT));
                fwrite(&AUTO_INCREMENT, sizeof(int), 1, archi2);
                printf("DESPUESlectura: %li\n", ftell(archi2));
            }
            else{
                printf("Ocurrio un error en la devolucion, AUTOINCREM: %i: \n", AUTO_INCREMENT);
            }
        }
        fclose(arch);
    }
    else{
        printf("OCurrio un error (manejarAUTOINCREMENT)\n");
    }
    printf("VALOR QUE REGRESO XD: %i\n", AUTO_INCREMENT);
    return AUTO_INCREMENT;
}
int SUPER_INSERT(int * ID, char *ruta, void *registro, size_t tam_elem, size_t num_elem){
    *ID = manejarAUTOINCREMENT(ruta);
    int nuevoID = *ID;
    //USUARIO *hola = registro;
    //printf("IDDDDDDDDDDDD: %i\n", hola->ID_usuario);
    //printf("IDDDDDDDDDDDD: %s\n", hola->nombre);
    //printf("DDD %lli\n", sizeof(USUARIO));
    INSERT(ruta, registro, tam_elem, num_elem);
    return nuevoID;
}
int INSERT(char *ruta, void *registro, size_t tam_elem, size_t num_elem){
    int retorno;
    if(strcmp("./data/app.dat", ruta)==0){
        printf("ENTRE A APP.DAt");
        FILE *arch = fopen(ruta, "wb");
        if(arch!=NULL){
            fwrite(registro, tam_elem, num_elem, arch);
            fclose(arch);
        }else{
            printf("ERROR al abrir archivo wb app.dat\n");
        }
    }
    else{
        FILE *arch = fopen(ruta, "rb+");
        if(arch!=NULL){
            fseek(arch, 0, SEEK_END);//Se posiciona al final de to_do registro
            //printf("POSICICON %li\t", ftell(arch));
            fwrite(registro, tam_elem, num_elem, arch);
            fclose(arch);
        }
        else{
            printf("La base de datos no existe (INSERT)\n");
        }
    }
    return retorno;
}
int SELECT(char *ruta, void *registro_en_codigo, size_t tam_elem, size_t num_elem, int id){
    printf("\nFuncionSELECT\n");
    FILE *archivo = fopen(ruta, "rb");  //requiere de la apertura en el modo: rb ||
    if(archivo != NULL){
        rewind(archivo);
        //desplazarAUTOINCREMENT(archivo);
        fseek(archivo, (id - 1) * ((long)tam_elem), SEEK_CUR);
        //printf("Antes de lectura: %li\t", ftell(archivo));
        fread(registro_en_codigo, tam_elem, num_elem, archivo);
    }else
        printf("La base de datos no existe (SELECT)\n");
    return 0;
}
int UPDATE(char *ruta, void *registro_act, size_t tam_elem, size_t num_elem, int id){
    printf("\nFuncion UPDATE\n");
    FILE *archivo = fopen(ruta, "rb+");
    if(archivo!=NULL ){
//      fseek(ptrCF, 0, SEEK_END);
        rewind(archivo);
        desplazarAUTOINCREMENT(archivo);
        fseek(archivo, (id-1)*((long)tam_elem), SEEK_CUR);
        //printf("\tUPDATE: %li\n", ftell(archivo));
        fwrite(registro_act, tam_elem, num_elem, archivo);
        fclose(archivo);
    }else{
        printf("La base de datos no existe (UPDATE)\n");
    }
}
int DELETE(char *ruta, void *registro_a_elim, size_t tam_elem, size_t num_elem, int id){
    printf("\nFuncionDELETE\n");
    FILE *archivo = fopen(ruta, "rb+");
    HABITO hab, habNULL={'\0'};/*SE CREA habNULL PARA SOBRESCRIBIR EL REGISTRO QUE INDIQUE EL id*/
    if(archivo!=NULL ){
//      fseek(ptrCF, 0, SEEK_END);
        rewind(archivo);
        desplazarAUTOINCREMENT(archivo);
        fseek(archivo, (id-1)*((long)tam_elem), SEEK_CUR);
        //printf("\tUPDATE: %li\n", ftell(archivo));
        fwrite(&habNULL, tam_elem, num_elem, archivo);
    }else{
        printf("La base de datos no existe (DELETE)\n");
    }
    fclose(archivo);
}
// -- CONSIDERACIONES --
//INSERT INTO tabla VALUES (1,1,1,1); ** SOLO SE PUEDEN METER REGISTROS COMPLETOS
//SELECT * FROM tabla;
//UPDATE tabla SET col = val WHERE columna = valor;
//DELETE FROM tabla WHERE col = valor;