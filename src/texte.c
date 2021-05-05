#include "texte.h"
#include "couleur.h"
#include "erreur.h"

/*-----==========Gestion du formattage==========-----*/
/* Crée un formattage de texte */
MLV_Text_Format init_format(
  MLV_Text_justification justif,
  MLV_Horizontal_position h_pos,
  MLV_Vertical_position v_pos
){
  MLV_Text_Format format = malloc(sizeof(struct MLV_Text_Format_s));
  verif_alloc(format);
  format->justif = justif;
  format->h_pos = h_pos;
  format->v_pos = v_pos;

  return format;
}

/* Crée un formattage par défaut => Centré verticalement et collé à gauche */
MLV_Text_Format init_format_defaut(){
  MLV_Text_Format format = malloc(sizeof(struct MLV_Text_Format_s));
  verif_alloc(format);
  format->justif = MLV_TEXT_LEFT;
  format->h_pos = MLV_HORIZONTAL_LEFT;
  format->v_pos = MLV_VERTICAL_CENTER;

  return format;
}

/* Crée un fomattage centré => Centré verticalement et horizontalement */
MLV_Text_Format init_format_centre(){
  MLV_Text_Format format = malloc(sizeof(struct MLV_Text_Format_s));
  verif_alloc(format);
  format->justif = MLV_TEXT_LEFT;
  format->h_pos = MLV_HORIZONTAL_CENTER;
  format->v_pos = MLV_VERTICAL_CENTER;

  return format;
}

/* Libère l'espace occupé par le formattage */
void liberer_format(MLV_Text_Format *format){
  if (*format != NULL) {
    free(*format);
  }

  *format = NULL;
}

/*-----==========Gestion du texte==========-----*/
/* Ajoute le padding du contenu du texte (composé de " ") */
void texte_ajout_remplissage(MLV_Text texte);
/* Enlève le padding du contenu du texte */
void texte_suppr_remplissage(MLV_Text texte);
/* Crée un texte */
MLV_Text init_texte(int remplissage, MLV_Position pos, MLV_Text_Format format) {
  MLV_Text texte = malloc(sizeof(struct MLV_Text_s));
  verif_alloc(texte);
  texte->msg = String_new_empty(0);
  texte->couleur = couleur_hex("abb2bf"); /* Couleur par défaut */
  texte->remplissage = remplissage;
  texte->placement = pos;
  texte->format = format;
  texte->visible = true;
  texte->bordure = true;

  return texte;
}

/* Libère l'espace occupé par le texte */
void liberer_texte(MLV_Text *texte){
  if (*texte != NULL) {
    String_free(&(*texte)->msg);
    liberer_position(&(*texte)->placement);
    liberer_format(&(*texte)->format);
    free(*texte);
  }

  *texte = NULL;
}

/* Retourne le contenu du texte */
String contenu_texte(MLV_Text texte){
  return (texte->msg);
}

/* Change la couleur du texte */
void texte_changer_couleur(MLV_Color col, MLV_Text texte){
  texte->couleur = col;
}


void texte_ajout_remplissage(MLV_Text texte){
  String espaces = String_new_pat(" ", texte->remplissage);

  String_concat(espaces, texte->msg);
  String_copy(texte->msg, espaces);

  String_free(&espaces);
}

void texte_suppr_remplissage(MLV_Text texte){
  String_substr(
    texte->msg, texte->remplissage, 
    texte->msg->length - texte->remplissage
  );
}

/* Change le contenu du texte */
void modif_texte(char *chaine, MLV_Text texte){
  String msg = String_new(chaine);

  String_copy(texte->msg, msg);

  String_free(&msg);
}

/* Change le contenu du texte à partir de la représentation d'un entier */
void modif_texte_int(int val, MLV_Text texte){
  String entier = String_new_empty(0);

  String_set_int(entier, val);
  String_copy(texte->msg, entier);

  String_free(&entier);
}

/* Concatène str au contenu du texte */
void texte_ajouter_str(char *str, MLV_Text texte){
  String chaine = String_new(str);
  String_concat(texte->msg, chaine);

  String_free(&chaine);
}

