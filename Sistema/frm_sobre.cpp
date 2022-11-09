#include "frm_sobre.h"
#include "ui_frm_sobre.h"

frm_sobre::frm_sobre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_sobre)
{
    ui->setupUi(this);

     ui->lb_git->setText("Git: ""<a href=\"https://github.com/ustop0/TCC\"> "
                         "https://github.com/ustop0</a>");

     ui->lb_git->setTextFormat(Qt::RichText);
     ui->lb_git->setTextInteractionFlags(Qt::TextBrowserInteraction);
     ui->lb_git->setOpenExternalLinks(true);
}

frm_sobre::~frm_sobre()
{
    delete ui;
}
