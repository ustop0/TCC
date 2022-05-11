#ifndef FRM_NOVAVENDA_H
#define FRM_NOVAVENDA_H

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
class frm_novavenda;
}

class frm_novavenda : public QDialog
{
    Q_OBJECT

public:
    explicit frm_novavenda(QWidget *parent = nullptr);
    ~frm_novavenda();

    //instanciando conexao com o banco de dados
    Conexao con;

private slots:
    void on_tw_listapecas_itemSelectionChanged();

    void on_txt_ge_filtrar_returnPressed();

    void on_btn_pesquisarproduto_clicked();

private:
    Ui::frm_novavenda *ui;
};

#endif // FRM_NOVAVENDA_H
