#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

// =============================================================================
// LoginWindow — Ventana de login y registro
//
// Se muestra antes de MainWindow. El usuario debe autenticarse contra
// el servidor remoto (poo.juriserver.website) para poder usar el programa.
// Al loguearse exitosamente, crea MainWindow pasandole el token JWT
// y la API Key de Gemini que devuelve el servidor.
// =============================================================================

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void onLoginClicked();
    void onRegistroClicked();
    void onCambiarARegistro();
    void onCambiarALogin();
    void onLoginResponse(QNetworkReply *reply);
    void onRegistroResponse(QNetworkReply *reply);

private:
    void setupUI();
    void setLoading(bool loading);

    // Paginas del stacked widget
    QStackedWidget *m_stack;

    // Campos de login
    QLineEdit *m_loginUsuario;
    QLineEdit *m_loginPassword;
    QPushButton *m_btnLogin;
    QPushButton *m_btnIrRegistro;
    QLabel *m_loginError;

    // Campos de registro
    QLineEdit *m_regUsuario;
    QLineEdit *m_regPassword;
    QLineEdit *m_regConfirmar;
    QLineEdit *m_regApiKey;
    QPushButton *m_btnRegistro;
    QPushButton *m_btnIrLogin;
    QLabel *m_regError;

    QNetworkAccessManager *m_manager;

    static const QString SERVER_URL;
};

#endif // LOGINWINDOW_H
