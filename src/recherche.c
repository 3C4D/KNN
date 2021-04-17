/* Fichier source contenant les fonctions concernant la recherche de kppv */
/* dans un arbre kd */

#include <stdlib.h>
#include <stdio.h>
#include "points.h"
#include "erreur.h"
#include "arbre.h"
#include "recherche.h"

/* Met à jour une liste de point en fonction d'un nouveau point */
int maj_liste(point *p_tmp, point *cible, point *liste, int *taille_k, int k){
  int i, victime = 0;

  if(*taille_k < k){  /* Si il reste de la place dans le tableau on le met */
    liste[*taille_k] = *p_tmp;
    *taille_k += 1;
    return 1;
  }

  /* On cherche la victime soit le point le plus éloigné parmi les K-PPV */
  for(i = 0; i < *taille_k; i++){
    if(calc_distance(liste[victime], *cible, p_tmp->dimension)
    < calc_distance(liste[i], *cible, p_tmp->dimension)){
      victime = i;
    }
  }

  /* Si la victime est plus éloigné que p_tmp on la remplace par p_tmp */
  if(calc_distance(*p_tmp, *cible, p_tmp->dimension)
  < calc_distance(liste[victime], *cible, p_tmp->dimension)){
    liste[victime] = *p_tmp;
    return 1; /* La liste a été modifiée, on retourne 1 */
  }
  return 0; /* Sinon la liste n'a pas été modifiée on retourne 0 */
}

/* Renvoie le point le plus proche du point p dans la zone z_tmp */
point *point_proche_dans_zone(point *p, zone z_tmp){
  point *point_gauche;
  point *point_droit;
  if(est_feuille(z_tmp)){ /* Si l'arbre est une feuille on renvoie la racine */
    return racine(z_tmp);
  }
  else{
    /* Trois cas se distinguent si l'arbre n'est pas une feuille : */

    /* Si l'arbre n'a qu'un fils gauche on renvoie le point le plus proche */
    /* entre le point le plus proche du fils gauche et la racine */
    if(est_vide_arbre_kd(renvoyer_fils_gauche(z_tmp))){
      point_droit = point_proche_dans_zone(p, renvoyer_fils_droit(z_tmp));
      if(calc_distance(*racine(z_tmp), *p, p->dimension)
      < calc_distance(*point_droit, *p, p->dimension)){
        return racine(z_tmp);
      }
      return point_droit;
    }

    /* Si l'arbre n'a qu'un fils droit on renvoie le point le plus proche */
    /* entre le point le plus proche du fils droit et la racine */
    else if(est_vide_arbre_kd(renvoyer_fils_droit(z_tmp))){
      point_gauche = point_proche_dans_zone(p, renvoyer_fils_gauche(z_tmp));
      if(calc_distance(*racine(z_tmp), *p, p->dimension)
      < calc_distance(*point_gauche, *p, p->dimension)){
        return racine(z_tmp);
      }
      return point_gauche;
    }

    /* Si l'arbre a deux fils, on saisi les points plus proches des deux fils */
    /* pour enfin renvoyer le plus proche des trois */
    else{
      point_gauche = point_proche_dans_zone(p, renvoyer_fils_gauche(z_tmp));
      point_droit = point_proche_dans_zone(p, renvoyer_fils_droit(z_tmp));

      /* Si la racine est plus proche que le plus proche dans le fils droit : */
      if(calc_distance(*racine(z_tmp), *p, p->dimension)
      < calc_distance(*point_droit, *p, p->dimension)){
        /* Si la racine est plus proche que le plus proche du fils gauche : */
        if(calc_distance(*racine(z_tmp), *p, p->dimension)
        < calc_distance(*point_gauche, *p, p->dimension)){
          return racine(z_tmp); /* On renvoie la racine */
        }
        return point_gauche;  /* Sinon on renvoie le point gauche */
      }
      /* Sinon si le point droit est inférieur au point gauche */
      if(calc_distance(*point_droit, *p, p->dimension)
      < calc_distance(*point_gauche, *p, p->dimension)){
        return point_droit;   /* On renvoie le point droit */
      }
      return point_gauche;   /* Sinon on renvoie le point gauche */
    }
  }
}

/* Fonction auxiliaire recursive qui recherche les kppv d'un point dans un */
/* arbre kd */
void recherche_aux(arbre_kd a, point *p, int k, point *kppv, int *taille_tab, int prof, int axe){
  point *p_tmp;

  if(est_feuille(a)){ /* Si a est une feuille on met a jour la liste */
    maj_liste(racine(a), p, kppv, taille_tab, k);
  }
  else{ /* Sinon on explore la zone où se trouve le point */
    maj_liste(racine(a), p, kppv, taille_tab, k);  /* On met à jour les KPPV */

    /* Si le point se trouve dans le sous-arbre gauche */
    if(p->coord[prof%axe] < racine(a)->coord[prof%axe]){
      /* On l'explore si il n'est pas vide */
      if(!est_vide_arbre_kd(renvoyer_fils_gauche(a))){
        recherche_aux(renvoyer_fils_gauche(a), p, k, kppv, taille_tab, prof+1, axe);
      }
      if(!est_vide_arbre_kd(renvoyer_fils_droit(a))){
        p_tmp = point_proche_dans_zone(p, renvoyer_fils_droit(a));
        if(maj_liste(p_tmp, p, kppv, taille_tab, k)){
          recherche_aux(renvoyer_fils_droit(a), p, k, kppv, taille_tab, prof+1, axe);
        }
      }
    }

    /* Si le point se trouve dans le sous-arbre droit */
    if(p->coord[prof%axe] < racine(a)->coord[prof%axe]){
      /* On l'explore si il n'est pas vide */
      if(!est_vide_arbre_kd(renvoyer_fils_gauche(a))){
        recherche_aux(renvoyer_fils_gauche(a), p, k, kppv, taille_tab, prof+1, axe);
      }
      if(!est_vide_arbre_kd(renvoyer_fils_droit(a))){
        p_tmp = point_proche_dans_zone(p, renvoyer_fils_gauche(a));
        if(maj_liste(p_tmp, p, kppv, taille_tab, k)){
          recherche_aux(renvoyer_fils_droit(a), p, k, kppv, taille_tab, prof+1, axe);
        }
      }
    }
  }
}

/* Recherche les kppv d'un point dans un arbre kd */
TabPts recherche(arbre_kd a, point *p, int k, int nbclasse){
  TabPts tab_kppv = creer_tab_pts(p->dimension, nbclasse);
  point *kppv = (point *)malloc(k * sizeof(point));
  if(kppv == NULL){
    erreur("Erreur d'allocation dans la fonction recherche");
  }
  recherche_aux(a, p, k, kppv, &tab_kppv.taille, 0, p->dimension);

  tab_kppv.tab = kppv;
  return tab_kppv;
}
