#include "ventanaprincipal.h"

#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QDebug>

VentanaPrincipal::VentanaPrincipal( QWidget * parent ) : QWidget( parent )  {

    this->setWindowTitle( "Ventana Principal - Ejercicio 8" );
    this->setFixedSize( 400, 250 );

    QVBoxLayout * vlPrincipal = new QVBoxLayout( this );

    lblBienvenida = new QLabel( "Bienvenido al sistema" );
    lblBienvenida->setAlignment( Qt::AlignCenter );
    QFont fuente = lblBienvenida->font();
    fuente.setPointSize( 14 );
    fuente.setBold( true );
    lblBienvenida->setFont( fuente );

    pbPerfil = new QPushButton( "Consultar perfil (endpoint protegido)" );

    lblPerfil = new QLabel;
    lblPerfil->setAlignment( Qt::AlignCenter );
    lblPerfil->setWordWrap( true );

    pbCerrarSesion = new QPushButton( "Cerrar sesión" );

    vlPrincipal->addWidget( lblBienvenida );
    vlPrincipal->addSpacing( 10 );
    vlPrincipal->addWidget( pbPerfil );
    vlPrincipal->addWidget( lblPerfil );
    vlPrincipal->addStretch();
    vlPrincipal->addWidget( pbCerrarSesion );

    nam = new QNetworkAccessManager( this );

    connect( pbPerfil, SIGNAL( clicked() ), this, SLOT( slot_obtenerPerfil() ) );
    connect( pbCerrarSesion, SIGNAL( clicked() ), this, SLOT( slot_cerrarSesion() ) );
    connect( nam, SIGNAL( finished( QNetworkReply * ) ),
             this, SLOT( slot_respuestaPerfil( QNetworkReply * ) ) );
}

void VentanaPrincipal::slot_recibirToken( QString token )  {
    this->token = token;
    lblPerfil->clear();
    this->show();
}

void VentanaPrincipal::slot_obtenerPerfil()  {
    if ( token.isEmpty() )  {
        lblPerfil->setText( "No hay token disponible." );
        return;
    }

    QNetworkRequest request{ QUrl( "http://127.0.0.1:8000/perfil" ) };
    request.setRawHeader( "Authorization", ( "Bearer " + token ).toUtf8() );

    nam->get( request );
}

void VentanaPrincipal::slot_respuestaPerfil( QNetworkReply * reply )  {
    QByteArray datos = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson( datos );
    QJsonObject obj = doc.object();

    int statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt();

    if ( statusCode == 200 )  {
        QString usuario = obj.value( "usuario" ).toString();
        QString nombre = obj.value( "nombre" ).toString();
        QString apellido = obj.value( "apellido" ).toString();

        lblPerfil->setText( QString( "Usuario: %1\nNombre: %2 %3" )
                            .arg( usuario ).arg( nombre ).arg( apellido ) );

        qDebug() << "Perfil obtenido:" << usuario << nombre << apellido;
    }
    else  {
        QString detalle = obj.value( "detail" ).toString( "Error al obtener perfil" );
        lblPerfil->setText( "Error: " + detalle );
        qDebug() << "Error al obtener perfil:" << detalle;
    }

    reply->deleteLater();
}

void VentanaPrincipal::slot_cerrarSesion()  {
    this->token = "";
    lblPerfil->clear();
    this->hide();

    emit cerrarSesion();
}
