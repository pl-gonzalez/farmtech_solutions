import requests

URL = "https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&daily=precipitation_probability_max,temperature_2m_min,temperature_2m_max&timezone=America%2FSao_Paulo"

# If 05:00  -> realiza request
response = requests.get(URL)

data = response.json()


# Sera envia via MQTT para o ESP32

# data['daily']['time'][0] -> [0] pq sempre que pesquisado, o 1 elemento será o dia atual.
print(f'{data['daily']['time'][0]};{data['daily']['temperature_2m_min'][0]};{data['daily']['temperature_2m_max'][0]};{data['daily']['precipitation_probability_max'][0]}')

# Input JSON com previsao de 7 dias
# Output: time; temperature_2m_min; temperature_2m_max; precipitation_probability_max;
