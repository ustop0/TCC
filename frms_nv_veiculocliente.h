#ifndef FRMS_NV_VEICULOCLIENTE_H
#define FRMS_NV_VEICULOCLIENTE_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <thread> //gerar threads
#include "ConexaoBanco.h"
#include "funcoes_globais.h"

namespace Ui {
class frms_nv_veiculocliente;
}

class frms_nv_veiculocliente : public QDialog
{
    Q_OBJECT

public:
    explicit frms_nv_veiculocliente(QWidget *parent = nullptr, QString c_codigo_cliente = ""
                                                             , QString c_nome_marca = ""
                                                             , QString c_codigo_modelo = ""
                                                             , QString c_nome_modelo = "");

    ~frms_nv_veiculocliente();

    //instanciando conexao com o banco de dados
    Conexao con;

    //a chave estrangeira é feita por uma query que precisa do cpf para o filtro where
    QString g_veiculo_modelo; //removido static
    QString g_codigo_cliente;

    QString g_codigo_marca;
    QString g_nome_marca;
    QString g_codigo_modelo;
    QString g_nome_modelo;

public slots:
    void conf_tw_ge_veiculos();

    void prepararCB();

    void cbFiltro( const QString &nome_marca );

    QString crudModelo();

private slots:
    void on_tw_nv_clientes_itemSelectionChanged();

    void on_txt_nv_filtrar_returnPressed();

    void on_btn_nv_filtrar_clicked();

    void on_btn_selecionaVeiculo_clicked();

    void on_btn_nv_salvar_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_ge_veiculos_itemSelectionChanged();

    void on_txt_ge_filtrar_returnPressed();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

private:
    Ui::frms_nv_veiculocliente *ui;
};

#endif // FRMS_NV_VEICULOCLIENTE_H
