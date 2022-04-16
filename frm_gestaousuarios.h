#ifndef FRM_GESTAOUSUARIOS_H
#define FRM_GESTAOUSUARIOS_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "ConexaoBanco.h"
#include "funcoes_globais.h"

namespace Ui {
class frm_gestaousuarios;
}

class frm_gestaousuarios : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaousuarios(QWidget *parent = nullptr);
    ~frm_gestaousuarios();

    //instanciando conexao com o banco de dados
    Conexao con;

private slots:
    void on_btn_nv_novo_clicked();

    void on_btn_nv_gravar_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_ge_listausuario_itemSelectionChanged();

    void on_txt_ge_filtro_returnPressed();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

private:
    Ui::frm_gestaousuarios *ui;
};

#endif // FRM_GESTAOUSUARIOS_H
