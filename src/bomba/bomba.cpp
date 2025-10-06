#include <Arduino.h>
#include "bomba.h"

/**
 * Aciona a bomba informando o que foi adicionado a água
 */
void aciona_bomba(const char *insumo) {
  digitalWrite(BOMBA_AGUA, HIGH);
  Serial.println(insumo);
}