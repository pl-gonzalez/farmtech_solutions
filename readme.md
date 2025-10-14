# 🌱 Projeto de Irrigação Inteligente com ESP32

## 📋 Descrição

Este projeto implementa um sistema de **irrigação automatizada com ESP32**, que decide o tipo de irrigação (água, NPK ou calagem) de acordo com as condições do solo e do ambiente.  
O objetivo é criar um sistema de irrigação inteligente, capaz de reagir automaticamente a variações climáticas e nutricionais.
A lavoura escolhida foi a cana-de-açucar, por tanto, buscamos atender o ambiente ideal para esta lavoura em umidade e temperatura apenas.

---

## ⚙️ Funcionalidades principais

- 💧 **Irrigação automática**
  - Ativa quando a **umidade** está abaixo de **50%**, independentemente da temperatura.
  - Se a temperatura ultrapassar **35 °C**, o limite de umidade sobe para **70%**.
- 🧪 **Controle de nutrientes NPK**
  - Irriga com **N**, **P**, **K** ou suas combinações (**NP**, **NK**, **PK**, **NPK**), conforme leitura dos botões que simulam os sensores de nutrientes.
  - Cada nutriente possui **três botões**, representando os níveis **baixo**, **médio** e **alto**.
- 🧂 **Correção de pH (Calagem)**
  - Caso o pH esteja **baixo (simulado via sensor LDR)**, é realizada irrigação **somente com cal**.
  - **NPK e Cal não se misturam**, portanto não ocorrem simultaneamente.
- 🚿 **Tempo de irrigação**
  - A bomba é acionada por **2 segundos** (modo demonstrativo).
- 🌐 **Comunicação MQTT**
  - O ESP32 atua como **subscriber**, recebendo dados via MQTT do broker `flespi.io`.
  - Um script Python atua como **publisher**, enviando dados climáticos da API Open-Meteo.

---

## 🔄 Adaptações para simulação (Wokwi)

Como o projeto foi desenvolvido para o **ambiente de simulação Wokwi**, algumas substituições foram feitas em relação aos sensores reais:

| Sensor Real | Simulado por | Função |
|--------------|---------------|--------|
| Sensor de Nitrogênio (N) | 3 botões verdes (baixo, médio e alto) | Define o nível de Nitrogênio |
| Sensor de Fósforo (P) | 3 botões verdes (baixo, médio e alto) | Define o nível de Fósforo |
| Sensor de Potássio (K) | 3 botões verdes (baixo, médio e alto) | Define o nível de Potássio |
| Sensor de pH do solo | Sensor LDR | Simula o pH do solo pela intensidade de luz |
| Sensor de umidade do solo | Sensor DHT22 | Mede temperatura e umidade |

> 💡 Essas adaptações foram orientadas pela faculdade para viabilizar a simulação e facilitar a demonstração prática no Wokwi.

---

## 🧰 Estrutura do Projeto



## 🔌 Conexões (Simulação Wokwi)

| Componente | Pinos ESP32 | Descrição |
|-------------|-------------|-----------|
| **Botões N** | D12, D13, D14 | Níveis baixo, médio e alto |
| **Botões P** | D25, D26, D27 | Níveis baixo, médio e alto |
| **Botões K** | D32, D33, D34 | Níveis baixo, médio e alto |
| **LDR** | A0 | Simula o pH do solo |
| **DHT22** | D15 | Mede temperatura e umidade |
| **Bomba (LED)** | D5 | Acionamento por 2 segundos |

---

## 🚀 Próximos passos



* Melhorar como irrigação é feita.

* Criar um dashboard para visualização dos dados MQTT.

* Testar o projeto com sensores reais de NPK e pH em campo.

🧩 Observação
Esse projeto foi desenvolvido como parte de uma atividade acadêmica