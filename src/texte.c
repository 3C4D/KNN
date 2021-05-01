#include "texte.h"
#include "couleur.h"
#include "erreur.h"

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

MLV_Text_Format init_format_defaut(){
  MLV_Text_Format format = malloc(sizeof(struct MLV_Text_Format_s));
  verif_alloc(format);
  format->justif = MLV_TEXT_LEFT;
  format->h_pos = MLV_HORIZONTAL_LEFT;
  format->v_pos = MLV_VERTICAL_CENTER;

  return format;
}

MLV_Text_Format init_format_centre(){
  MLV_Text_Format format = malloc(sizeof(struct MLV_Text_Format_s));
  verif_alloc(format);
  format->justif = MLV_TEXT_LEFT;
  format->h_pos = MLV_HORIZONTAL_CENTER;
  format->v_pos = MLV_VERTICAL_CENTER;

  return format;
}

void liberer_format(MLV_Text_Format *format){
  if (*format != NULL) {
    free(*format);
  }

  *format = NULL;
}

MLV_Text init_texte(int remplissage, MLV_Position pos, MLV_Text_Format format) {
  MLV_Text texte = malloc(sizeof(struct MLV_Text_s));
  verif_alloc(texte);
  texte->msg = String_new_empty(0);
  texte->couleur = couleur_hex("abb2bf");
  texte->remplissage = remplissage;
  texte->placement = pos;
  texte->format = format;
  texte->visible = true;
  texte->bordure = true;

  return texte;
}

void liberer_texte(MLV_Text *texte){
  if (*texte != NULL) {
    String_free(&(*texte)->msg);
    liberer_position(&(*texte)->placement);
    liberer_format(&(*texte)->format);
    free(*texte);
  }

  *texte = NULL;
}

String contenu_texte(MLV_Text texte){
  return (texte->msg);
}

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

void modif_texte(char *chaine, MLV_Text texte){
  String msg = String_new(chaine);

  String_copy(texte->msg, msg);

  String_free(&msg);
}

void modif_texte_int(int val, MLV_Text texte){
  String entier = String_new_empty(0);

  String_set_int(entier, val);
  String_copy(texte->msg, entier);

  String_free(&entier);
}

void texte_ajouter_str(char *str, MLV_Text texte){
  String chaine = String_new(str);
  String_concat(texte->msg, chaine);

  String_free(&chaine);
}

void texte_ajouter_int(char *n, MLV_Text texte){
  if (n[0] >= '0' && n[0] <= '9'){
    texte_ajouter_str(n, texte);
  }
}

void texte_suppr_char(MLV_Text texte){
  int dernier_carac = texte->msg->length - 1;
  int i;
  if (dernier_carac < 0){
    return;
  }
  
  if ((unsigned char)texte->msg->str[dernier_carac] < 128){
    String_substr(texte->msg, 0, dernier_carac);
  } else {
    i = 1;
    while ((unsigned char)texte->msg->str[dernier_carac - i] < 192){
      i++;
    }
    String_substr(texte->msg, 0, dernier_carac - i);
  }
}

void texte_changer_visibilite(MLV_Text texte){
  if (texte_est_visible(texte))
    texte_invisible(texte);
  else
    texte_visible(texte);
}

void texte_visible(MLV_Text texte){
  texte->visible = true;
}

void texte_invisible(MLV_Text texte){
  texte->visible = false;
}

bool texte_est_visible(MLV_Text texte){
  return (texte->visible);
}

void texte_changer_bordure(MLV_Text texte){
  if (texte->bordure) {
    texte->bordure = false;
  } else {
    texte->bordure = true;
  }
}

int dist_texte_droite(MLV_Text texte){
  int x, droite;

  texte_ajout_remplissage(texte);
  if (texte->format->h_pos == MLV_HORIZONTAL_LEFT){
    MLV_get_size_of_text(texte->msg->str, &x, NULL);
    droite = x;
  }
  else if (texte->format->h_pos == MLV_HORIZONTAL_RIGHT){
    droite = texte->placement->dimension.x;
  }
  else{
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
    MLV_get_size_of_text(texte->msg->str, NULL, &y);
    bas = y;
  }
  else if (texte->format->v_pos == MLV_VERTICAL_BOTTOM){
    bas = texte->placement->dimension.x;
  }
  else{
    MLV_get_size_of_text(texte->msg->str, NULL, &y);
    bas = y + (texte->placement->dimension.y - y)  / 2;
  }
  texte_suppr_remplissage(texte);

  return bas;
}

void afficher_texte(MLV_Text texte){
  MLV_Color bordure;
  if (texte->bordure) {
    bordure = texte->couleur;
  } else {
    bordure = couleur_hex("00000000");
  }

  texte_ajout_remplissage(texte);

  MLV_draw_text_box (
    texte->placement->decalage.x, texte->placement->decalage.y,
    texte->placement->dimension.x, texte->placement->dimension.y,
    texte->msg->str, 1,
    bordure,
    texte->couleur,
    couleur_hex("00000000"),
    texte->format->justif, texte->format->h_pos, texte->format->v_pos
  );

  texte_suppr_remplissage(texte);
}
