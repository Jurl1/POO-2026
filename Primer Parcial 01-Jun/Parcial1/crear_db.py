import sqlite3

conn = sqlite3.connect("dibujos.sqlite")
c = conn.cursor()

c.execute("""CREATE TABLE IF NOT EXISTS usuarios (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT NOT NULL UNIQUE,
    clave TEXT NOT NULL,
    fecha_login TEXT
)""")

c.execute("""CREATE TABLE IF NOT EXISTS log_sesiones (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario TEXT NOT NULL,
    fecha TEXT NOT NULL
)""")

c.execute("""CREATE TABLE IF NOT EXISTS dibujos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nombre TEXT NOT NULL,
    categoria TEXT,
    tipo TEXT,
    fecha TEXT,
    usuario TEXT
)""")

c.execute("INSERT OR IGNORE INTO usuarios (usuario, clave) VALUES ('admin', '1234')")
c.execute("INSERT OR IGNORE INTO usuarios (usuario, clave) VALUES ('santi', 'abcd')")

conn.commit()

print("Usuarios:")
for row in c.execute("SELECT * FROM usuarios"):
    print("  ", row)

print("Tablas log_sesiones y dibujos creadas (vacias)")
conn.close()
print("Base de datos dibujos.sqlite creada correctamente.")
