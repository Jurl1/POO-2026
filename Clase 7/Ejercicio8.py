from fastapi import FastAPI, HTTPException
import mysql.connector
from pydantic import BaseModel

app = FastAPI()

# Configuración de tu DB local MySQL
db_config = {
    'user': 'root',         
    'password': '',         
    'host': '127.0.0.1',
    'database': 'poo2025'   
}

class Usuario(BaseModel):
    usuario: str
    clave: str

@app.post("/validar_usuario")
def validar_usuario(datos: Usuario):
    try:
        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor(dictionary=True)

        query = "SELECT * FROM usuarios WHERE usuario = %s AND clave = %s"
        cursor.execute(query, (datos.usuario, datos.clave))
        
        usuario_db = cursor.fetchone()
        
        cursor.close()
        conn.close()

        if usuario_db:
            return {"status": "ok", "datos": usuario_db}
        else:
            raise HTTPException(status_code=401, detail="Credenciales invalidas")
            
    except mysql.connector.Error as err:
        raise HTTPException(status_code=500, detail=str(err))