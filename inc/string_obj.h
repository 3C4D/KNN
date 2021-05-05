/*
Module de création et gestion de chaine de caractères variables
Permet une plus grande flexibilité dans l'utilisation des chaine
avec des foncitons inspirée par  celles présentes par défaut 
dans des langages comme Java ou Python.

Ce module fut crée le 25 Février 2021 par Soam LE DORTZ
*/

#ifndef STRING_OBJ_H
#define STRING_OBJ_H

#define MIN_STR_LEN 16 /* Taille minimale allouée par un String */

struct String_s{
  char *str; /* Chaine de caractère */
  int length; /* Taille de la chaine = strlen(str) */
  int max_len; /* Taille maximale de la chaine avant reallocation */
};
typedef struct String_s *String;

/*-----==========Création de String==========-----*/
/* Crée un nouveau String à partir d'une chaine de caractères */
String String_new(const char *str);
/* Crée un nouveau String vide avec une taille allouée de minimum [length] */
String String_new_empty(int length);
/* Crée un nouveau String à partir d'une chaine de caractères
faisant office de patterne répété [count] fois */
String String_new_pat(const char *pattern, int count);
/* Libère l'espace mémoire occupé par [*str] */
void String_free(String *str);

/*-----==========Initialisation de String==========-----*/
/* Change la valeur de la chaine du String pour [new_str] */
void String_set(String str, const char *new_str);
/* Change la valeur de la chaine du String pour la représention de [entier] */
void String_set_int(String str, int entier);
/* Copie la valeur de [src] dans [dest] */
void String_copy(String dest, const String src);

/*-----==========Recherche dans un String==========-----*/
/* Trouve le nombre d'occurence du paterne [substr] dans le String */
int String_count(const String str, const char *substr);
/* Trouve l'index de la 1ere occurence du paterne [substr] dans le String */
int String_find(const String str, const char *substr);
/* Trouve l'index de la dernière occurence du paterne [substr] dans le String */
int String_find_last(const String str, const char *substr);
/* Trouve l'index de la n-ième occurence du paterne [substr] dans le String */
int String_find_nth(const String str, const char *substr, int occ_num);

/*-----==========Modification de String==========-----*/
/* Partionne le String [str] en 2 parties,
[str] contiendrat la partie de longueur [len],
[split] contiendrat le reste */
void String_split(int len, String str, String split);
/* Récupère dans [str] une sous chaine 
commençant à [index] et de longueur [length] */
void String_substr(String str, int index, int length);
/* Concatène dans [str1] les valeurs de [str1] et [str2] */
void String_concat(String str1, String str2);
/* Concatène dans [str] les valeurs de [str] et [concat] */
void String_concat_str(String str, char const *concat);
/* Remplace dans [str] le paterne [old] par [new]*/
void String_replace(String str, const char *old, const char *new);

#endif
