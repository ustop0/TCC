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

    //TESTES

    //enviando dados entre os formulários
    ui->txt_nomeCliente->setText( c_nome_cliente );
    g_codigo_cliente = c_codigo_cliente;

    ui->txt_nomeVeiculo->setText( c_nome_veiculo );
    //ui->txt_nomeVeiculo->setText( recebeNome );
    //recebendo g_codigo_veiculo da seleção de veiculos
    g_codigo_veiculo = c_codigo_veiculo;

}

frm_agendaservicos::~frm_agendaservicos()//**INICIO** destrutor
{
    con.fechar();
    delete ui;
}

//abre formulário de seleção de clientes
void frm_agendaservicos::on_btn_selecionaCliente_clicked() //frms de seleção de clientes
{
    frms_selecionacliente *fmSelecionaCliente = new frms_selecionacliente();
    fmSelecionaCliente->exec();

    //deletando ponteiro
    try
    {
        delete fmSelecionaCliente;
    }
    catch (...)
    {
        qDebug() << "__Falha ao deletar ponteiro: fmSelecionaCliente na tela de agendaserviços";
    }
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
        //enviando codigo do cliente para a selecaoveiculo
        frms_selecionaveiculo *fm_selecionaveiculo = new frms_selecionaveiculo(this, g_codigo_cliente);
        fm_selecionaveiculo->exec();

        //deletando ponteiro
        try
        {
            delete fm_selecionaveiculo;
        }
        catch (...)
        {
            qDebug() << "__Falha ao deletar ponteiro: fm_selecionaveiculo na tela de agendaserviços";
        }
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

//**FUNÇÕES**
