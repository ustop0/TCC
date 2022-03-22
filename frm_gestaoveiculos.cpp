#include "frm_gestaoveiculos.h"
#include "ui_frm_gestaoveiculos.h"

frm_gestaoveiculos::frm_gestaoveiculos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaoveiculos)
{
    ui->setupUi(this);
}

frm_gestaoveiculos::~frm_gestaoveiculos()
{
    delete ui;
}
