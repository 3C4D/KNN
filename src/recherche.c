/* Fichier source contenant les fonctions concernant la recherche de kppv */
/* dans un arbre kd */

#include <stdlib.h>
#include <stdio.h>
#include "points.h"
#include "erreur.h"
#include "arbre.h"
#include "recherche.h"

/* Défini si un point est acceptable parmi les KPPV */
int acceptable(point *p_tmp, point *cible, point *liste, int *taille_k, int k){
  int i, victime = 0;
  if(*taille_k < k){  /* Si il reste de la place dans le tableau */
    return 1;
  }
  /* On cherche la victime soit le point le plus éloigné parmi les K-PPV */
  for(i = 0; i < *taille_k; i++){
    if(calc_distance(liste[victime], *cible, p_tmp->dimension)
    <= calc_distance(liste[i], *cible, p_tmp->dimension)){
      victime = i;
    }
  }
  if(calc_distance(*p_tmp, *cible, p_tmp->dimension)
  <= calc_distance(liste[victime], *cible, p_tmp->dimension)){
    return 1; /* acceptable, on retourne 1 */
  }
  return 0; /* non acceptable, on retourne 0 */
}

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
    <= calc_distance(liste[i], *cible, p_tmp->dimension)){
      victime = i;
    }
  }

  /* Si la victime est plus éloigné que p_tmp on la remplace par p_tmp */
  if(calc_distance(*p_tmp, *cible, p_tmp->dimension)
  <= calc_distance(liste[victime], *cible, p_tmp->dimension)){
    liste[victime] = *p_tmp;
    return 1; /* La liste a été modifiée, on retourne 1 */
  }
  return 0; /* Sinon la liste n'a pas été modifiée on retourne 0 */
}

/* Renvoie le point le plus proche du point p dans la zone z_tmp */
/* (ATTENTION ne marche pour l'instant qu'avec 2 dimension) */
point *point_proche_dans_zone(point *p, zone z_tmp){
  point *p_proche;

  /* allocation du point le plus proche */
  p_proche = (point *)malloc(sizeof(point));
  verif_alloc(p_proche);  /* Vérif de l'allocation */
  p_proche->dimension = 2;

  /* Allocation du tableaux de coordonnées */
  p_proche->coord = (double *)malloc(2 * sizeof(double));
  verif_alloc(p_proche->coord); /* Vérif de l'allocation */

  if(p->coord[0] < z_tmp.x1){
    if(p->coord[1] < z_tmp.y1){         /* En bas à gauche */
      p_proche->coord[0] = z_tmp.x1 ;
      p_proche->coord[1] = z_tmp.y1;
    }
    else if(p->coord[1] > z_tmp.y2){    /* En haut à gauche */
      p_proche->coord[0] = z_tmp.x1;
      p_proche->coord[1] = z_tmp.y2;
    }
    else{ /* p->coord[1] entre y1 et y2 ( à gauche) */
      p_proche->coord[0] = z_tmp.x1;
      p_proche->coord[1] = p->coord[1];
    }
  }
  else if(p->coord[0] > z_tmp.x2){
    if(p->coord[1] < z_tmp.y1){         /* En bas à droite */
      p_proche->coord[0] = z_tmp.x2;
      p_proche->coord[1] = z_tmp.y1;
    }
    else if(p->coord[1] > z_tmp.y2){    /* En haut à droite */
      p_proche->coord[0] = z_tmp.x2;
      p_proche->coord[1] = z_tmp.y2;
    }
    else{ /* p->coord[1] entre y1 et y2 (à droite) */
      p_proche->coord[0] = z_tmp.x2;
      p_proche->coord[1] = p->coord[1];
    }
  }
  else{ /* p->coord[0] entre x1 et x2 */
    if(p->coord[1] < z_tmp.y1){       /* En bas */
      p_proche->coord[0] = p->coord[0];
      p_proche->coord[1] = z_tmp.y1;
    }
    else{ /* p-<coord[1] > y2 (en haut) */
      p_proche->coord[0] = p->coord[0];
      p_proche->coord[1] = z_tmp.y2;
    }
  }
  return p_proche;
}

int est_dans_zone_pt(zone z_tmp, point *p){
  if(z_tmp.x1 <= p->coord[0] && p->coord[0] <= z_tmp.x2){
    if(z_tmp.y1 <= p->coord[1] && p->coord[1] <= z_tmp.y2){
      return 1;
    }
  }
  return 0;
}

