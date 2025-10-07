#include <Arduino.h>
#include "npk.h"


/**
 * Mede nivel de NPK
 * 
 * OBS: Nao esta sendo tratado Debouncing e há inputs flutuantes que devrão ser corrigidos no circuito
 *      Os botões são acionado um por vez, visto que nao há como ter nivel baixo e médio ao mesmo tempo (Ctrl + Click no Wokwi)
 * 
 */

int medir_N() {
    int nAlto = digitalRead(N_ALTO);
    int nMedio = digitalRead(N_MEDIO);
    int nBaixo = digitalRead(N_BAIXO);

    int nivel = 0;
    
    if (nAlto == 0){
        Serial.println("Nivel N Alto");
        return nivel = 3;
    }
    
    if (nMedio == 0){
        Serial.println("Nivel N Medio");
        return nivel = 2;
    }
    
    if (nBaixo == 0){
        Serial.println("Nivel N Baixo");
        Serial.println(nBaixo);
        return nivel = 1;
    }
    
    return nivel;
}

int medir_P() {
  int pAlto = digitalRead(P_ALTO);
  int pMedio = digitalRead(P_MEDIO);
  int pBaixo = digitalRead(P_BAIXO);
  
  int nivel = 0;

  if (pAlto == 0){
    Serial.println("Nivel P Alto");
    return nivel = 3;
  }

  if (pMedio == 0){
    Serial.println("Nivel P Medio");
    return nivel = 2;
  }

  if (pBaixo == 0){
    Serial.println("Nivel P Baixo");
    return nivel = 1;
  }
  return nivel;

  
}

int medir_K() {
    int kAlto = digitalRead(K_ALTO);
    int kMedio = digitalRead(K_MEDIO);
    int kBaixo = digitalRead(K_BAIXO);

    int nivel = 0;
    
    if (kAlto == 0){
        Serial.println("Nivel K Alto");
        return nivel = 3;
    }
    
    if (kMedio == 0){
        Serial.println("Nivel K Medio");
        return nivel = 2;
    }
    
    if (kBaixo == 0){
        Serial.println("Nivel K Baixo");
        return nivel = 1;
    }
    return nivel;
    
    
}

// int verifica_npk(){
//   int npk[3] = {};

//   int nivel_n = medir_N();
//   int nivel_p = medir_P();
//   int nivel_k = medir_K();

//   switch (medir_N())
//   {
//   case 1:
//     /* Nivel Baixo */
//     Serial.println("Baixo N");
//     npk[0] = nivel_n;

//     break;

//   case 2:
//     /* Nivel Medio */
//     npk[0] = nivel_n;
//     break;

//   case 3:
//     /* Nivel Alto */
//     npk[0] = nivel_n;
//     break;
  
//   default:
//     break;
//   }

//   switch (medir_P())
//   {
//   case 1:
//     /* Nivel Baixo */
//     Serial.println("Baixo P");
//     npk[1] = nivel_p;
//     break;

//   case 2:
//     /* Nivel Medio */
//     npk[1] = nivel_p;
//     break;

//   case 3:
//     /* Nivel Alto */
//     npk[1] = nivel_p;
//     break;
  
//   default:
//     break;
//   }

//   switch (medir_K())
//   {
//   case 1:
//     /* Nivel Baixo */
//     Serial.println("Baixo K");
//     npk[2] = nivel_k;
    
//     break;

//   case 2:
//     /* Nivel Medio */
//     npk[2] = nivel_k;
    
//     break;

//   case 3:
//     /* Nivel Alto */
//     npk[2] = nivel_k;
//     break;
  
//   default:
//     break;
//   }

//   return *npk;

// }
