# Central apenas recebe informações MQTT, por isso nao tem pub
# e fica sempre aguardando publicação no topico inscrito

from config import BROKER, PORT, TOKEN, CLIENT_ID, TOPIC
import paho.mqtt.client as mqtt
from database.database import gravar_banco

# Callback quando conecta
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        client.subscribe(TOPIC)
    else:
        print(f"Falha na conexão. Código: {rc}")

# Callback quando recebe mensagem
def on_message(client, userdata, msg):
    try:
        payload = msg.payload.decode()  # converte bytes -> string

        valores = payload.split(";")

        # Converte para dicionário
        # INPUT: 2602;cana-de-açucar;-5.80;43.00;3.00;K
        dados = {
            "id": valores[0],
            "cultura": valores[1],
            "temperatura": float(valores[2]),
            "umidade": float(valores[3]),
            "ph": float(valores[4]),
            "tipo_irrigacao": valores[5]
        }

        # Aqui chama função para gravação no banco
        gravar_banco(dados)
        

    except Exception as e:
        print("Erro ao processar mensagem:", e)


def conectar_mqtt():
    # Criar e configurar cliente
    client = mqtt.Client(client_id=CLIENT_ID)
    client.username_pw_set(TOKEN)
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(BROKER, PORT, 60)
    client.loop_start() 
