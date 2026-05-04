#include "widget.h"
#include "ui_widget.h"
#include "bienvenida.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>
#include <QFile> // <-- Fundamental para el candado de seguridad

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // LÓGICA INFALIBLE: Buscamos la carpeta root usando tu propio código como faro
    QDir dir(QCoreApplication::applicationDirPath());

    // Mientras la carpeta actual NO contenga "widget.cpp", seguimos subiendo niveles
    while (!dir.exists("widget.cpp") && !dir.isRoot()) {
        dir.cdUp();
    }

    // Una vez que el bucle frena, estamos 100% seguros de que estamos en el root
    QString rutaDB = dir.absolutePath() + "/base_de_datos_POO.db";

    // CANDADO DE SEGURIDAD: Evita que SQLite cree archivos adicionales
    if (!QFile::exists(rutaDB)) {
        QMessageBox::critical(this, "Error Crítico",
                              "No se encontró la base de datos original en el root:\n" + rutaDB +
                                  "\n\nEl programa se niega a crear copias adicionales.");
        return; // Cortamos la ejecución acá
    }

    db.setDatabaseName(rutaDB);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Se encontró el archivo pero no se pudo abrir.");
    }
    // Eliminamos todo el código de CREATE TABLE para asegurar que solo use tu archivo
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_btnLogin_clicked() {
    QString user = ui->txtUsuario->text().trimmed();
    QString pass = ui->txtClave->text().trimmed();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Login", "Ingresá usuario y clave.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT ultimo_ingreso FROM usuarios WHERE usuario = :u AND clave = :c");
    query.bindValue(":u", user);
    query.bindValue(":c", pass);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error de SQL", query.lastError().text());
        return;
    }

    if (query.next()) {
        // 1. Capturamos la fecha vieja (la que está guardada de antes)
        QString fechaAnterior = query.value(0).toString();

        // 2. Liberamos la consulta de lectura para que no bloquee la base de datos
        query.finish();

        // 3. Creamos la ventana de Bienvenida con esa fecha "vieja"
        Bienvenida *v = new Bienvenida(user, fechaAnterior);
        v->show();

        // 4. SOBRESCRIBIMOS la base de datos principal
        QString ahora = QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss");

        QSqlQuery update;
        update.prepare("UPDATE usuarios SET ultimo_ingreso = :ahora WHERE usuario = :u");
        update.bindValue(":ahora", ahora);
        update.bindValue(":u", user);

        if (!update.exec()) {
            qDebug() << "Error al actualizar fecha en la BD principal:" << update.lastError().text();
        } else {
            qDebug() << "Éxito: Se actualizó la fecha en el archivo root.";
        }

        // 5. Cerramos la ventana de Login
        this->close();

    } else {
        QMessageBox::warning(this, "Login", "Usuario o clave incorrectos.");
    }
}