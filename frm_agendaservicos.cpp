#include "frm_agendaservicos.h"
#include "ui_frm_agendaservicos.h"

frm_agendaservicos::frm_agendaservicos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_agendaservicos)
{
    ui->setupUi(this);
}

frm_agendaservicos::~frm_agendaservicos()
{
    delete ui;
}
