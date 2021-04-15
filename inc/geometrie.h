#ifndef COORD_H_
#define COORD_H_

typedef struct {
  int x;
  int y;
} Coord;

typedef struct {
  double x;
  double y;
} Coord_R;

typedef struct {
  int min;
  int max;
  int pas;
} Axe;

typedef struct {
  double min;
  double max;
  double pas;
} Axe_R;

typedef struct Plan_Z_s *Plan_Z;
struct Plan_Z_s{
  Axe abs;
  Axe ord;
};

typedef struct Plan_R_s *Plan_R;
struct Plan_R_s{
  Axe_R abs;
  Axe_R ord;
};


Coord init_coord(int x, int y);
Coord_R init_coordr(double x, double y);

Axe init_axe(int a, int b);
Axe_R init_axer(double a, double b, double pas);

Plan_Z init_planz(Axe abs, Axe ord);
void liberer_planz(Plan_Z *p);
Plan_R init_planr(Axe_R abs, Axe_R ord);
void liberer_planr(Plan_R *p);

int long_axe(Axe a);
double long_axer(Axe_R a);
int long_rtoz(double longueur, Axe_R axe_in, Axe axe_out);
double long_ztor(int longueur, Axe axe_in, Axe_R axe_out);

Coord coord_info_en_math(Coord c, Plan_Z z);
Coord_R coord_ztor(Coord c, Plan_R r, Plan_Z z);
Coord coord_rtoz(Coord_R cr, Plan_R r, Plan_Z z);
Coord_R coord_ztor(Coord c, Plan_R r, Plan_Z z);

#endif
