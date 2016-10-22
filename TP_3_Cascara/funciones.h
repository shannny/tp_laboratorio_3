#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#define MOVIEDAT "./Dat/movies.dat"
#define LOGS "./Logs/log.txt"


typedef struct{
    char titulo[20];
    char genero[20];
    int duracion;
    char descripcion[50];
    int puntaje;
    char linkImagen[1000];
    int estado;
}EMovie;


/**
 *  Agrega una pelicula al archivo binario.
 *  @param movie la estructura a ser agregada al archivo.
 *  @return retorna 1 o 0 de acuerdo a si pudo agregar la pelicula o no.
 */
int agregarPelicula(char fileName[], EMovie *movie);

/**
 *  Borra una pelicula del archivo binario.
 *  @param movie la estructura a ser eliminada al archivo.
 *  @return retorna 1 o 0 de acuerdo a si pudo eliminar la pelicula o no.
 */
int borrarPelicula(char fileName[], EMovie movie);

/**
 *  Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 *  @param lista la lista de peliculas a ser agregadas en el archivo.
 *  @param nombre el nombre para el archivo.
 */
void generarPagina(EMovie lista[], char nombre[]);

/**
* Busca en un archivo binario una pelicula por nombre retornando la informacion de la misma.
* @param fileName archivo binario donde se buscara la pelicula.
* @param movieTittle el nombre de la pelicula que se buscara.
*/
EMovie* obtenerPelicula(char fileName[], char movieTittle[]);

/**
* Busca en un archivo binario la existencia de una pelicula por nombre.
* @param fileName archivo binario donde se buscara la pelicula.
* @param movieTittle el nombre de la pelicula que se buscara.
*/
int existePelicula(char fileName[], char movieTittle[]);

/**
* Crea logs para la aplicacion.
* @param fName puntero al archivo de logs.
* @param message mensaje que se guardara en el archivo.
*/
void logger(char message[]);

/**
* @brief Solicita una cadena de caracteres al usuario y la valida.
* @param input Se carga el string ingresado.
* @param message Es el mensaje a ser mostrado.
* @param eMessage Es el mensaje a ser mostrado en caso de error.
* @param lowLimit Longitud mínima de la cadena.
* @param hiLimit Longitud máxima de la cadena.
* @return Si obtuvo la cadena [0] si no [-1].
*/
int getString(char* input,char message[],char eMessage[], int lowLimit, int hiLimit);

/**
* @brief Solicita un número al usuario y lo valida.
* @param input Se carga el numero ingresado.
* @param message Es el mensaje a ser mostrado.
* @param eMessage Es el mensaje a ser mostrado en caso de error.
* @param lowLimit Limite inferior a validar.
* @param hiLimit Limite superior a validar.
* @return Si obtuvo el numero [0] si no [-1].
*/
int getInt(int* input,char message[],char eMessage[], int lowLimit, int hiLimit);


#endif // FUNCIONES_H_INCLUDED
