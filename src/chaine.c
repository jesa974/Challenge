#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/chaine.h"


/**
 * Supprime les espaces présents dans un char*
 * 
 */
char *trim (char *str) {
	
	char * result ;
	int deb = 0;
	int j = 0 ;
	result = (char *)malloc(sizeof(char)*(longChaine(str)+1)) ;
	
	
	for (int i =0; i<longChaine(str);i++)
	{
		if ((deb == 0) & (str[i] != ' '))
		{
			deb = 1 ;
		}
		
		if ((deb == 1) & (str[i] != ' '))
		{
			result[j] = str[i] ;
			j++ ;
		}
	}
	result[j] = '\0' ;
	return result ;
	
}


char *supprCaract (char *str, char carac) {
	
	char * result ;
	int deb = 0;
	int j = 0 ;
	result = (char *)malloc(sizeof(char)*(longChaine(str)+1)) ;
	
	
	for (int i =0; i<longChaine(str);i++)
	{
		if ((deb == 0) & (str[i] != carac))
		{
			deb = 1 ;
		}
		
		if ((deb == 1) & (str[i] != carac))
		{
			result[j] = str[i] ;
			j++ ;
		}
	}
	result[j] = '\0' ;
	return result ;
	
}


/**
 * Supprime les \n présents dans un char*
 * 
 */
char *suppr (char *str) {
	
	char * result ;
	int deb = 0;
	int j = 0 ;
	result = (char *)malloc(sizeof(char)*(longChaine(str)+1)) ;
	
	
	for (int i =0; i<longChaine(str);i++)
	{
		if ((deb == 0) & (str[i] != '\n'))
		{
			deb = 1 ;
		}
		
		if ((deb == 1) & (str[i] != '\n'))
		{
			result[j] = str[i] ;
			j++ ;
		}
	}
	result[j] = '\0' ;
	return result ;
	
}


char *trim2(char *str)
{
	char *ibuf, *obuf;
	
	if (str)
	{
		for (ibuf = obuf = str; *ibuf; )
		{
			while (*ibuf && (isspace(*ibuf)))
				ibuf++;
			if (*ibuf && (obuf != str))
				*(obuf++) = ' ';
			while (*ibuf && (!isspace(*ibuf)))
				*(obuf++) = *(ibuf++) ;
		}
		*obuf = '\0' ;
	}
	return (str);
}


/**
 * Renvoi la longueur d'une chaine passée en paramètres
 * 
 */
int longChaine(char *chaine)
{
	int i = 0;
	
	while(chaine[i] != '\0')
	{
		i++;
	}
	
	return i;
}


/**
 * Calcule le nombre de séparateurs présent dans une chaine passée en paramètre
 * 
 */
void nbSeparation(char *chaine, int *nbSep, int position[50],char sep)
{
	int i = 0, j = 0;
	
	while(chaine[i] != '\0')
	{	
		if(chaine[i] == sep)
		{
			(*nbSep)++;
			position[j] = i+1;
			j++;
		}
		
		i++;
	}
		
	if(*nbSep == 0)
	{
		position[j] = longChaine(chaine)+1;
		(*nbSep)++;
	}
}


/**
 * Compare deux chaines passées en paramètres
 * 
 */
