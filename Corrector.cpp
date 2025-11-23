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
#include <stdio.h>
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
			int pos = 0;
			char signos[] = { ' ', '\t', '\n', ',', ';', '(', ')','\r', '.' };
			char buff;
			int banInvalida = false;
			char buffer[TAMTOKEN];
			int fin = 1;
			while (!feof(fp))
			{
				int banCompa = false;
				//se asegura que el caracter sea valido
				banInvalida = false;
				fscanf_s(fp, "%c", &buff, 1);
				for (int i = 0; i <= 8 && banInvalida == false; i++)
				{
					if (buff == signos[i])
					{
						banInvalida = true;
					}
				}
				//si es caracter valido, agregar a palabra
				if (banInvalida == false)
				{
					buffer[pos] = buff;
					pos++;
				}
				//si no es caracter invalido, dejar listo para comparar/guardar
				else
				{
					//Si el caracter es unico e invalido, no guardar
					int banFor = false;
					if (pos == 0)
					{
						banFor = true;
					}
					if (!banFor)
					{
						buffer[pos] = '\0';
						_strlwr_s(buffer, TAMTOKEN);
						pos = 0;
						banCompa = true;
					}
				}
				//LISTO PARA COMPARAR
				if (banCompa)
				{
					int repetido = 0;
					int banUnico = true, banBloqueo = false;
					int banFinalizar = false;
					banUnico = true;
					for (int comp = 0; (comp < a) && (comp != a); comp++)
					{
						//si no es igual, dejar banUnico como true 
						if (strcmp(buffer, szPalabras[comp]) != 0)
						{
						}
						//si es igual, agregar un valor 
						else
						{
							repetido = comp;
							iEstadisticas[repetido]++;
							banFinalizar = true;
							banUnico = false;
						}
					}
					//si la banUnico se dejo como true, agregar la palabra y su frecuencia 1 a su arreglo
					if (banUnico)
					{
						strcpy_s(szPalabras[a], TAMTOKEN, buffer);
						iEstadisticas[a] = 1;
						a++;
					}
				}
			}
		} while (!feof(fp));
		fclose(fp);
	}
	else//SI NO PUDO ABRIR EL DOCUMENTO PRUEBA
	{
		printf("ERROR");
	}
	//ORDENAR ALFABETICAMENTE LAS PALABRAS
	char  aux[TAMTOKEN];
	int comp, auxfrec;
	for (int pasada = 0; pasada <= a - 2; pasada++)
	{
		for (int i = 0; i <= a - 2; i++)
		{
			comp = strcmp(szPalabras[i], szPalabras[i + 1]);//EN C EL RESULTADO DE CMP ES UN VALOR TEMPORAL, ES POR ESO QUE SE DEBE GUARDAR EN UNA VARIABLE
			if (comp == 1)
			{
				strcpy_s(aux, 49, szPalabras[i]);
				auxfrec = iEstadisticas[i];
				strcpy_s(szPalabras[i], 49, szPalabras[i + 1]);
				iEstadisticas[i] = iEstadisticas[i + 1];
				strcpy_s(szPalabras[i + 1], 49, aux);
				iEstadisticas[i + 1] = auxfrec;
			}
		}
	}
	iNumElementos = a;
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
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c�digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[0]); //la palabra candidata
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
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	iNumSugeridas = 0;
	int longiPalabra = strlen(szPalabraLeida);
	char szPalabraLeidaModif[TAMTOKEN];
	strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN,szPalabraLeida );
	iNumSugeridas++;
	//SUPRECION
	strcpy_s(szPalabraLeidaModif, TAMTOKEN, szPalabraLeida);
	for (int i = 0; i < longiPalabra; i++)
	{
		if (longiPalabra != 1)
		{
			strcpy_s(szPalabraLeidaModif, TAMTOKEN, szPalabraLeida);
			szPalabraLeidaModif[i] = ' ';
			for (int y = i; y < longiPalabra; y++)
			{
				szPalabraLeidaModif[y] = szPalabraLeidaModif[y + 1];
			}
			strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, szPalabraLeidaModif);
			iNumSugeridas++;
		}
	}
	//TRASPOCICION
	for (int i = 0; i < longiPalabra-1; i++)
	{
		strcpy_s(szPalabraLeidaModif, TAMTOKEN, szPalabraLeida);
		char aux = szPalabraLeidaModif[i];
		szPalabraLeidaModif[i] = szPalabraLeidaModif[i + 1];
		szPalabraLeidaModif[i + 1] = aux;
		strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, szPalabraLeidaModif);
		iNumSugeridas++;
	}
	//SUSTITUCION
	char alfabeto[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n',(char)0xF1,'o','p','q','r','s','t','u','v','w','x','y','z',(char)0xE1,(char)0xE9,(char)0xED,(char)0xF3,(char)0xFA};
	for (int i = 0; i < longiPalabra; i++)
	{
		for (int y = 0; y <= 31; y++)
		{
			strcpy_s(szPalabraLeidaModif, TAMTOKEN, szPalabraLeida);
			szPalabraLeidaModif[i] = alfabeto[y];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, szPalabraLeidaModif);
			iNumSugeridas++;
		}

	}
	//INSERCION
	char buffer[TAMTOKEN];
	int posInterrupcion = 0;
	int longiPalabraLeida = strlen(szPalabraLeida);

	for (int longi = 0; longi <= longiPalabraLeida; longi++)
	{
		strcpy_s(szPalabraLeidaModif, TAMTOKEN, szPalabraLeida);
		
		for (int posabc = 0; posabc <= 31; posabc++)
		{
			int posPalabraBase = 0;
			for (int posPalabra = 0; posPalabra <= longiPalabraLeida+1; posPalabra++)
			{
				if (posPalabra == posInterrupcion)
				{
					buffer[posPalabra] = alfabeto[posabc];
				}
				else
				{
					buffer[posPalabra] = szPalabraLeidaModif[posPalabraBase];
					posPalabraBase++;
				}
			}
			strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, buffer);
			iNumSugeridas++;
		}
		posInterrupcion++;
	}
	char auxBurb[TAMTOKEN];
	for (int corrida = 0; corrida < iNumSugeridas-1; corrida++)
	{
		for (int x = 0; x < iNumSugeridas-1; x++)
		{
			if (strcmp(szPalabrasSugeridas[x], szPalabrasSugeridas[x + 1]) > 0)
			{
				strcpy_s(auxBurb, TAMTOKEN, szPalabrasSugeridas[x]);
				strcpy_s(szPalabrasSugeridas[x], TAMTOKEN, szPalabrasSugeridas[x + 1]);
				strcpy_s(szPalabrasSugeridas[x + 1], TAMTOKEN, auxBurb);
			}
		}
	}
}