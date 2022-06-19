#include "frm_login.h"
#include "ui_frm_login.h"
#include "frm_principal.h" //formulario principal

Frm_login::Frm_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Frm_login)
{
    ui->setupUi(this);
}

Frm_login::~Frm_login()
{
    delete ui;
}

void Frm_login::on_btn_logar_clicked()
{
    if(!con.abrir()) //verifica a conexao com o banco de dados
    {
        QMessageBox::warning(this, "ERRO", "Não foi possível se conectar ao banco de dados");
    }
    else //login com o banco de dados
    {
        //QMessageBox::warning(this, "", "Conectado ao banco de dados");
        QString usuario = ui->txt_usuario->text();
        QString senha = ui->txt_senha->text();

        QSqlQuery query;
        query.prepare("SELECT "
                        "* "
                      "FROM "
                        "a001_usuarios "
                      "WHERE "
                        "a001_usuario = '"+usuario+"' AND "
                        "a001_senha   = '"+senha+  "'");

        if(query.exec()) //executa a query
        {
            query.first(); //pega o primeiro retorno da consulta
            if(query.value(1).toString() != "") //verificando as credenciais do login
            {
                //obtendo o nome e o acessono
                variaveis_globais::logado = true;
                variaveis_globais::nome_colab = query.value(1).toString();
                variaveis_globais::username_colab = query.value(2).toString();
                variaveis_globais::id_colab = query.value(0).toInt();
                variaveis_globais::acesso_colab = query.value(5).toString();


                con.fechar(); //fecha a conexao com o banco após a consulta
                close(); //fecha a janela de login

                //mostrando splashscreen
                splashScreen();

                //abrindo o menu principal, sem splash screen
                //auto w = new Frm_principal();
                //w->setAttribute(Qt::WA_DeleteOnClose); //deleta o objeto
                //w->show();
            }
            else
            {
                QMessageBox::warning(this, "ERRO", "Usuário não encontrado");
            }
        }
        else
        {
           QMessageBox::warning(this, "ERRO", "Falha no login");
        }
    }
    con.fechar(); //fecha a conexao com o banco de dados após o login
}

/**FUNÇÕES**/
//splash screen
void Frm_login::splashScreen()
{
    QSplashScreen *telaSplash = new QSplashScreen;

    telaSplash->setPixmap(QPixmap(":/Imagens/splash.png"));
    telaSplash->show(); //mostrando tela splashscreen

    auto w = new Frm_principal();
    w->setAttribute(Qt::WA_DeleteOnClose);

    //define o tempo de duração do splash
    QTimer::singleShot(3000, telaSplash, SLOT(close()));
    //define o tempo para mostrar o formulario principal
    QTimer::singleShot(3000, w, SLOT(show()));

}
