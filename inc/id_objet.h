/*
Les Id_Obj permettent d'identifier quel genre d'objet est utilisé dans une 
fonction et donc de pouvoir prendre des decisions adequate (cf. lien_elem.c)
*/

#ifndef ID_OBJ_H_
#define ID_OBJ_H_

typedef enum {
  NON_DEFINI,
  CLICKABLE, 
  HOVERABLE, 
  KEYLOGGER, 
  BUTTON, 
  TOGGLE, 
  CHECKBOX, 
  SPINBOX,
  COMBOBOX,
  INPUT,
  FILEMAN,
  GRAPH,
  GKPPV
} Id_Obj;

#endif