#include <Arduino.h>
#include "bomba.h"

/**
 * Aciona a bomba informando o que foi adicionado a água
 */
void aciona_bomba(const char *insumo) {
  digitalWrite(BOMBA_AGUA, HIGH);
  Serial.println(insumo);

  delay(2000); // Mantem irrigacao acionada por 2s 

  digitalWrite(BOMBA_AGUA, LOW);
}

void init_bomba(){
  pinMode(BOMBA_AGUA, OUTPUT);
}