#include <stdlib.h>
#include <stdio.h>
#include <limits.h>



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




/***********************************************************************/


   main(int argc, char * argv[]) {
   
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
         while (lireMot(fp, &buffer[0])) {
            printf("%s ", buffer);
				n++;
         }
			printf("\n\n Il y a %d mots dans %s", n, argv[1]);
      }
   
   }



