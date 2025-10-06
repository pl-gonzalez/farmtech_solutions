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
  delay(200);
  
  // int nivel_N = medir_N();
  // int nivel_P = medir_P();
  // int nivel_K = medir_K();

  float temperatura = temp_umidade().temperature;
  float umidade = temp_umidade().humidity;
  delay(1000);

  Serial.println(temperatura);
  Serial.println(umidade);


  // float ph = medir_ph_solo();

  if(umidade < 70.0f || temperatura > 30){
    //   // verifica_npk(); // retorno nivel baixo de NPK
    // aciona_bomba(strcat("Irrigação iniciada.", verifica_npk())); // Com NPK necessário
    // Serial.println(temperatura);
    Serial.println("Conseguiu");

  }

  // switch (nivel_N)
  // {
  // case 1:
  //   /* Nivel Baixo */

  //   if(temperatura > 30 && umidade < 70){
  //     aciona_bomba("Irrigação com N, para elevar nivel de N");
  //   }


  //   break;

  // case 2:
  //   /* Nivel Medio */
    
  //   break;

  // case 3:
  //   /* Nivel Alto */
  //   break;
  
  // default:
  //   break;
  // }

  // switch (nivel_P)
  // {
  // case 1:
  //   /* Nivel Baixo */
  //   if(temperatura > 30 && umidade < 70){
  //     aciona_bomba("Irrigação com P, para elevar nivel de P");
  //   }
  //   break;

  // case 2:
  //   /* Nivel Medio */
  //   break;

  // case 3:
  //   /* Nivel Alto */
  //   break;
  
  // default:
  //   break;
  // }

  // switch (nivel_K)
  // {
  // case 1:
  //   /* Nivel Baixo */
  //   if(temperatura > 30 && umidade < 70){
  //     aciona_bomba("Irrigação com K, para elevar nivel de K");
  //   }
  //   break;

  // case 2:
  //   /* Nivel Medio */
  //   break;

  // case 3:
  //   /* Nivel Alto */
  //   break;
  
  // default:
  //   break;
  // }

}