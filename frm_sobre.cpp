#include "frm_sobre.h"
#include "ui_frm_sobre.h"

frm_sobre::frm_sobre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_sobre)
{
    ui->setupUi(this);
}

frm_sobre::~frm_sobre()
{
    delete ui;
}
