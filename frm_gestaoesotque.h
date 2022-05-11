#ifndef FRM_GESTAOESOTQUE_H
#define FRM_GESTAOESOTQUE_H

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
class frm_gestaoesotque;
}

class frm_gestaoesotque : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaoesotque(QWidget *parent = nullptr);
    ~frm_gestaoesotque();

    //instanciando conexao com o banco de dados
    Conexao con;

public slots:

private slots:
    void on_tabWidget_currentChanged(int index);

    //fornecedores
    void on_tw_nv_listafornecedores_itemSelectionChanged();

    void on_txt_nv_filtrar_returnPressed();

    void on_btn_nv_filtrar_clicked();

    //marcas/modelos
    void on_tw_nv_listamodelos_itemSelectionChanged();

    void on_txt_nv_filtrarModelos_returnPressed();

    void on_btn_nv_filtrarmodelos_clicked();

    //salvando peças
    void on_btn_nv_novo_clicked();

    void on_btn_nv_salvar_clicked();

    //tela de gestão peças
    void on_tw_ge_listapecas_itemSelectionChanged();

    void on_txt_ge_filtrar_returnPressed();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

private:
    Ui::frm_gestaoesotque *ui;
};

#endif // FRM_GESTAOESOTQUE_H
