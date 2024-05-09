#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned char pixel[3];
    unsigned int profundidad;  // Esta estructura admite formatos de distinta profundidad de color, a priori utilizaremos s�lo 24 bits.
}t_pixel;

typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;    // El tama�o del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoImagen;   // Por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
}t_metadata;

void rotarIzq(int , int , t_pixel , FILE *file, FILE *file2);
void rotarDer(int , int , t_pixel , FILE *file, FILE *file2);

int main2()// argc= numero de argumentos pasados. argv=  array de punteros a cadenas de caracteres que representan los argumentos pasados al programa desde la l�nea de comandos.
{
    t_pixel pixel;
    t_metadata metadata;
    int alto;
    int ancho;

    char elByte;
    int puntero=0;


    char ruta[] = "unlam.bmp";

    FILE *file= fopen(ruta,"rb");
    FILE* file2 = fopen("modificacion.bmp", "wb");

    if(file==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    //nuevoArchivo("modificacion.bmp",metadata,&pixel,alto, ancho);
    fseek(file2,0,SEEK_SET);
    fseek(file,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,file);

        printf("%X",elByte);
        fwrite(&elByte,sizeof(elByte),1,file2);
        puntero++;
        fseek(file,puntero,SEEK_SET);
        fseek(file2,puntero,SEEK_SET);
        }

    fseek(file,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,file);
    alto=metadata.alto;

    fseek(file,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,file);
    ancho=metadata.ancho;
    printf("El ancho de los pixeles es de %i px\n",metadata.ancho);

    fseek(file2,18,SEEK_SET);
    fwrite(&metadata.alto,sizeof(metadata.alto), 1, file2);
    fwrite(&metadata.ancho,sizeof(metadata.ancho), 1, file2);



//    rotarIzq(alto,ancho,pixel,file,file2);


    rotarDer(alto,ancho,pixel,file,file2);
    fclose(file2);
    fclose(file);



}
/*
void rotarIzq(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2){

fseek(file2,54,SEEK_SET);
    for (int i = 0; i < ancho; i++)
    {
        for (int j = alto-1; j >= 0 ; j--)
        {

            fseek(file,(sizeof(pixel.pixel)*(j*ancho+i))+54,SEEK_SET);
            fread(&pixel.pixel,sizeof(pixel.pixel),1,file);
            fwrite(&pixel.pixel,sizeof(pixel.pixel),1,file2);

        }

    }


}
*/
void rotarDer(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2){
    fseek(file2,54,SEEK_SET);
    for (int i = ancho -1  ; i >= 0 ;  i--) {
        for (int j = 0; j < alto; j++) {

           fseek(file,(sizeof(pixel.pixel) * (j*ancho+i))+54,SEEK_SET);

            fread(&pixel.pixel,sizeof(pixel.pixel),1,file);

            fwrite(&pixel.pixel, sizeof(pixel.pixel), 1, file2);

        }
    }
}
