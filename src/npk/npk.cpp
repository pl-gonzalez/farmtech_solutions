#include <Arduino.h>
#include "npk.h"


/**
 * Mede nivel de NPK
 * 
 * OBS: Nao esta sendo tratado Debouncing e há inputs flutuantes que devrão ser corrigidos no circuito
 *      Os botões são acionado um por vez, visto que nao há como ter nivel baixo e médio ao mesmo tempo (Ctrl + Click no Wokwi)
 * 
 */

void medir_N() {
    int nAlto = digitalRead(N_ALTO);
    int nMedio = digitalRead(N_MEDIO);
    int nBaixo = digitalRead(N_BAIXO);
    
    if (nAlto == 0){
        Serial.println("Nivel N Alto");
    }
    
    if (nMedio == 0){
        Serial.println("Nivel N Medio");
    }
    
    if (nBaixo == 0){
        Serial.println("Nivel N Baixo");
    }
    
    
}

void medir_P() {
  int pAlto = digitalRead(P_ALTO);
  int kMedio = digitalRead(P_MEDIO);
  int kBaixo = digitalRead(P_BAIXO);

  if (pAlto == 0){
    Serial.println("Nivel P Alto");
  }

  if (kMedio == 0){
    Serial.println("Nivel P Medio");
  }

  if (kBaixo == 0){
    Serial.println("Nivel P Baixo");
  }

  
}

void medir_K() {
    int kAlto = digitalRead(K_ALTO);
    int kMedio = digitalRead(K_MEDIO);
    int kBaixo = digitalRead(K_BAIXO);
    
    if (kAlto == 0){
        Serial.println("Nivel K Alto");
    }
    
    if (kMedio == 0){
        Serial.println("Nivel K Medio");
    }
    
    if (kBaixo == 0){
        Serial.println("Nivel K Baixo");
    }
    
    
}
