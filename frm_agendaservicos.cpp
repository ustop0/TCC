#include "frm_agendaservicos.h"
#include "ui_frm_agendaservicos.h"
#include "frms_selecionacliente.h" //formulario de seleção de clientes

frm_agendaservicos::frm_agendaservicos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_agendaservicos)
{
    ui->setupUi(this);
}

frm_agendaservicos::~frm_agendaservicos()
{
    delete ui;
}




void frm_agendaservicos::on_btn_selecionaCliente_clicked() //frms de seleção de clientes
{
    frms_selecionacliente fmSelecionaCliente;
    fmSelecionaCliente.show();
}

