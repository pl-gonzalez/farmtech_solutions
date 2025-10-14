#include <Arduino.h>
#include <WiFi.h>

#include "DHTesp.h"

#include "npk/npk.h"
#include "pH/ph.h"
#include "bomba/bomba.h"
#include "dht/dht.h"
#include "mqtt/mqtt.h"

DHTesp dhtSensor;

struct Dados dados;


unsigned long lastUpdate = 0;
const unsigned long interval = 5000; // 5 segundos

void setup() {
  Serial.begin(115200);

  dhtSensor.setup(DHT_PIN, DHTesp :: DHT22);
  init_mqtt();
  init_npk();
  init_bomba();
  init_ph();
  
  delay(3000);
  
}


void loop() {

  if (!client.connected()) {
        reconnect();
    }
    client.loop(); // mantém conexão e recebe mensagens

  // executa tarefas periodicamente sem travar o loop
    unsigned long now = millis();
    if (now - lastUpdate >= interval) {
        lastUpdate = now;

        
        if(dados.atualizado){
          
          Serial.print("Data: ");
          Serial.println(dados.date);
          Serial.print("Probabalidade de chuva: ");
          Serial.print(dados.probChuva);
          Serial.println("%");
          Serial.print("Temp. Minima: ");
          Serial.print(dados.tempMin);
          Serial.println("°C");
          Serial.print("Temp. Maxima: ");
          Serial.print(dados.tempMax);
          Serial.println("°C");
        }
        
        
        float temperatura = temp_umidade().temperature;
        float umidade = temp_umidade().humidity;
        float ph_solo = medir_ph_solo();
        
        Serial.print("pH: ");
        Serial.print(ph_solo);
        
        Serial.print("\t Temp. Solo: ");
        Serial.print(temperatura);
        
        Serial.print("\t Umidade solo (%): ");
        Serial.println(umidade);
        
        
        // Mediçoes de nivel de NPK retornam o estado de cada sensor
        int nivel_n = medir_N();
        int nivel_p = medir_P();
        int nivel_k = medir_K();
        
        /**
         * Umidade < 50% -> Estresse hidrico, irrigar agora
         * Temperatura > 35°C -> Muitoo quente para cana de açucar
         * 
         * @note: plantação será irrigada para manter umidade entre 50-70% e
         *  temperatura abaixo dos 35°C. As informações foram encontradas na internet.
         */
        
        if(umidade < 50.0f || (umidade < 70.0f && temperatura > 35.0f)){
          
          
          if(dados.probChuva < 60.f){
            
            if (nivel_n == BAIXO_N && nivel_p == BAIXO_P  && nivel_k == BAIXO_K) aciona_bomba("Irrigação com N, P e K");
            // se n p
            else if (nivel_n == BAIXO_N && nivel_p == BAIXO_P) aciona_bomba("Irrigação com N e P");
            // se n k
            else if (nivel_n == BAIXO_N && nivel_k == BAIXO_K) aciona_bomba("Irrigação com N e K");
            // se p k
            else if (nivel_p == BAIXO_P && nivel_k == BAIXO_K) aciona_bomba("Irrigação com P e K");
            // se n
            else if (nivel_n == BAIXO_N) aciona_bomba("Irrigação com N");
            // se p
            else if (nivel_p == BAIXO_P) aciona_bomba("Irrigação com P");
            // se k
            else if (nivel_k == BAIXO_K) aciona_bomba("Irrigação com K");
       
            else if (ph_solo < 5.5f) aciona_bomba("Irrigação com Cal para elevar pH");

            else if(umidade < 50.0f || umidade < 70.0f) aciona_bomba("Irrigação apenas com água");

          }
          
          else {
            Serial.println("Sistema de irrigação nao será ligado devido a previsão de chuva");
          }
          
        }
        
      }
}