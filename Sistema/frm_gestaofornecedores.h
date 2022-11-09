#ifndef FRM_GESTAOFORNECEDORES_H
#define FRM_GESTAOFORNECEDORES_H

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

namespace Ui {
class frm_gestaofornecedores;
}

class frm_gestaofornecedores : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaofornecedores(QWidget *parent = nullptr);
    ~frm_gestaofornecedores();

    //instanciando conexao com o banco de dados
    Conexao con;

public slots:
    void validaCNPJ();

private slots:
    void on_btn_nv_novo_clicked();

    void on_btn_nv_salvar_clicked();

    void on_txt_nv_cnpj_returnPressed();

    void on_tabWidget_currentChanged(int index);

    void on_tw_ge_listarFornecedores_itemSelectionChanged();

    void on_txt_ge_filtrar_returnPressed();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

    void on_btn_validacnpj_clicked();

private:
    Ui::frm_gestaofornecedores *ui;
};

#endif // FRM_GESTAOFORNECEDORES_H
