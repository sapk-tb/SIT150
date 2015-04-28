#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<limits.h>

#define TAILLE 26

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

/* Hashage simple
int hashage(char *mot,int taille)	{
   return (int) (toupper(mot[0])-65)%taille;
}
//*/

int hashage(char *mot,int taille)	{
   int i,hash=0;
   for(i =0; i<strlen(mot);i++)
        hash ^= mot[i];
        
   return hash%taille;
}
//*/

/***********************************************************************/


main(int	argc,	char * argv[])	{
	
   // On utilise la première lettre de mot comme fontion de hashage
   information	*dico[TAILLE], *elm;
   int hash;
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
      
      //INITIALISATION tableau à NULL
      for (i=0;i<TAILLE;i++)
         dico[i] = NULL;
      
      while	(lireMot(fp, &buffer[0])) {
         //printf("%s ", buffer);
         
         hash = hashage(buffer,TAILLE);
         //printf("%d %c\n",hash,buffer[0]);
         
         if	(dico[hash]	==	NULL){
            dico[hash] = malloc(sizeof(information));
            elm =	dico[hash];
         } else {
            elm =	find(dico[hash],buffer);
         }
         
     
      
         if(elm->mot == NULL){
            //Si mot n'est pas définit on est dans une nouvelle case
            elm->mot	= strdup(buffer);
            elm->occurence=1;
         } else{
            //Sinon on incremetne juste le compteur
            elm->occurence++;
         }
        
     // */
         n++;
      }
   		
       
      for (i=0;i<TAILLE;i++){
         elm = dico[i];
         while(elm != NULL){
            printf("\n %s : %d ",elm->mot,elm->occurence);
            elm = elm->suivant;
         }
      }
      
      
      printf("\n\n Il y a %d mots dans %s", n, argv[1]);
      
      
   }
	
   return 0;
	
}