#include <stdlib.h>
#include "obj_complexe.h"
#include "couleur.h"
#include "canvas.h"
#include "erreur.h"

/*-----==========Gestion des coches==========-----*/
/* Crée un coche */
MLV_CheckBox init_coche(MLV_Position pos, char *label, bool valide){
  MLV_CheckBox coche = malloc(sizeof(struct MLV_CheckBox_s));
  MLV_Position pos_inter = cp_pos(pos);
  MLV_Position pos_label = cp_pos(pos);
  Pose pose;
  verif_alloc(coche);

  if (valide) {
    pose = ETAT_B;
  } else {
    pose = ETAT_A;
  }
  coche->placement = pos;

  pos_inter->dimension.x = pos_inter->dimension.y;
  coche->case_coche = init_bascule(pos_inter, changer_validation, pose);
  click_maj_proprio((void *)coche, coche->case_coche->zone);
  bascule_image(
    "ressources/img/vide.png",
    "ressources/img/croix.png",
    coche->case_coche
  );

  pos_label->dimension.x -= pos_inter->dimension.x + 10;
  pos_label->decalage.x += pos_inter->dimension.x + 10;
  coche->label = init_texte(2, pos_label, init_format_defaut());
  modif_texte(label, coche->label);
  coche->valide = valide;

  return coche;
}

/* Libère l'espace occupé par le coche */
void liberer_coche(MLV_CheckBox *coche) {
  if (*coche != NULL) {
    liberer_position(&(*coche)->placement);
    liberer_bascule(&(*coche)->case_coche);
    free(*coche);
  }

  *coche = NULL;
}

/* Désactive le coche */
void desactiver_coche(MLV_CheckBox coche){
  desactiver_bascule(coche->case_coche);
  texte_changer_couleur(couleur_hex("9f9f9f"), coche->label);
}

/* Active le coche */
void activer_coche(MLV_CheckBox coche){
  activer_bascule(coche->case_coche);
  texte_changer_couleur(couleur_hex("abb2bf"), coche->label);
}

/* Coche/valide le coche */
void cocher_case_coche(MLV_CheckBox coche){
  coche->valide = true;
  bascule_pose(ETAT_B, coche->case_coche);
}

/* Décoche le coche */
void decocher_case_coche(MLV_CheckBox coche){
  coche->valide = false;
  bascule_pose(ETAT_A, coche->case_coche);
}

/* Change la validation du coche */
Id_Obj changer_validation(MLV_Clickable click, Info_Souris souris) {
  MLV_CheckBox coche;

  if (souris->bouton != MLV_BUTTON_LEFT) {
    return CHECKBOX;
  }

  coche = (MLV_CheckBox)click_proprio(click);

  if (coche->valide) {
    decocher_case_coche(coche);
  } else {
    cocher_case_coche(coche);
  }

  return CHECKBOX;
}

/*-----==========Gestion des compteurs==========-----*/
/* Incrémente la valeur du compteur */
Id_Obj aug_compteur(MLV_Clickable click, Info_Souris souris);
/* Décrémente la valeur du compteur */
Id_Obj dim_compteur(MLV_Clickable click, Info_Souris souris);
/* Met à jour la valeur du compteur */
Id_Obj maj_compteur(MLV_Clickable click, Info_Souris souris);

/* Crée un compteur */
MLV_SpinBox init_compteur(MLV_Position pos, int min, int max, int val){
  MLV_SpinBox compteur = malloc(sizeof(struct MLV_SpinBox_s));
  MLV_Position pos_aug = cp_pos(pos);
  MLV_Position pos_dim;
  MLV_Position pos_info = cp_pos(pos);
  verif_alloc(compteur);

  /* Positon du bouton incrémental */
  compteur->placement = pos;
  pos_aug->dimension.y /= 2;
  pos_aug->dimension.x = pos_aug->dimension.y;

  /* Positon du bouton décrémental */
  pos_dim = cp_pos(pos_aug);
  pos_dim->decalage.y += pos_aug->dimension.y;

  /* Positon de l'entrée */
  pos_info->dimension.x -= pos_aug->dimension.x + 10;
  pos_info->decalage.x += pos_aug->dimension.x + 10;

  compteur->aug = init_bouton(pos_aug, aug_compteur);
  bouton_image(
    "ressources/img/fleche_haut.png",
    compteur->aug
  );
  click_maj_proprio((void *)compteur, compteur->aug->zone);

  compteur->dim = init_bouton(pos_dim, dim_compteur);
  bouton_image(
    "ressources/img/fleche_bas.png",
    compteur->dim
  );
  click_maj_proprio((void *)compteur, compteur->dim->zone);

  compteur->info = init_saisie(pos_info, NULL, maj_compteur);
  click_maj_proprio((void *)compteur, compteur->info->sortie);

  /* Initialisation des valeurs et vérification de limite */
  compteur->min = min;
  compteur->max = max;
  if (val > max) {
    compteur->val = max;
  } else if (val < min) {
    compteur->val = min;
  } else {
    compteur->val = val;
  }

  modif_texte_int(compteur->val, compteur->info->texte);

  return compteur;
}

