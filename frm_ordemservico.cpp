#include "frm_ordemservico.h"
#include "ui_frm_ordemservico.h"

frm_ordemservico::frm_ordemservico(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_ordemservico)
{
    ui->setupUi(this);
}

frm_ordemservico::~frm_ordemservico()
{
    delete ui;
}
