#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct {
   char * mot;
   int occurence;
} information;

/***********************************************************************/
	

   int lireMot(FILE * fp, char * mot) {
      int i;
      char c;
      while ( ! (isalpha (c = fgetc(fp)))) {
         if  (c == EOF) {
            mot[0] = '\0';
            return 0;
         }
      }
      mot[0] = c & 0xdf;
      i = 1;
      while ( isalpha (c = fgetc(fp))) {
         mot[i] = c & 0xdf;
         i++;
      }
      mot[i] = '\0';
      return 1;
   }


   int find (information * dico,char * mot, int nb_dico){
       int i;
       for(i = 0; i < nb_dico; i++){
         if(strcmp (dico[i].mot,mot) == 0 ){
             break;
         }
      }
      return i;
   }


/***********************************************************************/


   main(int argc, char * argv[]) {
   
      information dico[5120];
      int nb_dico=0;
      FILE *fp;
   
      if (argc < 2)
         return;
   
      if ((fp = fopen(argv[1], "r")) == NULL) {
         printf("\n Pb d'ouverture du fichier %s \n", argv[1]);
         return;
      } 
      else {
         char buffer[512];
			int n = 0;
         int i;
         while (lireMot(fp, &buffer[0])) {
            //printf("%s ", buffer);
            // Trouve l'occurence du mot ou la dernière case du tableau
            int i = find(dico,buffer,nb_dico);
            if(i == nb_dico){
               nb_dico++;
               dico[i].mot = strdup(buffer);
               dico[i].occurence=1;
            }else{
               dico[i].occurence++;
            }
            

				n++;
         }
			printf("\n\n Il y a %d mots dans %s", n, argv[1]);
         
         for(i = 0; i < nb_dico; i++){
            printf("\n %s : %d ",dico[i].mot,dico[i].occurence);
         }
      }
   
   	return 0;
	
   }