/* Libère l'espace occupé par le compteur */
void liberer_compteur(MLV_SpinBox *compteur){
  if (*compteur != NULL) {
    liberer_position(&(*compteur)->placement);
    liberer_bouton(&(*compteur)->aug);
    liberer_bouton(&(*compteur)->dim);
    liberer_saisie(&(*compteur)->info);
    free(*compteur);
  }

  *compteur = NULL;
}

/* Désactive le compteur */
void desactiver_compteur(MLV_SpinBox compteur){
  desactiver_bouton(compteur->aug);
  desactiver_bouton(compteur->dim);
  desactiver_saisie(compteur->info);
}

/* Active le compteur */
void activer_compteur(MLV_SpinBox compteur){
  activer_bouton(compteur->aug);
  activer_bouton(compteur->dim);
  activer_saisie(compteur->info);
}

Id_Obj aug_compteur(MLV_Clickable click, Info_Souris souris){
  MLV_SpinBox compteur;

  if (souris->bouton != MLV_BUTTON_LEFT) {
    return SPINBOX;
  }
  compteur = (MLV_SpinBox)click_proprio(click);

  /* Incrémentation et vérification de limite */
  compteur->val++;
  if (compteur->val > compteur->max) {
    compteur->val = compteur->max;
  }

  /* Changement du texte affiché */
  modif_texte_int(compteur->val, compteur->info->texte);

  return SPINBOX;
}

Id_Obj dim_compteur(MLV_Clickable click, Info_Souris souris){
  MLV_SpinBox compteur;

  if (souris->bouton != MLV_BUTTON_LEFT) {
    return SPINBOX;
  }
  compteur = (MLV_SpinBox)click_proprio(click);

  /* Decrémentation et vérification de limite */
  compteur->val--;
  if (compteur->val < compteur->min) {
    compteur->val = compteur->min;
  }

  /* Changement du texte affiché */
  modif_texte_int(compteur->val, compteur->info->texte);

  return SPINBOX;
}

Id_Obj maj_compteur(MLV_Clickable click, Info_Souris souris){
  MLV_SpinBox compteur = (MLV_SpinBox)click_proprio(click);

  compteur->val = atoi(compteur->info->texte->msg->str);
  if (compteur->val < compteur->min) {
    compteur->val = compteur->min;
  } else if (compteur->val > compteur->max) {
    compteur->val = compteur->max;
  }
  
  compteur->info->keylog->etat = INACTIF;
  couleur_fond_canvas(couleur_hex("39404d"), compteur->info->fond);
  modif_texte_int(compteur->val, compteur->info->texte);
  return SPINBOX;
}


/*-----==========Gestion des graphiques==========-----*/
/* Crée un graphique */
MLV_Graph2D init_graph2D(MLV_Position pos, Plan_R plan){
  MLV_Graph2D graph2D = malloc(sizeof(struct MLV_Graph2D_s));
  verif_alloc(graph2D);
  graph2D->placement = pos;
  graph2D->surface = init_canvas(cp_pos(pos), true);
  vider_graph(graph2D);
  graph2D->plan = plan;
  graph2D->mat_pix = init_planz(
    init_axe(0, pos->dimension.x), init_axe(0, pos->dimension.y)
  );

  return graph2D;
}

