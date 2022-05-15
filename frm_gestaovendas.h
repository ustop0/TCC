#ifndef FRM_GESTAOVENDAS_H
#define FRM_GESTAOVENDAS_H

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
#include <QPrinter>          //impressora
#include <QPainter>          //criar relatório pdf
#include <QDir>              //manipulação de diretórios
#include <QDesktopServices> //aplicativos desktop
#include "ConexaoBanco.h"
#include "funcoes_globais.h"
#include "variaveis_globais.h"

namespace Ui {
class frm_gestaovendas;
}

class frm_gestaovendas : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaovendas(QWidget *parent = nullptr);
    ~frm_gestaovendas();

    //instanciando conexao com o banco de dados
    Conexao con;

private slots:
    void on_tw_listaVendas_itemSelectionChanged();

    void on_btn_filtrar_clicked();

    void on_btn_mostratTodasVendas_clicked();

    void on_btn_relatorio_clicked();



private:
    Ui::frm_gestaovendas *ui;
};

#endif // FRM_GESTAOVENDAS_H
