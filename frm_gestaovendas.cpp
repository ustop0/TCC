#include "frm_gestaovendas.h"
#include "ui_frm_gestaovendas.h"

frm_gestaovendas::frm_gestaovendas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaovendas)
{
    ui->setupUi(this);
}

frm_gestaovendas::~frm_gestaovendas()
{
    delete ui;
}
