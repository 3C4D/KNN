#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_obj.h"
#include "math_op.h"
#include "erreur.h"

/*Un String est une chaîne de caractères dynamique, cette flexibilité est très
utile pour l'analyse et l'édition de texte*/

int calc_adap_size(int size);
void String_adapted_size(int new_len, String s);

void print_d(char *str, int n){
  for (size_t i = 0; i < n; i++){
    printf("%02x", str[i]);
  }
  putchar('\n');
  for (size_t i = 0; i < n; i++){
    putchar(str[i]);
  }
  putchar('\n');
}

/*Crée un String à partir d'une chaîne de caractères*/
String String_new(const char *str){
  int len_str = strlen(str);
  int max_len = calc_adap_size(len_str);
  String s = malloc(sizeof(struct String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (max_len + 1));
  verif_alloc((void *)s->str);
  strcpy(s->str, str);
  s->length = len_str;
  s->max_len = max_len;

  return s;
}

String String_new_pat(const char *pattern, int count){
  int i;
  int len_str = strlen(pattern) * count;
  int max_len = calc_adap_size(len_str);
  String s = malloc(sizeof(struct String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (max_len + 1));
  verif_alloc((void *)s->str);
  s->str[0] = '\0';
  for (i = 0; i < count; i++){
    strcat(s->str, pattern);
  }
  s->length = len_str;
  s->max_len = max_len;

  return s;
}

/*Crée un String vide*/
String String_new_empty(int length){
  int max_len = calc_adap_size(length);
  String s = malloc(sizeof(struct String_s));
  verif_alloc((void *)s);

  s->str = malloc(sizeof(char) * (max_len + 1));
  verif_alloc((void *)s->str);
  memset(s->str, 0, max_len + 1);
  s->length = length;
  s->max_len = max_len;

  return s;
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
  if (size <= MIN_STR_LEN){
    return MIN_STR_LEN;
  } else {
    return (1 << entier_sup(log_bin(size)));
  }
}

/*(Ré)initilise la valeur d'un String à partir d'une chaîne de caractère*/
void String_set(String str, const char *new_str){
  int len_new_str = strlen(new_str);
  String_adapted_size(len_new_str, str);

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
  String_adapted_size(len_new_str, str);

  strcpy(str->str, int_buff);
  str->length = len_new_str;
}

/*Crée une copie d'un String*/
void String_copy(String dest, const String src){
  dest->length = src->length;
  String_adapted_size(dest->length, dest);
  strcpy(dest->str, src->str);
}

/*Libère l'espace mémoire occupé par un String*/
void String_free(String *str) {
  if (*str != NULL){
    free((*str)->str);
    free(*str);
  }
  
  *str = NULL;
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

int String_find_last(const String str, const char *substr){
  int nb_occ = String_count(str, substr);
  int index = String_find_nth(str, substr, nb_occ);

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

/*Crée une sous-chaine de la chaine du String*/
void String_substr(String str, int index, int length){
  if (index + length > str->length){
    return;
  }
  
  str->length = length;
  memmove(str->str, str->str + index, length);
  str->str[length] = '\0';
  String_adapted_size(length, str);
}

/*Concatène 2 String*/
void String_concat(String str1, String str2){
  int concat_len = str1->length + str2->length;
  String_adapted_size(concat_len, str1);

  str1->length = concat_len;
  strcat(str1->str, str2->str);
}

void String_concat_str(String str, char const *concat){
  String conc_str = String_new(concat);
  String_concat(str, conc_str);
  String_free(&conc_str);
}

/*Remplace un paterne par un autre dans un String*/
void String_replace(String str, const char *old, const char *new) {
  int ind, len_old = strlen(old);;
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
