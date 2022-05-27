#ifndef FRM_AGENDASERVICOS_H
#define FRM_AGENDASERVICOS_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject> //sinais entre forms
#include "ConexaoBanco.h"
#include "funcoes_globais.h"
#include "Classes/clcliente.h"
#include "Classes/clveiculo.h"

namespace Ui {
class frm_agendaservicos;
}

class frm_agendaservicos : public QDialog
{
    Q_OBJECT

public:
    explicit frm_agendaservicos(QWidget *parent = nullptr, QString c_codigo_cliente = ""
                                                         , QString c_nome_cliente = ""
                                                         , QString c_codigo_veiculo = ""
                                                         , QString c_nome_veiculo = "");
    ~frm_agendaservicos();

    //instanciando conexao com o banco de dados
    Conexao con;

    QString g_codigo_cliente;
    QString g_nome_cliente;
    QString g_codigo_veiculo;
    QString g_nome_veiculo;

public slots:

private slots:
    void on_btn_selecionaCliente_clicked();

    void on_btn_agendarServico_clicked();

private:
    Ui::frm_agendaservicos *ui;
};

#endif // FRM_AGENDASERVICOS_H
