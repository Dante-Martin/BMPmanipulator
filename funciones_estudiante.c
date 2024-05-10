#include "funciones_estudiante.h"
#include "estructuras.h"
//Primitivas Secundarias
t_pixel IncrementoAzul(t_pixel);
t_pixel IncrementoRojo(t_pixel);
t_pixel IncrementoVerde(t_pixel);
t_pixel IncrementoDeGris(t_pixel);
t_pixel ImgNegativa(t_pixel);
t_pixel ContrasteAumenta(t_pixel);
t_pixel ContrasteReduce(t_pixel);
void rotarDer(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2);
void rotarIzq(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2);
void recortar(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2);
//Funciones Principales
void BMPmanipuleitor(int argc, char* argv[]){
    for(int i=0; i<argc; i++)
    {
        if(strcmp(argv[i],"--tonalidad-azul")==0)
        {
            TonalidadAzul(argc, argv);
        }
        if(strcmp(argv[i],"--tonalidad-rojo")==0)
        {
            TonalidadRojo(argc, argv);
        }
        if(strcmp(argv[i],"--tonalidad-verde")==0)
        {
            TonalidadVerde(argc, argv);
        }
        if(strcmp(argv[i],"--escala-de-grises")==0)
        {
            EscalaDeGrises(argc, argv);
        }
        if(strcmp(argv[i],"--negativo")==0)
        {
            Negativo(argc, argv);
        }
        if(strcmp(argv[i],"--aumentar-contraste")==0)
        {
            AumentarContraste(argc, argv);
        }
        if(strcmp(argv[i],"--reducir-contraste")==0)
        {
            ReducirContraste(argc, argv);
        }
        if(strcmp(argv[i],"--rotar-derecha")==0)
        {
            RotarDerecha(argc, argv);
        }
        if(strcmp(argv[i],"--rotar-izquierda")==0)
        {
            RotarIzquierda(argc, argv);
        }
        if(strcmp(argv[i],"--recortar")==0)
        {
            RecortarImagen(argc, argv);
        }
    }
}
void TonalidadAzul(int argc, char *argv[]){
    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("TonalidadAzul.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    while(puntero <= metadata.tamArchivo){//colores
       fread(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       pixel=IncrementoAzul(pixel);
       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void TonalidadRojo(int argc, char *argv[]){
    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("TonalidadRojo.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    while(puntero <= metadata.tamArchivo){//colores
       fread(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       pixel=IncrementoRojo(pixel);
       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void TonalidadVerde(int argc, char *argv[]){
    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("TonalidadVerde.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    while(puntero <= metadata.tamArchivo){//colores
       fread(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       pixel=IncrementoVerde(pixel);
       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void EscalaDeGrises(int argc, char *argv[]){
    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("EscalaDeGrises.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    while(puntero <= metadata.tamArchivo){//colores
       fread(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       pixel=IncrementoDeGris(pixel);
       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void Negativo(int argc, char* argv[]){
    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("Negativa.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    while(puntero <= metadata.tamArchivo){//colores
       fread(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       pixel = ImgNegativa(pixel);
       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero = puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);


}
void RotarDerecha(int argc, char* argv[]){
    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("RotadaDerecha.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);
    int alto = metadata.alto;

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);
    int ancho=metadata.ancho;

    fseek(ImagenDeSalida,18,SEEK_SET);
    fwrite(&metadata.alto,sizeof(metadata.alto), 1, ImagenDeSalida);
    fwrite(&metadata.ancho,sizeof(metadata.ancho), 1, ImagenDeSalida);

    rotarDer(alto, ancho, pixel, ImagenDeEntrada, ImagenDeSalida);

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void RotarIzquierda(int argc, char* argv[]){

    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("RotadaIzquierda.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);
    int alto = metadata.alto;

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);
    int ancho=metadata.ancho;

    fseek(ImagenDeSalida,18,SEEK_SET);
    fwrite(&metadata.alto,sizeof(metadata.alto), 1, ImagenDeSalida);
    fwrite(&metadata.ancho,sizeof(metadata.ancho), 1, ImagenDeSalida);

    rotarIzq(alto, ancho, pixel, ImagenDeEntrada, ImagenDeSalida);

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void RecortarImagen(int argc, char* argv[]){
    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("recortada.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);



    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }



    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }



    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);
    int NuevoAncho = metadata.ancho / 2;
    fseek(ImagenDeSalida,18,SEEK_SET);
    fwrite(&NuevoAncho,sizeof(metadata.ancho),1,ImagenDeSalida);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);
    int NuevoAlto = metadata.alto / 2;
    fseek(ImagenDeSalida,22,SEEK_SET);
    fwrite(&NuevoAlto,sizeof(metadata.alto),1,ImagenDeSalida);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);
    printf("El tamaño del archivo es de %i Bits\n",metadata.tamArchivo);
    int NuevoTamArchivo= metadata.tamArchivo/4;
    fseek(ImagenDeSalida,2,SEEK_SET);
    fwrite(&NuevoTamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeSalida);



    recortar(NuevoAlto, NuevoAncho, pixel, ImagenDeEntrada, ImagenDeSalida);



    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);

}
void AumentarContraste(int argc, char *argv[]){

    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("ContrasteAumentado.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    while(puntero <= metadata.tamArchivo){//colores
       fread(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       pixel=ContrasteAumenta(pixel);
       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void ReducirContraste(int argc, char *argv[]){

    t_pixel pixel;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    char ruta[] = "unlam.bmp";

    FILE* ImagenDeEntrada = fopen(ruta,"rb");
    FILE* ImagenDeSalida = fopen("ContrasteReducido.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,14,SEEK_SET);
    fread(&metadata.tamEncabezado,sizeof(metadata.tamEncabezado),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeEntrada,10,SEEK_SET);
    fread(&metadata.comienzoImagen,sizeof(metadata.comienzoImagen),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);

    fseek(ImagenDeEntrada,28,SEEK_SET);
    fread(&metadata.profundidad, sizeof(metadata.profundidad), 1, ImagenDeEntrada);

    if (metadata.profundidad != 24) {
        printf("La imagen no es de 24 bits por pixel.\n");
        fclose(ImagenDeEntrada);
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        fseek(ImagenDeEntrada,puntero,SEEK_SET);
        fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    while(puntero <= metadata.tamArchivo){//colores
       fread(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       pixel=ContrasteReduce(pixel);
       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
//Funciones secundarias
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
t_pixel IncrementoRojo (t_pixel cambio){

    int rojo;
    t_pixel pixel;
    rojo=cambio.pixel[2]*1.5;
    if(rojo>255){
        rojo=255;
    }


    pixel.pixel[2]=(char) rojo;
    pixel.pixel[1]=cambio.pixel[1];
    pixel.pixel[0]=cambio.pixel[0];

    return pixel;
}
t_pixel IncrementoVerde (t_pixel cambio){

    int verde;
    t_pixel pixel;
    verde=cambio.pixel[1]*1.5;
    if(verde>255){
        verde=255;
    }


    pixel.pixel[1]=(char) verde;
    pixel.pixel[2]=cambio.pixel[2];
    pixel.pixel[0]=cambio.pixel[0];

    return pixel;
}
t_pixel IncrementoDeGris (t_pixel cambiar){

    char gris;
    t_pixel  ret;
    gris=(cambiar.pixel[2]+cambiar.pixel[1]+cambiar.pixel[0])/3;

    ret.pixel[2]=gris;
    ret.pixel[1]=gris;
    ret.pixel[0]=gris;

    return ret;
}
t_pixel ImgNegativa (t_pixel cambio){
    t_pixel pixel;

    pixel.pixel[0]= 255 - cambio.pixel[0];
    pixel.pixel[1]= 255 - cambio.pixel[1];
    pixel.pixel[2]= 255 - cambio.pixel[2];

    return pixel;
}
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
t_pixel ContrasteReduce(t_pixel cambiar){

    t_pixel ret;
    unsigned char gris;
    float multiplicador;

    unsigned int aux;

    gris = (cambiar.pixel[2] + cambiar.pixel[1] + cambiar.pixel[0]) / 3;

    multiplicador = 125;


    if (gris <= 30)    {        multiplicador = 125;    }
    if (gris > 30)    {        multiplicador = 120;    }
    if (gris > 60)    {        multiplicador = 110;    }
    if (gris > 90)    {        multiplicador = 105;    }
    if (gris > 120)    {        multiplicador = 100;    }
    if (gris > 150)    {        multiplicador = 95;    }
    if (gris > 180)    {        multiplicador = 90;    }
    if (gris > 210)    {        multiplicador = 80;    }
    if (gris > 240)    {        multiplicador = 75;    }

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
t_pixel ContrasteAumenta (t_pixel cambiar){


    t_pixel ret;
    unsigned char gris;
    float multiplicador;

    unsigned int aux;

    gris = (cambiar.pixel[2] + cambiar.pixel[1] + cambiar.pixel[0]) / 3;

    multiplicador = 125;


    if (gris <= 30){multiplicador=75;}
    if (gris > 30){multiplicador=78;}
    if (gris > 60){multiplicador=82;}
    if (gris > 90){multiplicador=90;}
    if (gris > 120){multiplicador=100;}
    if (gris > 150){multiplicador=110;}
    if (gris > 180){multiplicador=118;}
    if (gris > 210){multiplicador=122;}
    if (gris > 240){multiplicador=125;}

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

    if (multiplicador/100 != 1)//{ printf("%f  %f  %02X  %02X\n",multiplicador/100,(multiplicador/100)  * cambiar.pixel[0],cambiar.pixel[0],ret.pixel[0]);}

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
void recortar(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2){
    printf("ALTO: %d/n", alto);
    printf("ANCHO: %d", ancho);
fseek(file2,54,SEEK_SET);
    for (int i = 0  ; i < alto ;  i++) {
        for (int j = 0; j < ancho; j++) {

           fseek(file,(sizeof(pixel.pixel) * (j*alto+i))+54,SEEK_SET);

            fread(&pixel.pixel,sizeof(pixel.pixel),1,file);

            fwrite(&pixel.pixel, sizeof(pixel.pixel), 1, file2);

        }
    }
}




