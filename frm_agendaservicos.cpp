#include "frm_agendaservicos.h"
#include "ui_frm_agendaservicos.h"
#include "frms_selecionacliente.h" //formulario de seleção de clientes
#include "frms_selecionaveiculo.h" //formulario de seleção de veiculos

//globais, recebem dos formulários de seleção
//QString g_nome_cliente;
//QString g_codigo_cliente;
//QString g_nome_veiculo;
//QString g_codigo_veiculo;

frm_agendaservicos::frm_agendaservicos(QWidget *parent, QString c_codigo_cliente
                                                      , QString c_nome_cliente
                                                      , QString c_codigo_veiculo
                                                      , QString c_nome_veiculo) :
    QDialog(parent),
    ui(new Ui::frm_agendaservicos)
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

    //enviando dados entre os formulários
    ui->txt_nomeCliente->setText( c_nome_cliente );
    g_codigo_cliente = c_codigo_cliente;

    //ui->txt_nomeVeiculo->setText( c_nome_veiculo );
    ui->txt_nomeVeiculo->setText( g_nome_veiculo );
    //recebendo g_codigo_veiculo da seleção de veiculos
    //g_codigo_veiculo = c_codigo_veiculo;

}

frm_agendaservicos::~frm_agendaservicos()//**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//abre formulário de seleção de clientes
void frm_agendaservicos::on_btn_selecionaCliente_clicked() //frms de seleção de clientes
{
    frms_selecionacliente fmSelecionaCliente;
    fmSelecionaCliente.exec();
}

//abre formulário de seleção de veiculos
void frm_agendaservicos::on_btn_selecionaVeiculo_clicked()
{
    if( ui->txt_nomeCliente->text() == "" )
    {
        QMessageBox::information(this, "Aviso", "Informe um cliente antes de "
                                                "selecionar um veículo");

    }
    else
    {
        //teste
        g_codigo_cliente = "2";
        //enviando codigo do cliente para a selecaoveiculo
        frms_selecionaveiculo fm_selecionaveiculo(this, g_codigo_cliente);
        fm_selecionaveiculo.exec();
    }
}

void frm_agendaservicos::on_btn_agendarServico_clicked()
{
    if( ui->txt_nomeCliente->text() == "" || ui->txt_nomeCliente->text() == ""
                                          || g_codigo_cliente == ""
                                          || g_codigo_veiculo == "")
    {
        QMessageBox::information(this, "Erro", "Os campos Nome Cliente e Veiculo Cliente estão vazios");
    }
    else
    {
        QSqlQuery query;

        query.prepare("");
    }

}
