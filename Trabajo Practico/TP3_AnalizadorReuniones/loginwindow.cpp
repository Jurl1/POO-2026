#include "loginwindow.h"
#include "mainwindow.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QApplication>
#include <QGraphicsDropShadowEffect>

const QString LoginWindow::SERVER_URL = "https://poo.juriserver.website";

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , m_manager(new QNetworkAccessManager(this))
{
    setupUI();
}

void LoginWindow::setupUI()
{
    setWindowTitle("A.R.I.A. — Iniciar Sesión");
    setFixedSize(420, 520);

    // Estilo general oscuro (mismo tema que MainWindow)
    setStyleSheet(
        "QWidget { background-color: #0e0e0f; color: #e8e6e0; font-family: 'Segoe UI'; }"
        "QLineEdit { background-color: #111113; border: 1px solid #2a2a2e; border-radius: 6px; "
        "  color: #e8e6e0; padding: 10px 14px; font-size: 13px; }"
        "QLineEdit:focus { border: 1px solid #f0a500; }"
        "QPushButton#btnPrimario { background-color: #f0a500; color: #0e0e0f; border: none; "
        "  border-radius: 6px; font-size: 14px; font-weight: bold; padding: 12px; letter-spacing: 1px; }"
        "QPushButton#btnPrimario:hover { background-color: #ffc107; }"
        "QPushButton#btnPrimario:disabled { background-color: #2a2510; color: #5a5020; }"
        "QPushButton#btnSecundario { background-color: transparent; color: #f0a500; border: none; "
        "  font-size: 12px; text-decoration: underline; }"
        "QPushButton#btnSecundario:hover { color: #ffc107; }"
        "QLabel#lblTitulo { color: #f0a500; font-size: 22px; font-weight: bold; letter-spacing: 3px; }"
        "QLabel#lblSubtitulo { color: #6b6b70; font-size: 11px; letter-spacing: 1px; }"
        "QLabel#lblError { color: #f87171; font-size: 11px; }"
    );

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 30, 40, 30);

    // Titulo
    auto *lblTitulo = new QLabel("A.R.I.A.");
    lblTitulo->setObjectName("lblTitulo");
    lblTitulo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(lblTitulo);

    auto *lblSub = new QLabel("ANALIZADOR DE REUNIONES");
    lblSub->setObjectName("lblSubtitulo");
    lblSub->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(lblSub);

    mainLayout->addSpacing(25);

    // Stacked widget para login / registro
    m_stack = new QStackedWidget;
    mainLayout->addWidget(m_stack);

    // ── Página 0: Login ──────────────────────────────────────────────────────
    auto *loginPage = new QWidget;
    auto *loginLayout = new QVBoxLayout(loginPage);
    loginLayout->setContentsMargins(0, 0, 0, 0);
    loginLayout->setSpacing(12);

    m_loginUsuario = new QLineEdit;
    m_loginUsuario->setPlaceholderText("Usuario");
    loginLayout->addWidget(m_loginUsuario);

    m_loginPassword = new QLineEdit;
    m_loginPassword->setPlaceholderText("Contraseña");
    m_loginPassword->setEchoMode(QLineEdit::Password);
    loginLayout->addWidget(m_loginPassword);

    m_loginError = new QLabel;
    m_loginError->setObjectName("lblError");
    m_loginError->setWordWrap(true);
    m_loginError->hide();
    loginLayout->addWidget(m_loginError);

    m_btnLogin = new QPushButton("INICIAR SESIÓN");
    m_btnLogin->setObjectName("btnPrimario");
    loginLayout->addWidget(m_btnLogin);

    loginLayout->addSpacing(8);

    m_btnIrRegistro = new QPushButton("¿No tenés cuenta? Registrate");
    m_btnIrRegistro->setObjectName("btnSecundario");
    loginLayout->addWidget(m_btnIrRegistro, 0, Qt::AlignCenter);

    loginLayout->addStretch();
    m_stack->addWidget(loginPage);

    // ── Página 1: Registro ───────────────────────────────────────────────────
    auto *regPage = new QWidget;
    auto *regLayout = new QVBoxLayout(regPage);
    regLayout->setContentsMargins(0, 0, 0, 0);
    regLayout->setSpacing(10);

    m_regUsuario = new QLineEdit;
    m_regUsuario->setPlaceholderText("Elegí un nombre de usuario");
    regLayout->addWidget(m_regUsuario);

    m_regPassword = new QLineEdit;
    m_regPassword->setPlaceholderText("Contraseña (mínimo 6 caracteres)");
    m_regPassword->setEchoMode(QLineEdit::Password);
    regLayout->addWidget(m_regPassword);

    m_regConfirmar = new QLineEdit;
    m_regConfirmar->setPlaceholderText("Confirmar contraseña");
    m_regConfirmar->setEchoMode(QLineEdit::Password);
    regLayout->addWidget(m_regConfirmar);

    m_regApiKey = new QLineEdit;
    m_regApiKey->setPlaceholderText("API Key de Gemini (AIza...)");
    m_regApiKey->setEchoMode(QLineEdit::Password);
    regLayout->addWidget(m_regApiKey);

    m_regError = new QLabel;
    m_regError->setObjectName("lblError");
    m_regError->setWordWrap(true);
    m_regError->hide();
    regLayout->addWidget(m_regError);

    m_btnRegistro = new QPushButton("CREAR CUENTA");
    m_btnRegistro->setObjectName("btnPrimario");
    regLayout->addWidget(m_btnRegistro);

    regLayout->addSpacing(8);

    m_btnIrLogin = new QPushButton("Ya tengo cuenta, iniciar sesión");
    m_btnIrLogin->setObjectName("btnSecundario");
    regLayout->addWidget(m_btnIrLogin, 0, Qt::AlignCenter);

    regLayout->addStretch();
    m_stack->addWidget(regPage);

    // Empezar en la página de login
    m_stack->setCurrentIndex(0);

    // Conexiones
    connect(m_btnLogin,      &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(m_btnRegistro,   &QPushButton::clicked, this, &LoginWindow::onRegistroClicked);
    connect(m_btnIrRegistro, &QPushButton::clicked, this, &LoginWindow::onCambiarARegistro);
    connect(m_btnIrLogin,    &QPushButton::clicked, this, &LoginWindow::onCambiarALogin);

    // Enter para hacer login/registro
    connect(m_loginPassword, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
    connect(m_regApiKey,     &QLineEdit::returnPressed, this, &LoginWindow::onRegistroClicked);
}

void LoginWindow::onCambiarARegistro()
{
    m_loginError->hide();
    m_stack->setCurrentIndex(1);
}

void LoginWindow::onCambiarALogin()
{
    m_regError->hide();
    m_stack->setCurrentIndex(0);
}

void LoginWindow::setLoading(bool loading)
{
    m_btnLogin->setEnabled(!loading);
    m_btnRegistro->setEnabled(!loading);
    m_btnLogin->setText(loading ? "CONECTANDO..." : "INICIAR SESIÓN");
    m_btnRegistro->setText(loading ? "REGISTRANDO..." : "CREAR CUENTA");
}

// ── Login ────────────────────────────────────────────────────────────────────

void LoginWindow::onLoginClicked()
{
    QString usuario  = m_loginUsuario->text().trimmed();
    QString password = m_loginPassword->text();

    if (usuario.isEmpty() || password.isEmpty()) {
        m_loginError->setText("Completá usuario y contraseña.");
        m_loginError->show();
        return;
    }

    m_loginError->hide();
    setLoading(true);

    QJsonObject json;
    json["usuario"]  = usuario;
    json["password"] = password;

    QUrl url(SERVER_URL + "/login.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    auto *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onLoginResponse(reply);
    });
}

