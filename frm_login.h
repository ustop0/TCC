#ifndef FRM_LOGIN_H
#define FRM_LOGIN_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql> //banco de dados
#include <QMessageBox>
#include <QSplashScreen> //usar splash screens
#include <QTimer>
#include "ConexaoBanco.h" //conexao com o banco
#include "funcoes_globais.h"
#include "variaveis_globais.h" //variaveis globais do programa

namespace Ui {
class Frm_login;
}

class Frm_login : public QDialog
{
    Q_OBJECT

public:
    explicit Frm_login(QWidget *parent = nullptr);
    ~Frm_login();

    //conexao com o banco
    bool logado;
    Conexao con;
    QString nome, acesso;
    int id;

    //mostrar splashscreen
    static void splashScreen();

private slots:
    void on_btn_logar_clicked();

private:
    Ui::Frm_login *ui;
};

#endif // FRM_LOGIN_H
