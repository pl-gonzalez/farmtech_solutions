import requests
import paho.mqtt.client as mqtt
import time
import datetime

URL = "https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&daily=precipitation_probability_max,temperature_2m_min,temperature_2m_max&timezone=America%2FSao_Paulo"

BROKER = "mqtt.flespi.io"
PORT = 1883
TOKEN = "FLESPI_TOKEN"  # Substitua pelo seu token do Flespi
CLIENT_ID = "Central"

 # Callback quando conecta
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Conectado ao broker")
    else:
        print(f"Falha na conexão. Código: {rc}")

# Callback quando publica
def on_publish(client, userdata, mid):
    print(f"Mensagem publicada. ID: {mid}")

def consultar_open_meteo():
    print("Consultando API")
    response = requests.get(URL)
        
    data = response.json()

    return data

def publicar_msg(data):
    # Publicar mensagem
        topic = "central"
        message = f'{data['daily']['time'][0]};{data['daily']['temperature_2m_min'][0]};{data['daily']['temperature_2m_max'][0]};{data['daily']['precipitation_probability_max'][0]}'
        result = client.publish(topic, message)

        print(message)

        if result.rc == mqtt.MQTT_ERR_SUCCESS:
            print("Publicação bem-sucedida!")
        else:
            print("Erro na publicação")

client = mqtt.Client(client_id=CLIENT_ID)
client.username_pw_set(TOKEN)  # Token como usuário (senha vazia)
client.on_connect = on_connect
client.on_publish = on_publish

    
while True:
    previsao = datetime.datetime.now()

    # Todo dia, as 06:30H, é realizada uma consulta a OpenMeteo API para termos previsão do tempo, chuva e temperaturas maxima e minima
    if previsao.hour == 6 and previsao.minutes == 0:
        data = consultar_open_meteo()
        # Para evitar rodar varias vezes no mesmo minuto; Espera 30 minutos
        time.sleep(30 * 60)
        
        # Conectar
        client.connect(BROKER, PORT, 60)
        client.loop_start()

        publicar_msg(data) # Publica e trata erro de envio

        time.sleep(2)

        # Desconectar
        client.loop_stop()
        client.disconnect()

    else:
        # Espera 30 segundos e verifica de novo
        time.sleep(30)
