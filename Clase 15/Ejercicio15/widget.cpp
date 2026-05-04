#include "widget.h"
#include "ui_widget.h"
#include "bienvenida.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>
#include <QCoreApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // La DB se copia junto al ejecutable gracias a la regla en el .pro
    QString rutaDB = QCoreApplication::applicationDirPath() + "/base_de_datos_POO.db";
    db.setDatabaseName(rutaDB);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos en:\n" + rutaDB);
    } else {
        QSqlQuery init;
        init.exec("CREATE TABLE IF NOT EXISTS usuarios "
                  "(usuario TEXT PRIMARY KEY, clave TEXT NOT NULL, ultimo_ingreso TEXT)");
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
        QString fechaAnterior = query.value(0).toString();

        QString ahora = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        QSqlQuery update;
        update.prepare("UPDATE usuarios SET ultimo_ingreso = :ahora WHERE usuario = :u");
        update.bindValue(":ahora", ahora);
        update.bindValue(":u", user);
        update.exec();

        Bienvenida *v = new Bienvenida(user, fechaAnterior);
        v->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Login", "Usuario o clave incorrectos.");
    }
}