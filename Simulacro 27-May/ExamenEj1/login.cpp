#include "login.h"
#include "ui_login.h"
#include "admindb.h"
#include <QNetworkRequest>
#include <QMessageBox>
#include <QDebug>


Login::Login( QWidget * parent ) : QWidget( parent ), ui( new Ui::Login )  {
    ui->setupUi( this );

    m_nam = new QNetworkAccessManager( this );

    // Cuando el usuario termina de escribir el nombre, descargar el avatar
    connect( ui->leUsuario, SIGNAL( editingFinished() ),
             this, SLOT( slot_descargarAvatar() ) );

    // Respuesta del servidor con la imagen
    connect( m_nam, SIGNAL( finished( QNetworkReply * ) ),
             this, SLOT( slot_avatarDescargado( QNetworkReply * ) ) );

    // Botón de login
    connect( ui->pbLogin, SIGNAL( clicked() ),
             this, SLOT( slot_iniciarSesion() ) );
}

Login::~Login()  {
    delete ui;
}

void Login::slot_descargarAvatar()  {
    QString usuario = ui->leUsuario->text().trimmed();

    if ( usuario.isEmpty() )  {
        return;
    }

    QString url = "https://robohash.org/" + usuario + ".png";

    QNetworkRequest request{ QUrl( url ) };
    request.setAttribute( QNetworkRequest::RedirectPolicyAttribute,
                          QNetworkRequest::NoLessSafeRedirectPolicy );
    m_nam->get( request );

    qDebug() << "Descargando avatar desde:" << url;
}

void Login::slot_avatarDescargado( QNetworkReply * reply )  {
    if ( reply->error() != QNetworkReply::NoError )  {
        qDebug() << "Error al descargar avatar:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray datos = reply->readAll();
    QImage imagen;
    imagen.loadFromData( datos );

    if ( ! imagen.isNull() )  {
        ui->widgetImagen->setImagen( imagen );
    }

    reply->deleteLater();
}

void Login::slot_iniciarSesion()  {
    QString usuario = ui->leUsuario->text().trimmed();
    QString clave   = ui->leClave->text();

    if ( usuario.isEmpty() || clave.isEmpty() )  {
        ui->lblEstado->setText( "Complete ambos campos." );
        return;
    }

    if ( AdminDB::getInstancia()->validarUsuario( usuario, clave ) )  {
        AdminDB::getInstancia()->registrarLogin( usuario );
        ui->lblEstado->setText( "" );
        emit loginExitoso();
    }
    else  {
        ui->lblEstado->setText( "Usuario o clave incorrectos." );
        ui->leClave->clear();
    }
}
