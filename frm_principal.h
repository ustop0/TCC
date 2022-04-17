#ifndef FRM_PRINCIPAL_H
#define FRM_PRINCIPAL_H

#include <QMainWindow>
#include <QDialog>
#include <QMainWindow>
#include <QtSql> //banco de dados
#include <QMessageBox>
#include <QTime> //relogio do sistema
#include <QDateTime>
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

private slots:
    void on_actionUsuario_triggered();

    void on_actionClientes_triggered();

    void on_actionFornecedores_triggered();

    void on_actionVeiculos_triggered();

    void on_actionEstoque_triggered();

    void on_actionNova_Venda_triggered();

    void on_actionGestao_de_Vendas_triggered();

    void on_actionOrdem_de_Servi_o_2_triggered();

    void on_actionAgendar_Servi_o_2_triggered();

    void on_actionSobre_triggered();

    void on_actionSair_triggered();

private:
    Ui::Frm_principal *ui;

    QTimer *tempo;
};
#endif // FRM_PRINCIPAL_H
