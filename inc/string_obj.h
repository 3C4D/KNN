#ifndef STRING_OBJ_H
#define STRING_OBJ_H

struct _String_s{
  char *str;
  int length;
};

typedef struct _String_s *String;

String String_new(const char *str);
String String_new_empty(int length);
String String_new_pat(const char *pattern, int count);
void String_set(String str, const char *new_str);
void String_set_int(String str, int entier);
void String_copy(String dest, const String src);
void String_free(String str);
int String_count(const String str, const char *substr);
int String_find(const String str, const char *substr);
int String_find_nth(const String str, const char *substr, int occ_num);
void String_substr(String str, int index, int length);
void String_concat(String str1, String str2);
void String_replace(String str, const char *old, const char *new);

#endif
