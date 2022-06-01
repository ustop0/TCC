#ifndef FRM_ORDEMSERVICO_H
#define FRM_ORDEMSERVICO_H

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
class frm_ordemservico;
}

class frm_ordemservico : public QDialog
{
    Q_OBJECT

public:
    explicit frm_ordemservico(QWidget *parent = nullptr, QString c_codigo_cliente = ""
                                                              , QString c_nome_cliente = ""
                                                              , QString c_codigo_veiculo = ""
                                                              , QString c_nome_veiculo = ""
                                                              , QString c_placa_veiculo = ""
                                                              , QString c_cor_veiculo = "");
    ~frm_ordemservico();

    //instanciando conexao com o banco de dados
    Conexao con;

    QString g_codigo_cliente;
    QString g_nome_cliente;
    QString g_codigo_veiculo;
    QString g_nome_veiculo;
    QString g_placa_veiculo;
    QString g_cor_veiculo;

private:
    Ui::frm_ordemservico *ui;
};

#endif // FRM_ORDEMSERVICO_H
