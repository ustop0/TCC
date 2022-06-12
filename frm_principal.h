#ifndef FRM_PRINCIPAL_H
#define FRM_PRINCIPAL_H

#include <cstdlib>
#include <QMainWindow>
#include <QDialog>
#include <QMainWindow>
#include <QtSql> //banco de dados
#include <QMessageBox>
#include <QTime> //relogio do sistema
#include <QDateTime>
#include <QCloseEvent> //chama um evento durante o fechamento da janela
#include "ConexaoBanco.h" //banco
#include "funcoes_globais.h" //funcoes globais
#include "variaveis_globais.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Frm_principal; }
QT_END_NAMESPACE

class Frm_principal : public QMainWindow
{
    Q_OBJECT

public:
    Frm_principal(QWidget *parent = nullptr);
    ~Frm_principal();

    //instanciando conexao com o banco de dados
    Conexao con;

public slots:

    //relógio da barra de status do sistema
    void atualizaRelogio();

    //backup do banco de dados do sistema
    //void closeEvent( QCloseEvent *event );

private slots:
    void on_actionUsu_rios_triggered();

    void on_actionClientes_triggered();

    void on_actionFornecedores_triggered();

    void on_actionCadastro_de_Marcas_triggered();

    void on_actionCadastro_de_Modelos_triggered();

    void on_actionCadastro_de_Ve_culos_de_Clientes_triggered();

    void on_actionEstoque_triggered();

    void on_actionNova_Venda_triggered();

    void on_actionGestao_Vendas_triggered();

    void on_actionAgendar_Servi_o_triggered();

    void on_actionOrdem_de_Servi_o_triggered();

    void on_actionSobre_triggered();

    void on_actionSair_triggered();

private:
    Ui::Frm_principal *ui;

    QTimer *tempo;
};
#endif // FRM_PRINCIPAL_H