int compChaine(char *chaine1, char *chaine2)
{
	int verif = 0;
	
	if(longChaine(chaine1) == longChaine(chaine2))
	{
		for(int i = 0;i < longChaine(chaine1); i++)
		{
			if(chaine1[i] == chaine2[i])
			{
				verif++;
			}
			else
			{
				return -1;
			}
		}
	}
	else
	{
		return -1;
	}
	
	if( verif == longChaine(chaine1) && verif == longChaine(chaine2))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


/**
 * Copie 
 * 
 */
void copieChaine(char *dest, char *src)
{
	int i;
	
	for(i = 0;src[i] != '\0'; ++i)
	{
		dest[i] = src[i];
	}
	
	dest[i] = '\0';
}


void concatChaine(char **dest, char *src)
{
	char *result = NULL;
	
	result = (char*)malloc(sizeof(char)*(longChaine(*dest)+longChaine(src)));
	
	copieChaine(result,*dest);
	
	copieChaine(result+longChaine(*dest),src);
	
	/*if(*dest != NULL) {
		free(dest);
		*dest = NULL;
	}*/
	
	*dest = result;
}


/**
 * Initialisation des informations concernant la chaine passée en paramètre
 * 
 */
void chaine(char *chaine, int *lgChaine, int *nbSep, int position[50], char sep)
{	
	if(*nbSep != 0)
	{
		*nbSep = 0;
	}
	
	*lgChaine = longChaine(chaine);
	
	nbSeparation(chaine,nbSep,position,sep);
}


/**
 * Initialise mon tableau de sous-chaine
 * 
 */
void initResult(int *lgChaine, char ***resultat, int position[50], int *nbSep)
{
	(*resultat) = (char **)malloc(sizeof(char *)*(*nbSep + 1));
	
	for(int j = 0;j <= *nbSep; j++)
	{
		if(j == 0)
		{
			(*resultat)[j] = (char *)malloc(sizeof(char)*((position[j]+1)));
		}
		else if(j < *nbSep && j != 0)
		{
			(*resultat)[j] = (char *)malloc(sizeof(char)*(position[j]-position[j-1]+1));
		}
		else
		{
			(*resultat)[j] = (char *)malloc(sizeof(char)*(*lgChaine-position[j-1]+2));
		}
	}
}


/**
 * Créée les sous-chaines
 * 
 */
void sousChaine(char *chaine, int *lgChaine, char **resultat, int position[20], int *nbSep)
{
	int i,j,k;
	
	for(j = 0;j <= *nbSep; j++)
	{
		if(j == 0 && position[j] != 1)
		{
			for(i = 0,k = 0;i < position[j]-1; i++,k++)
			{
				resultat[j][k] = chaine[i];
			}
			
			resultat[j][k] = '\0';
		}
		else if(j < *nbSep && j != 0)
		{
			for(i = position[j-1],k = 0;i < position[j]-1; i++, k++)
			{
				resultat[j][k] = chaine[i];
			}
			
			resultat[j][k] = '\0';
		}
		else if(j == *nbSep)
		{
			for(i = position[j-1],k = 0;i < *lgChaine; i++,k++)
			{
				resultat[j][k] = chaine[i];
			}
			
			resultat[j][k] = '\0';
		}
	}
}


/**
 * Vérifie si la chaine remplie de séparateurs ou non
 * 
 */
int Fill(char *chaine, char sep)
{
	int i,empty = 0;
	
	for(i = 0;i < longChaine(chaine); i++)
	{
		if(chaine[i] == sep)
		{
			empty ++;
		}
		else
		{
			break;
		}
	}
	
	if(empty == longChaine(chaine) && empty != 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


/**
 * Affiche les sous-chaines
 * 
 */
void afficheSousChaine(int nbSep,int posit[nbSep], char **result) {
	for(int i = 0;i <= nbSep; i++)
	{
		if((posit[nbSep] != longChaine(result[i])) && compChaine(result[i],"") != 0)
		{
			printf("Sous chaine %d = %s\n",i,result[i]);
		}
	}
}


void fonct(char *info, char ***R, int *nb, char sep)
{
	int lg = 0,nbSep = 0,posit[50];
	
	char **result;
		
	if(info == NULL)
	{
		//printf("Chaine nulle\n");
	}
	else if(Fill(info,sep) != 0)
	{
		//printf("Chaine remplie de séparateurs\n");
	}
	else if(info[0] != '\0' && info != NULL)
	{
		// SEPARATION SOUS CHAINE
		chaine(info,&lg,&nbSep,posit,sep);
			
		initResult(&lg,&result,posit,&nbSep);
				
		sousChaine(info,&lg,result,posit,&nbSep);
		
		*R = result;
		*nb = nbSep;
	}
	else
	{
		//printf("Chaine vide\n");
	}
}


/**
 * Compte le nombre de ligne d'informations dans un fichier csv
 * 
 */
int cpt_ligne(char *nomfichier) {
	FILE* csv;
	int lig = 0;
	char c = 0;
	
	csv = fopen(nomfichier, "rt");
	
	// Compte du nombre de lignes
	while(c != EOF){
		c = getc(csv);

		if (c == '\n') {
			lig++; // On incremente le nombre de lignes lues
		}
	}
	fclose(csv);
		
	return lig-1;
}


int ordreAlpha(char *s1,char *s2){
	int etat = -1;
	int Ls1 = longChaine(s1);
	int Ls2 = longChaine(s2);
	
	if(Ls1<=Ls2) {
		
		for(int i = 0;i < Ls1; i++) {
			
			if(s1[i] < s2[i]) {
				etat = 1;
				return etat;
			} else if(s1[i] > s2[i]) {
				etat = 2;
				return etat;
			} else if(s1[i] == s2[i]) {
				etat = 0;
			}
		}
	} else {
		
		for(int i = 0;i < Ls2; i++){
			if(s1[i] < s2[i]) {
				etat = 1;
				return etat;
			} else if(s1[i] > s2[i]) {
				etat = 2;
				return etat;
			} else if(s1[i] == s2[i]) {
				etat = 0;
			}
		}
	}
	
	if(Ls1 > Ls2 && etat == 0){
		etat = 2;
	}
	
	if(Ls1 < Ls2 && etat == 0){
		etat = 1;
	}
	
	return etat;
}









/*int ordreAlph(char *str1, char *second) {
	int result = -1;
	int lg1 = longChaine(str1);
	int lg2 = longChaine(second);
	
	char *tab_str1 = (char*)malloc(sizeof(char)*lg1);
	char *tab_second = (char*)malloc(sizeof(char)*lg2);
	
	for(int i = 0;i < lg1; i++) {
		tab_str1[i] = str1[i];
	}
	
	for(int j = 0;j < lg2; j++) {
		tab_second[j] = second[j];
	}
	
	if(compChaine(str1,second) == 0) {
		result = 0;
	} else {
		if(lg1 < lg2) {
			
		} else if (lg1 > lg2) {
			
		} else {
			
		}
	}
	
	return result;
}*/
