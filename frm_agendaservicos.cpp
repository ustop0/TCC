#include "frm_agendaservicos.h"
#include "ui_frm_agendaservicos.h"
#include "frms_selecionacliente.h" //formulario de seleção de clientes
#include "frms_selecionaveiculo.h" //formulario de seleção de veiculos

//globais, recebem dos formulários de seleção
QString g_nome_cliente;
QString g_nome_veiculo;

frm_agendaservicos::frm_agendaservicos(QWidget *parent) :
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
    fmSelecionaCliente.show();

    //ou .exec();
}

//abre formulário de seleção de veiculos
void frm_agendaservicos::on_btn_selecionaVeiculo_clicked()
{
    frms_selecionaveiculo fmSelecionaVeiculo;
    fmSelecionaVeiculo.exec();
}

void frm_agendaservicos::on_btn_agendarServico_clicked()
{
    ClCliente cliente;
    ClVeiculo veiculo;

    //cliente.codigo;
    cliente.nome = ui->txt_nomeCliente->text();
    //veiculo.marca_veiculo;
    //veiculo.modelo_veiculo;

    QSqlQuery query;

    query.prepare("");

}
