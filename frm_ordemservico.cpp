#include "frm_ordemservico.h"
#include "ui_frm_ordemservico.h"
#include "frms_selecionacliente.h" //formulario de seleção de clientes

frm_ordemservico::frm_ordemservico(QWidget *parent, QString c_codigo_cliente
                                                  , QString c_nome_cliente
                                                  , QString c_codigo_veiculo
                                                  , QString c_nome_veiculo
                                                  , QString c_placa_veiculo
                                                  , QString c_cor_veiculo) :
    QDialog(parent),
    ui(new Ui::frm_ordemservico)
{
    ui->setupUi(this);

    //abrindo a conexao com o banco
    if( !con.abrir() ) //verificando se a conexao foi aberta
    {
        if( !con.abrir() )
        {
            QMessageBox::warning(this, "ERRO", "Erro ao abrir banco de dados");
        }
    }

}

frm_ordemservico::~frm_ordemservico() //**INICIO** destrutor
{
    con.fechar();
    delete ui;
}
