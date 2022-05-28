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

    QString g_codigo_marca;

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_tw_listamarcas_itemSelectionChanged();

    void on_txt_nv_filtrar_returnPressed();

    void on_btn_nv_filtrar_clicked();

    void on_btn_nv_novo_clicked();

    void on_btn_nv_salvar_clicked();

private:
    Ui::frm_modelos *ui;
};

#endif // FRM_GESTAOMODELOS_H
