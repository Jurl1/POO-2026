# Ejercicio 8 - Servidor FastAPI con JWT
# 
# Instalar dependencias:
#   pip install fastapi uvicorn mysql-connector-python PyJWT
#
# Ejecutar:
#   uvicorn main:app --reload
#
# Asegurarse de tener MySQL corriendo con la base de datos 'poo2025'
# y la tabla 'usuarios' creada (ver script sql_setup.sql)

from fastapi import FastAPI, HTTPException, Depends
from fastapi.security import HTTPBearer, HTTPAuthorizationCredentials
import mysql.connector
from pydantic import BaseModel
import jwt
import datetime

SECRET_KEY = "clave_secreta_poo2025"
ALGORITHM = "HS256"

app = FastAPI()

security = HTTPBearer()

# Configuración de tu DB local MySQL
db_config = {
    'user': 'admin',
    'password': 'adminpassword',
    'host': '100.88.165.95',
    'database': 'poo_db'
}


class Usuario( BaseModel ):
    usuario: str
    clave: str


def crear_token( datos: dict ):
    payload = datos.copy()
    payload[ "exp" ] = datetime.datetime.utcnow() + datetime.timedelta( hours = 1 )
    return jwt.encode( payload, SECRET_KEY, algorithm = ALGORITHM )


def verificar_token( credentials: HTTPAuthorizationCredentials = Depends( security ) ):
    try:
        payload = jwt.decode( credentials.credentials, SECRET_KEY, algorithms = [ ALGORITHM ] )
        return payload
    except jwt.ExpiredSignatureError:
        raise HTTPException( status_code = 401, detail = "Token expirado" )
    except jwt.InvalidTokenError:
        raise HTTPException( status_code = 401, detail = "Token inválido" )


@app.post( "/login" )
def login( datos: Usuario ):
    try:
        conn = mysql.connector.connect( **db_config )
        cursor = conn.cursor( dictionary = True )

        query = "SELECT * FROM usuarios WHERE usuario = %s AND clave = %s"
        cursor.execute( query, ( datos.usuario, datos.clave ) )

        usuario_db = cursor.fetchone()

        cursor.close()
        conn.close()

        if usuario_db:
            token = crear_token( {
                "usuario": usuario_db[ "usuario" ],
                "nombre": usuario_db.get( "nombre", "" ),
                "apellido": usuario_db.get( "apellido", "" )
            } )
            return { "status": "ok", "token": token, "datos": usuario_db }
        else:
            raise HTTPException( status_code = 401, detail = "Credenciales inválidas" )

    except mysql.connector.Error as err:
        raise HTTPException( status_code = 500, detail = str( err ) )


@app.get( "/perfil" )
def perfil( payload: dict = Depends( verificar_token ) ):
    return {
        "status": "ok",
        "usuario": payload.get( "usuario" ),
        "nombre": payload.get( "nombre" ),
        "apellido": payload.get( "apellido" )
    }
