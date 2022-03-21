#include "frm_gestaoesotque.h"
#include "ui_frm_gestaoesotque.h"

frm_gestaoesotque::frm_gestaoesotque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaoesotque)
{
    ui->setupUi(this);
}

frm_gestaoesotque::~frm_gestaoesotque()
{
    delete ui;
}
