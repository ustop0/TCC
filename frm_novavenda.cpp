#include "frm_novavenda.h"
#include "ui_frm_novavenda.h"

frm_novavenda::frm_novavenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_novavenda)
{
    ui->setupUi(this);
}

frm_novavenda::~frm_novavenda()
{
    delete ui;
}