/* Libère l'espace occupé par le graphique */
void liberer_graph2D(MLV_Graph2D *graph2D){
  if (*graph2D != NULL){
    liberer_position(&(*graph2D)->placement);
    liberer_canvas(&(*graph2D)->surface);
    liberer_planr(&(*graph2D)->plan);
    liberer_planz(&(*graph2D)->mat_pix);
    free(*graph2D);
  }
  
  *graph2D = NULL;
}

/* Efface tout le contenu du graphique */
void vider_graph(MLV_Graph2D graph2D){
  couleur_fond_canvas(MLV_COLOR_WHITE, graph2D->surface);
}

/* Affiche l'axe des abscisses */
void aff_axe_x(MLV_Graph2D graph2D){
  graph_placer_segment(
    init_coordr(graph2D->plan->abs.min, 0.0),
    init_coordr(graph2D->plan->abs.max, 0.0),
    MLV_COLOR_BLACK, graph2D
  );
}

/* Affiche l'axe des ordonnées */
void aff_axe_y(MLV_Graph2D graph2D){
  graph_placer_segment(
    init_coordr(0.0, graph2D->plan->ord.min),
    init_coordr(0.0, graph2D->plan->ord.max),
    MLV_COLOR_BLACK, graph2D
  );
}

/* Affiche la grille sur les x */
void aff_grille_x(MLV_Graph2D graph2D){
  double pos_y = 0.0;
  /* Parallèles avec y > 0 */
  while (pos_y < graph2D->plan->ord.max){
    graph_placer_segment(
      init_coordr(graph2D->plan->abs.min, pos_y),
      init_coordr(graph2D->plan->abs.max, pos_y),
      MLV_COLOR_GREY75, graph2D
    );
    pos_y += graph2D->plan->ord.pas; /* Incrément d'un pas */
  } 

  /* Parallèles avec y < 0 */
  pos_y = -graph2D->plan->ord.pas;
  while (pos_y > graph2D->plan->ord.min){
    graph_placer_segment(
      init_coordr(graph2D->plan->abs.min, pos_y),
      init_coordr(graph2D->plan->abs.max, pos_y),
      MLV_COLOR_GREY75, graph2D
    );
    pos_y -= graph2D->plan->ord.pas; /* Décrément d'un pas */
  } 
}

/* Affiche la grille sur les y */
void aff_grille_y(MLV_Graph2D graph2D){
  double pos_x = 0.0;
  /* Parallèles avec x > 0 */
  while (pos_x < graph2D->plan->abs.max){
    graph_placer_segment(
      init_coordr(pos_x, graph2D->plan->ord.min),
      init_coordr(pos_x, graph2D->plan->ord.max),
      MLV_COLOR_GREY75, graph2D
    );
    pos_x += graph2D->plan->abs.pas; /* Incrément d'un pas */
  } 

  /* Parallèles avec x < 0 */
  pos_x = -graph2D->plan->abs.pas;
  while (pos_x > graph2D->plan->abs.min){
    graph_placer_segment(
      init_coordr(pos_x, graph2D->plan->ord.min),
      init_coordr(pos_x, graph2D->plan->ord.max),
      MLV_COLOR_GREY75, graph2D
    );
    pos_x -= graph2D->plan->abs.pas; /* Décrément d'un pas */
  } 
}

/* Affiche la sous-grille sur les x */
void aff_sous_grille_x(int nb_sections, MLV_Graph2D graph2D){
  double pos_y = 0.0;
  /* Parallèles avec y > 0 */
  while (pos_y < graph2D->plan->ord.max){
    graph_placer_segment(
      init_coordr(graph2D->plan->abs.min, pos_y),
      init_coordr(graph2D->plan->abs.max, pos_y),
      couleur_hex("bfbfbf3f"), graph2D
    );
    /* Incrément d'une fraction d'un pas */
    pos_y += graph2D->plan->ord.pas/nb_sections; 
  } 

  /* Parallèles avec y < 0 */
  pos_y = -graph2D->plan->ord.pas/nb_sections;
  while (pos_y > graph2D->plan->ord.min){
    graph_placer_segment(
      init_coordr(graph2D->plan->abs.min, pos_y),
      init_coordr(graph2D->plan->abs.max, pos_y),
      couleur_hex("bfbfbf3f"), graph2D
    );
    /* Décrément d'une fraction d'un pas */
    pos_y -= graph2D->plan->ord.pas/nb_sections;
  } 
}

