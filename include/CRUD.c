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
        fclose(archi);
        retorno = n_bytes;
    }
    else{
        printf("Ocurrio un error\n");
        retorno = -1; //ERROR
    }
    return retorno;
}
int desplazarAUTOINCREMENT(FILE *arch){ //requiere de la apertura en el modo: rb ||
    int variableDestino=0, retorno;
    fseek(arch, 0, SEEK_SET);
    fread(&variableDestino, sizeof(int), 1, arch);
    printf("\n-- AUTO_INCREMENT: %i --\n", variableDestino);
    return retorno = (variableDestino > 0)? variableDestino: -1;
}

int INSERT(char *, void *, size_t, size_t);
int SELECT(char *, void *, size_t, size_t, int id);
int UPDATE(char *, void *, size_t, size_t);
int DELETE(char *, void *, size_t, size_t);

int manejarAUTOINCREMENT(char *ruta){//Solamente ejecutable dentro de INSERT,
    int AUTO_INCREMENT=0;
    FILE *arch = fopen(ruta, "rb+");
    if(arch != NULL){
        if(contadorBytesArch(ruta)==0){
            printf("\nEl archivo esta vacío\n");
            AUTO_INCREMENT=1;
            fwrite(&AUTO_INCREMENT, sizeof(int), 1, arch);
        }
        else{
            AUTO_INCREMENT = desplazarAUTOINCREMENT(arch);
            AUTO_INCREMENT++;
            rewind(arch);
            fwrite(&AUTO_INCREMENT, sizeof(int), 1, arch);
        }
        fclose(arch);
    }//--TODO MANEJAR ERRORES POSIBLES
    return AUTO_INCREMENT;
}
int INSERT(char *ruta, void *registro, size_t tam_elem, size_t num_elem){
    int retorno;
    if(strcmp("./data/app.dat", ruta)==0){
        FILE *arch = fopen(ruta, "wb");
        if(arch!=NULL){
            fwrite(registro, tam_elem, num_elem, arch);
            fclose(arch);
        }// --TODO funcion que imprima error
    }
    else{
        FILE *arch = fopen(ruta, "rb+");
        if(arch!=NULL){
            fseek(arch, 0, SEEK_END);//Se posiciona al final de to_do registro
            fwrite(registro, tam_elem, num_elem, arch);
            fclose(arch);
        }
        else{
            printf("Hubo un error al abrir el archivo de INSERT");
        }

    }
    return retorno;
}
int SELECT(char *ruta, void *registro_en_codigo, size_t tam_elem, size_t num_elem, int id){
    FILE *archivo = fopen(ruta, "rb");  //requiere de la apertura en el modo: rb ||
    if(archivo != NULL){
        rewind(archivo);
        desplazarAUTOINCREMENT(archivo);
        fseek(archivo, (id - 1) * ((long)tam_elem), SEEK_CUR);
        printf("AAAA: %li\t", ftell(archivo));
        fread(registro_en_codigo, tam_elem, num_elem, archivo);
        printf("a: %li\n", ftell(archivo));
    }else
        printf("Hubo un error al abrir el archivo");
    return 0;
}
int UPDATE(char *ruta, void *registro_act, size_t tam_elem, size_t num_elem){

    FILE *ptrCF;
    ptrCF= fopen(ruta, "wb");
    if(ptrCF!=NULL ){
//      fseek(ptrCF, 0, SEEK_END);
        fwrite(registro_act, tam_elem, num_elem, ptrCF);
    }
    fclose(ptrCF);


    ptrCF= fopen(ruta, "rb");
    EJEMPLO ej2;
    HABITO hab;
    if (ptrCF != NULL) {
        while (fread(&hab, tam_elem, 1, ptrCF) == 1) {
            printf("nombre: %s, nota:%s, repeticion:%s, racha:%i  \n", hab.nombre, hab.nota, hab.repeticion_semanal, hab.racha);
        }
        fclose(ptrCF);
    }
}



int DELETE(char *ruta, void *registro_a_elim, size_t tam_elem, size_t num_elem){

}

//INSERT INTO tabla VALUES (1,1,1,1); ** SOLO SE PUEDEN METER REGISTROS COMPLETOS
//SELECT * FROM tabla;
//UPDATE tabla SET col = val WHERE columna = valor;
//DELETE FROM tabla WHERE col = valor;