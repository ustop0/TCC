#include "frms_selecionacliente.h"
#include "ui_frms_selecionacliente.h"

frms_selecionacliente::frms_selecionacliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frms_selecionacliente)
{
    ui->setupUi(this);
}

frms_selecionacliente::~frms_selecionacliente()
{
    delete ui;
}
