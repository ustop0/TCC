#ifndef FRMS_SELECIONACLIENTE_OS_H
#define FRMS_SELECIONACLIENTE_OS_H

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
class frms_selecionacliente_os;
}

class frms_selecionacliente_os : public QDialog
{
    Q_OBJECT

public:
    explicit frms_selecionacliente_os(QWidget *parent = nullptr);
    ~frms_selecionacliente_os();

    //instanciando conexao com o banco de dados
    Conexao con;

    //variaveis globais
    QString g_codigo_cliente;
    QString g_nome_cliente;
    QString g_codigo_veiculo;
    QString g_nome_veiculo;
    QString g_placa_veiculo;
    QString g_cor_veiculo;

private slots:
    void on_tw_selecionaCliente_itemSelectionChanged();

    void on_tw_selecionaVeiculo_itemSelectionChanged();

    void on_txt_filtrarCliente_returnPressed();

    void on_btn_filtrarCliente_clicked();

    void on_btn_confirmarCliente_clicked();

private:
    Ui::frms_selecionacliente_os *ui;
};

#endif // FRMS_SELECIONACLIENTE_OS_H
