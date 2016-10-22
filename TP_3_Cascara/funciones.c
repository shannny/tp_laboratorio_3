#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"


int agregarPelicula(char fileName[], EMovie *movie)
{
     int retorno=1;
    FILE* pArchivo=fopen("bin.dat","ab");
		if(pArchivo==NULL)
            retorno=0;

		else
        {
            fwrite(&movie,sizeof(EMovie),1,pArchivo);
        }
    fclose(pArchivo);
    return retorno;
}

int borrarPelicula(char fileName[], EMovie movie)
{

    FILE *fMovies;
    EMovie *movieAux=NULL;
    int cant;
    int ret=0;

    fMovies=fopen(fileName, "r+b");
    if(fMovies!=NULL)
    {
        while(!feof(fMovies))
        {
            cant=fread(movieAux, sizeof(EMovie), 1, fMovies);
            if(cant!=1)
            {
                if(feof(fMovies))
                {
                    ret= -1;
                    break;
                }else
                {
                    printf("No se pudo leer el ultimo registro");
                    ret= -1;
                    break;
                }
            }
            if(strcmp(movieAux->titulo, movie.titulo)==0 && movieAux->estado==0)
            {
                movieAux->estado=1;
                if(fseek(fMovies, (-1)*sizeof(EMovie), SEEK_CUR)!=0)
                {
                    printf("Ocurrio un error al intentar reposicion el puntero");
                    ret= -1;
                    break;
                }
                if(fwrite(movieAux, sizeof(EMovie), 1, fMovies)!=1)
                {
                    printf("No se pudo actualizar el archivo de peliculas");
                    ret= -1;
                    break;
                }
                printf("La pelicula fue eliminada exitosamente\n");
                break;
            }
        }
    }

    fclose(fMovies);
    return ret;
}

void generarPagina(EMovie lista[], char nombre[])
{
    char DOCTYPE[]={"<!DOCTYPE html>\n<!-- Template by Quackit.com -->\n"};
    char LANG[]={"<html lang='en'>\n"};
    char HEAD[]={"<head>\n\t<meta charset='utf-8'>\n\t<meta http-equiv='X-UA-Compatible' content='IE=edge'>\n\t<meta name='viewport' content='width=device-width, initial-scale=1'>\n\t<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->\n\t<title>Lista peliculas</title>\n\t<!-- Bootstrap Core CSS -->\n\t<link href='css/bootstrap.min.css' rel='stylesheet'>\n\t<!-- Custom CSS: You can use this stylesheet to override any Bootstrap styles and/or apply your own styles -->\n\t<link href='css/custom.css' rel='stylesheet'>\n\t<!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->\n\t<!-- WARNING: Respond.js doesn't work if you view the page via file:// -->\n\t<!--[if lt IE 9]>\n\t\t<script src='https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js'></script>\n\t\t<script src='https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js'></script>\n\t<![endif]-->\n</head>\n"};
    char BODYIN[]={"<body>\n"};
    char DIV[]={"\t<div class='container'>\n\t\t<div class='row'>\n"};
    char ARTICLEIN[]={"\t\t\t<article class='col-md-4 article-intro'>\n"};
    char AIN[]={"\t\t\t\t<a href='#'>"};
    char AFIN[]={"</a>\n"};
    char IMAGE[]={"\t\t\t\t\t<img class='img-responsive img-rounded' src="};
    char IMAGEFI[]={" alt=''>\n"};
    char H3[]={"<h3>\n"};
    char H3FI[]={"</h3>\n"};
    char UL[]={"<ul>\n"};
    char ULFI[]={"</ul>\n"};
    char LI[]={"<li>"};
    char LIFI[]={"</li>\n"};
    char P[]={"<p>"};
    char PFI[]={"</p>\n"};
    char ARTICLEFI[]={"</article>\n"};
    char DIVFI[]={"\t\t</div>\n\t</div>\n"};
    char SCRIPT[]={"\t<script src='js/jquery-1.11.3.min.js'></script>\n\t<script src='js/bootstrap.min.js'></script>\n\t<script src='js/ie10-viewport-bug-workaround.js'></script>\n\t<script src='js/holder.min.js'></script>\n"};
    char BODYFI[]={"</body>\n"};
    char HTML[]={"</html>\n"};

    int length=sizeof(lista)/sizeof(EMovie);
    int i;
    FILE *indexFile;

    indexFile=fopen(nombre, "w");

    fwrite(DOCTYPE, sizeof(char), strlen(DOCTYPE), indexFile);
    fwrite(LANG, sizeof(char), strlen(LANG), indexFile);
    fwrite(HEAD, sizeof(char), strlen(HEAD), indexFile);
    fwrite(BODYIN, sizeof(char), strlen(BODYIN), indexFile);
    fwrite(DIV, sizeof(char), strlen(DIV), indexFile);

    for(i=0; i<length; i++)
    {
        fwrite(ARTICLEIN, sizeof(char), strlen(ARTICLEIN), indexFile);
        fwrite(AIN, sizeof(char), strlen(AIN), indexFile);
        fwrite("\n", sizeof(char), strlen("\n"), indexFile);
        fwrite(IMAGE, sizeof(char), strlen(IMAGE), indexFile);
        fwrite(lista[i].linkImagen, sizeof(char), strlen(lista[i].linkImagen), indexFile);
        fwrite(IMAGEFI, sizeof(char), strlen(IMAGEFI), indexFile);
        fwrite(AFIN, sizeof(char), strlen(AFIN), indexFile);
        fwrite(H3, sizeof(char), strlen(H3), indexFile);
        fwrite(AIN, sizeof(char), strlen(AIN), indexFile);
        fwrite(lista[i].titulo, sizeof(char), strlen(lista[i].titulo), indexFile);
        fwrite(AFIN, sizeof(char), strlen(AFIN), indexFile);
        fwrite(H3FI, sizeof(char), strlen(H3FI), indexFile);
        fwrite(UL, sizeof(char), strlen(UL), indexFile);
        fwrite(LI, sizeof(char), strlen(LI), indexFile);
        fwrite("Género:", sizeof(char), strlen("Género:"), indexFile);
        fwrite(lista[i].genero, sizeof(char), strlen(lista[i].genero), indexFile);
        fwrite(LIFI, sizeof(char), strlen(LIFI), indexFile);
        fwrite(LI, sizeof(char), strlen(LI), indexFile);
        fwrite("Puntaje:", sizeof(char), strlen("Puntaje:"), indexFile);
        fprintf(indexFile, "%d", lista[i].puntaje);
        fwrite(LIFI, sizeof(char), strlen(LIFI), indexFile);
        fwrite(LI, sizeof(char), strlen(LI), indexFile);
        fwrite("Duración:", sizeof(char), strlen("Duración:"), indexFile);
        fprintf(indexFile, "%d", lista[i].duracion);
        fwrite(LIFI, sizeof(char), strlen(LIFI), indexFile);
        fwrite(ULFI, sizeof(char), strlen(ULFI), indexFile);
        fwrite(P, sizeof(char), strlen(P), indexFile);
        fwrite(lista[i].descripcion, sizeof(char), strlen(lista[i].descripcion), indexFile);
        fwrite(PFI, sizeof(char), strlen(PFI), indexFile);
        fwrite(ARTICLEFI, sizeof(char), strlen(ARTICLEFI), indexFile);
    }


    fwrite(DIVFI, sizeof(char), strlen(DIVFI), indexFile);
    fwrite(SCRIPT, sizeof(char), strlen(SCRIPT), indexFile);
    fwrite(BODYFI, sizeof(char), strlen(BODYFI), indexFile);
    fwrite(HTML, sizeof(char), strlen(HTML), indexFile);


    fclose(indexFile);
}

