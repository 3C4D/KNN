/* Fichier source contenant les fonctions de test permettant de juger de */
/* l'efficacité des différentes algorithmes de calcul des KPPV */

#include <stdlib.h>
#include <stdio.h>
#include "time.h"
#include "erreur.h"
#include "generation.h"
#include "arbre.h"
#include "kppv.h"
#include "recherche.h"

/* Fonction usage de l'exécutable benchmark */
void usage(char *str){
  fprintf(stderr, "\nUsage : %s <nbpoint> <dimension> <nbclasse> <debug>\n", str);
  fprintf(stderr, "\t<nbpoint> : entier positif non nul\n");
  fprintf(stderr, "\t<dimension> : entier positif supérieur à 1\n");
  fprintf(stderr, "\t<nbclasse> : entier positif non nul\n");
  fprintf(stderr, "\t<debug> : 0 -> classique | 1 -> debug\n\n");

  exit(-1);
}

/* Fonction faisant un comparatif entre les deux algorithmes */
void benchmark(int nbpoints, int dimension, int nbclasse, int debug){

  /* On génère un tableau aléatoire */
  TabPts *tab_tmp = generation_tableau_alea(nbpoints, dimension, nbclasse);
  TabPts *kppv;
  arbre_kd a_tmp = creer_arbre_kd(tab_tmp);
  point pt_k;
  clock_t begin, end;
  double duree_tab, duree_arbre;

  srand(time(NULL));  /* Initialisation de l'horloge servant au hasard */

  /* Génération d'un point au hasard dont on voudra connaitre les KPPV */
  pt_k = generation_pt_alea(dimension, nbclasse);

  if(debug){  /* debug */
    printf("\n################# DEBUG ################\n\n");
    printf("########## Affichage du tableau de point :\n\n");
    afficher_tab_pts(*tab_tmp);
    printf("\n########## Affichage de l'arbre_kd :\n\n");
    afficher_arbre_bis(a_tmp);
  }

  /* Mesure du temps pour le premier algorithme (tableaux)*/
  begin = clock();  /* Démarrage du chronomètre */
  kppv = trouver_kppv_tab(tab_tmp, pt_k, nbpoints/2);
  end = clock();    /* Fin du chronomètre */
  duree_tab = ((float) end - begin) / CLOCKS_PER_SEC;

  if(debug){  /* debug */
    printf("Tableau : \n");
    afficher_tab_pts(*kppv);
  }

  /* Mesure du temps pour le second algorithme (arbres) */
  begin = clock();  /* Démarrage du chronomètre */
  kppv = recherche(a_tmp, &pt_k, nbpoints/2, nbclasse);
  end = clock();    /* Fin du chronomètre */
  duree_arbre = ((float) end - begin) / CLOCKS_PER_SEC;

  if(debug){  /* debug */
    printf("Arbre : \n");
    afficher_tab_pts(*kppv);
  }

  /* Affichage des temps d'exécution */
  printf("\nTemps d'exécution pour les tableaux : %f secondes\n\n", duree_tab);
  printf("Temps d'exécution pour les arbres : %f secondes\n\n", duree_arbre);
}
