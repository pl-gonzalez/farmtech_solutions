#ifndef NPK_H
#define NPK_H

#define N_ALTO 23
#define N_MEDIO 22
#define N_BAIXO 21

#define P_ALTO 19
#define P_MEDIO 18
#define P_BAIXO 5

#define K_ALTO 17
#define K_MEDIO 16
#define K_BAIXO 4

enum Irrigar {
  N_OK,
  P_OK,
  K_OK,
  IRRIGAR_N,
  IRRIGAR_P,
  IRRIGAR_K,
  IRRIGAR_NP,
  IRRIGAR_PK,
  IRRIGAR_NK,
  IRRIGAR_NPK,
  IRRIGAR_AGUA,
  IRRIGAR_CAL
};

int medir_N();
int medir_P();
int medir_K();

int verifica_npk();

#endif
