#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
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

/* Dimensions de la grille */
#define GRILLE_X 90
#define GRILLE_Y 60

/* Fonction lancée lorsque l'on sort de l'interface */
void sortie_interface(void *val);
/* Place les boites et les conteneurs sur l'interface */
void mise_en_place(Grid grille, Manager gest);
/* Ajoute les éléments dans les conteneurs */
void ajout_elements(Grid grille, Manager gest);
/* Démarre la boucle infinie de l'interface */
void demarrer_interface(Manager gest, int *stop);
/* Finalise la sortie (e.g. Libération de la mémoire) */
void fin_interface(Manager gest);

/* Lance l'interface */
int lancer_interface() {
  Manager gestionnaire = init_gestionnaire();
  MLV_Canvas fond;
  int sortie = 0; /* Sera mis à 1 lors de la sortie */
  /* La hauteur de la fenếtre fait la moitié de la hauteur de l'écran */
  int echelle = MLV_get_desktop_height() / 2;
  /* Initialisation de la grille */
  Grid grille = init_grille(
    GRILLE_X, GRILLE_Y,
    echelle,
    false
  );
  int hauteur = grille_hauteur(grille);
  int longueur = grille_longueur(grille);

  /* Execute la fonction sortie_interface lors de la sortie d'interface */
  MLV_execute_at_exit(sortie_interface, &sortie);

  MLV_create_window_with_default_font(
    "K Plus Proches Voisins", "KPPV",
    longueur, hauteur,
    "ressources/polices/Lato-Thin.ttf", (int)(echelle / 45)
  );

  /* Mise en place du fond */
  fond = init_canvas(
    grille_pos(0, 0, GRILLE_X, GRILLE_Y, grille), true
  );
  couleur_fond_canvas(couleur_hex("21252b"), fond);
  ajouter_canvas(fond, gestionnaire->liste_canvas);

  /* Mise en place des éléments */
  mise_en_place(grille, gestionnaire);
  ajout_elements(grille, gestionnaire);

  /* Démarrage de l'interface */
  demarrer_interface(gestionnaire, &sortie);
  fin_interface(gestionnaire);

  return 0;
}

void sortie_interface(void *val){
  int *sortie = (int *)val;
  *sortie = 1; /* Met la varible sortie à 1 */
}

void fin_interface(Manager gest){
  printf("Au revoir et à bientôt ;)\n");

  /* Libération de la mémoire */
  liberer_gestionnaire(&gest);
  MLV_free_window();
}

