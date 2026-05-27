import sqlite3

conn = sqlite3.connect("login.sqlite")
c = conn.cursor()

c.execute("""CREATE TABLE IF NOT EXISTS usuarios (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT NOT NULL UNIQUE,
    clave TEXT NOT NULL,
    fecha_login TEXT
)""")

c.execute("INSERT OR IGNORE INTO usuarios (usuario, clave) VALUES ('admin', '1234')")
c.execute("INSERT OR IGNORE INTO usuarios (usuario, clave) VALUES ('santi', 'abcd')")
c.execute("INSERT OR IGNORE INTO usuarios (usuario, clave) VALUES ('lucas', 'pass')")

conn.commit()

for row in c.execute("SELECT * FROM usuarios"):
    print(row)

conn.close()
print("Base de datos creada correctamente.")
