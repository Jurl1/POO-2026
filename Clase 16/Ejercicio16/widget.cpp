#include "widget.h"
#include "ui_widget.h"
#include "bienvenida.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QCryptographicHash>

// Función auxiliar: convierte una clave en texto plano a su hash MD5 en hex
static QString md5(const QString &texto) {
    return QCryptographicHash::hash(texto.toUtf8(), QCryptographicHash::Md5).toHex();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Subimos desde el ejecutable hasta encontrar widget.cpp,
    // que está en la carpeta raíz del proyecto junto a la DB.
    QDir dir(QCoreApplication::applicationDirPath());
    while (!dir.exists("widget.cpp") && !dir.isRoot()) {
        dir.cdUp();
    }

    QString rutaDB = dir.absolutePath() + "/base_de_datos_POO.db";

    if (!QFile::exists(rutaDB)) {
        QMessageBox::critical(this, "Error Crítico",
                              "No se encontró la base de datos en:\n" + rutaDB);
        return;
    }

    db.setDatabaseName(rutaDB);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos.\n" + db.lastError().text());
        return;
    }

    // Crear tabla si no existe (sin tocar los datos existentes)
    QSqlQuery init;
    init.exec("CREATE TABLE IF NOT EXISTS usuarios "
              "(usuario TEXT PRIMARY KEY, clave TEXT NOT NULL, ultimo_ingreso TEXT)");


}

Widget::~Widget() {
    delete ui;
}

void Widget::on_btnLogin_clicked() {
    QString user = ui->txtUsuario->text().trimmed();
    QString claveIngresada = ui->txtClave->text();  // No hacer trimmed() a la clave

    if (user.isEmpty() || claveIngresada.isEmpty()) {
        QMessageBox::warning(this, "Login", "Ingresá usuario y clave.");
        return;
    }

    // Convertir la clave ingresada a MD5 para comparar con lo almacenado
    QString claveMd5 = md5(claveIngresada);

    QSqlQuery query;
    query.prepare("SELECT ultimo_ingreso FROM usuarios "
                  "WHERE usuario = :u AND clave = :c");
    query.bindValue(":u", user);
    query.bindValue(":c", claveMd5);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error de SQL", query.lastError().text());
        return;
    }

    if (query.next()) {
        QString fechaAnterior = query.value(0).toString();

        // Actualizar el último ingreso con la fecha/hora actual
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