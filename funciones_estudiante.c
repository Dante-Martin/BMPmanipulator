/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Clara
    Nombre: Lucas
    DNI: 46265738
    Entrega: Si
    -----------------
    Apellido: Martin
    Nombre: Dante
    DNI: 41926845
    Entrega: Si
    -----------------
    (Sólo para grupos de tres integrantes)
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP: El trabajo práctico estuvo bueno, se nos hizo bastante complicado de hacer,
    teniendo en cuenta que venimos de la materia anterior realizarlo fue bastante complicado, seguramente se puedan mejorar y agilizar muchos
    procesos, pero nos priorizamos en cumplir el objetivo. Sin embargo, valoramos que a pesar del esfuerzo  y complicaciones aprendimos muchas cosas
    nuevas e interesantes, sobre todo, la manipulación de imágenes bmp :).
    Por otro lado, tuvimos un problema con la foto unlam.bmp y para la funcion recortar y rotar, debimos utilizar la aplicacion GIMP y guardar la foto
    nuevamente como un archivo .bmp de 24 bits, es probable que haya algun error en el archivo tal vez que no nos permitia que funcionen
    correctamente dichas funciones.
*/
#include "funciones_estudiante.h"
#include "estructuras.h"
//Funciones Primitivas Secundarias
void rotarDer(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2);
void rotarIzq(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2);
void Recortar(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2);
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
        if(strcmp(argv[i],"--comodin")==0)
        {
            Comodin(argc, argv);
        }
    }
}
void TonalidadAzul(int argc, char *argv[]){
    t_pixel pixel;
    t_pixel cambio;
    t_metadata metadata;
    char elByte;
    int puntero=0, azul;

    FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("TonalidadAzul.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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
       fread(&cambio.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       azul=cambio.pixel[0]*1.5;
        if(azul>255){
        azul=255;}
       pixel.pixel[0]=(char) azul;
       pixel.pixel[1]=cambio.pixel[1];
       pixel.pixel[2]=cambio.pixel[2];
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
    t_pixel cambio;
    t_metadata metadata;
    char elByte;
    int puntero=0, rojo;

    FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("TonalidadRojo.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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
       fread(&cambio.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
      rojo=cambio.pixel[2]*1.5;
       if(rojo>255){
        rojo=255;}
       pixel.pixel[2]=(char) rojo;
       pixel.pixel[1]=cambio.pixel[1];
       pixel.pixel[0]=cambio.pixel[0];
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
    t_pixel cambio;
    t_metadata metadata;
    char elByte;
    int puntero=0, verde;
    FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("TonalidadVerde.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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
       fread(&cambio.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
        verde=cambio.pixel[1]*1.5;
       if(verde>255){
        verde=255;}
       pixel.pixel[1]=(char) verde;
       pixel.pixel[2]=cambio.pixel[2];
       pixel.pixel[0]=cambio.pixel[0];
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
    t_pixel cambio;
    t_metadata metadata;
    char elByte, gris;
    int puntero=0;
    FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("EscalaDeGrises.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    };

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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
       fread(&cambio.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       gris=(cambio.pixel[2]+cambio.pixel[1]+cambio.pixel[0])/3;
       pixel.pixel[2]=gris;
       pixel.pixel[1]=gris;
       pixel.pixel[0]=gris;
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
    t_pixel cambio;
    t_metadata metadata;
    char elByte;
    int puntero=0;

    FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("Negativa.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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
       fread(&cambio.pixel, sizeof(cambio.pixel),1,ImagenDeEntrada);

       pixel.pixel[0]= 255 - cambio.pixel[0];
       pixel.pixel[1]= 255 - cambio.pixel[1];
       pixel.pixel[2]= 255 - cambio.pixel[2];

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

    FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("RotadaDerecha.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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

     FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("RotadaIzquierda.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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

     FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("recortada.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;
        }

    fseek(ImagenDeEntrada,18,SEEK_SET);
    fread(&metadata.ancho,sizeof(metadata.ancho),1,ImagenDeEntrada);
    unsigned int NuevoAncho = metadata.ancho / 2;
    fseek(ImagenDeSalida,18,SEEK_SET);
    fwrite(&NuevoAncho,sizeof(metadata.ancho),1,ImagenDeSalida);

    fseek(ImagenDeEntrada,22,SEEK_SET);
    fread(&metadata.alto,sizeof(metadata.alto),1,ImagenDeEntrada);
    unsigned int NuevoAlto = metadata.alto / 2;
    fseek(ImagenDeSalida,22,SEEK_SET);
    fwrite(&NuevoAlto,sizeof(metadata.alto),1,ImagenDeSalida);

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);
    unsigned int NuevoTamArchivo= metadata.tamArchivo/4;
    fseek(ImagenDeSalida,2,SEEK_SET);
    fwrite(&NuevoTamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeSalida);

    Recortar(NuevoAlto, NuevoAncho, pixel, ImagenDeEntrada, ImagenDeSalida);

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void ReducirContraste(int argc, char *argv[]){

    t_pixel pixel;
    t_pixel cambio;
    t_metadata metadata;
    char elByte;
    int puntero=0;
    unsigned char gris;
    float multiplicador;

    unsigned int aux;

     FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("ContrasteReducido.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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
       fread(&cambio.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
       gris = (cambio.pixel[2] + cambio.pixel[1] + cambio.pixel[0]) / 3;

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

    aux = (multiplicador / 100) * cambio.pixel[0];
    if (aux > 255)
    {
        aux = 255;
    }
    pixel.pixel[0] = aux;

    aux = multiplicador / 100 * cambio.pixel[1];
    if (aux > 255)
    {
        aux = 255;
    }
    pixel.pixel[1] = aux;

    aux = multiplicador / 100 * cambio.pixel[2];
    if (aux > 255)
    {
        aux = 255;
    }
    pixel.pixel[2] = aux;
       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
void Comodin(int argc, char* argv[]){

    t_pixel pixel,ret;
    t_metadata metadata;
    char elByte;
    int puntero=0;
    float multiplicador;

    unsigned int aux;


    FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("Comodin.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

    fseek(ImagenDeSalida,0,SEEK_SET);
    fseek(ImagenDeEntrada,0,SEEK_SET);
    while(puntero<54){

        fread(&elByte,sizeof(elByte),1,ImagenDeEntrada);
        fwrite(&elByte,sizeof(elByte),1,ImagenDeSalida);
        puntero++;

        }

    while(puntero <= metadata.tamArchivo){//colores
       fread(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);



    multiplicador = 125;

    aux = (multiplicador / 100) * pixel.pixel[0];
    if (aux > 255)
    {
        aux = 255;
    }
    ret.pixel[0] = aux;

    aux = multiplicador / 100 * pixel.pixel[1];
    if (aux > 255)
    {
        aux = 255;
    }
    ret.pixel[1] = aux;

    aux = multiplicador / 100 * pixel.pixel[2];
    if (aux > 255)
    {
        aux = 255;
    }
    ret.pixel[2] = aux;

    pixel=ret;

       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);

       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }


    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);

}
void AumentarContraste(int argc, char *argv[]){

    t_pixel pixel;
    t_pixel cambio;
    t_metadata metadata;
    char elByte;
    int puntero=0;
    unsigned char gris;
    float multiplicador;

    unsigned int aux;

    FILE* ImagenDeEntrada = fopen("unlam.bmp", "rb");
    FILE* ImagenDeSalida = fopen("ContrasteAumentado.bmp", "wb");

    if(ImagenDeEntrada==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }
    if(ImagenDeSalida==NULL){
        printf("El archivo no se pudo cargar \n");
        exit(1);
    }

    fseek(ImagenDeEntrada,2,SEEK_SET);
    fread(&metadata.tamArchivo, sizeof(metadata.tamArchivo), 1, ImagenDeEntrada);

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
       fread(&cambio.pixel,sizeof(pixel.pixel),1,ImagenDeEntrada);
        gris = (cambio.pixel[2] + cambio.pixel[1] + cambio.pixel[0]) / 3;

    multiplicador = 125;
    if (gris <= 30){multiplicador=75;}
    if (gris > 30){multiplicador=88;}
    if (gris > 60){multiplicador=95;}
    if (gris > 90){multiplicador=98;}
    if (gris > 120){multiplicador=100;}
    if (gris > 150){multiplicador=102;}
    if (gris > 180){multiplicador=105;}
    if (gris > 210){multiplicador=112;}
    if (gris > 240){multiplicador=125;}
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

    aux = (multiplicador / 100) * cambio.pixel[0];
    if (aux > 255)
    {
        aux = 255;
    }
    pixel.pixel[0] = aux;

    if (multiplicador/100 != 1)//{ printf("%f  %f  %02X  %02X\n",multiplicador/100,(multiplicador/100)  * cambiar.pixel[0],cambiar.pixel[0],ret.pixel[0]);}

    aux = multiplicador / 100 * cambio.pixel[1];
    if (aux > 255)
    {
        aux = 255;
    }
    pixel.pixel[1] = aux;

    aux = multiplicador / 100 * cambio.pixel[2];
    if (aux > 255)
    {
        aux = 255;
    }
    pixel.pixel[2] = aux;

       fwrite(&pixel.pixel,sizeof(pixel.pixel),1,ImagenDeSalida);
       puntero=puntero+sizeof(pixel.pixel);
       fseek(ImagenDeEntrada,puntero,SEEK_SET);
       fseek(ImagenDeSalida,puntero,SEEK_SET);
        }

    fclose(ImagenDeSalida);
    fclose(ImagenDeEntrada);
}
//Funciones secundarias
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
void Recortar(int alto, int ancho, t_pixel pixel, FILE *file, FILE *file2){
fseek(file2,54,SEEK_SET);
   for (int i = 0   ; i < (alto) ;  i++) {
        for (int j = 0; j < (ancho); j++) {

           fseek(file,(sizeof(pixel.pixel) * (i*ancho*2+j))+54,SEEK_SET);

            fread(&pixel.pixel,sizeof(pixel.pixel),1,file);

            fwrite(&pixel.pixel, sizeof(pixel.pixel), 1, file2);

        }
    }
}

