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
#include <QFileInfo>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Lógica para encontrar la carpeta raíz (fuera de build/debug)
    QDir dir(QCoreApplication::applicationDirPath());
    while (dir.dirName().contains("build") ||
           dir.dirName() == "debug" ||
           dir.dirName() == "release") {
        dir.cdUp();
    }

    QString rutaDB = dir.absolutePath() + "/base_de_datos_POO.db";
    db.setDatabaseName(rutaDB);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos en:\n" + rutaDB);
    } else {
        QSqlQuery init;
        init.exec("CREATE TABLE IF NOT EXISTS usuarios "
                  "(usuario TEXT PRIMARY KEY, clave TEXT NOT NULL, ultimo_ingreso TEXT)");
        // Insertamos el admin solo si no existe para no pisar tus datos de SQLiteStudio
        init.exec("INSERT OR IGNORE INTO usuarios VALUES ('admin', '1234', '')");
    }
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

        // 2. Creamos la ventana de Bienvenida con esa fecha "vieja"
        Bienvenida *v = new Bienvenida(user, fechaAnterior);
        v->show();

        // 3. SOBRESCRIBIMOS la base de datos con la fecha y hora de ESTE ingreso
        // Esto es lo que se verá la PRÓXIMA vez que el usuario entre.
        QDateTime ahora = QDateTime::currentDateTime(); // Pasa el objeto, no el string
        QSqlQuery update;
        update.prepare("UPDATE usuarios SET ultimo_ingreso = :ahora WHERE usuario = :u");
        update.bindValue(":ahora", ahora);
        update.bindValue(":u", user);

        // Ejecuta SOLO una vez dentro del condicional
        if (!update.exec()) {
            qDebug() << "Error al actualizar fecha:" << update.lastError().text();
        } else {
            qDebug() << "Se actualizo la fecha";
        }

        // 4. Cerramos la ventana de Login
        this->close();

    } else {
        QMessageBox::warning(this, "Login", "Usuario o clave incorrectos.");
    }
}