/* Fonction auxiliaire recursive qui recherche les kppv d'un point dans un */
/* arbre kd */
void recherche_aux(arbre_kd a,
                  zone z_tmp,
                  point *p,
                  int k,
                  point *kppv,
                  int *taille_tab,
                  int prof,
                  int axe){

  point *p_tmp, *p_tmp1, *p_tmp2;
  zone zone1 = z_tmp;
  zone zone2 = z_tmp;

  if(est_vide_arbre_kd(a)){ /* Si a est vide on ne fait rien */
    return;
  }
  else if(est_feuille(a)){
    maj_liste(racine(a), p, kppv, taille_tab, k);  /* On met à jour les KPPV */
  }
  else{ /* Sinon on parcours */
    /* On coupe la zone temporaire en fonction de l'axe */
    if(prof%axe == 0){
      zone1.x2 = racine(a)->coord[0];
      zone2.x1 = racine(a)->coord[0];
    }
    else{
      zone1.y2 = racine(a)->coord[1];
      zone2.y1 = racine(a)->coord[1];
    }

    maj_liste(racine(a), p, kppv, taille_tab, k);  /* On met à jour les KPPV */

    /* Le point est dans la zone 1 */
    if(est_dans_zone_pt(zone1, p)){
      /* On recherche dans le sous-arbre gauche */
      recherche_aux(renvoyer_fils_gauche(a), zone1, p, k, kppv,
          taille_tab, prof+1, axe);

      /* On saisi le point le plus proche */
      p_tmp = point_proche_dans_zone(p, zone2);
      /* Si le point temporaire rentre dans les kppv on explore l'autre côté */
      if(acceptable(p_tmp, p, kppv, taille_tab, k)){
        recherche_aux(renvoyer_fils_droit(a), zone2, p, k, kppv,
            taille_tab, prof+1, axe);
      }

      free(p_tmp);  /* On libère le point temporaire */
      return;       /* On s'arrete la */
    }

    /* Le point est dans la zone 2 */
    if(est_dans_zone_pt(zone2, p)){
      /* On recherche dans le sous-arbre droit */
      recherche_aux(renvoyer_fils_droit(a), zone2, p, k, kppv,
          taille_tab, prof+1, axe);

      /* On saisi le point le plus proche */
      p_tmp = point_proche_dans_zone(p, zone1);
      /* Si le point temporaire rentre dans les kppv on explore l'autre côté */
      if(acceptable(p_tmp, p, kppv, taille_tab, k)){
        recherche_aux(renvoyer_fils_gauche(a), zone1, p, k, kppv,
            taille_tab, prof+1, axe);
      }
      free(p_tmp);  /* On libère le point temporaire */
      return;       /* On s'arrete la */
    }


    /* Sinon on saisi les points plus proches des deux zones */
    p_tmp1 = point_proche_dans_zone(p, zone1);
    p_tmp2 = point_proche_dans_zone(p, zone2);

    /* On commence par le plus proche du point dont on cherche les KPPV */

    /* Cas où le gauche est le plus proche */
    if(calc_distance(*p_tmp1, *p, 2) < calc_distance(*p_tmp2, *p, 2)){
      /* Si le point gauche est acceptable alors on parcours le sous-arbre */
      if(acceptable(p_tmp1, p, kppv, taille_tab, k)){
        recherche_aux(renvoyer_fils_gauche(a), zone1, p, k, kppv,
            taille_tab, prof+1, axe);
      }
      /* Si le point droit est acceptable alors on parcours le sous-arbre */
      if(acceptable(p_tmp2, p, kppv, taille_tab, k)){
        recherche_aux(renvoyer_fils_droit(a), zone2, p, k, kppv,
            taille_tab, prof+1, axe);
      }
    }
    /* Cas où le droit est le plus proche */
    else{
      /* Si le point droit est acceptable alors on parcours le sous-arbre */
      if(acceptable(p_tmp2, p, kppv, taille_tab, k)){
        recherche_aux(renvoyer_fils_droit(a), zone2, p, k, kppv,
            taille_tab, prof+1, axe);
      }
      /* Si le point gauche est acceptable alors on parcours le sous-arbre */
      if(acceptable(p_tmp1, p, kppv, taille_tab, k)){
        recherche_aux(renvoyer_fils_gauche(a), zone1, p, k, kppv,
            taille_tab, prof+1, axe);
      }
    }
  }
}

/* Recherche les kppv d'un point dans un arbre kd */
TabPts *recherche(arbre_kd a, point *p, int k, int nbclasse){
  TabPts *tab_kppv = creer_tab_pts(p->dimension, nbclasse);
  point *kppv = (point *)malloc(k * sizeof(point));
  zone global_zone;

  /* Définition de la zone globale */
  global_zone.x1 = -1;
  global_zone.x2 = 1;
  global_zone.y1 = -1;
  global_zone.y2 = 1;

  if(kppv == NULL){
    erreur("Erreur d'allocation dans la fonction recherche");
  }
  recherche_aux(a, global_zone, p, k, kppv, &tab_kppv->taille, 0, p->dimension);

  tab_kppv->tab = kppv;
  return tab_kppv;
}
