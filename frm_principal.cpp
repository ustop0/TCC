#include "frm_principal.h"
#include "ui_frm_principal.h"

Frm_principal::Frm_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Frm_principal)
{
    ui->setupUi(this);
}

Frm_principal::~Frm_principal()
{
    delete ui;
}

