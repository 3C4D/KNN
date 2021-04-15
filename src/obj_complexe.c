#include <stdlib.h>
#include "obj_complexe.h"
#include "canvas.h"
#include "erreur.h"

MLV_CheckBox init_coche(MLV_Position pos, char *label, bool valide){
  MLV_CheckBox coche = malloc(sizeof(struct MLV_CheckBox_s));
  MLV_Position pos_inter = copie_position(pos);
  MLV_Position pos_label = copie_position(pos);
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
    "ressources/img/vide_inactif.png",
    "ressources/img/croix_inactif.png",
    coche->case_coche
  );

  pos_label->dimension.x -= pos_inter->dimension.x + 10;
  pos_label->decalage.x += pos_inter->dimension.x + 10;
  coche->label = init_texte(2, pos_label, init_format_defaut());
  modif_texte(label, coche->label);
  coche->valide = valide;

  return coche;
}

void liberer_coche(MLV_CheckBox *coche) {
  if (*coche != NULL) {
    liberer_position(&(*coche)->placement);
    liberer_bascule(&(*coche)->case_coche);
    free(*coche);
  }

  *coche = NULL;
}

Id_Obj changer_validation(MLV_Clickable click, Info_Souris souris) {
  MLV_CheckBox coche;

  if (souris->bouton != MLV_BUTTON_LEFT) {
    return NON_DEFINI;
  }

  coche = (MLV_CheckBox)click_proprio(click);
  bascule_changer_pose(coche->case_coche);
  if (coche->valide) {
    printf("off\n");
    coche->valide = false;
  } else {
    coche->valide = true;
    printf("on\n");
  }

  return NON_DEFINI;
}


Id_Obj maj_compteur(MLV_Clickable click, Info_Souris souris);

