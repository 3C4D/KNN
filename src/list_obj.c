#include <stdlib.h>
#include "list_obj.h"
#include "erreur.h"

/*Un List est une liste de String dynamique, ici elle est surtout utilisée pour
récupérer les arguements d'une fonction*/

/*Crée une liste vide*/
List List_new() {
  List l = malloc(sizeof(struct _List_s));
  verif_alloc((void *)l);
  l->elem = NULL;
  l->last = -1;

  return l;
}

/*Ajoute un element à la liste*/
void List_push(List list, char *str) {
  String s = String_new(str);
  list->last++;
  list->elem = realloc(list->elem, list->last * sizeof(String) + 1);
  verif_alloc((void *)list->elem);
  list->elem[list->last] = s;
}

/*Sort un élément de la liste*/
String List_pop(List list){
  String out;

  if (list->last == -1) {
    return NULL;
  }

  out  = list->elem[list->last];
  list->last--;
  list->elem = realloc(list->elem, list->last * sizeof(String) + 1);
  verif_alloc((void *)list->elem);
  return out;
}

/*Vide la liste*/
void List_empty_all(List list){
  String tmp_str;
  while ((tmp_str = List_pop(list)) != NULL) {
    String_free(&tmp_str);
  }
  list->elem = NULL;
  list->last = -1;
}

/*Libère l'espace mémoire pris par une liste*/
void List_free(List list) {
  List_empty_all(list);
  free(list);
}
