#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include "tris.h"
#include "data.h"


/* Type des données à trier */
#define UNKNOWN  0
#define FICHIER 1
#define RANDOM  2
#define TRIE    3
#define TRIE_INVERSE 4


/* Type de tri à utiliser */
/* Numéro XY, X pour la famille, Y pour la version */
#define BULLE_NAIF 11
#define BULLE_BOOL 12
#define BULLE_OPT  13 
#define SELECTION  2
#define INSERTION  3
#define TRIRAPIDE  4



/* -------------------------------------------------------------------------- */
/* analyse_complexite                                                         */
/* void analyse_complexite(complexiteDef *complexite, char * tri)             */
/*                                                                            */
/* Afficher les différentes options du programme [nom]                        */
/*                                                                            */
/* Entrées :                                                                  */
/*        [complexite] : le résultat en terme de complexité du tri            */
/*        [tri] : le nom du tri                                               */
/*        [n]   : le nombre d'éléments triés                                  */
/* -------------------------------------------------------------------------- */
/* Old
   void analyse_complexite(structSondes sondes, char *tri, int n)
   {
      printf("\nAnalyse de la complexite du tri %s de %d entiers\n", tri, n);
      printf("\t  nombre de comparaisons = %d\n", sondes.nb_comparaisons);
      printf("\t  nombre de copies       = %d\n", sondes.nb_copies); 
      printf("\t  nombre d'échanges      = %d\n", sondes.nb_echanges); 
   }
*/
   void analyse_complexite(structSondes sondes, char *tri, int n)
   {
      printf("\nAnalyse de la complexite du tri %s de %d entiers\n", tri, n);
      printf("\t  nombre de comparaisons = %lu\n", sondes.nb_comparaisons);
      printf("\t  nombre de copies       = %lu\n", sondes.nb_copies); 
      printf("\t  nombre d'échanges      = %lu\n", sondes.nb_echanges); 

      printf("\n%s\n%d\n%lu\n%lu\n%lu\n", tri, n , sondes.nb_comparaisons , sondes.nb_copies , sondes.nb_echanges);
   }


/* -------------------------------------------------------------------------- */
/* aide                                                                       */
/* int aide(char * nom)                                                       */
/*                                                                            */
/* Afficher les différentes options du programme [nom]                        */
/*                                                                            */
/* Entrées :                                                                  */
/*        [nom] : le nom de l'exécutable                                      */
/* -------------------------------------------------------------------------- */

   void aide(char *nom)
   {
      printf("\nUtilisation :\n\n  %s [options]\n", nom);
   
      printf("\nOptions :\n");
      printf("\n[1] Pour les données (des entiers):\n");
      printf("\n  - lues dans un Fichier texte : -f nom_fichier\n");
      printf("\n    où nom_fichier est le nom d'un fichier texte de la forme\n");
      printf("\n      nombre_elements");
      printf("\n      entier1");
      printf("\n      entier2");
      printf("\n      ...");
      printf("\n      entiern");
      printf("\n");
      printf("\n   - crées Aléatoirement   : -a nombre_elements\n");
      printf("\n    où nombre_elements est le nombre d'éléments du tableau créé\n");
      printf("\n");
      printf("\n   - déjà triées (Meilleur des Cas) : -mc nombre_elements\n");
      printf("\n    où nombre_elements est le nombre d'éléments du tableau créé\n");
      printf("\n");
      printf("\n   - triées dans l'ordre inverse (Pire des Cas) : -pc nombre_elements\n");
      printf("\n    où nombre_elements est le nombre d'éléments du tableau créé\n");
      printf("\n");
      printf("\n   - pour sauver la tableau initial dans un fichier texte : -si nom_fichier\n");
      printf("\n    où nom_fichier est le nom d'un fichier\n");
      printf("\n");
      printf("\n   - pour sauver la tableau final dans un fichier texte : -sf nom_fichier\n");
      printf("\n    où nom_fichier est le nom d'un fichier\n");
      printf("\n");
      printf("\n[2] Pour l'algorithme de Tri :");
      printf("\n  -t algo\n");
      printf("\n    où algo = bulle_naif, bulle_bool, bulle_opt, selection, insertion, rapide\n");
      printf("\n");
      printf("\nExemples :\n\n");
      printf("\n  données lues dans le fichier tab1.dat et triées avec bulle naïf");
      printf("\n    -f tab1.dat -t bulle_naif\n");
      printf("\n    -t bulle_naif -f tab1.dat\n\n");
      printf("\n  10 données créées aléatoirement et triées avec insertion");
      printf("\n    -a 10 -t insertion\n");
      printf("\n    -t insertion -a 10\n\n");
      printf("\n  8 données dans l'ordre inverse, triées avec tri rapide, sauvées dans tab1.dat");
      printf("\n    -pc 8 -t rapide -sf tab1.dat\n");
      printf("\n");
      printf("\n[3]  Pour afficher ou non les tableaux : ");
		printf("\n    -v   (par défaut on n'affiche pas)\n");
      printf("\n");
   }





