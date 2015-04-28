#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<limits.h>

#define TAILLE 26*26

typedef struct	Information	{
   char * mot;
   int occurence;
   struct Information *	suivant;
   struct Information *	precedent;
} information;

/***********************************************************************/


void afficher_information(information *obj) {

	//printf("\n#### %p %s %d %p %p\n",obj,obj->mot,obj->occurence,obj->suivant,obj->precedent);
	printf("\n#### %s : %d\n",obj->mot,obj->occurence);
	
}	

int hashage(char *mot,int taille)	{
   //return (int) (toupper(mot[0])-65)%taille;
   return (int) ((toupper(mot[0])-65)*(toupper(mot[0])-65))%taille;
}

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

information	* new (char * mot,information * prec,information * suiv){
   information * elm = malloc(sizeof(information));
   elm->mot = strdup(mot);
   elm->occurence = 1;
   elm->precedent = prec;
   elm->suivant = suiv;
   //printf("\n Create : %s ",elm->mot);
   return elm;
}

information	* find_or_create (information * dico,char * mot){
   // On vérifie pour un par un les éléments.
   int order = 0;

    while(1){
      //afficher_information(dico);

      if(strcmp (dico->mot,mot) > 0 ){
	//printf("SUP\n");
	//Si le dico courant contient un mot supérieur alpha au mot cherché.
	if(dico->precedent == NULL ){
		// Si pas d'élément précédent
            	dico = new(mot,NULL,dico);
		(dico->suivant)->precedent=dico;
		return dico;
	}else if(order==1){
		//Si on était dans le cas inverse précédement 
            	dico = new(mot,dico->precedent,dico);
		(dico->precedent)->suivant=dico;
		(dico->suivant)->precedent=dico;
		return dico;
	}

	//printf("UP\n");
        dico = dico->precedent;
	order=-1;

      }else if(strcmp (dico->mot,mot) < 0 ){
	//printf("INF\n");
	//Si le dico courant contient un mot inférieur alpha au mot cherché.
	if(dico->suivant == NULL ){
		// Si pas d'élément suivant
            	dico = new(mot,dico,NULL);
		(dico->precedent)->suivant=dico;
		return dico;
	}else if(order==-1){
		//Si on était dans le cas inverse précédement 
            	dico = new(mot,dico,dico->suivant);
		(dico->precedent)->suivant=dico;
		(dico->suivant)->precedent=dico;
		return dico;
	}

	//printf("DOWN\n");
        dico = dico->suivant;
	order=1;
      }else{
	 //Si le dico courant contient un mot égal alpha au mot cherché donc il existe déjà dans la liste.
	 //printf("FIND\n");
	 dico->occurence++;
         return dico;
      }
   }
}

/***********************************************************************/


main(int	argc,	char * argv[])	{
	
   information	* dico = NULL;
   information	* hash[TAILLE];
   FILE *fp;
	
   if	(argc	< 2)
      return;
	
   if	((fp = fopen(argv[1], "r")) == NULL) {
      printf("\n Pb d'ouverture du fichier %s \n",	argv[1]);
      return;
   } 
   else {
      char buffer[512];
      int i,n=0;
      
      
      while	(lireMot(fp, &buffer[0])) {
         //printf("%s ", buffer);
         
         if (dico == NULL){
            //printf("\n INIT");
            dico = new(buffer,NULL,NULL);
	    for(i=0;i<TAILLE;i++){
		hash[i] = malloc(sizeof(information*));
	    	hash[i] = dico;
	    }

         } else {
            //printf("\n find_or_create : %s ",buffer);
	    dico = hash[hashage(buffer,TAILLE)];
            dico = find_or_create(dico,buffer);
	    hash[hashage(buffer,TAILLE)]= dico;
         }

	 //afficher_information(dico);
         n++;
      }


     // printf("\n RESET TO START");
      while(dico->precedent != NULL){
	//afficher_information(dico);
	dico = dico->precedent;
      }
      
      printf("\n PRINT ALL");
      do {
	afficher_information(dico);
	dico = dico->suivant;
      } while(dico != NULL) ;

      printf("\n\n Il y a %d mots dans %s", n, argv[1]);
      
      
   }

   return 0;
	
}



