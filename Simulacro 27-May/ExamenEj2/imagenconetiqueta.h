#ifndef IMAGENCONETIQUETA_H
#define IMAGENCONETIQUETA_H

#include <QWidget>
#include <QImage>
#include <QString>

class ImagenConEtiqueta : public QWidget  {
    Q_OBJECT

public:
    ImagenConEtiqueta( const QString & ruta,
                       const QString & etiqueta,
                       QWidget * parent = nullptr );

    virtual void mostrar() = 0;

    QString getRuta() const;
    QString getEtiqueta() const;

protected:
    QString m_ruta;
    QString m_etiqueta;
    QImage m_imagen;
};

#endif // IMAGENCONETIQUETA_H
