/* Fichier source contenant les fonctions relatives aux arbres */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "erreur.h"
#include "arbre.h"

/* Permet de renvoyer un arbre vide */
arbre_kd creer_arbre_vide(){
  return NULL;    /* L'arbre vide correspond à la valeur NULL */
}

/* Permet de déterminer si un arbre est vide */
int est_vide_arbre_kd(arbre_kd arbre){
  return (arbre == NULL);   /* Un arbre est vide si il équivaut à NULL */
}

/* Permet de creer un noeud à partir de sa racine (ie un point) */
arbre_kd creer_noeud(point *pt){
  arbre_kd arbre = creer_arbre_vide();    /* Crée un noeud vide */

  arbre = (Noeud *)malloc(sizeof(Noeud)); /* Allocation du noeud */
  if(arbre == creer_arbre_vide()){        /* Vérification de l'allocation */
    erreur("Erreur d'allocation dans la fonction creer_noeud");
  }

  arbre->racine = pt;                     /* Insertion de la valeur du noeud */
  arbre->fils_g = creer_arbre_vide();     /* Met à vide le fils gauche */
  arbre->fils_d = creer_arbre_vide();     /* Met à vide le fils droit*/
  return arbre;                           /* On retourne le noeud obtenu */
}

/* Permet de creer un arbre à partir de sa racine et de ses fils*/
arbre_kd creer_arbre(point *pt, arbre_kd fils_gauche, arbre_kd fils_droit){
  arbre_kd arbre = creer_noeud(pt);       /* Création du noeud */

  arbre->fils_g = fils_gauche;            /* Insertion du fils gauche */
  arbre->fils_d = fils_droit;             /* Insertion du fils droit */

  return arbre;                           /* On retrourne l'arbre */
}

/* Permet de renvoyer la racine */
point *racine(arbre_kd arbre){
  return arbre->racine;
}

/* Permet de renvoyer le fils gauche */
arbre_kd renvoyer_fils_gauche(arbre_kd arbre){
  return arbre->fils_g;         /* On renvoie le fils droit */
}

/* Permet de renvoyer le fils droit */
arbre_kd renvoyer_fils_droit(arbre_kd arbre){
  return arbre->fils_d;         /* On renvoie le fils droit */
}

/* Permet d'insérer le fils gauche d'un arbre */
arbre_kd inserer_fils_gauche(arbre_kd arbre, arbre_kd fils_gauche){
  arbre->fils_g = fils_gauche;  /* On Insère le fils gauche */
  return arbre;                 /* On retourne l'arbre */
}

/* Permet d'insérer le fils droit d'un arbre */
arbre_kd inserer_fils_droit(arbre_kd arbre, arbre_kd fils_droit){
  arbre->fils_d = fils_droit;   /* On Insère le fils droit */
  return arbre;                 /* On retourne l'arbre */
}

/* Permet de déterminer si un noeud est une feuille */
int est_feuille(arbre_kd arbre){
  if(est_vide_arbre_kd(arbre)){  /* Si le noeud est vide il y a une erreur */
    erreur("Erreur, arbre vide passé en paramètre, fonction est_feuille");
  }
  /* Si les deux fils sont vides le noeud est une feuille */
  if(est_vide_arbre_kd(arbre->fils_g) && est_vide_arbre_kd(arbre->fils_d)){

  }
  return 0;           /* Sinon le noeud n'est pas une feuille */
}

/* Permet de détruire un arbre */
void detruire_arbre(arbre_kd arbre){
  if(est_feuille(arbre)){ /* Si l'arbre est une feuille on le libère */
    free(arbre);
  }
  else{     /* Sinon on libère ses fils non vides */
    /* On libère le fils gauche si il n'est pas vide */
    if(!est_vide_arbre_kd(renvoyer_fils_gauche(arbre))){
      detruire_arbre(renvoyer_fils_gauche(arbre));
    }
    /* On libère le fils droit si il n'est pas vide */
    if(!est_vide_arbre_kd(renvoyer_fils_droit(arbre))){
      detruire_arbre(renvoyer_fils_droit(arbre));
    }
    free(arbre);    /* Enfin on libère l'arbre lui-même */
  }
}

