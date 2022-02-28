#include "frm_gestaousuarios.h"
#include "ui_frm_gestaousuarios.h"

frm_gestaousuarios::frm_gestaousuarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaousuarios)
{
    ui->setupUi(this);
}

frm_gestaousuarios::~frm_gestaousuarios()
{
    delete ui;
}
