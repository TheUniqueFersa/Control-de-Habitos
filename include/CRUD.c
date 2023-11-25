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
    FILE *arch = fopen(ruta, "rb");
    int retorno = 0, n_bytes;
    if(arch != NULL){
        fseek(arch, 0, SEEK_END);
        n_bytes = ftell(arch);
        printf("Numero de bytes del archivo: %i\n", n_bytes);
        fclose(arch);
        retorno = n_bytes;
    }
    else{
        printf("Ocurrio un error");
        retorno = -1; //ERROR
    }
    return retorno;
}
int moverNLastId(FILE *arch){
    int *varDestino, retorno;
    fseek(arch, 0, SEEK_SET);
    fread(&varDestino, sizeof(int), 1, arch);
    printf("\nLastId: %i\n", *varDestino);
    return retorno = (*varDestino > 0)? 0: -1;
}

int INSERT(char *, void *, size_t, size_t);
int SELECT(char *, void *, size_t, size_t);
int UPDATE(char *, void *, size_t, size_t);
int DELETE(char *, void *, size_t, size_t);

int INSERT(char *ruta, void *registro, size_t tam_elem, size_t num_elem){
    FILE *arch;/* = fopen(ruta, "")*/
    int retorno;

    if(arch!=NULL){
        fwrite(&registro, tam_elem, num_elem, arch);
    }

    return retorno;
}
int SELECT(char *ruta, void *registro_en_codigo, size_t tam_elem, size_t num_elem){

}
int UPDATE(char *ruta, void *registro_act, size_t tam_elem, size_t num_elem){

}
int DELETE(char *ruta, void *registro_a_elim, size_t tam_elem, size_t num_elem){

}

//INSERT INTO tabla VALUES (1,1,1,1); ** SOLO SE PUEDEN METER REGISTROS COMPLETOS
//SELECT * FROM tabla;
//UPDATE tabla SET col = val WHERE columna = valor;
//DELETE FROM tabla WHERE col = valor;