/* Fonction auxiliaire récursive permettant de construire un arbre kd */
/* à partir d'un tableau de point */
arbre_kd creer_arbre_kd_aux(TabPts *tab, int debut, int fin, int prof, int axe){
  int mediane;                                /* Calcul de l'index median */
  if(fin-debut % 2 != 0){
    mediane = (fin-debut)/2;
  }
  else{
    mediane = ((fin-debut)-1)/2;
  }

  if(mediane == 0){                           /* Si l'intervalle est de 0 : */
    return creer_noeud(&tab->tab[debut]);     /* On retourne la feuille */
  }

  /* On trie l'intervalle selon l'axe */
  tri_tab(tab->tab, debut, fin, prof%axe);

  /* Cas particulier si on a un intervalle de 2 */
  if(fin == debut+2){                       /* Cas particuler: deux élements */
    return creer_arbre(&tab->tab[debut+mediane],
                       creer_noeud(&tab->tab[debut]),
                       creer_arbre_vide()
                     );
  }

  if(fin == debut+3){                     /* Cas particuler: trois élements */
    return creer_arbre(&tab->tab[debut+mediane],
                       creer_noeud(&tab->tab[debut]),
                       creer_noeud(&tab->tab[fin-1])
                     );
  }

  /* On renvoie l'arbre créé en rappellant la fonction sur ses fils : */
  /* Légende : D : Debut, M : Mediane, F : Fin */
  return creer_arbre(&tab->tab[debut+mediane],
                     creer_arbre_kd_aux(tab,  /* Intervalle : D -> D+M-1 */
                                        debut,
                                        debut+mediane,
                                        prof+1,
                                        axe),
                     creer_arbre_kd_aux(tab,  /* Intervalle : D+M+1 -> F */
                                        debut+mediane+1,
                                        fin,
                                        prof+1,
                                        axe)
                    );
}

/* Permet de construire un arbre_kd à partir d'un tableau de points */
arbre_kd creer_arbre_kd(TabPts *tab){
  /* On retourne l'arbre créé recursivement */
  return creer_arbre_kd_aux(tab, 0, tab->taille, 0, tab->dimension);
}

/* Fonction auxiliaire recursive permettant d'inserer un point dans un */
/* arbre kd */
arbre_kd insere_aux(arbre_kd arbre, point *pt, int prof, int axe){

  if(est_vide_arbre_kd(arbre)){ /* Si l'arbre est vide : on renvoie le noeud */
    return creer_noeud(pt);
  }
  /*Sinon, on envoie le point sur l'un des deux fils en fonction de l'axe*/
  else{
    if(racine(arbre)->coord[prof%axe] > pt->coord[prof%axe]){
      return inserer_fils_gauche(arbre, /* Fils gauche si l'axe est inférieur */
                                 insere_aux(renvoyer_fils_gauche(arbre),
                                            pt,
                                            prof+1,
                                            axe)
                                );
    }
    else{
      return inserer_fils_droit(arbre, /* Fils droit sinon */
                                 insere_aux(renvoyer_fils_droit(arbre),
                                            pt,
                                            prof+1,
                                            axe)
                                );
    }
  }
}

/* Fonction permettant d'inserer un point dans un arbre kd */
arbre_kd insere(arbre_kd arbre, point *pt){
  /* On retourne l'arbre une fois le point inséré recursivement */
  return insere_aux(arbre, pt, 0, pt->dimension);
}

/* Permet d'afficher un arbre recursivement */

void afficher_arbre(arbre_kd arbre){
  /* Si l'arbre n'est pas vide on affiche sa racine */
  if(!est_vide_arbre_kd(arbre)){
    afficher_pt(*racine(arbre), racine(arbre)->dimension);
  }
  /* On affiche son fils gauche si il n'est pas vide */
  if(!est_vide_arbre_kd(renvoyer_fils_gauche(arbre))){
    afficher_arbre(renvoyer_fils_gauche(arbre));
  }
  /* On affiche son fils droit si il n'est pas vide */
  if(!est_vide_arbre_kd(renvoyer_fils_droit(arbre))){
    afficher_arbre(renvoyer_fils_droit(arbre));
  }
}

/* Fonction locale recursive permettant de connaître la profondeur d'un arbre */
int profondeur_arbre(arbre_kd arbre){
  if(est_vide_arbre_kd(arbre)){  /* Si l'arbre est vide, on renvoie 0 */
    return 0;
  }
  /* Sinon sinon on renvoie la profondeur du fils le plus profond + 1 */
  if(profondeur_arbre(arbre->fils_d) > profondeur_arbre(arbre->fils_g)){
    return 1+profondeur_arbre(arbre->fils_d);
  }
  else{
    return 1+profondeur_arbre(arbre->fils_g);
  }
}

/* Fonction locale recursive permettant d'afficher un noeud (ie un arbre) */
void aff_noeud(arbre_kd arbre, int prof, int max_prof){
  int i;

  if(!est_vide_arbre_kd(arbre)){        /* Si le noeud n'est pas vide : */
    aff_noeud(arbre->fils_d, prof+1, max_prof); /* On affiche le fils droit */
    for (i = 0; i < prof; i++){
      /* On affiche le nombre d'espace necessaire */
      printf("                                ");
    }
    afficher_pt(*racine(arbre), racine(arbre)->dimension);

    aff_noeud(arbre->fils_g, prof+1, max_prof); /* On affiche le fils gauche */
  }
  else{                 /* Sinon (ie si le noeud est vide) : */
    for (i = 0; i < prof; i++) {
      /* On affiche le nombre d'espace necessaire */
      printf("                                ");
    }
    printf("NULL\n");     /* On affiche NULL puisque le noeud est vide */
  }
}

/* Fonction permettant d'afficher un arbre de manière plus clair dans le */
/* terminal */
void afficher_arbre_bis(arbre_kd a){
  aff_noeud(a, 0, profondeur_arbre(a));
}