void LoginWindow::onLoginResponse(QNetworkReply *reply)
{
    reply->deleteLater();
    setLoading(false);

    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (reply->error() != QNetworkReply::NoError) {
        QString msg = "Error de conexión con el servidor.";
        if (doc.isObject() && doc.object().contains("error"))
            msg = doc.object()["error"].toString();
        m_loginError->setText(msg);
        m_loginError->show();
        return;
    }

    QJsonObject obj = doc.object();

    if (obj["status"].toString() != "ok") {
        m_loginError->setText(obj["error"].toString());
        m_loginError->show();
        return;
    }

    QString token   = obj["token"].toString();
    QString apiKey  = obj["api_key"].toString();
    QString usuario = obj["usuario"].toString();

    // Crear MainWindow con los datos de la sesión
    auto *mainWindow = new MainWindow(token, apiKey, usuario);
    mainWindow->setAttribute(Qt::WA_DeleteOnClose);
    mainWindow->show();

    // Cerrar la ventana de login
    this->close();
}

// ── Registro ─────────────────────────────────────────────────────────────────

void LoginWindow::onRegistroClicked()
{
    QString usuario   = m_regUsuario->text().trimmed();
    QString password  = m_regPassword->text();
    QString confirmar = m_regConfirmar->text();
    QString apiKey    = m_regApiKey->text().trimmed();

    if (usuario.isEmpty() || password.isEmpty() || apiKey.isEmpty()) {
        m_regError->setText("Todos los campos son obligatorios.");
        m_regError->show();
        return;
    }
    if (password != confirmar) {
        m_regError->setText("Las contraseñas no coinciden.");
        m_regError->show();
        return;
    }
    if (password.length() < 6) {
        m_regError->setText("La contraseña debe tener al menos 6 caracteres.");
        m_regError->show();
        return;
    }

    m_regError->hide();
    setLoading(true);

    QJsonObject json;
    json["usuario"]  = usuario;
    json["password"] = password;
    json["api_key"]  = apiKey;

    QUrl url(SERVER_URL + "/register.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    auto *reply = m_manager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onRegistroResponse(reply);
    });
}

void LoginWindow::onRegistroResponse(QNetworkReply *reply)
{
    reply->deleteLater();
    setLoading(false);

    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (reply->error() != QNetworkReply::NoError) {
        QString msg = "Error de conexión con el servidor.";
        if (doc.isObject() && doc.object().contains("error"))
            msg = doc.object()["error"].toString();
        m_regError->setText(msg);
        m_regError->show();
        return;
    }

    QJsonObject obj = doc.object();

    if (obj["status"].toString() == "ok") {
        QMessageBox::information(this, "Cuenta creada",
            "Tu cuenta fue creada correctamente.\nAhora podés iniciar sesión.");
        // Volver a la página de login con el usuario ya escrito
        m_loginUsuario->setText(m_regUsuario->text());
        m_loginPassword->clear();
        m_stack->setCurrentIndex(0);
    } else {
        m_regError->setText(obj["error"].toString());
        m_regError->show();
    }
}
