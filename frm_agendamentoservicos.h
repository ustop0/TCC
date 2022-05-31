#ifndef FRM_AGENDAMENTOSERVICOS_H
#define FRM_AGENDAMENTOSERVICOS_H

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
class frm_agendamentoservicos;
}

class frm_agendamentoservicos : public QDialog //frm_agendamentoservicos
{
    Q_OBJECT

public:
    explicit frm_agendamentoservicos(QWidget *parent = nullptr, QString c_codigo_cliente = ""
                                                              , QString c_nome_cliente = ""
                                                              , QString c_codigo_veiculo = ""
                                                              , QString c_nome_veiculo = "");
    ~frm_agendamentoservicos();

    //instanciando conexao com o banco de dados
    Conexao con;

    QString g_codigo_cliente;
    QString g_nome_cliente;
    QString g_codigo_veiculo;
    QString g_nome_veiculo;

private slots:
    void on_btn_selecionaCliente_clicked();

    void on_btn_agendarServico_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_listaservicos_itemSelectionChanged();

    void on_txt_ge_filtrar_returnPressed();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

private:
    Ui::frm_agendamentoservicos *ui;
};

#endif // FRM_AGENDAMENTOSERVICOS_H
