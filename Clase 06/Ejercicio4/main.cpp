#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main( int argc, char** argv )  {
    QApplication a( argc, argv );

    QWidget * ventana = new QWidget;
    ventana->setWindowTitle( "Volumen: 15" );
    ventana->resize( 300, 50 );

    QSpinBox * spinBox = new QSpinBox;
    QSlider  * slider  = new QSlider( Qt::Horizontal );
    spinBox->setRange( 0, 100 );
    slider->setRange( 0, 100 );

    // Conexion original: spinBox <-> slider (bidireccional)
    QObject::connect( spinBox, SIGNAL( valueChanged( int ) ),
                      slider,  SLOT(   setValue( int )     ) );
    QObject::connect( slider,  SIGNAL( valueChanged( int ) ),
                      spinBox, SLOT(   setValue( int )     ) );

    // Ejercicio 4: cuando el slider cambia, actualizar el titulo de la ventana
    // Usamos lambda porque setWindowTitle recibe QString y no int
    QObject::connect( slider, &QSlider::valueChanged,
                      ventana, [ventana]( int valor ) {
                          ventana->setWindowTitle( "Volumen: " + QString::number( valor ) );
                      });

    spinBox->setValue( 15 );

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget( spinBox );
    layout->addWidget( slider );
    ventana->setLayout( layout );
    ventana->setVisible( true );

    return a.exec();
}
