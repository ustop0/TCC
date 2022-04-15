#include "frm_principal.h"
#include "ui_frm_principal.h"
#include "frm_gestaousuarios.h"
#include "frm_gestaoclientes.h"
#include "frm_gestaofornecedores.h"
#include "frm_gestaoveiculos.h"
#include "frm_gestaoesotque.h"
#include "frm_novavenda.h"
#include "frm_gestaovendas.h"
#include "frm_ordemservico.h"
#include "frm_agendaservicos.h"
#include "frm_sobre.h"

int variaveis_globais::id_colab;
QString variaveis_globais::nome_colab;
QString variaveis_globais::acesso_colab;
QString variaveis_globais::username_colab;
bool variaveis_globais::logado;

//definindo banco de dados, POSTGRESQL
//static QSqlDatabase bancoDeDados=QSqlDatabase::addDatabase("QPSQL");

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
    //está apresentando erro, conferir
    if(variaveis_globais::acesso_colab != 'A') //verifica a permissao de acesso do colaborador
    {
        frm_gestaousuarios f_gestaousuarios;
        f_gestaousuarios.exec();
   }
   else
   {
       QMessageBox::information(this, "ACESSO", "Acesso não permitido");
   }
}


void Frm_principal::on_actionClientes_triggered() //abre a tela de clientes
{
    frm_gestaoclientes f_gestaoclientes ;
    f_gestaoclientes.exec();
}


void Frm_principal::on_actionFornecedores_triggered() //abre a tela de fornecedores
{
    frm_gestaofornecedores f_gestaofornecedores;
    f_gestaofornecedores.exec();
}


void Frm_principal::on_actionVeiculos_triggered() //abre a tela de veiculos
{
    frm_gestaoveiculos f_gestaoveiculos;
    f_gestaoveiculos.exec();
}

void Frm_principal::on_actionEstoque_triggered() //abre a tela de estoque
{
    frm_gestaoesotque f_gestaoesotque;
    f_gestaoesotque.exec();
}


void Frm_principal::on_actionNova_Venda_triggered() //abre tela de nova venda
{
    frm_novavenda f_novavenda;
    f_novavenda.exec();
}


void Frm_principal::on_actionGestao_de_Vendas_triggered() //abre tela de gestão de vendas
{
    frm_gestaovendas f_gestaovendas;
    f_gestaovendas.exec();
}


void Frm_principal::on_actionOrdem_de_Servi_o_2_triggered() //abre tela de ordem de serviço
{
    frm_ordemservico f_ordemservico;
    f_ordemservico.exec();
}


void Frm_principal::on_actionAgendar_Servi_o_2_triggered() //abre tela de agendar serviço
{
    frm_agendaservicos f_agendaservicos;
    f_agendaservicos.exec();
}


void Frm_principal::on_actionSobre_triggered() //abre tela de sobre, informações sistema
{
    frm_sobre f_sobre ;
    f_sobre.exec();
}


void Frm_principal::on_actionSair_triggered() //sair do sistema
{
    close();
}

