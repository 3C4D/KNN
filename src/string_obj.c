#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_obj.h"
#include "erreur.h"

/*Un String est une chaîne de caractères dynamique, cette flexibilité est très
utile pour l'analyse et l'édition de texte*/

/*Crée un String à partir d'une chaîne de caractères*/
String String_new(const char *str){
  int len_str = strlen(str);
  String s = malloc(sizeof(struct _String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (len_str + 1));
  verif_alloc((void *)s->str);
  strcpy(s->str, str);
  s->length = len_str;

  return s;
}

String String_new_pat(const char *pattern, int count){
  int i;
  int len_str = strlen(pattern) * count;
  String s = malloc(sizeof(struct _String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (len_str + 1));
  verif_alloc((void *)s->str);
  s->str[0] = '\0';
  for (i = 0; i < count; i++){
    strcat(s->str, pattern);
  }
  s->length = len_str;

  return s;
}

/*Crée un String vide*/
String String_new_empty(int length){
  String s = malloc(sizeof(struct _String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (length + 1));
  verif_alloc((void *)s->str);
  memset(s->str, 0, length + 1);
  s->length = length;

  return s;
}

/*(Ré)initilise la valeur d'un String à partir d'une chaîne de caractère*/
void String_set(String str, const char *new_str){
  int len_new_str = strlen(new_str);

  str->str = realloc(str->str, sizeof(char) * (len_new_str + 1));
  verif_alloc((void *)str->str);
  strcpy(str->str, new_str);
  str->length = len_new_str;
}

/*(Ré)initilise la valeur d'un String à partir d'un entier*/
void String_set_int(String str, int entier){
  char int_buff[12];
  int len_new_str;
  memset(int_buff, 0, 12 * sizeof(char));
  sprintf(int_buff, "%d", entier);
  len_new_str = strlen(int_buff);

  str->str = realloc(str->str, sizeof(char) * (len_new_str + 1));
  verif_alloc((void *)str->str);
  strcpy(str->str, int_buff);
  str->length = len_new_str;
}

/*Crée une copie d'un String*/
void String_copy(String dest, const String src){
  dest->length = src->length;
  dest->str = realloc(dest->str, src->length + 1);
  verif_alloc((void *)dest->str);
  strcpy(dest->str, src->str);
}

/*Libère l'espace mémoire occupé par un String*/
void String_free(String str) {
  free(str->str);
  free(str);
}

/*Compte le nombre d'occurence d'un paterne dans un String*/
int String_count(const String str, const char *substr){
  int count = 0;
  char *tmp_str = str->str;

  while ((tmp_str = strstr(tmp_str, substr))) {
    tmp_str++;
    count ++;
  }

  return count;
}

/*Trouve l'index de la 1ere occurence d'un paterne dans un String*/
int String_find(const String str, const char *substr){
  int index = -1;
  char *tmp_str = str->str;

  tmp_str = strstr(tmp_str, substr);

  if(tmp_str != NULL){
    index = (int)(tmp_str - str->str);
  }

  return index;
}

/*Trouve l'index de la nieme occurence d'un paterne dans un String*/
int String_find_nth(const String str, const char *substr, int occ_num){
  int index = -1, i;
  char *tmp_str = str->str;
  int occ_max = String_count(str, substr);

  if (occ_num > occ_max) {
    return index;
  }

  for (i = 0; i < occ_num; i++) {
    tmp_str = strstr(tmp_str, substr);

    if (i != (occ_num - 1)) {
      tmp_str++;
    }
  }

  if(tmp_str != NULL){
    index = (int)(tmp_str - str->str);
  }

  return index;
}

/*Crée une sous-chaine de la chaine du String*/
void String_substr(String str, int index, int length){
  str->length = length;
  memmove(str->str, str->str + index, length);
  str->str[length] = '\0';
  str->str = realloc(str->str, length + 1);
  verif_alloc((void *)str->str);
}

/*Concatène 2 String*/
void String_concat(String str1, String str2){
  int concat_len = str1->length + str2->length;

  str1->length = concat_len;
  str1->str = realloc(str1->str, concat_len + 1);
  verif_alloc((void *)str1->str);
  strcat(str1->str, str2->str);
}

/*Remplace un paterne par un autre dans un String*/
void String_replace(String str, const char *old, const char *new) {
  int ind, len_old;
  String tmp_str = String_new_empty(0);
  String new_str = String_new(new);
  String out_str = String_new_empty(0);

  while ((ind = String_find(str, old)) != -1) {
    String_set(out_str, "");
    String_copy(tmp_str, str);
    String_substr(tmp_str, 0, ind);

    String_concat(out_str, tmp_str);
    String_concat(out_str, new_str);

    String_copy(tmp_str, str);
    len_old = strlen(old);
    String_substr(tmp_str, ind + len_old, tmp_str->length - (ind + len_old));
    String_concat(out_str, tmp_str);

    String_copy(str, out_str);
  }

  String_free(new_str);
  String_free(tmp_str);
  String_free(out_str);
}
