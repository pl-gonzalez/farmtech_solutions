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

  float temperatura = temp_umidade().temperature;
  float umidade = temp_umidade().humidity;

  delay(1000);  // Para dar tempo para o simulador do esp32


  float ph_solo = medir_ph_solo();

  if(ph_solo < 5.5f && umidade < 60.0f){
    aciona_bomba("Irrigação com Cal para aumentar pH do solo");
  }

  /**
   * Umidade < 50% -> Estresse hidrico, irrigar agora
   * Temperatura > 35°C -> Muitoo quente para cana de açucar
   */
  if(umidade < 50.0f || temperatura > 35.0f){
    int nivel_n = medir_N();
    int nivel_p = medir_P();
    int nivel_k = medir_K();

    

    if(nivel_n == 1){
      aciona_bomba("Irrigação enriquecida com N");
    }

    else if(nivel_p == 1){
      aciona_bomba("Irrigação enriquecida com P");
    }

    else if(nivel_k == 1){
      aciona_bomba("Irrigação enriquecida com K");
    }

    else {
      aciona_bomba("Irrigacao sem aditivos");
    }
    
    

  }

  


}