/* Concatène n au contenu du texte si celui-ci est un chiffre */
void texte_ajouter_int(char *n, MLV_Text texte){
  if (n[0] >= '0' && n[0] <= '9'){
    texte_ajouter_str(n, texte);
  }
}

/* Supprime un charactère du contenu du texte */
void texte_suppr_char(MLV_Text texte){
  int dernier_carac = texte->msg->length - 1;
  int i;

  /* Si il n'y a plus de caractère dans le contenu */
  if (dernier_carac < 0){
    return;
  }
  
  /* Si le caractère est codé sur 1 octet (norme utf-8) => 0xxxxxxx*/
  if ((unsigned char)texte->msg->str[dernier_carac] < 128){
    String_substr(texte->msg, 0, dernier_carac);
  } else {
    /* Tant que la char actuel est de la for 10xxxxxx */
    i = 1;
    while ((unsigned char)texte->msg->str[dernier_carac - i] < 192){
      i++;
    }
    String_substr(texte->msg, 0, dernier_carac - i);
  }
}

/* Change la visibilité du texte */
void texte_changer_visibilite(MLV_Text texte){
  if (texte_est_visible(texte))
    texte_invisible(texte);
  else
    texte_visible(texte);
}

/* Rend le texte visible */
void texte_visible(MLV_Text texte){
  texte->visible = true;
}

/* Rend le texte invisible */
void texte_invisible(MLV_Text texte){
  texte->visible = false;
}

/* Retourne 1 si le texte est visible, sinon 0 */
bool texte_est_visible(MLV_Text texte){
  return (texte->visible);
}

/* Distance du texte du côté gauche en allant vers la droite */
void texte_changer_bordure(MLV_Text texte){
  if (texte->bordure) {
    texte->bordure = false;
  } else {
    texte->bordure = true;
  }
}

/* Distance du texte du haut en allant vers le bas */
int dist_texte_droite(MLV_Text texte){
  int x, droite;

  texte_ajout_remplissage(texte);

  if (texte->format->h_pos == MLV_HORIZONTAL_LEFT){
    /* Si le texte est à gauche */
    MLV_get_size_of_text(texte->msg->str, &x, NULL);
    droite = x;
  }
  else if (texte->format->h_pos == MLV_HORIZONTAL_RIGHT){
    /* Si le texte est à droite */
    droite = texte->placement->dimension.x;
  }
  else{
    /* Si le texte est centré */
    MLV_get_size_of_text(texte->msg->str, &x, NULL);
    droite = x + (texte->placement->dimension.x - x)  / 2;
  }

  texte_suppr_remplissage(texte);
  
  return droite;
}

int dist_texte_bas(MLV_Text texte){
  int y, bas;
  
  texte_ajout_remplissage(texte);

  if (texte->format->v_pos == MLV_VERTICAL_TOP){
    /* Si le texte est en haut */
    MLV_get_size_of_text(texte->msg->str, NULL, &y);
    bas = y;
  }
  else if (texte->format->v_pos == MLV_VERTICAL_BOTTOM){
    /* Si le texte est à bas */
    bas = texte->placement->dimension.y;
  }
  else{
    /* Si le texte est au milieu */
    MLV_get_size_of_text(texte->msg->str, NULL, &y);
    bas = y + (texte->placement->dimension.y - y)  / 2;
  }

  texte_suppr_remplissage(texte);

  return bas;
}

/* Affiche le texte sur l'interface */
void afficher_texte(MLV_Text texte){
  MLV_Color bordure;
  /* Affichage de la bordure */
  if (texte->bordure) {
    bordure = texte->couleur;
  } else {
    bordure = couleur_hex("00000000");
  }

  texte_ajout_remplissage(texte);

  /* Affichage du texte */
  MLV_draw_text_box (
    texte->placement->decalage.x, texte->placement->decalage.y,
    texte->placement->dimension.x, texte->placement->dimension.y,
    texte->msg->str, 1,
    bordure,
    texte->couleur,
    couleur_hex("00000000"), /* Le fond est toujours transparent */
    texte->format->justif, texte->format->h_pos, texte->format->v_pos
  );

  texte_suppr_remplissage(texte);
}
