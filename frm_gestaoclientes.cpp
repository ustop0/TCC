#include "frm_gestaoclientes.h"
#include "ui_frm_gestaoclientes.h"

frm_gestaoclientes::frm_gestaoclientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaoclientes)
{
    ui->setupUi(this);
}

frm_gestaoclientes::~frm_gestaoclientes()
{
    delete ui;
}


void frm_gestaoclientes::on_btn_nv_gravar_clicked() //gravar novo cliente **DESENVOLVENDO**
{
    //validandoCPF
    //int cpf;
    //int valCpf;
    //cpf = ui->txt_nv_cpf->text().toInt();

    //valCpf = fn_validaCpf::validaCPF( cpf );

    QString cpf2;
    funcoes_globais::tLower(cpf2);

//    if( valCpf == true )
//    {
//        qDebug() << "O CPF digitado É válido" << "\n";
//    }
//    else
//    {
//        qDebug() << "O CPF digitado NÃO É VÁLIDO" << "\n";
//    }
}

