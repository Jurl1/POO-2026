#include "widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QNetworkRequest>

Widget::Widget( QWidget * parent ) : QWidget( parent ),
    totalDescargas( 0 ),
    descargasCompletadas( 0 ),
    descargandoPagina( false )  {

    this->setWindowTitle( "Parser y Descargador de Recursos Web" );
    this->resize( 650, 500 );

    QVBoxLayout * vlPrincipal = new QVBoxLayout( this );

    // ---- Fila URL ----
    QHBoxLayout * hlUrl = new QHBoxLayout;
    QLabel * lblUrl = new QLabel( "URL:" );
    leUrl = new QLineEdit;
    leUrl->setPlaceholderText( "Ejemplo: https://www.ejemplo.com" );
    pbDescargar = new QPushButton( "Descargar" );

    hlUrl->addWidget( lblUrl );
    hlUrl->addWidget( leUrl );
    hlUrl->addWidget( pbDescargar );

    // ---- Fila Directorio ----
    QHBoxLayout * hlDir = new QHBoxLayout;
    QLabel * lblDir = new QLabel( "Directorio:" );
    leDirectorio = new QLineEdit;
    leDirectorio->setReadOnly( true );
    leDirectorio->setPlaceholderText( "Seleccione un directorio de destino..." );
    pbDirectorio = new QPushButton( "Examinar..." );

    hlDir->addWidget( lblDir );
    hlDir->addWidget( leDirectorio );
    hlDir->addWidget( pbDirectorio );

    // ---- Lista de URLs encontradas ----
    QLabel * lblLista = new QLabel( "URLs encontradas:" );
    lwUrls = new QListWidget;

    // ---- Barra de progreso y estado ----
    barraProgreso = new QProgressBar;
    barraProgreso->setValue( 0 );

    lblEstado = new QLabel( "Listo." );

    // ---- Armado del layout ----
    vlPrincipal->addLayout( hlUrl );
    vlPrincipal->addLayout( hlDir );
    vlPrincipal->addWidget( lblLista );
    vlPrincipal->addWidget( lwUrls );
    vlPrincipal->addWidget( barraProgreso );
    vlPrincipal->addWidget( lblEstado );

    // ---- Network Access Manager ----
    nam = new QNetworkAccessManager( this );

    // ---- Conexiones con SIGNAL y SLOT ----
    connect( pbDirectorio, SIGNAL( clicked() ), this, SLOT( slot_seleccionarDirectorio() ) );
    connect( pbDescargar, SIGNAL( clicked() ), this, SLOT( slot_descargar() ) );
    connect( nam, SIGNAL( finished( QNetworkReply * ) ), this, SLOT( slot_descargaFinalizada( QNetworkReply * ) ) );
}

void Widget::slot_seleccionarDirectorio()  {
    QString dir = QFileDialog::getExistingDirectory( this, "Seleccionar directorio de destino", "./" );

    if ( ! dir.isEmpty() )  {
        directorioDestino = dir;
        leDirectorio->setText( dir );
    }
}

void Widget::slot_descargar()  {
    QString url = leUrl->text().trimmed();

    if ( url.isEmpty() )  {
        QMessageBox::warning( this, "Advertencia", "Ingrese una URL." );
        return;
    }

    if ( directorioDestino.isEmpty() )  {
        QMessageBox::warning( this, "Advertencia", "Seleccione un directorio de destino." );
        return;
    }

    // Agregar http:// si no tiene protocolo
    if ( ! url.startsWith( "http://" ) && ! url.startsWith( "https://" ) )  {
        url = "http://" + url;
    }

    lwUrls->clear();
    urlsRecursos.clear();
    descargasCompletadas = 0;
    totalDescargas = 0;
    barraProgreso->setValue( 0 );

    descargandoPagina = true;
    lblEstado->setText( "Descargando página principal..." );
    pbDescargar->setEnabled( false );

    QNetworkRequest request{ QUrl( url ) };
    request.setAttribute( QNetworkRequest::RedirectPolicyAttribute,
                          QNetworkRequest::NoLessSafeRedirectPolicy );
    nam->get( request );
}