void mise_en_place(Grid grille, Manager gest){
  MLV_Box boite;
  MLV_Container cont;
  MLV_Position pos;

  /* Placement de la boite principale: [0] */
  pos = grille_pos(4, 2, GRILLE_X - 7, GRILLE_Y - 4, grille);
  boite = init_boite(HORIZONTAL, pos);
  cont = init_conteneur_centre();
  /* Conteneur gauche: [0][1]
    - Graphique kppv
    - Bascule choix mode
    - Choix du K */
  ajouter_conteneur(cont, grille_dist(50, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur droit: [0][1]
    - Choix classe
    - Bouton retour
    - Options d'affichage
    - Gestion des fichiers */
  ajouter_conteneur(cont, grille_dist(33, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  /* Placement de la boite gauche secondaire [1] */
  boite = placer_boite(
    grille_coord(50, 56, grille),
    VERTICAL, gest->liste_boite->liste[0]->elements[0] /* Conteneur gauche */
  );
  cont = init_conteneur_centre();
  /* Conteneur K+mode: [1][0]
    - Bascule choix mode
    - Choix du K */
  ajouter_conteneur(cont, grille_dist(4, grille), boite);

  ajouter_remplissage(grille_dist(2, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur graph kppv: [1][1]
    - Graphique kppv */
  ajouter_conteneur(cont, grille_dist(50, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  /* Placement de la boite droite secondaire [2] */
  boite = placer_boite(
    grille_coord(33, 56, grille),
    VERTICAL, gest->liste_boite->liste[0]->elements[1] /* Conteneur droit */
  );
  ajouter_remplissage(grille_dist(6, grille), boite);

  cont = init_conteneur(MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER);
  /* Conteneur Retour+Classe: [2][0]
    - Choix classe
    - Bouton retour */
  ajouter_conteneur(cont, grille_dist(10, grille), boite);

  ajouter_remplissage(grille_dist(1, grille), boite);

  cont = init_conteneur(MLV_HORIZONTAL_RIGHT, MLV_VERTICAL_CENTER);
  /* Conteneur OptAff+Fichiers: [2][1]
    - Options d'affichage
    - Gestion des fichiers */
  ajouter_conteneur(cont, grille_dist(31, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  /* Placemenet de la boite K+mode [3] */
  boite = placer_boite(
    grille_coord(50, 4, grille),
    HORIZONTAL, gest->liste_boite->liste[1]->elements[0] /* Conteneur K+mode */
  );
  cont = init_conteneur(MLV_HORIZONTAL_LEFT, MLV_VERTICAL_CENTER);
  /* Conteneur Mode: [3][0]
    - Bascule mode */
  ajouter_conteneur(cont, grille_dist(20, grille), boite);

  ajouter_remplissage(grille_dist(10, grille), boite);

  cont = init_conteneur(MLV_HORIZONTAL_RIGHT, MLV_VERTICAL_CENTER);
  /* Conteneur Label K: [3][1]
    - Label compteur K */
  ajouter_conteneur(cont, grille_dist(10, grille), boite);

  cont = init_conteneur(MLV_HORIZONTAL_RIGHT, MLV_VERTICAL_CENTER);
  /* Conteneur Compteur K: [3][2]
    - Compteur K */
  ajouter_conteneur(cont, grille_dist(10, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  /* Placemenet de la boite Retour+Classe [4] */
  boite = placer_boite(
    grille_coord(20, 10, grille),
    VERTICAL, gest->liste_boite->liste[2]->elements[0] /* Conteneur Ret+Class */
  );
  cont = init_conteneur_centre();
  /* Conteneur Retour: [4][0]
    - Bouton Retour */
  ajouter_conteneur(cont, grille_dist(5, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur Classe: [4][1]
    - Choix classe */
  ajouter_conteneur(cont, grille_dist(5, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  /* Placemenet de la boite OptAff+Fichiers [5] */
  boite = placer_boite(
    grille_coord(29, 31, grille),
    VERTICAL, gest->liste_boite->liste[2]->elements[1] /* Conteneur OptA+Fich */
  );
  cont = init_conteneur_centre();
  /* Conteneur OptAff: [5][0]
    - Options d'affichages */
  ajouter_conteneur(cont, grille_dist(21, grille), boite);

  ajouter_remplissage(grille_dist(3, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur Import: [5][1]
    - Import des fichiers */
  ajouter_conteneur(cont, grille_dist(3, grille), boite);

  ajouter_remplissage(grille_dist(1, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur Export: [5][2]
    - Export des fichiers */
  ajouter_conteneur(cont, grille_dist(3, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  /* Placement de la boite OptAff [6] */
  boite = placer_boite(
    grille_coord(29, 21, grille),
    VERTICAL, gest->liste_boite->liste[5]->elements[0] /* Conteneur OptAff */
  );
  cont = init_conteneur_centre();
  /* Conteneur TitreOpt: [6][0] */
  ajouter_conteneur(cont, grille_dist(3, grille), boite);

  ajouter_remplissage(grille_dist(1, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur OptAxes: [6][1] */
  ajouter_conteneur(cont, grille_dist(2, grille), boite);

  ajouter_remplissage(grille_dist(1, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur OptGrille: [6][2] */
  ajouter_conteneur(cont, grille_dist(2, grille), boite);

  ajouter_remplissage(grille_dist(1, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur OptSousGrille: [6][3] */
  ajouter_conteneur(cont, grille_dist(2, grille), boite);

  ajouter_remplissage(grille_dist(1, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur OptCercleKPPV: [6][4] */
  ajouter_conteneur(cont, grille_dist(2, grille), boite);

  ajouter_remplissage(grille_dist(1, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur OptDecision: [6][5] */
  ajouter_conteneur(cont, grille_dist(2, grille), boite);

  ajouter_remplissage(grille_dist(1, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur OptArbre: [6][6] */
  ajouter_conteneur(cont, grille_dist(2, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  /* Placement boite Classe: [7] */
  boite = placer_boite(
    grille_coord(20, 5, grille),
    HORIZONTAL, gest->liste_boite->liste[4]->elements[1] /* Conteneur Classe */
  );
  cont = init_conteneur_centre();
  /* Conteneur LabelClasse: [7][0] */
  ajouter_conteneur(cont, grille_dist(8, grille), boite);

  cont = init_conteneur_centre();
  /* Conteneur Compteur Classe: [7][1] */
  ajouter_conteneur(cont, grille_dist(12, grille), boite);
  ajouter_boite(boite, gest->liste_boite);

  /* Placement de la boite réinitialisation: [8] */
  pos = grille_pos(GRILLE_X - 5, 1, 4, 4, grille);
  boite = init_boite(HORIZONTAL, pos);
  cont = init_conteneur_centre();
  /* Conteneur BoutonReinit: [8][0] */
  ajouter_conteneur(cont, grille_dist(4, grille), boite);
  ajouter_boite(boite, gest->liste_boite);
}

void ajout_elements(Grid grille, Manager gest){
  /* Ajout des boutons */
  boutons[0] = init_bouton(
    position_contenu(
      grille_coord(4, 4, grille),
      gest->liste_boite->liste[8]->elements[0] /* Conteneur BoutonReinit */
    ),
    gkppv_reinit
  );
  bouton_image("ressources/img/reset.png", boutons[0]);
  charger_bouton(boutons[0], gest);

  boutons[1] = init_bouton(
    position_contenu(
      grille_coord(8, 4, grille),
      gest->liste_boite->liste[4]->elements[0] /* Conteneur Retour */
    ),
    NULL
  );
  bouton_image("ressources/img/undo.png", boutons[1]);
  charger_bouton(boutons[1], gest);

  /* Ajout des bascules */
  bascules[0] = init_bascule(
    position_contenu(
      grille_coord(15, 3, grille),
      gest->liste_boite->liste[3]->elements[0] /* Conteneur Mode */
    ),
    NULL, ETAT_A
  );
  bascule_label("Mode Création", "Mode KPPV", bascules[0]);
  charger_bascule(bascules[0], gest);

  /* Ajout des textes-labels */
  labels[0] = init_texte(
    0, position_contenu(
      grille_coord(25, 3, grille),
      gest->liste_boite->liste[6]->elements[0] /* Conteneur TitreOpt */
    ),
    init_format_centre()
  );
  modif_texte("Options d'affichage", labels[0]);
  ajouter_texte(labels[0], gest->liste_texte);

  labels[1] = init_texte(
    0, position_contenu(
      grille_coord(10, 3, grille),
      gest->liste_boite->liste[3]->elements[1] /* Conteneur Label K */
    ),
    init_format_centre()
  );
  modif_texte("Valeur de K:", labels[1]);
  labels[1]->bordure = false;
  ajouter_texte(labels[1], gest->liste_texte);

  labels[2] = init_texte(
    0, position_contenu(
      grille_coord(8, 3, grille),
      gest->liste_boite->liste[7]->elements[0] /* Conteneur LabelClasse */
    ),
    init_format_centre()
  );
  modif_texte("Classe:", labels[2]);
  labels[2]->bordure = false;
  ajouter_texte(labels[2], gest->liste_texte);

  /* Ajout des coches */
  coches[0] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[1] /* Conteneur OptAxes */
    ),
    "Affichage des axes", true
  );
  charger_coche(coches[0], gest);

  coches[1] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[2] /* Conteneur OptGrille */
    ),
    "Affichage de la grille", true
  );
  charger_coche(coches[1], gest);

  coches[2] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[3] /* Conteneur OptSousGrille */
    ),
    "Affichage de la sous-grille", true
  );
  charger_coche(coches[2], gest);

  coches[3] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[4] /* Conteneur OptCercleKPPV */
    ),
    "Affichage des KPPV", false
  );
  charger_coche(coches[3], gest);

  coches[4] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[5] /* Conteneur OptDecision */
    ),
    "Prise de décision", false
  );
  charger_coche(coches[4], gest);

  coches[5] = init_coche(
    position_contenu(
      grille_coord(20, 2, grille),
      gest->liste_boite->liste[6]->elements[6] /* Conteneur OptArbre */
    ),
    "Affichage de l'arbre-kd", false
  );
  charger_coche(coches[5], gest);

  /* Ajout des compteurs */
  compteurs[0] = init_compteur(
    position_contenu(
      grille_coord(10, 3, grille),
      gest->liste_boite->liste[3]->elements[2] /* Conteneur Compteur K */
    ),
    1, INT_MAX, 1
  );
  charger_compteur(compteurs[0], gest);

  compteurs[1] = init_compteur(
    position_contenu(
      grille_coord(12, 3, grille),
      gest->liste_boite->liste[7]->elements[1] /* Conteneur Compteur Classe */
    ),
    1, INT_MAX, 1
  );
  charger_compteur(compteurs[1], gest);

  /* Ajout du graphique KPPV */
  graphes[0] = init_graph_kppv(
    position_contenu(
      grille_coord(50, 50, grille),
      gest->liste_boite->liste[1]->elements[1] /* Conteneur graph kppv */
    )
  );
  charger_graph_kppv(graphes[0], gest);

  /* Ajout des gestionnaires de fichier */
  gests_fichier[0] = init_gest_fichier(
    position_contenu(
      grille_coord(25, 3, grille),
      gest->liste_boite->liste[5]->elements[1] /* Conteneur Import */
    ),
    "ressources/data/", importer_fichier
  );
  ajouter_icon_gest_fichier("ressources/img/load.png", gests_fichier[0]);
  charger_gest_fichier(gests_fichier[0], gest);

  gests_fichier[1] = init_gest_fichier(
    position_contenu(
      grille_coord(25, 3, grille),
      gest->liste_boite->liste[5]->elements[2] /* Conteneur Export */
    ),
    "ressources/data/", exporter_fichier
  );
  ajouter_icon_gest_fichier("ressources/img/save.png", gests_fichier[1]);
  charger_gest_fichier(gests_fichier[1], gest);
}

void demarrer_interface(Manager gest, int *stop){
  int i;
  Id_Obj obj;
  MLV_Event evenement = MLV_NONE;
  MLV_Clickable click;
  MLV_Keylogger keylog;
  Info_Periphs periphs = init_info_periph();

  /* Initialisation des interactions des éléments entre eux */
  init_elements();
  affichage_fenetre(gest);
  MLV_actualise_window();

  while (!*stop) {
    evenement = maj_evenement(periphs);

    switch(evenement){
      case MLV_NONE : /* Aucun évènement récupéré */
        break;
      case MLV_KEY : /* Utilisation du le clavier */
        for (i = 0; i < gest->liste_keylog->nb_keylog; i++){
          keylog = gest->liste_keylog->liste[i];
          if (keylog != NULL){
            obj = keylog_lancer_fct(keylog, periphs->clavier);
            maj_elements(obj);
          }
        }
        affichage_fenetre(gest);
        MLV_actualise_window();
        break;
      case MLV_INPUT_BOX : /* Utilisation d'une boîte de saisie. */
        break;
      case MLV_MOUSE_BUTTON : /* Utilisation d'un bouton de la souris */
        for (i = 0; i < gest->liste_click->nb_clicks; i++){
          click = gest->liste_click->liste[i];
          if (click != NULL) {
            obj = click_lancer_fct(click, periphs->souris);
            maj_elements(obj);
          }
        }
        affichage_fenetre(gest);
        MLV_actualise_window();
        break;
      case MLV_MOUSE_MOTION : /* Déplacement de la souris */
        break;
      default:
        fprintf(stderr,
        "Erreur : la valeur de l'évènement récupéré est impossible.");
        break;
    }
  }

  liberer_info_periph(&periphs);
}
