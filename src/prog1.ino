#include <Arduino.h>
#include "DHTesp.h"
#include "npk/npk.h"
#include "pH/ph.h"
#include "bomba/bomba.h"
#include "dht/dht.h"


DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);

  dhtSensor.setup(DHT_PIN, DHTesp :: DHT22);

  pinMode(N_ALTO, INPUT_PULLUP);
  pinMode(N_MEDIO, INPUT_PULLUP);
  pinMode(N_BAIXO, INPUT_PULLUP);

  pinMode(P_ALTO, INPUT_PULLUP);
  pinMode(P_MEDIO, INPUT_PULLUP);
  pinMode(P_BAIXO, INPUT_PULLUP);

  pinMode(K_ALTO, INPUT_PULLUP);
  pinMode(K_MEDIO, INPUT_PULLUP);
  pinMode(K_BAIXO, INPUT_PULLUP);

  pinMode(BOMBA_AGUA, OUTPUT);

  pinMode(PH_SOLO, INPUT);

  
}





void loop() {
  medir_K();
  medir_N();
  medir_P();
  delay(2000);
}