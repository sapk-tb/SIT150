#include "tris.h"
#include <stdio.h>

void echanger(int *t, int n1, int n2){
	int tmp;
	tmp = t[n1];
	t[n1] = t[n2];
	t[n2] = tmp;
};

structSondes tri_bulle_naif(int *t, int n){
	int i,tour;
	structSondes result = {0, 0, 0};
	for(tour=0;tour<n-2;tour++){
		for(i=n-1;i>=tour+1;i--){
			//printf("%d",i);
			if(t[i]<t[i-1]) {
				echanger(t, i, i-1);
				result.nb_echanges++;
			}
			result.nb_comparaisons++;
		}
	}
	result.nb_copies = result.nb_echanges *3;
	return result;
};
structSondes tri_bulle_bool(int *t, int n){
	int i,tour,echange_prec=-1;
	structSondes result = {0, 0, 0};
	for(tour=0;tour<n-2;tour++){
		//printf("\n echange : %lu \n ",result.nb_echanges);
		//printf("\n echange précédent : %d \n ",echange_prec);
		if(echange_prec!=result.nb_echanges){
			echange_prec=result.nb_echanges;
			for(i=n-1;i>=tour+1;i--){
				//printf("%d",i);
				if(t[i]<t[i-1]) {
					echanger(t, i, i-1);
					result.nb_echanges++;
				}
				result.nb_comparaisons++;
			}
		}
	}
	result.nb_copies = result.nb_echanges *3;
	return result;
};
structSondes tri_bulle_opt(int *t, int n){
	int i,tour,tmp,tmp2,echange_prec=-1,dernier_ech=0;
	structSondes result = {0, 0, 0};
	for(tour=0;tour<n-2;tour++){
		if(echange_prec!=result.nb_echanges){
			//printf("der_ech : %d\n",dernier_ech);
			tmp2 = dernier_ech;
			echange_prec=result.nb_echanges;
			for(i=n-1;i>=tmp2+1;i--){
				//printf("%d",i);
				if(t[i]<t[i-1]) {
					echanger(t, i, i-1);
					result.nb_echanges++;
					dernier_ech=i;
				}
				result.nb_comparaisons++;
			}
		}
	}
	result.nb_copies = result.nb_echanges *3;
	return result;
};

structSondes tri_insertion(int *t, int n){
	int i,tour,j,key;
	structSondes result = {0, 0, 0};
	for(j=1;j<n;j++){
		result.nb_copies++;
		key = t[j];
		i = j-1;
		result.nb_comparaisons++;
		while(i>=0 && t[i]>key){
			result.nb_comparaisons++;
			result.nb_copies++;
			t[i+1]=t[i];
			i--;
		} 
		result.nb_copies++;
		t[i+1]=key;
	}
	return result;

};
structSondes tri_selection(int *t, int n){
	structSondes result = {0, 0, 0};
	long unsigned int min,i,j;
	for(i=0;i<n-1;i++){
		result.nb_copies++;
		min=i;
		for(j=i+1;j<n;j++){
			result.nb_comparaisons++;
			if(t[j]<t[min]){
				result.nb_copies++;
				min=j;
			}
		}

		if(min != i){
			result.nb_echanges++;
			echanger(t, i, min);	
		}
	}
	result.nb_copies += result.nb_echanges *3;
	return result;

};

structSondes tri_rapide(int *t, int debut, int fin){
	structSondes r1,r2,result = {0, 0, 0};
    	int gauche = debut-1;
    	int droite = fin+1;
	int pivot = t[debut];
	//printf(":%d %d %d :\n", debut, fin,pivot);
	// Si le tableau est de longueur nulle, il n'y a rien à faire.

	result.nb_comparaisons++;
	if(debut >= fin)
		return result;

	while(1)   {
		do {
			result.nb_comparaisons++;
			droite--; 
		}while(t[droite] > pivot);

		do {
			result.nb_comparaisons++;
			gauche++; 
		}while(t[gauche] < pivot);

		result.nb_comparaisons++;
		if(gauche < droite){
			result.nb_echanges++;
		    	echanger(t, gauche, droite);
		}	
		else 
			break;
	}
	//printf("\\ %lu %lu\n",result.nb_comparaisons,result.nb_echanges);

	r1 = tri_rapide(t, debut, droite);
	r2 = tri_rapide(t, droite+1, fin);

	//printf("\nR1 %d %d %lu %lu\n",debut, droite,r1.nb_comparaisons,r1.nb_echanges);
	//printf("\nR2 %d %d %lu %lu\n",droite+1, fin,r2.nb_comparaisons,r2.nb_echanges);

	result.nb_echanges += r1.nb_echanges + r2.nb_echanges;
	result.nb_comparaisons += r1.nb_comparaisons + r2.nb_comparaisons;
	result.nb_copies += r1.nb_copies + r2.nb_copies;
	
	result.nb_copies += 3*result.nb_echanges;
	return result;
};

