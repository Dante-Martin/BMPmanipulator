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

//t_pixel Fgris(t_pixel);
t_pixel IncrementoAzul(t_pixel);
void rotar(t_metadata );

int main(int argc, char* argv[])// argc= numero de argumentos pasados. argv=  array de punteros a cadenas de caracteres que representan los argumentos pasados al programa desde la l�nea de comandos.
{
    t_pixel pixel;
    t_metadata metadata;
    int alto;
    int ancho;
    int resultadoPixel;
    int resultadoMeta;
    char elByte;
    int puntero=0;
    //int intensidadAzul;
    //int incremento;

    char ruta[] = "unlam.bmp";

    FILE *file= fopen(ruta,"rb");
    FILE* file2 = fopen("modificacion.bmp", "wb");

    if(file==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(file,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,file);
    printf("El tama�o del encabezado es de %d bits\n",metadata.tamEncabezado);
     fwrite(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado), 1, file2);

    fseek(file,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, file);
    printf("El tama�o del archivo es de %i Bits\n",metadata.tamArchivo);
    fwrite(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, file2);

    fseek(file,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,file);
    printf("Comienza por el %d \n",metadata.comienzoImagen);
    fwrite(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen), 1, file2);



    fseek(file,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,file);
    ancho=metadata.ancho;
    printf("El ancho de los pixeles es de %i px\n",metadata.ancho);
    printf("El ancho de los pixeles es de %i px\n",ancho);
     fwrite(&metadata.ancho,sizeof(metadata.ancho), 1, file2);

    fseek(file,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,file);
    alto=metadata.alto;
    printf("El alto de los pixeles es de %i px\n",metadata.alto);
    fwrite(&metadata.alto,sizeof(metadata.alto), 1, file2);

    fseek(file,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, file);
    fwrite(&metadata.profundidad,sizeof(metadata.profundidad), 1, file2);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(file);
        return 1;
    }
    printf("La imagen es de 24 bits por pixel.\n");


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



    fseek(file2,54,SEEK_SET);
    for (int i = 0; i < ancho; i++)
    {
        for (int j = 0; j < alto; j++)
        {

            fseek(file,(sizeof(pixel.pixel)*(j*ancho+i))+54+1,SEEK_SET);
            fread(&pixel.pixel,sizeof(pixel.pixel),1,file);
            fwrite(&pixel.pixel,sizeof(pixel.pixel),1,file2);
            puntero=puntero+sizeof(pixel.pixel);
        }

    }
printf("puntero: %d \n tamaño de archivo %d",&puntero,metadata.tamArchivo);


while(puntero<=metadata.tamArchivo){//colores
      fread(&pixel.pixel,sizeof(pixel.pixel),1,file);

        pixel=IncrementoAzul(pixel);

        //pixel = Fgris(pixel);


        fwrite(&pixel.pixel,sizeof(pixel.pixel),1,file2);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(file,puntero,SEEK_SET);
       fseek(file2,puntero,SEEK_SET);
        }


    fclose(file2);
    fclose(file);

    return (argc, argv);
}



/*
t_pixel Fgris(t_pixel cambiar)
{
    char gris;
    t_pixel  ret;
    gris=(cambiar.pixel[2]+cambiar.pixel[1]+cambiar.pixel[0])/3;

    ret.pixel[2]=gris;
    ret.pixel[1]=gris;
    ret.pixel[0]=gris;

    return ret;
}

t_pixel contrasteAumenta(t_pixel cambiar)
{

    t_pixel ret;
    unsigned char gris;
    float multiplicador;

    unsigned int aux;

    gris = (cambiar.pixel[2] + cambiar.pixel[1] + cambiar.pixel[0]) / 3;

    multiplicador = 125;
    // if (gris <= 30){multiplicador=75;}
    // if (gris > 30){multiplicador=88;}
    // if (gris > 60){multiplicador=95;}
    // if (gris > 90){multiplicador=98;}
    // if (gris > 120){multiplicador=100;}
    // if (gris > 150){multiplicador=102;}
    // if (gris > 180){multiplicador=105;}
    // if (gris > 210){multiplicador=112;}
    // if (gris > 240){multiplicador=125;}

    // if (gris <= 30){multiplicador=75;}
    // if (gris > 30){multiplicador=78;}
    // if (gris > 60){multiplicador=82;}
    // if (gris > 90){multiplicador=90;}
    // if (gris > 120){multiplicador=100;}
    // if (gris > 150){multiplicador=110;}
    // if (gris > 180){multiplicador=118;}
    // if (gris > 210){multiplicador=122;}
    // if (gris > 240){multiplicador=125;}

    if (gris <= 30)
    {
        multiplicador = 75;
    }
    if (gris > 30)
    {
        multiplicador = 75;
    }
    if (gris > 60)
    {
        multiplicador = 80;
    }
    if (gris > 90)
    {
        multiplicador = 80;
    }
    if (gris > 120)
    {
        multiplicador = 100;
    }
    if (gris > 150)
    {
        multiplicador = 120;
    }
    if (gris > 180)
    {
        multiplicador = 120;
    }
    if (gris > 210)
    {
        multiplicador = 125;
    }
    if (gris > 240)
    {
        multiplicador = 125;
    }

    aux = (multiplicador / 100) * cambiar.pixel[0];
    if (aux > 255)
    {
        aux = 255;
    }
    ret.pixel[0] = aux;

    //  printf("%02X-%02X-%02X: %02X  %02X   %f \n",cambiar.pixel[0],cambiar.pixel[1],cambiar.pixel[2],(cambiar.pixel[2]+cambiar.pixel[1]+cambiar.pixel[0])/3,gris,multiplicador);

    // if (multiplicador/100 != 1){ printf("%f  %f  %02X  %02X\n",multiplicador/100,(multiplicador/100)  * cambiar.pixel[0],cambiar.pixel[0],ret.pixel[0]);}

    aux = multiplicador / 100 * cambiar.pixel[1];
    if (aux > 255)
    {
        aux = 255;
    }
    ret.pixel[1] = aux;

    aux = multiplicador / 100 * cambiar.pixel[2];
    if (aux > 255)
    {
        aux = 255;
    }
    ret.pixel[2] = aux;

    return ret;
}
t_pixel contrasteReduce(t_pixel cambiar)
{


*/

t_pixel IncrementoAzul (t_pixel cambio){

    int azul;
    t_pixel pixel;
    azul=cambio.pixel[0]*1.5;
    if(azul>255){
        azul=255;
    }


    pixel.pixel[0]=(char) azul;
    pixel.pixel[1]=cambio.pixel[1];
    pixel.pixel[2]=cambio.pixel[2];

    return pixel;
}

