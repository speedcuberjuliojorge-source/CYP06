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
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
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
			char signos[] = { ' ', '\t', '\n', ',', ';', '(', ')','\r', '.'};
			char buff[TAMTOKEN];
			char buffer[TAMTOKEN];
			int ab = 0;

			fscanf_s(fp, "%s", buffer, TAMTOKEN);



			/*int len = strlen(buffer);

			int Bfin = false;
			for (int i = 0; i <=len ; i++)
			{
				
				for (int j = 0; j < 8 ; j++)
				{
					if (buff[i] == signos[j])
					{
						buff[i] = ' ';
					}
				}
				buffer[ab] = buff[i];
				ab++;
			}


				buffer[ab] = '\0';*/


			_strlwr_s(buffer, TAMTOKEN);

			//BORRA LOS CARACTERES INVALIDOS
			//char signos[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'á', 'é', 'í', 'ó', 'ú'};
			for (int j = 0; j < strlen(buffer); j++)
			{
				int banValida = true;
				for (int i = 0; (i < 9) && (banValida == true); i++)
				{
					if (buffer[j] != signos[i])
					{
						banValida = true;
					}
					else
					{
						banValida = false;
					}
				}
				if (banValida == false)
				{
					buffer[j] = ' ';
				}
			}
			//DEJA LAS PALABRAS 100% VALIDAS
			int longitud = strlen(buffer);
			for (int pasada = 0; pasada <= longitud; pasada++)
			{
				for (int i = 0; i <= longitud; i++)
				{
					if (buffer[i] == ' ')
					{
						buffer[i] = buffer[i + 1];
						buffer[i + 1] = ' ';
					}
				}
			}
			//ASIGNA EL VALOR ACTUAL DE BUFFER AL ARREGLO szPalabras
				strcpy_s(szPalabras[a], TAMTOKEN, buffer);
				a++;


		} while (!feof(fp));
		fclose(fp);
	}
	else//SI NO PUDO ABRIR EL DOCUMENTO PRUEBA
	{
		printf("ERROR");
	}

	//ORDENAR ALFABETICAMENTE LAS PALABRAS
	char  aux[TAMTOKEN];
	int comp;

	for (int pasada = 0; pasada <= a - 2; pasada++)
	{
		for (int i = 0; i <= a - 2; i++)
		{
			comp = strcmp(szPalabras[i], szPalabras[i + 1]);//EN C EL RESULTADO DE CMP ES UN VALOR TEMPORAL, ES POR ESO QUE SE DEBE GUARDAR EN UNA VARIABLE
			if (comp == 1)
			{
				strcpy_s(aux, 49, szPalabras[i]);
				strcpy_s(szPalabras[i], 49, szPalabras[i + 1]);
				strcpy_s(szPalabras[i + 1], 49, aux);
			}


		}
	}

	
	//SACAR LAS FRECUENCIAS DE LAS PALABRAS
	int asignar = 0;
	for (int i = 0; i <= a - 1; i++)
	{
		int repet = 1;

		if (strcmp(szPalabras[i], szPalabras[i - 1]) != 0)
		{
			for (int z = i + 1; z < a-1; z++)
			{
				if (strcmp(szPalabras[i], szPalabras[z]) == 0)
				{
					repet++;
				}
			}
			iEstadisticas[asignar] = repet;
			asignar++;
		}
	}


	//ORDENAR ALFABETICAMENTE TODAS LAS PALABRAS
	for (int indice = 0; indice < a ; indice++)
	{
		if ((szPalabras[indice] != " "))
		{
			for (int i = indice + 1; (i < a) ; i++)
			{
				if (strcmp(szPalabras[indice], szPalabras[i]) == 0)
				{
					strcpy_s(szPalabras[i], 49, " ");
				}

			}
		}
	}
	
	



	//DEJA A LAS PALABRAS JUNTAS EN EL ARRAY
	for (int pasada = 0; pasada < a ; pasada++)
	{
		for (int i = 0; i < a-1 ; i++)
		{
			int b = i + 1;
			if (strcmp(szPalabras[i], " ") == 0)
			{
				strcpy_s(szPalabras[i], 49, szPalabras[b]);
				strcpy_s(szPalabras[b], 49, " ");
			}
		}

	}

	int frecuencia = 0;
	for (int i = 0; i < a; i++)
	{
		if (strcmp(szPalabras[i], " ") != 0)
		{
			frecuencia++;
		}
	}
	iNumElementos = frecuencia;
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
