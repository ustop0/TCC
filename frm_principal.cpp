#include "frm_principal.h"
#include "ui_frm_principal.h"
#include "funcoes_gloabais.h" //funcoes globais
#include "frm_gestaousuarios.h"

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


void Frm_principal::on_actionUsuario_triggered() //abre a tela de usuários
{

    if(variaveis_globais::acesso_colab == 'A') //verifica a permissao de acesso do colaborador
    {
        frm_gestaousuarios f_gestaousuarios;
        f_gestaousuarios.exec();
    }
    else
    {
        QMessageBox::information(this, "ACESSO", "Acesso não permitido");
    }
}

