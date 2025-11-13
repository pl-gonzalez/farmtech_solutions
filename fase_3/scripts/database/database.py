import oracledb  
import pandas as pd
import os

from config import DB_CONFIG

def gravar_banco(mqtt_data: dict) -> bool:
    try:
        # Efetua a conexão com o Usuário no servidor
        conn = oracledb.connect(user='rm567944', password="260299", dsn='oracle.fiap.com.br:1521/ORCL')
        
        # Cria as instruções para cada módulo
        inst_cadastro = conn.cursor()

        # Nomes precisam ser identicos
        sql = f"""INSERT INTO MONITORAMENTO_SOLO_SIMULADO (id_dispositivo, cultura, temp_solo, umidade_solo, ph_solo, npk) VALUES('{mqtt_data["id"]}', '{mqtt_data["cultura"]}', '{mqtt_data["temperatura"]}', '{mqtt_data["umidade"]}',' {mqtt_data["ph"]}', '{mqtt_data["tipo_irrigacao"]}')"""
        
        inst_cadastro.execute(sql)
        conn.commit()

    except Exception as e:
        # Informa o erro
        print("Erro: ", e)
        conexao = False

        inst_cadastro.close()
        conn.close()

        return conexao
    else:
        conexao = True

        inst_cadastro.close()
        conn.close()

        return conexao
    # Callback quando conecta

def ler_banco() -> pd.DataFrame:
    try:
        # Efetua a conexão
        conn = oracledb.connect(
            user='rm567944', 
            password="260299", 
            dsn='oracle.fiap.com.br:1521/ORCL'
        )
        
        cursor = conn.cursor()
        sql = """SELECT * FROM MONITORAMENTO_SOLO_SIMULADO ORDER BY DATA_HORA_GRAVACAO DESC"""
        cursor.execute(sql)
        
        data = cursor.fetchall()
        print(data)
        
        # CORREÇÃO: Use as colunas EXATAS do seu banco (conforme o print)
        dados_df = pd.DataFrame.from_records(
            data, 
            columns=[
                'DATA_HORA_GRAVACAO',
                'ID_DISPOSITIVO', 
                'CULTURA', 
                'TEMP_SOLO', 
                'UMIDADE_SOLO', 
                'PH_SOLO', 
                'NPK'
            ]
        )
        
        cursor.close()
        conn.close()
        
        return dados_df

    except Exception as e:
        print("Erro: ", e)
        try:
            cursor.close()
            conn.close()
        except:
            pass
        return pd.DataFrame()  # Retorna DataFrame vazio