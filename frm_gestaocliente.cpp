#include "frm_gestaocliente.h"
#include "ui_frm_gestaocliente.h"

frm_gestaocliente::frm_gestaocliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaocliente)
{
    ui->setupUi(this);
}

frm_gestaocliente::~frm_gestaocliente()
{
    delete ui;
}