/* Affiche la sous-grille sur les y */
void aff_sous_grille_y(int nb_sections, MLV_Graph2D graph2D){
  double pos_x = 0.0;
  /* Parallèles avec x > 0 */
  while (pos_x < graph2D->plan->abs.max){
    graph_placer_segment(
      init_coordr(pos_x, graph2D->plan->ord.min),
      init_coordr(pos_x, graph2D->plan->ord.max),
      couleur_hex("bfbfbf3f"), graph2D
    );
    /* Incrément d'une fraction d'un pas */
    pos_x += graph2D->plan->abs.pas / nb_sections;
  } 

  /* Parallèles avec x < 0 */
  pos_x = -graph2D->plan->abs.pas / nb_sections;
  while (pos_x > graph2D->plan->abs.min){
    graph_placer_segment(
      init_coordr(pos_x, graph2D->plan->ord.min),
      init_coordr(pos_x, graph2D->plan->ord.max),
      couleur_hex("bfbfbf3f"), graph2D
    );
    /* Décrément d'une fraction d'un pas */
    pos_x -= graph2D->plan->abs.pas / nb_sections;
  } 
}

/* Place un segmenet sur le graphique */
void graph_placer_segment(
  Coord_R debut, Coord_R fin, MLV_Color col, MLV_Graph2D graph2D
){
  placer_ligne(
    coord_rtoz(debut, graph2D->plan, graph2D->mat_pix), 
    coord_rtoz(fin, graph2D->plan, graph2D->mat_pix),
    col, graph2D->surface
  );
}


/* Place un cercle plein sur le graphique */
void graph_placer_cercle_plein(
  Coord_R centre, double rayon, MLV_Color col, MLV_Graph2D graph
){
  /* NB: Le disque est relatif au plan, autrement dit sur un plan orthogonal,
  non-orthonormé le cercle apparaitrat comme une ellipse */
  Coord rayon_xy = init_coord(
    long_rtoz(rayon, graph->plan->abs, graph->mat_pix->abs),
    long_rtoz(rayon, graph->plan->ord, graph->mat_pix->ord)
  );
  placer_ellipse_pleine(
    coord_rtoz(centre, graph->plan, graph->mat_pix),
    rayon_xy, col, graph->surface
  );
}


/* Place un cercle sur le graphique */
void graph_placer_cercle(
  Coord_R centre, double rayon, MLV_Color col, MLV_Graph2D graph
){
  /* NB: Le cercle est relatif au plan, autrement dit sur un plan orthogonal,
  non-orthonormé le cercle apparaitrat comme une ellipse */
  Coord rayon_xy = init_coord(
    long_rtoz(rayon, graph->plan->abs, graph->mat_pix->abs),
    long_rtoz(rayon, graph->plan->ord, graph->mat_pix->ord)
  );
  placer_ellipse(
    coord_rtoz(centre, graph->plan, graph->mat_pix),
    rayon_xy, col, graph->surface
  );
}


/* Place un point sur le graphique */
void graph_placer_point(
  Coord_R centre, int taille, Forme type, MLV_Color col, MLV_Graph2D graph
){
  Coord c = coord_rtoz(centre, graph->plan, graph->mat_pix);
  switch (type){
  case LOSANGE:
    placer_losange_plein(c, taille, col, graph->surface);
    break;

  case ROND:
    /* Dû à MLV le seul moyen d'avoir un disque propre est de placer un disque
    et un cercle */
    placer_disque(c, taille, col, graph->surface);
    placer_cercle(c, taille, col, graph->surface);
    break;
  
  case CARRE:
    placer_carre_plein(c, taille, col, graph->surface);
    break;

  case TRIANGLE:
    placer_triangle_plein(c, taille, col, graph->surface);
    break;
  
  case CROIX:
    placer_croix(c, taille, col, graph->surface);
    break;
  
  default:
    placer_disque(c, taille, col, graph->surface);
    placer_cercle(c, taille, col, graph->surface);
    break;
  }
}


