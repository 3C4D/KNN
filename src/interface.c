#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "interface.h"
#include "lien_elems.h"

#include "id_objet.h"
#include "interactif.h"
#include "boite.h"
#include "position.h"
#include "grille.h"
#include "gestion.h"
#include "gestion_ajout.h"
#include "peripheriques.h"
#include "couleur.h"

#include "points.h"
#include "erreur.h"
#include "kppv.h"
#include "sauvegarde.h"
#include "arbre.h"
#include "generation.h"

#define GRILLE_X 90
#define GRILLE_Y 60

void mise_en_place(Grid grille, Manager gest);
void ajout_elements(Grid grille, Manager gest);
void demarrer_interface(Manager gest);


int lancer_interface() {
  int echelle = MLV_get_desktop_height() / 2 ;
  Grid grille = init_grille(
    GRILLE_X, GRILLE_Y,
    echelle,
    false
  );
  int hauteur = grille_hauteur(grille);
  int longueur = grille_longueur(grille);

  MLV_create_window_with_default_font(
    "K Plus Proches Voisins", "KPPV",
    longueur, hauteur,
    "ressources/polices/Lato-Thin.ttf", (int)(echelle / 45)
  );

  Manager gestionnaire = init_gestionnaire();
  MLV_Canvas fond = init_canvas(
    grille_pos(0, 0, GRILLE_X, GRILLE_Y, grille), true
  );
  couleur_fond_canvas(couleur_hex("21252b"), fond);

  ajouter_canvas(fond, gestionnaire->liste_canvas);
  mise_en_place(grille, gestionnaire);
  ajout_elements(grille, gestionnaire);
  affichage_debug(gestionnaire);

  MLV_actualise_window();
  MLV_wait_seconds( 3 );

  affichage_fenetre(gestionnaire);
  MLV_actualise_window();
  demarrer_interface(gestionnaire);
  MLV_wait_seconds( 3 );
  MLV_free_window();

  return 0;
}

