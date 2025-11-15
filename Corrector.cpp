/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	Cruz Trujillo Julio Jorge 323290687
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{
	int a = 0;
	//Se busca el documento
	FILE* fp;
	fopen_s(&fp, szNombre, "r");

	//Si encuentra el documento
	if (fp != NULL)
	{

		//LEER SOLO LOS CARACTERES ALFABETICOS Y  GUARDARLOS EN EL ARRAY 2D
		do
		{
			char buffer[TAMTOKEN];
			fscanf_s(fp, "%s", buffer, TAMTOKEN);
			strlwr(buffer);

			//BORRA LOS CARACTERES INVALIDOS
			char signos[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'á', 'é', 'í', 'ó', 'ú' };
			for (int j = 0; j < strlen(buffer); j++)
			{
				int banValida = false;
				for (int i = 0; (i < 32) && (banValida == false); i++)
				{
					if (buffer[j] == signos[i])
					{
						banValida = true;
					}
				}
				if (banValida == false)
				{
					buffer[j] = ' ';
				}
			}
			//DEJA LAS PALABRAS 100% VALIDAS
			for (int pasada = 0; pasada < strlen(buffer); pasada++)
			{
				for (int i = 0; i < strlen(buffer); i++)
				{
					if (buffer[i] == ' ')
					{
						buffer[i] = buffer[i + 1];
						buffer[i + 1] = ' ';
					}
				}
			}
			//ASIGNA EL VALOR ACTUAL DE BUFFER AL ARREGLO szPalabras
			strcpy_s(szPalabras[a], 49, buffer);
			a++;

		} while (!feof(fp));
		fclose(fp);
	}
	else//SI NO PUDO ABRIR EL DOCUMENTO PRUEBA
	{
		printf("ERROR");
	}


	
	int indice = 0;
	for (int i = 0; i < a+1; i++)
	{
		if (szPalabras[i] != " ");
		{
			if (strcmp(szPalabras[indice], szPalabras[i]) == 0)
			{
				strcpy_s(szPalabras[i], 49, " ");
			}
			indice++;
		}
	}


}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c�digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su c�digo
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
