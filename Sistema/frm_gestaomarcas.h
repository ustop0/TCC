#ifndef FRM_GESTAOMARCAS_H
#define FRM_GESTAOMARCAS_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "ConexaoBanco.h"
#include "funcoes_globais.h"

namespace Ui {
class frm_gestaomarcas;
}

class frm_gestaomarcas : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaomarcas(QWidget *parent = nullptr);
    ~frm_gestaomarcas();

    //instanciando conexao com o banco de dados
    Conexao con;

private slots:
    void on_btn_nv_novo_clicked();

    void on_btn_nv_salvar_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_listamarcas_itemSelectionChanged();

    void on_txt_ge_filtrar_returnPressed();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

private:
    Ui::frm_gestaomarcas *ui;
};

#endif // FRM_GESTAOMARCAS_H
