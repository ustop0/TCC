#include "frm_login.h"
#include "ui_frm_login.h"

Frm_login::Frm_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Frm_login)
{
    ui->setupUi(this);
}

Frm_login::~Frm_login()
{
    delete ui;
}
