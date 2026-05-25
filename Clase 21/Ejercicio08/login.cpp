#include "login.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QDebug>

Login::Login( QWidget * parent ) : QWidget( parent )  {

    this->setWindowTitle( "Login - Ejercicio 8" );
    this->setFixedSize( 350, 200 );

    QVBoxLayout * vlPrincipal = new QVBoxLayout( this );

    // ---- Usuario ----
    QHBoxLayout * hlUsuario = new QHBoxLayout;
    QLabel * lblUsuario = new QLabel( "Usuario:" );
    leUsuario = new QLineEdit;
    leUsuario->setPlaceholderText( "Ingrese su usuario" );
    hlUsuario->addWidget( lblUsuario );
    hlUsuario->addWidget( leUsuario );

    // ---- Clave ----
    QHBoxLayout * hlClave = new QHBoxLayout;
    QLabel * lblClave = new QLabel( "Clave:" );
    leClave = new QLineEdit;
    leClave->setPlaceholderText( "Ingrese su clave" );
    leClave->setEchoMode( QLineEdit::Password );
    hlClave->addWidget( lblClave );
    hlClave->addWidget( leClave );

    // ---- Botón Login ----
    pbLogin = new QPushButton( "Iniciar sesión" );

    // ---- Estado ----
    lblEstado = new QLabel;
    lblEstado->setAlignment( Qt::AlignCenter );

    // ---- Layout ----
    vlPrincipal->addLayout( hlUsuario );
    vlPrincipal->addLayout( hlClave );
    vlPrincipal->addWidget( pbLogin );
    vlPrincipal->addWidget( lblEstado );

    // ---- NAM ----
    nam = new QNetworkAccessManager( this );

    // ---- Conexiones ----
    connect( pbLogin, SIGNAL( clicked() ), this, SLOT( slot_login() ) );
    connect( nam, SIGNAL( finished( QNetworkReply * ) ),
             this, SLOT( slot_respuestaLogin( QNetworkReply * ) ) );
}

void Login::slot_login()  {
    QString usuario = leUsuario->text().trimmed();
    QString clave = leClave->text();

    if ( usuario.isEmpty() || clave.isEmpty() )  {
        lblEstado->setText( "Complete ambos campos." );
        return;
    }

    lblEstado->setText( "Conectando..." );
    pbLogin->setEnabled( false );

    // Armar el JSON con las credenciales
    QJsonObject json;
    json[ "usuario" ] = usuario;
    json[ "clave" ] = clave;

    QJsonDocument doc( json );

    QNetworkRequest request{ QUrl( "http://127.0.0.1:8000/login" ) };
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/json" );

    nam->post( request, doc.toJson() );
}

void Login::slot_respuestaLogin( QNetworkReply * reply )  {
    pbLogin->setEnabled( true );

    QByteArray datos = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson( datos );
    QJsonObject obj = doc.object();

    int statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt();

    if ( statusCode == 200 && obj.contains( "token" ) )  {
        QString token = obj[ "token" ].toString();

        qDebug() << "Login exitoso. Token:" << token;

        lblEstado->setText( "Login exitoso." );

        emit loginExitoso( token );
        this->hide();
    }
    else  {
        QString detalle = obj.value( "detail" ).toString( "Credenciales inválidas" );
        lblEstado->setText( "Error: " + detalle );
        qDebug() << "Login fallido:" << detalle;
    }

    reply->deleteLater();
}
