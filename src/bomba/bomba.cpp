#include <Arduino.h>
#include "bomba.h"

/**
 * Aciona a bomba informando o que foi adicionado a água
 */
void aciona_bomba(const char *insumo) {
  digitalWrite(BOMBA_AGUA, HIGH);
  Serial.println(insumo);

  delay(3000); // Mantem irrigacao acionada por 1,5s 

  digitalWrite(BOMBA_AGUA, LOW);
}