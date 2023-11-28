#include <stdio.h>
void obtenerTamanioEstructura(size_t tamanio, char * nombreEstruct){
    printf("Tamaño de struct %s %lli \n",nombreEstruct, tamanio);
}
int verificarExistenciaDeArchivo(const char *ruta) {
    FILE *archivo;
    int retorno;
    archivo = fopen(ruta, "r"); // Intenta abrir el archivo en modo lectura ("r")
    if (archivo == NULL) {
        retorno = 0; // El archivo no existe o no se puede abrir
    } else {
        fclose(archivo); // Cierra el archivo si se pudo abrir correctamente
        retorno = 1; // El archivo existe
    }
    return retorno;
}