/* -------------------------------------------------------------------------- */

   int main(int argn, char *argv[])
   {
      int type_data;
      int type_tri;
      int sauvegarde_tableau_initial;
      int sauvegarde_tableau_final;
      int affichage_tableaux;
      int n = 0;
      char *fichier_lecture_tableau_initial, *fichier_sauvegarde_tableau_initial, *fichier_sauvegarde_tableau_final;
      int *tab;
      int i;
   
   
      structSondes sondes = {0, 0, 0};
   
      if (argn == 1) 
      {
         aide(argv[0]);
         exit(1);
      }
   
      type_data = UNKNOWN;
      type_tri = UNKNOWN;
      sauvegarde_tableau_initial = FALSE;
      sauvegarde_tableau_final = FALSE;
      affichage_tableaux = FALSE;
   
      for ( i = 1; i < argn; i+=2 )
      {
      	// choix des données à trier et des sauvegardes éventuelles du tableau initial et final
         if (strcmp("-f", argv[i]) == 0)
         {
            fichier_lecture_tableau_initial = (char *) malloc(1 + strlen(argv[i+1]) * sizeof(char));
            strcpy(fichier_lecture_tableau_initial, argv[i+1]);
            type_data = FICHIER;
            continue;
         }
      
         if (strcmp("-si", argv[i]) == 0)
         {
            fichier_sauvegarde_tableau_initial = (char *) malloc(1 + strlen(argv[i+1]) * sizeof(char));
            strcpy(fichier_sauvegarde_tableau_initial, argv[i+1]);
            sauvegarde_tableau_initial = TRUE;
            continue;
         }
      
         if (strcmp("-sf", argv[i]) == 0)
         {
            fichier_sauvegarde_tableau_final = (char *) malloc(1 + strlen(argv[i+1]) * sizeof(char));
            strcpy(fichier_sauvegarde_tableau_final, argv[i+1]);
            sauvegarde_tableau_final = TRUE;
            continue;
         }
      
         if (strcmp("-a", argv[i]) == 0)
         {
            n = atoi(argv[i+1]);
            type_data = RANDOM;
            continue;
         }
      
         if (strcmp("-mc", argv[i]) == 0)
         {
            n = atoi(argv[i+1]);
            type_data = TRIE;
            continue;
         }
      
         if (strcmp("-pc", argv[i]) == 0)
         {
            n = atoi(argv[i+1]);
            type_data = TRIE_INVERSE;
            continue;
         }

      
       	// choix de l'algorithme de tri
         if (strcmp("-t", argv[i]) == 0)
         {
            if (strcmp("bulle_naif", argv[i+1]) == 0)
               type_tri = BULLE_NAIF;
            
            else if (strcmp("bulle_bool", argv[i+1]) == 0)
               type_tri = BULLE_BOOL;
            
            else if (strcmp("bulle_opt", argv[i+1]) == 0)
               type_tri = BULLE_OPT;
            
            else if (strcmp("selection", argv[i+1]) == 0)
               type_tri = SELECTION;
            
            else if (strcmp("insertion", argv[i+1]) == 0)
               type_tri = INSERTION;
            
            else if (strcmp("rapide", argv[i+1]) == 0)
               type_tri = TRIRAPIDE;
            	
            else 
            {
	       printf("\n le tri demandé < %s >  n'existe pas \n", argv[i+1]);
               aide(argv[0]);
               exit(1);
            }
            continue;
         }

      
       	// choix de la visualisation (affichage) du tableau initial et final
         if (strcmp("-v", argv[i]) == 0)
         {
            affichage_tableaux = TRUE;
            i--;
            continue;
         }
      	
			printf("\n l'option demandée < %s >  n'existe pas \n", argv[i]);
         aide(argv[0]);	
			exit(1);
      }
	if(type_data == FICHIER)
	   	tab = f_lire_data(fichier_lecture_tableau_initial, &n);

   	if (n < 1) {
			printf("\n le nombre d'éléments à trier est incorrect : %d \n", n);
         aide(argv[0]);	
			exit(1);
		}
   
   
      switch(type_data)
      {
         case TRIE:
            {
               tab = data_triee(n);
               printf("Tableau initial trié (meilleur des cas)");
               break;
            }
         
         case TRIE_INVERSE:
            {
               tab = data_triee_inverse(n);
               printf("Tableau intial trié en ordre inverse (pire des cas)");
               break;
            }
         case FICHIER:
            {
               tab = f_lire_data(fichier_lecture_tableau_initial, &n);
               printf("Tableau initial lu dans %s", fichier_lecture_tableau_initial);
               break;
            }
         case RANDOM:
            {
               tab = random_data(n);
               printf("Tableau initial aléatoire");
               break;
            }
         case UNKNOWN:
            aide(argv[0]);
            exit(1);
      }
   
      if (sauvegarde_tableau_initial == TRUE)
         f_ecrire_data(fichier_sauvegarde_tableau_initial, tab, n);
   
   
      if (affichage_tableaux == TRUE) {
         printf("\n");
         ecrire_data(tab,  n);
      }
   
      switch(type_tri)
      {
         case BULLE_NAIF: 
            sondes = tri_bulle_naif(tab, n);
            if (affichage_tableaux == TRUE) {
               printf("Tableau trié (bulle naïf)\n");
               ecrire_data(tab,  n);
            }
            analyse_complexite(sondes, "bulle naïf", n);
            break;
         case BULLE_BOOL: 
            sondes = tri_bulle_bool(tab, n);
            if (affichage_tableaux == TRUE) {
               printf("Tableau trié (bulle bool)\n");
               ecrire_data(tab,  n);
            }
            analyse_complexite(sondes, "bulle bool", n);
            break;
         case BULLE_OPT: 
            sondes = tri_bulle_opt(tab, n);
            if (affichage_tableaux == TRUE) {
               printf("Tableau trié (bulle opt)\n");
               ecrire_data(tab,  n);
            }
            analyse_complexite(sondes, "bulle opt", n);
            break;
         case SELECTION:
            sondes = tri_selection(tab, n);
            if (affichage_tableaux == TRUE) {
               printf("Tableau trié (selection)\n");
               ecrire_data(tab,  n);
            }
            analyse_complexite(sondes, "selection", n);
            break;
         case INSERTION:
            sondes = tri_insertion(tab, n);
            if (affichage_tableaux == TRUE) {
               printf("Tableau trié (insertion)\n");
               ecrire_data(tab,  n);
            }
            analyse_complexite(sondes, "insertion", n);
            break;
         case TRIRAPIDE:
            sondes = tri_rapide(tab, 0, n-1);
            if (affichage_tableaux == TRUE) {
               printf("Tableau trié (rapide)\n");
               ecrire_data(tab,  n);
            }
            analyse_complexite(sondes, "rapide", n);
            break;
         case UNKNOWN:
            aide(argv[0]);
            exit(1);
      }
   
   
      if (sauvegarde_tableau_final == TRUE)
         f_ecrire_data(fichier_sauvegarde_tableau_final, tab, n);
   
      printf("\n");
      return 0;
   }


