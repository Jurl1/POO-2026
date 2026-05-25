-- Crear la base de datos si no existe
CREATE DATABASE IF NOT EXISTS poo2025;
USE poo2025;

-- Crear la tabla de usuarios
CREATE TABLE IF NOT EXISTS usuarios (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    apellido VARCHAR(100) NOT NULL,
    usuario VARCHAR(50) NOT NULL UNIQUE,
    clave VARCHAR(100) NOT NULL,
    mail VARCHAR(150)
);

-- Insertar algunos usuarios de prueba
INSERT IGNORE INTO usuarios (nombre, apellido, usuario, clave, mail) VALUES
('Juan', 'Pérez', 'jperez', '1234', 'jperez@mail.com'),
('María', 'García', 'mgarcia', 'abcd', 'mgarcia@mail.com'),
('Carlos', 'López', 'clopez', 'pass123', 'clopez@mail.com');