void Widget::slot_descargaFinalizada( QNetworkReply * reply )  {

    if ( reply->error() != QNetworkReply::NoError )  {
        qDebug() << "Error en descarga:" << reply->url().toString() << "-" << reply->errorString();

        if ( descargandoPagina )  {
            lblEstado->setText( "Error al descargar la página: " + reply->errorString() );
            pbDescargar->setEnabled( true );
            descargandoPagina = false;
        }
        else  {
            descargasCompletadas++;

            if ( totalDescargas > 0 )  {
                barraProgreso->setValue( descargasCompletadas * 100 / totalDescargas );
            }

            if ( descargasCompletadas >= totalDescargas )  {
                lblEstado->setText( QString( "Finalizado. %1 recursos procesados." ).arg( totalDescargas ) );
                pbDescargar->setEnabled( true );
            }
        }

        reply->deleteLater();
        return;
    }

    if ( descargandoPagina )  {
        descargandoPagina = false;

        QByteArray datos = reply->readAll();
        QString html = QString::fromUtf8( datos );
        QString baseUrl = reply->url().toString();

        // Guardar el HTML como index.html
        QFile archivoHtml( directorioDestino + "/index.html" );
        if ( archivoHtml.open( QIODevice::WriteOnly ) )  {
            archivoHtml.write( datos );
            archivoHtml.close();
            qDebug() << "Guardado: index.html";
        }

        // Parsear y buscar todas las URLs
        urlsRecursos = parser.buscarUrls( html, baseUrl );
        totalDescargas = urlsRecursos.size();

        for ( int i = 0; i < urlsRecursos.size(); i++ )  {
            lwUrls->addItem( urlsRecursos.at( i ) );
        }

        if ( totalDescargas == 0 )  {
            lblEstado->setText( "No se encontraron recursos para descargar." );
            pbDescargar->setEnabled( true );
            reply->deleteLater();
            return;
        }

        lblEstado->setText( QString( "Se encontraron %1 recursos. Descargando..." ).arg( totalDescargas ) );
        barraProgreso->setMaximum( 100 );

        // Iniciar la descarga de cada recurso
        for ( int i = 0; i < urlsRecursos.size(); i++ )  {
            QNetworkRequest request{ QUrl( urlsRecursos.at( i ) ) };
            request.setAttribute( QNetworkRequest::RedirectPolicyAttribute,
                                  QNetworkRequest::NoLessSafeRedirectPolicy );
            nam->get( request );
        }
    }
    else  {
        // Guardar el recurso descargado en un archivo
        QByteArray datos = reply->readAll();
        QString nombreArchivo = reply->url().fileName();

        if ( nombreArchivo.isEmpty() )  {
            nombreArchivo = "recurso_" + QString::number( descargasCompletadas );
        }

        QFile archivo( directorioDestino + "/" + nombreArchivo );
        if ( archivo.open( QIODevice::WriteOnly ) )  {
            archivo.write( datos );
            archivo.close();
            qDebug() << "Guardado:" << nombreArchivo;
        }

        descargasCompletadas++;

        if ( totalDescargas > 0 )  {
            barraProgreso->setValue( descargasCompletadas * 100 / totalDescargas );
        }

        lblEstado->setText( QString( "Descargado %1 de %2 recursos." )
                            .arg( descargasCompletadas ).arg( totalDescargas ) );

        if ( descargasCompletadas >= totalDescargas )  {
            lblEstado->setText( QString( "Finalizado. %1 recursos descargados en: %2" )
                                .arg( totalDescargas ).arg( directorioDestino ) );
            pbDescargar->setEnabled( true );
        }
    }

    reply->deleteLater();
}