void mise_en_place(Grid grille, Manager gest){
  MLV_Box boite;
  MLV_Container cont;
  MLV_Position pos;

  pos = grille_pos(4, 2, GRILLE_X - 7, GRILLE_Y - 4, grille);
  boite = init_boite(HORIZONTAL, pos);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(50, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(33, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  boite = placer_boite(
    grille_coord(50, 56, grille),
    VERTICAL, gest->liste_boite->liste[0]->elements[0]
  );
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(4, grille), boite);
  ajouter_remplissage(grille_dist(2, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(50, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  boite = placer_boite(
    grille_coord(33, 56, grille),
    VERTICAL, gest->liste_boite->liste[0]->elements[1]
  );
  ajouter_remplissage(grille_dist(6, grille), boite);
  cont = init_conteneur(MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER);
  ajouter_conteneur(cont, grille_dist(10, grille), boite);
  ajouter_remplissage(grille_dist(2, grille), boite);
  cont = init_conteneur(MLV_HORIZONTAL_RIGHT, MLV_VERTICAL_CENTER);
  ajouter_conteneur(cont, grille_dist(29, grille), boite);
  cont = init_conteneur(MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER);
  ajouter_remplissage(grille_dist(1, grille), boite);
  ajouter_conteneur(cont, grille_dist(8, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  boite = placer_boite(
    grille_coord(50, 4, grille),
    HORIZONTAL, gest->liste_boite->liste[1]->elements[0]
  );
  cont = init_conteneur(MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER);
  ajouter_conteneur(cont, grille_dist(20, grille), boite);
  ajouter_remplissage(grille_dist(10, grille), boite);
  cont = init_conteneur(MLV_HORIZONTAL_RIGHT, MLV_VERTICAL_CENTER);
  ajouter_conteneur(cont, grille_dist(20, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  boite = placer_boite(
    grille_coord(20, 10, grille),
    VERTICAL, gest->liste_boite->liste[2]->elements[0]
  );
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(5, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(5, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  boite = placer_boite(
    grille_coord(29, 29, grille),
    VERTICAL, gest->liste_boite->liste[2]->elements[1]
  );
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(18, grille), boite);
  ajouter_remplissage(grille_dist(4, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(3, grille), boite);
  ajouter_remplissage(grille_dist(1, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(3, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  boite = placer_boite(
    grille_coord(29, 18, grille),
    VERTICAL, gest->liste_boite->liste[5]->elements[0]
  );
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(3, grille), boite);
  ajouter_remplissage(grille_dist(1, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(2, grille), boite);
  ajouter_remplissage(grille_dist(1, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(2, grille), boite);
  ajouter_remplissage(grille_dist(1, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(2, grille), boite);
  ajouter_remplissage(grille_dist(1, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(2, grille), boite);
  ajouter_remplissage(grille_dist(1, grille), boite);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(2, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  pos = grille_pos(GRILLE_X - 5, 1, 4, 4, grille);
  boite = init_boite(HORIZONTAL, pos);
  cont = init_conteneur_centre();
  ajouter_conteneur(cont, grille_dist(4, grille), boite);
  ajouter_boite(boite, gest->liste_boite);
}

void ajout_elements(Grid grille, Manager gest){
  TabPts *tab;

  boutons[0] = init_bouton(
    position_contenu(
      grille_coord(4, 4, grille),
      gest->liste_boite->liste[7]->elements[0]
    ),
    tester
  );
  bouton_image("ressources/img/reset.png", boutons[0]);
  charger_bouton(boutons[0], gest);

  boutons[1] = init_bouton(
    position_contenu(
      grille_coord(8, 4, grille),
      gest->liste_boite->liste[4]->elements[0]
    ),
    tester
  );
  bouton_image("ressources/img/undo.png", boutons[1]);
  charger_bouton(boutons[1], gest);

  bascules[0] = init_bascule(
    position_contenu(
      grille_coord(15, 3, grille),
      gest->liste_boite->liste[3]->elements[0]
    ),
    tog, ETAT_B
  );
  bascule_label("Mode Création", "Mode KPPV", bascules[0]);
  charger_bascule(bascules[0], gest);

  labels[0] = init_texte(
    0, position_contenu(
      grille_coord(25, 3, grille),
      gest->liste_boite->liste[6]->elements[0]
    ),
    init_format_centre()
  );
  modif_texte("Options d'affichage", labels[0]);
  ajouter_texte(labels[0], gest->liste_texte);

  coches[0] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[1]
    ),
    "Affichage des axes", true
  );
  charger_coche(coches[0], gest);

  coches[1] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[2]
    ),
    "Affichage de la grille", true
  );
  charger_coche(coches[1], gest);

  coches[2] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[3]
    ),
    "Affichage de la sous-grille", true
  );
  charger_coche(coches[2], gest);

  coches[3] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[4]
    ),
    "Affichage des KPPV", true
  );
  charger_coche(coches[3], gest);

  coches[4] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[5]
    ),
    "Prise de décision", true
  );
  charger_coche(coches[4], gest);

  compteurs[0] = init_compteur(
    position_contenu(
      grille_coord(10, 3, grille),
      gest->liste_boite->liste[3]->elements[1]
    ),
    -1000, 100000, 15
  );
  charger_compteur(compteurs[0], gest);

  compteurs[1] = init_compteur(
    position_contenu(
      grille_coord(10, 3, grille),
      gest->liste_boite->liste[4]->elements[1]
    ),
    1, 100, 15
  );
  charger_compteur(compteurs[1], gest);

  graphes[0] = init_graph_kppv(
    position_contenu(
      grille_coord(50, 50, grille),
      gest->liste_boite->liste[1]->elements[1]
    )
  );

  tab = chargement_fichier("out.dat");
  graph_kppv_ajouter_tab_pts(tab, graphes[0]);
  graph_kppv_aff(graphes[0]);

  charger_graph_kppv(graphes[0], gest);

  gests_fichier[0] = init_gest_fichier(
    position_contenu(
      grille_coord(25, 3, grille),
      gest->liste_boite->liste[5]->elements[1]
    ),
    "ressources/data/"
  );
  ajouter_icon_gest_fichier("ressources/img/load.png", gests_fichier[0]);
  charger_gest_fichier(gests_fichier[0], gest);

  gests_fichier[1] = init_gest_fichier(
    position_contenu(
      grille_coord(25, 3, grille),
      gest->liste_boite->liste[5]->elements[2]
    ),
    "ressources/data/"
  );
  ajouter_icon_gest_fichier("ressources/img/save.png", gests_fichier[1]);
  charger_gest_fichier(gests_fichier[1], gest);
}

void demarrer_interface(Manager gest){
  int sortie = 0, i;
  Id_Obj obj;
  MLV_Event evenement = MLV_NONE;
  MLV_Clickable click;
  MLV_Keylogger keylog;

  Info_Periphs periphs = init_info_periph();

  while (!sortie) {
    evenement = maj_evenement(periphs);

    switch(evenement){
      case MLV_NONE : // Aucun évènement récupéré
        break;
      case MLV_KEY : // L'utilisateur a utilisé le clavier
        for (i = 0; i < gest->liste_keylog->nb_keylog; i++){
          keylog = gest->liste_keylog->liste[i];
          if (keylog != NULL){
            obj = keylog_lancer_fct(keylog, periphs->clavier);
          }
        }
        break;
      case MLV_INPUT_BOX : // L'utilisateur a utilisé une boîte de saisie.
        break;
      case MLV_MOUSE_BUTTON : // L'utilisateur a utilisé un bouton de la souris
        for (i = 0; i < gest->liste_click->nb_clicks; i++){
          click = gest->liste_click->liste[i];
          if (click != NULL) {
            obj = click_lancer_fct(click, periphs->souris);
            maj_elements(obj);
          }
        }
        break;
      case MLV_MOUSE_MOTION : // L'utilisateur a déplacé la souris
        break;
      default:
        fprintf(stderr,
        "Erreur : la valeur de l'évènement récupéré est impossible.");
        sortie = 1;
    }

    affichage_fenetre(gest);
    MLV_actualise_window();
  }
}
