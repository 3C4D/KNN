#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_obj.h"
#include "math_op.h"
#include "erreur.h"

/*-----Fonctions privées-----*/
/* Calcule la taille maximale adaptée => puissance de 2 supérieure */
int calc_adap_size(int size);
/* Change la taille allouée si besoin */
void String_adapted_size(int new_len, String s);

/*-----==========Création de String==========-----*/
/* Crée un nouveau String à partir d'une chaine de caractères */
String String_new(const char *str){
  int len_str = strlen(str);
  int max_len = calc_adap_size(len_str);
  String s = malloc(sizeof(struct String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (max_len + 1));
  verif_alloc((void *)s->str);
  strcpy(s->str, str); /* Copie de la valeur de str dans s->str */
  s->length = len_str;
  s->max_len = max_len;

  return s;
}

/* Crée un nouveau String à partir d'une chaine de caractères
faisant office de patterne répété [count] fois */
String String_new_pat(const char *pattern, int count){
  int i;
  int len_str = strlen(pattern) * count;
  int max_len = calc_adap_size(len_str);
  String s = malloc(sizeof(struct String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (max_len + 1));
  verif_alloc((void *)s->str);
  s->str[0] = '\0'; /* s->str = "" => Concaténation immédiate possible */
  for (i = 0; i < count; i++){
    strcat(s->str, pattern);
  }
  s->length = len_str;
  s->max_len = max_len;

  return s;
}

/* Crée un nouveau String vide avec une taille allouée de minimum [length] */
String String_new_empty(int length){
  int max_len = calc_adap_size(length);
  String s = malloc(sizeof(struct String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (max_len + 1));
  verif_alloc((void *)s->str);
  memset(s->str, 0, max_len + 1); /* Initialise l'espace alloué avec des 0s */
  s->length = length;
  s->max_len = max_len;

  return s;
}

/* Libère l'espace mémoire occupé par [*str] */
void String_free(String *str) {
  if (*str != NULL){
    free((*str)->str);
    free(*str);
  }
  
  *str = NULL;
}

void String_adapted_size(int new_len, String s){
  int new_max = calc_adap_size(new_len);
  if (new_max != s->max_len){
    s->max_len = new_max;
    s->str = realloc(s->str, s->max_len + 1);
    verif_alloc(s->str);
  }
}

int calc_adap_size(int size){
  if (size <= MIN_STR_LEN){ /* Minimum imposé */
    return MIN_STR_LEN;
  } else {
    /* Calcule 2^⎡log2(size)⎤ <=> Puissance de 2 strictement supérieure à size*/
    return (1 << entier_sup(log_bin(size)));
  }
}

/*-----==========Initialisation de String==========-----*/
/* Change la valeur de la chaine du String pour [new_str] */
void String_set(String str, const char *new_str){
  int len_new_str = strlen(new_str);
  String_adapted_size(len_new_str, str);

  strcpy(str->str, new_str);
  str->length = len_new_str;
}

/* Change la valeur de la chaine du String pour la représention de [entier] */
void String_set_int(String str, int entier){
  /* Le int le plus long étant -2147483648, soit 11 caractère un buffer de 12
  char est suffisant */
  char int_buff[12];
  int len_new_str;
  /* Initialisation du buffer avec des 0s */
  memset(int_buff, 0, 12 * sizeof(char));
  /* Copie de la représentation de entier dans int_buff */
  sprintf(int_buff, "%d", entier);
  len_new_str = strlen(int_buff);
  String_adapted_size(len_new_str, str);

  strcpy(str->str, int_buff);
  str->length = len_new_str;
}

/* Copie la valeur de [src] dans [dest] */
void String_copy(String dest, const String src){
  dest->length = src->length;
  String_adapted_size(dest->length, dest);
  strcpy(dest->str, src->str);
}

/*-----==========Recherche dans un String==========-----*/
/* Trouve le nombre d'occurence du paterne [substr] dans le String */
int String_count(const String str, const char *substr){
  int count = 0;
  char *tmp_str = str->str;

  /* strstr renvoie l'adresse de la 1ere occurence de substr dans tmp_str
  ou alors renvoie NULL.
  L'adresse de tmp_str est changée pour celle de l'occurence + 1,
  ainsi strstr devrat trouver l'occurence suivante au prochain tours */
  while ((tmp_str = strstr(tmp_str, substr))) {
    tmp_str++;
    count ++;
  }

  return count;
}

/* Trouve l'index de la 1ere occurence du paterne [substr] dans le String */
int String_find(const String str, const char *substr){
  int index = -1;
  char *tmp_str = str->str;

  /* strstr renvoie l'adresse de la 1ere occurence de substr dans tmp_str
  ou alors renvoie NULL. */
  tmp_str = strstr(tmp_str, substr);

  if(tmp_str != NULL){
    /* Pour connaitre l'index, on utilise de l'arthmétique sur les adresses,
    index = adresse_de_l'occurence - adresse_de_la_chaine */
    index = (int)(tmp_str - str->str);
  }

  return index;
}

/* Trouve l'index de la dernière occurence du paterne [substr] dans le String */
int String_find_last(const String str, const char *substr){
  int nb_occ = String_count(str, substr);
  int index = String_find_nth(str, substr, nb_occ);

  return index;
}

/* Trouve l'index de la n-ième occurence du paterne [substr] dans le String */
int String_find_nth(const String str, const char *substr, int occ_num){
  int index = -1, i;
  char *tmp_str = str->str;
  int occ_max = String_count(str, substr);

  if (occ_num > occ_max) {
    return index;
  }

  for (i = 0; i < occ_num; i++) {
    /* strstr renvoie l'adresse de la 1ere occurence de substr dans tmp_str
    ou alors renvoie NULL. */
    tmp_str = strstr(tmp_str, substr);

    /* On applique le décalage pour strstr si l'occurence trouvé n'est pas 
    celle voulu */
    if (i != (occ_num - 1)) {
      tmp_str++;
    }
  }

  if(tmp_str != NULL){
    index = (int)(tmp_str - str->str);
  }

  return index;
}

/*-----==========Modification de String==========-----*/
/* Partionne le String [str] en 2 parties,
[str] contiendrat la partie de longueur [len],
[split] contiendrat le reste */
void String_split(int len, String str, String split){
  String cpy = String_new_empty(0);
  
  if (split != NULL){
    String_copy(cpy, str);
    String_substr(cpy, len, cpy->length - len);
    String_copy(split, cpy);
  }

  String_substr(str, 0, len);
  String_free(&cpy);
}

/* Récupère dans [str] une sous chaine 
commençant à [index] et de longueur [length] */
void String_substr(String str, int index, int length){
  if (index + length > str->length){
    return;
  }
  
  str->length = length;
  /* Décalage des char de l'index [index] vers l'index 0 */
  memmove(str->str, str->str + index, length);
  str->str[length] = '\0';
  String_adapted_size(length, str);
}

/* Concatène dans [str1] les valeurs de [str1] et [str2] */
void String_concat(String str1, String str2){
  int concat_len = str1->length + str2->length;
  String_adapted_size(concat_len, str1);

  str1->length = concat_len;
  strcat(str1->str, str2->str);
}

/* Concatène dans [str] les valeurs de [str] et [concat] */
void String_concat_str(String str, char const *concat){
  String conc_str = String_new(concat);
  String_concat(str, conc_str);
  String_free(&conc_str);
}

/* Remplace dans [str] le paterne [old] par [new]*/
void String_replace(String str, const char *old, const char *new) {
  int ind, len_old = strlen(old);
  String out_str = String_new_empty(0);
  String split_str = String_new_empty(0);
  String_copy(out_str, str); 

  while ((ind = String_find(out_str, old)) != -1) {
    String_split(ind, out_str, split_str);
    String_concat_str(out_str, new);
    String_substr(split_str, len_old, split_str->length - len_old);
    String_concat(out_str, split_str);
  }
  String_copy(str, out_str);

  String_free(&split_str);
  String_free(&out_str);
}