/*-----==========Gestion des gestionnaires de fichiers==========-----*/
/* Comportement de l'entrée du gestionnaire de fichier */
Id_Obj gest_fichier_saisie(MLV_Clickable click, Info_Souris souris);
/* Comportement du bouton du gestionnaire de fichier */
Id_Obj gest_fichier_bouton(MLV_Clickable click, Info_Souris souris);
/* Crée le chemin vers le fichier grâce au fichier entré
en s'assurant qui celui ci ne possède pas de caractère illegaux */
void format_fichier(String str, MLV_FileManager gest_fichier);

/* Crée un gestionnaire de fichier */
MLV_FileManager init_gest_fichier(
  MLV_Position pos, char const *rep, void (*fct)(char *)
){
  MLV_Position pos_saisie = cp_pos(pos);
  MLV_Position pos_bouton = cp_pos(pos);
  MLV_FileManager gest_fichier = malloc(sizeof(struct MLV_FileManager_s));
  verif_alloc(gest_fichier);
  
  gest_fichier->placement = pos;

  /* Placement de l'entrée textuelle */
  pos_saisie->dimension.x -= pos_saisie->dimension.y + 10;

  gest_fichier->fichier = init_saisie(pos_saisie, NULL, gest_fichier_saisie);
  click_maj_proprio((void *)gest_fichier, gest_fichier->fichier->sortie);

  /* Placement du bouton */
  pos_bouton->dimension.x = pos_bouton->dimension.y;
  pos_bouton->decalage.x += pos_saisie->dimension.x + 10;

  gest_fichier->operation = init_bouton(pos_bouton, gest_fichier_bouton);
  click_maj_proprio((void *)gest_fichier, gest_fichier->operation->zone);

  /* Mise en place du repertoire racine */
  gest_fichier->repertoire = String_new(rep);
  gest_fichier->fct_fichier = fct;

  return gest_fichier;
}

/* Libère l'espace occupé par le gestionnaire de fichier */
void liberer_gest_fichier(MLV_FileManager *gest_fichier){
  if(*gest_fichier != NULL){
    liberer_position(&(*gest_fichier)->placement);
    liberer_saisie(&(*gest_fichier)->fichier);
    liberer_bouton(&(*gest_fichier)->operation);
    String_free(&(*gest_fichier)->repertoire);
    free(*gest_fichier);
  }

  *gest_fichier = NULL;
}

/* Change l'icon du bouton du gestionnaire de fichier */
void ajouter_icon_gest_fichier(char *chemin, MLV_FileManager gest_fichier){
  bouton_image(chemin, gest_fichier->operation);
}


Id_Obj gest_fichier_saisie(MLV_Clickable click, Info_Souris souris){
  MLV_FileManager gest_fichier = (MLV_FileManager)click_proprio(click);
  String fichier = String_new("");

  format_fichier(fichier, gest_fichier);

  /* Sortie de l'entrée */
  gest_fichier->fichier->keylog->etat = INACTIF;
  couleur_fond_canvas(couleur_hex("39404d"), gest_fichier->fichier->fond);

  String_free(&fichier);
  return FILEMAN;
}

Id_Obj gest_fichier_bouton(MLV_Clickable click, Info_Souris souris){
  MLV_FileManager gest_fichier = (MLV_FileManager)click_proprio(click);
  String fichier = String_new("");

  format_fichier(fichier, gest_fichier);

  /* Sortie de l'entrée */
  gest_fichier->fichier->keylog->etat = INACTIF;
  couleur_fond_canvas(couleur_hex("39404d"), gest_fichier->fichier->fond);

  /* Si il y une action on lance */
  if (gest_fichier->fct_fichier != NULL) {
    (gest_fichier->fct_fichier)(fichier->str);
  }

  String_free(&fichier);
  return FILEMAN;
}

void format_fichier(String str, MLV_FileManager gest_fichier){
  int i;
  /* Caractères illegaux sous UNIX et MS-DOS */
  char illegal[] = ":/\\|<>?\"*";
  char buff[2] = {0};
  String_concat(str, gest_fichier->repertoire);
  for (i = 0; i < 9; i++){
    buff[0] = illegal[i];
    /* Remplace les occurence d'un caractère par la chaine vide => supprime */
    String_replace(gest_fichier->fichier->texte->msg, buff, "");
  }
  String_concat(str, gest_fichier->fichier->texte->msg);
}
