#ifndef FRMS_SELECIONAVEICULO_H
#define FRMS_SELECIONAVEICULO_H

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
class frms_selecionaveiculo;
}

class frms_selecionaveiculo : public QDialog
{
    Q_OBJECT

public:
    explicit frms_selecionaveiculo(QWidget *parent = nullptr, QString c_codigoCliente = "");
    ~frms_selecionaveiculo();

    //instanciando conexao com o banco de dados
    Conexao con;

    //recebe nome cliente do agenda serviços
    QString g_codigo_cliente;

    QString g_nomeMarca;
    QString g_codigoVeiculo;
    QString g_nomeVeiculo;

public slots:


private slots:
    void on_tw_selecionaVeiculo_itemSelectionChanged();

    void on_txt_filtrarVeiculo_returnPressed();

    void on_btn_filtrarVeiculo_clicked();

    void on_btn_confirmarVeiculo_clicked();

signals:
    void sendData( QString );

private:
    Ui::frms_selecionaveiculo *ui;
};

#endif // FRMS_SELECIONAVEICULO_H
