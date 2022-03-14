#include "frms_ge_editarcliente.h"
#include "ui_frms_ge_editarcliente.h"

frms_ge_editarcliente::frms_ge_editarcliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frms_ge_editarcliente)
{
    ui->setupUi(this);
}

frms_ge_editarcliente::~frms_ge_editarcliente()
{
    delete ui;
}