MLV_SpinBox init_compteur(MLV_Position pos, int min, int max, int val){
  MLV_SpinBox compteur = malloc(sizeof(struct MLV_SpinBox_s));
  MLV_Position pos_aug = copie_position(pos);
  MLV_Position pos_dim ;
  MLV_Position pos_info = copie_position(pos);
  verif_alloc(compteur);

  compteur->placement = pos;
  pos_aug->dimension.y /= 2;
  pos_aug->dimension.x = pos_aug->dimension.y;

  pos_dim = copie_position(pos_aug);
  pos_dim->decalage.y += pos_aug->dimension.y;

  pos_info->dimension.x -= pos_aug->dimension.x + 10;
  pos_info->decalage.x += pos_aug->dimension.x + 10;

  compteur->aug = init_bouton(pos_aug, aug_compteur);
  bouton_image(
    "ressources/img/fleche_haut.png",
    "ressources/img/fleche_haut_inactif.png",
    compteur->aug
  );
  click_maj_proprio((void *)compteur, compteur->aug->zone);

  compteur->dim = init_bouton(pos_dim, dim_compteur);
  bouton_image(
    "ressources/img/fleche_bas.png",
    "ressources/img/fleche_bas_inactif.png",
    compteur->dim
  );
  click_maj_proprio((void *)compteur, compteur->dim->zone);

  compteur->info = init_saisie(pos_info, NULL, maj_compteur);
  click_maj_proprio((void *)compteur, compteur->info->sortie);

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

Id_Obj aug_compteur(MLV_Clickable click, Info_Souris souris){
  MLV_SpinBox compteur;

  if (souris->bouton != MLV_BUTTON_LEFT) {
    return NON_DEFINI;
  }
  compteur = (MLV_SpinBox)click_proprio(click);

  compteur->val++;
  if (compteur->val > compteur->max) {
    compteur->val = compteur->max;
  }

  modif_texte_int(compteur->val, compteur->info->texte);

  return NON_DEFINI;
}

Id_Obj dim_compteur(MLV_Clickable click, Info_Souris souris){
  MLV_SpinBox compteur;

  if (souris->bouton != MLV_BUTTON_LEFT) {
    return NON_DEFINI;
  }
  compteur = (MLV_SpinBox)click_proprio(click);

  compteur->val--;
  if (compteur->val < compteur->min) {
    compteur->val = compteur->min;
  }

  modif_texte_int(compteur->val, compteur->info->texte);

  return NON_DEFINI;
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
  couleur_fond_canvas(MLV_rgba(0x39, 0x40, 0x4d, 0xff), compteur->info->fond);
  modif_texte_int(compteur->val, compteur->info->texte);
  return NON_DEFINI;
}


MLV_Graph2D init_graph2D(MLV_Position pos, Plan_R plan){
  MLV_Graph2D graph2D = malloc(sizeof(struct MLV_Graph2D_s));
  verif_alloc(plan);
  graph2D->placement = pos;
  graph2D->surface = init_canvas(pos, true);
  couleur_fond_canvas(MLV_COLOR_WHITE, graph2D->surface);
  graph2D->plan = plan;
  graph2D->mat_pix = init_planz(
    init_axe(0, pos->dimension.x), init_axe(0, pos->dimension.y)
  );

  return graph2D;
}

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

void aff_axe_x(MLV_Graph2D graph2D){
  graph_placer_segment(
    init_coordr(graph2D->plan->abs.min, 0.0),
    init_coordr(graph2D->plan->abs.max, 0.0),
    MLV_COLOR_BLACK, graph2D
  );
}


void aff_axe_y(MLV_Graph2D graph2D){
  graph_placer_segment(
    init_coordr(0.0, graph2D->plan->ord.min),
    init_coordr(0.0, graph2D->plan->ord.max),
    MLV_COLOR_BLACK, graph2D
  );
}

void aff_grille_x(MLV_Graph2D graph2D){
  double pos_y = graph2D->plan->ord.pas;
  while (pos_y < graph2D->plan->ord.max){
    graph_placer_segment(
      init_coordr(graph2D->plan->abs.min, pos_y),
      init_coordr(graph2D->plan->abs.max, pos_y),
      MLV_COLOR_GREY75, graph2D
    );
    pos_y += graph2D->plan->ord.pas;
  } 

  pos_y = -graph2D->plan->ord.pas;
  while (pos_y > graph2D->plan->ord.min){
    graph_placer_segment(
      init_coordr(graph2D->plan->abs.min, pos_y),
      init_coordr(graph2D->plan->abs.max, pos_y),
      MLV_COLOR_GREY75, graph2D
    );
    pos_y -= graph2D->plan->ord.pas;
  } 
}

void aff_grille_y(MLV_Graph2D graph2D){
  double pos_x = graph2D->plan->abs.pas;
  while (pos_x < graph2D->plan->abs.max){
    graph_placer_segment(
      init_coordr(pos_x, graph2D->plan->ord.min),
      init_coordr(pos_x, graph2D->plan->ord.max),
      MLV_COLOR_GREY75, graph2D
    );
    pos_x += graph2D->plan->abs.pas;
  } 

  pos_x = -graph2D->plan->abs.pas;
  while (pos_x > graph2D->plan->abs.min){
    graph_placer_segment(
      init_coordr(pos_x, graph2D->plan->ord.min),
      init_coordr(pos_x, graph2D->plan->ord.max),
      MLV_COLOR_GREY75, graph2D
    );
    pos_x -= graph2D->plan->abs.pas;
  } 
}

void aff_sous_grille_x(int nb_sections, MLV_Graph2D graph2D){
  double pos_y = graph2D->plan->ord.pas/nb_sections;
  while (pos_y < graph2D->plan->ord.max){
    graph_placer_segment(
      init_coordr(graph2D->plan->abs.min, pos_y),
      init_coordr(graph2D->plan->abs.max, pos_y),
      MLV_rgba(0xbf, 0xbf, 0xbf, 0x3f), graph2D
    );
    pos_y += graph2D->plan->ord.pas/nb_sections;
  } 

  pos_y = -graph2D->plan->ord.pas/nb_sections;
  while (pos_y > graph2D->plan->ord.min){
    graph_placer_segment(
      init_coordr(graph2D->plan->abs.min, pos_y),
      init_coordr(graph2D->plan->abs.max, pos_y),
      MLV_rgba(0xbf, 0xbf, 0xbf, 0x3f), graph2D
    );
    pos_y -= graph2D->plan->ord.pas/nb_sections;
  } 
}

void aff_sous_grille_y(int nb_sections, MLV_Graph2D graph2D){
  double pos_x = graph2D->plan->abs.pas / nb_sections;
  while (pos_x < graph2D->plan->abs.max){
    graph_placer_segment(
      init_coordr(pos_x, graph2D->plan->ord.min),
      init_coordr(pos_x, graph2D->plan->ord.max),
      MLV_rgba(0xbf, 0xbf, 0xbf, 0x3f), graph2D
    );
    pos_x += graph2D->plan->abs.pas / nb_sections;
  } 

  pos_x = -graph2D->plan->abs.pas / nb_sections;
  while (pos_x > graph2D->plan->abs.min){
    graph_placer_segment(
      init_coordr(pos_x, graph2D->plan->ord.min),
      init_coordr(pos_x, graph2D->plan->ord.max),
      MLV_rgba(0xbf, 0xbf, 0xbf, 0x3f), graph2D
    );
    pos_x -= graph2D->plan->abs.pas / nb_sections;
  } 
}

void graph_placer_segment(
  Coord_R debut, Coord_R fin, MLV_Color col, MLV_Graph2D graph2D
){
  placer_ligne(
    coord_rtoz(debut, graph2D->plan, graph2D->mat_pix), 
    coord_rtoz(fin, graph2D->plan, graph2D->mat_pix),
    col, graph2D->surface
  );
}

void graph_placer_cercle_plein(
  Coord_R centre, double rayon, MLV_Color col, MLV_Graph2D graph
){
  Coord rayon_xy = init_coord(
    long_rtoz(rayon, graph->plan->abs, graph->mat_pix->abs),
    long_rtoz(rayon, graph->plan->ord, graph->mat_pix->ord)
  );
  placer_ellipse_pleine(
    coord_rtoz(centre, graph->plan, graph->mat_pix),
    rayon_xy, col, graph->surface
  );
}

void graph_placer_cercle(
  Coord_R centre, double rayon, MLV_Color col, MLV_Graph2D graph
){
  Coord rayon_xy = init_coord(
    long_rtoz(rayon, graph->plan->abs, graph->mat_pix->abs),
    long_rtoz(rayon, graph->plan->ord, graph->mat_pix->ord)
  );
  placer_ellipse(
    coord_rtoz(centre, graph->plan, graph->mat_pix),
    rayon_xy, col, graph->surface
  );
}

void graph_placer_point(
  Coord_R centre, MLV_Color sur, MLV_Color cir, MLV_Graph2D graph
){
  double rayon = long_ztor(2, graph->mat_pix->abs, graph->plan->abs);
  graph_placer_cercle_plein(centre, rayon, sur, graph);
  graph_placer_cercle(centre, rayon, cir, graph);
}
