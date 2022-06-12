#ifndef FRMS_SELECIONACLIENTE_H
#define FRMS_SELECIONACLIENTE_H

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
class frms_selecionacliente;
}

class frms_selecionacliente : public QDialog
{
    Q_OBJECT

public:
    explicit frms_selecionacliente(QWidget *parent = nullptr);
    ~frms_selecionacliente();

    //instanciando conexao com o banco de dados
    Conexao con;

    //variaveis globais
    QString g_codigoCliente;
    QString g_nomeCliente;
    QString g_codigoVeiculo;
    QString g_nomeVeiculo;

private slots:
    void on_tw_selecionaCliente_itemSelectionChanged();

    void on_tw_selecionaVeiculo_itemSelectionChanged();

    void on_txt_filtrarCliente_returnPressed();

    void on_btn_confirmarCliente_clicked();

    void on_btn_filtrarCliente_clicked();

private:
    Ui::frms_selecionacliente *ui;
};

#endif // FRMS_SELECIONACLIENTE_H
