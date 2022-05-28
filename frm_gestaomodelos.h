#ifndef FRM_GESTAOMODELOS_H
#define FRM_GESTAOMODELOS_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "ConexaoBanco.h"
#include "funcoes_globais.h"

namespace Ui {
class frm_modelos;
}

class frm_modelos : public QDialog
{
    Q_OBJECT

public:
    explicit frm_modelos(QWidget *parent = nullptr);
    ~frm_modelos();

    //instanciando conexao com o banco de dados
    Conexao con;

private slots:
    void on_btn_nv_novo_clicked();

private:
    Ui::frm_modelos *ui;
};

#endif // FRM_GESTAOMODELOS_H
