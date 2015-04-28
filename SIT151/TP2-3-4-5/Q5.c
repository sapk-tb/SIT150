#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<limits.h>

typedef struct	Information	{
   char * mot;
   int occurence;
   struct Information *	suivant;
} information;

/***********************************************************************/
	

int lireMot(FILE * fp, char *	mot) {
   int i;
   char c;
   while	( ! (isalpha (c =	fgetc(fp)))) {
      if	 (c == EOF)	{
         mot[0] =	'\0';
         return 0;
      }
   }
   mot[0] =	c & 0xdf;
   i = 1;
   while	( isalpha (c =	fgetc(fp)))	{
      mot[i] =	c & 0xdf;
      i++;
   }
   mot[i] =	'\0';
   return 1;
}


information	* find (information * dico,char * mot){
   // On vérifie pour un par un les éléments.
   while(dico->suivant	!=	NULL){
      
      if(strcmp (dico->mot,mot) == 0 ){
         break;
      }
      
      dico = dico->suivant;
   }
   
   // On vérifie pour le dernier élément qui n'a pas d'élément suivant.
   if(strcmp (dico->mot,mot) != 0 ){
      dico->suivant = malloc(sizeof(information));
      dico = dico->suivant;		
   }
   
   return dico;
}


/***********************************************************************/


main(int	argc,	char * argv[])	{
	
   information	*dico = NULL, *elm = NULL;
   FILE *fp;
	
   if	(argc	< 2)
      return;
	
   if	((fp = fopen(argv[1], "r")) == NULL) {
      printf("\n Pb d'ouverture du fichier %s \n",	argv[1]);
      return;
   } 
   else {
      char buffer[512];
      int n	= 0;
      int i;
      while	(lireMot(fp, &buffer[0])) {
         //printf("%s ", buffer);
      	//	Trouve l'occurence du mot ou la dernière case du tableau ou initialise dico
         if	(dico	==	NULL){
            dico = malloc(sizeof(information));
            elm =	dico;
         } 
         
         else {
            elm =	find(dico,buffer);
         }
      
         if(elm->mot == NULL){
            //Si mot n'est pas définit on est dans une nouvelle case
            elm->mot	= strdup(buffer);
            elm->occurence=1;
         } else{
            //Sinon on incremente juste le compteur
            elm->occurence++;
         }
         
      
         n++;
      }
      printf("\n\n Il y a %d mots dans %s", n, argv[1]);
   		
         
      elm = dico;
      while(elm != NULL){
         printf("\n %s : %d ",elm->mot,elm->occurence);
         elm = elm->suivant;
      }
      
   }
	
   return 0;
	
}



