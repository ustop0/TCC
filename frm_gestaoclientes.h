#ifndef FRM_GESTAOCLIENTES_H
#define FRM_GESTAOCLIENTES_H

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
#include "ConexaoBanco.h"
#include "funcoes_globais.h"
#include "fn_validacpf.h"

namespace Ui {
class frm_gestaoclientes;
}

class frm_gestaoclientes : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaoclientes(QWidget *parent = nullptr);
    ~frm_gestaoclientes();

    //instanciando conexao com o banco de dados
    Conexao con;

public slots:

    bool recebeCPF( const QString &cliente_cpf );

    void validaCEP();

private slots:
    void on_btn_nv_gravar_clicked(); //original( void )

    void on_txt_nv_cep_returnPressed(); //pressiona campo cep

    void on_btn_nv_validacepj_clicked();

    void on_btn_nv_cadastrarveiculo_clicked();

    void on_tw_ge_listaclientes_itemSelectionChanged();

    void on_txt_ge_filtro_returnPressed();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_txt_ge_cep_returnPressed();

    void on_tabWidget_currentChanged(int index);

    void on_btn_nv_novo_clicked();



    void on_btn_ge_validacep_clicked();

private:
    Ui::frm_gestaoclientes *ui;
};

#endif // FRM_GESTAOCLIENTES_H