EMovie* obtenerPelicula(char fileName[], char movieTittle[])
{
    char screenMes[]={"Ah ocurrido un error contactese con el administrador"};
    EMovie *movie=NULL;
    FILE *fMovies=NULL;
    FILE *fLogs;

    fMovies = fopen(fileName, "rb");
    fLogs=fopen(LOGS, "a");

    if(fMovies!=NULL)
    {
        while(!feof(fMovies))
        {
            if(fread(movie, sizeof(EMovie), 1, fMovies)!=1)
            {
                if(feof(fMovies))
                {
                    printf("%s\n", screenMes);
                    logger("Error, al leer el dato, se llego al final del archivo");
                    break;
                }else
                {
                    printf("%s\n", screenMes);
                    logger("No se pudo leer el ultimo registro");
                    break;
                }
            }
            if(strcmp(movie->titulo, movieTittle))
            {
                break;
            }
        }

    }
    fclose(fMovies);
    fclose(fLogs);
    return movie;
}

int existePelicula(char fileName[], char movieTittle[])
{
    char screenMes[]={"Ah ocurrido un error contactese con el administrador"};
    EMovie *movie=NULL;
    FILE *fMovies=NULL;
    FILE *fLogs;

    fMovies = fopen(fileName, "rb");
    fLogs=fopen(LOGS, "a");

    if(fMovies!=NULL)
    {
        while(!feof(fMovies))
        {
            if(fread(movie, sizeof(EMovie), 1, fMovies)!=1)
            {
                if(feof(fMovies))
                {
                    printf("%s\n", screenMes);
                    logger("Error, al leer el dato, se llego al final del archivo");
                    return -1;
                }else
                {
                    printf("%s\n", screenMes);
                    logger("No se pudo leer el ultimo registro");
                    return -1;
                }
            }
            if(strcmp(movie->titulo, movieTittle)&& movie->estado==0)
            {
                return 0;
            }
        }

    }
    fclose(fMovies);
    fclose(fLogs);
    return -1;
}

void logger(char message[])
{

}

int getInt(int* input,char message[],char eMessage[], int lowLimit, int hiLimit)
{
    int aux;
    char opcion='s';

    while(tolower(opcion)=='s')
    {
        printf("%s\n", message);
        fflush(stdin);
        scanf("%d", &aux);
        if(aux>=lowLimit && aux<=hiLimit)
        {
            *input=aux;
            return 0;
        }

        printf(eMessage);
        printf("Desea volver a ingresar el valor (s/n)");
        fflush(stdin);
        scanf("%c", &opcion);
    }
    return -1;
}

int getString(char* input,char message[],char eMessage[], int lowLimit, int hiLimit)
{
    char aux[2000];
    int auxLenght;
    char opcion='s';

    while(tolower(opcion)=='s')
    {
        printf("%s\n", message);
        fflush(stdin);
        scanf("%s",aux);
        auxLenght=strlen(aux);
        if(auxLenght>lowLimit && auxLenght<hiLimit)
        {
            strcpy(input, aux);
            return 0;
        }
        printf(eMessage);
        printf("Desea volver a ingresar el valor (s/n)");
        fflush(stdin);
        scanf("%c", &opcion);
    }
    return -1;
}
