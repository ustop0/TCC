#include "frm_gestaomodelos.h"
#include "ui_frm_gestaomodelos.h"

frm_modelos::frm_modelos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_modelos)
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

frm_modelos::~frm_modelos()
{
    con.fechar();
    delete ui;
}

//novo modelo
void frm_modelos::on_btn_nv_novo_clicked()
{
    ui->txt_ge_modelo->clear();
    ui->txt_ge_modelo->setFocus();
}

