#ifndef LIST_OBJ_H
#define LIST_OBJ_H

#include "string_obj.h"

struct _List_s{
  String *elem;
  int last;
};

typedef struct _List_s *List;

List List_new();
void List_push(List list, char *str);
String List_pop(List list);
void List_empty_all(List list);
void List_free(List list);

#endif
