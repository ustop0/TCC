#include "frm_gestaofornecedores.h"
#include "ui_frm_gestaofornecedores.h"

frm_gestaofornecedores::frm_gestaofornecedores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaofornecedores)
{
    ui->setupUi(this);
}

frm_gestaofornecedores::~frm_gestaofornecedores()
{
    delete ui;
}
