#include "frm_agendaservicos.h"
#include "ui_frm_agendaservicos.h"
#include "frms_selecionacliente.h" //formulario de seleção de clientes

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

    //recebendo dados cliente
    ui->txt_nomeCliente->setText( c_nome_cliente );
    g_codigo_cliente = c_codigo_cliente;

    //recebendo dados veiculo
    ui->txt_nomeVeiculo->setText( c_nome_veiculo );
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

//btn agendar serviço
void frm_agendaservicos::on_btn_agendarServico_clicked()
{
    if( ui->txt_nomeCliente->text() == "" || ui->txt_nomeCliente->text() == ""
                                          || g_codigo_cliente == ""
                                          || g_codigo_veiculo == "" )
    {
        QMessageBox::information(this, "Erro", "Os campos com os dados do cliente estão vázios");
    }
    else
    {
        QString data = ui->de_dataHora->text();
        QString servico = ui->txt_tipoServico->text();
        QString observacao = ui->txt_tipoServico->text();
        QString codigo_cliente = g_codigo_cliente;
        QString codigo_veiculo = g_codigo_veiculo;

        QSqlQuery query;

        query.prepare("INSERT INTO "
                        "a009_agenda_servicos(a009_data_hora           "
                                             ",a009_servico            "
                                             ",a009_observacao         "
                                             ",a009_status             "
                                             ",a009_ativo boolean      "
                                             ",a009_fk_codigo_cliente  "
                                             ",a009_fk_codigo_veiculo) "
                      "VALUES('" +data           + "'"
                            ",'" +servico        + "'"
                            ",'" +observacao     + "'"
                            ",'1'                  "
                            ",'" +codigo_cliente + "'"
                            ",'" +codigo_veiculo + "'"
                            ",'" +servico        + "')");
    }

}
