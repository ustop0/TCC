#include "frms_selecionacliente.h"
#include "ui_frms_selecionacliente.h"
#include "frm_agendaservicos.h" //formulário de agendamento de serviços
#include "ui_frm_agendaservicos.h"

frms_selecionacliente::frms_selecionacliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frms_selecionacliente)
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

frms_selecionacliente::~frms_selecionacliente()//**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}


//filtrando clientes
void frms_selecionacliente::on_txt_filtrarCliente_returnPressed()
{

}

//botão filtrar clientes
void frms_selecionacliente::on_btn_filtrarCliente_clicked() //filtro
{

}


void frms_selecionacliente::on_btn_confirmarCliente_clicked() //confirmar
{
   //preenche o campo nome do cliente no formulário de agendamento de serviços
   //objeto instanciado por alocação automática, verificar se não vai causar
   //problemas de memória
   Ui_frm_agendaservicos uiAgendaServicos;

   QString cliente_selecionado = "provisória"; //recebe do table widget
   uiAgendaServicos.txt_nomeCliente->setText(cliente_selecionado);
}



