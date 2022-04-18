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

public slots:
    bool recebeCPF( const QString &cliente_cpf );

    void validaCEP( const QString &cliente_cep );

private slots:
    void on_btn_nv_gravar_clicked(); //original( void )

private:
    Ui::frm_gestaoclientes *ui;
};

#endif // FRM_GESTAOCLIENTES_H
