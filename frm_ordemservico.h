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
#include "variaveis_globais.h"
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

    //função para resetar campos
    inline void resetaCampos();

    //função para calculo do valor total
    double calculaTotal( QTableWidget *tw, int coluna );


    //**cliente/veiculo
    QString g_codigo_cliente;
    QString g_nome_cliente;
    QString g_codigo_veiculo;
    QString g_nome_veiculo;
    QString g_placa_veiculo;
    QString g_cor_veiculo;

    //Peças O.S.
    QString g_codigo_peca;
    QString g_qtde;
    QString g_denominacao;
    QString g_valor_unitario;
    QString g_valor_comprado;
    QString g_valor_total;
    QString g_margem_lucro;

    //variável global, verifica se um produto foi alterado
    static bool g_alterou;



private slots:
    void on_btn_selecionaveiculo_clicked();

    void on_tw_listapecas_itemSelectionChanged();

    void on_btn_adicionarItem_clicked();

    void on_btn_removerItem_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::frm_ordemservico *ui;
};

#endif // FRM_ORDEMSERVICO_H
