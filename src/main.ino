#include <Arduino.h>

#include "DHTesp.h"

#include "npk/npk.h"
#include "pH/ph.h"
#include "bomba/bomba.h"
#include "dht/dht.h"
#include "api_clima/api.h"

DHTesp dhtSensor;

enum Irrigar estado;

struct Dados dados;

// Dados da consulta a API com Python inseridos manualmente
// API_DATA = time; temperature_2m_min; temperature_2m_max; precipitation_probability_max;
const char *API_DATA = "2025-10-09;12.2;14.5;85";

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

  formata_dados(API_DATA, &dados);

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

  delay(3000);
  
}





void loop() {
    
  float temperatura = temp_umidade().temperature;
  float umidade = temp_umidade().humidity;

  float ph_solo = medir_ph_solo();
  
  delay(1500);  // Para dar tempo para o simulador do esp32
  

  // Mediçoes de nivel de NPK retornam o estado de cada sensor
  int nivel_n = medir_N();
  int nivel_p = medir_P();
  int nivel_k = medir_K();

  delay(500);
  /**
   * Umidade < 50% -> Estresse hidrico, irrigar agora
   * Temperatura > 35°C -> Muitoo quente para cana de açucar
   * 
   * @note: plantação será irrigada para manter umidade entre 50-70% e
   *  temperatura abaixo dos 35°C. As informações foram encontradas na internet.
   */

  if(umidade < 50.0f || (umidade < 70.0f && temperatura > 35.0f)){


    if(dados.probChuva < 60.f){
    
      
      if(nivel_n == IRRIGAR_N){
        // estado = IRRIGAR_N;
        aciona_bomba("Irrigação com N");
        return;
      }
      
      if (nivel_p == IRRIGAR_P){
        // estado = IRRIGAR_P;
        aciona_bomba("Irrigação com P");
        return;
      }
      
      if(nivel_k == IRRIGAR_K){
        // estado = IRRIGAR_K;
        aciona_bomba("Irrigação com K");
        return;
      }
      
      if (ph_solo < 5.5f){
        // estado = IRRIGAR_CAL;
        aciona_bomba("Irrigação com Cal para elevar pH");
        return;
      }
      
      else {
        // estado = IRRIGAR_AGUA;
        aciona_bomba("Irrigação apenas com água");
        return;
      }
    }

    else {
      Serial.println("Sistema de irrigação nao será ligado devido a previsão de chuva");
    }

  }
  
}