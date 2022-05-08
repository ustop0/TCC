#include "frm_principal.h"
#include "ui_frm_principal.h"
#include "frm_gestaousuarios.h"
#include "frm_gestaoclientes.h"
#include "frm_gestaofornecedores.h"
#include "frm_gestaoveiculos.h"
#include "frm_gestaoesotque.h"
#include "frms_nv_veiculocliente.h" //estudando
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
    , ui(new Ui::Frm_principal) //**INICIO** construtor
{
    ui->setupUi(this);

    Conexao dadosBanco; //instanciando banco

    //**ATENÇÃO** Função atualiza relógio não pode ser chamada diretamento
    //atualizaRelogio();
    //--Configurando barra de status--
    tempo = new QTimer(this);
    connect( tempo, SIGNAL( timeout() ),this, SLOT( atualizaRelogio() ) );
    tempo->start( 1000 );


    //barra de status, utilizando variaveis_globais e atributos da ConexaoBanco

    QString nome_usuario = "Usuário: " + variaveis_globais::username_colab;
    QString base_dados = "Base de dados: " + dadosBanco.banco_nome;

    ui->lb_nome_usuario->setText( nome_usuario );
    ui->lb_base_dados->setText( base_dados );

    ui->statusbar->addPermanentWidget( ui->lb_nome_usuario );
    ui->statusbar->addPermanentWidget( ui->line_2 );
    ui->statusbar->addPermanentWidget( ui->lb_base_dados );
    ui->statusbar->addPermanentWidget( ui->line_3 );
    ui->statusbar->addPermanentWidget( ui->lb_relogio );

    //ui->statusbar->showMessage("TESTE", 4000);
}

Frm_principal::~Frm_principal()//**INICIO** destrutor
{
    delete ui;
}

//abre a tela de usuários
void Frm_principal::on_actionUsuario_triggered()
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

//abre a tela de clientes
void Frm_principal::on_actionClientes_triggered()
{
    frm_gestaoclientes f_gestaoclientes ;
    f_gestaoclientes.exec();
}

//abre a tela de fornecedores
void Frm_principal::on_actionFornecedores_triggered()
{
    frm_gestaofornecedores f_gestaofornecedores;
    f_gestaofornecedores.exec();
}

//abre tela de cadastro de veiculos
void Frm_principal::on_actionCadastro_de_veiculos_triggered()
{
    frm_gestaoveiculos f_gestaoveiculos;
    f_gestaoveiculos.exec();
}

//abre tela de cadastro de veiculos de clientes
void Frm_principal::on_actionVeiculos_de_clientes_triggered()
{
    frms_nv_veiculocliente f_veiculocliente;
    f_veiculocliente.exec();
}

void Frm_principal::on_actionEstoque_triggered() //abre a tela de estoque
{
    frm_gestaoesotque f_gestaoesotque;
    f_gestaoesotque.exec();
}

//abre tela de nova venda
void Frm_principal::on_actionNova_Venda_triggered()
{
    frm_novavenda f_novavenda;
    f_novavenda.exec();
}

//abre tela de gestão de vendas
void Frm_principal::on_actionGestao_de_Vendas_triggered()
{
    frm_gestaovendas f_gestaovendas;
    f_gestaovendas.exec();
}

//abre tela de ordem de serviço
void Frm_principal::on_actionOrdem_de_Servi_o_2_triggered()
{
    frm_ordemservico f_ordemservico;
    f_ordemservico.exec();
}

//abre tela de agendar serviço
void Frm_principal::on_actionAgendar_Servi_o_2_triggered()
{
    frm_agendaservicos f_agendaservicos;
    f_agendaservicos.exec();
}

//abre tela de sobre, informações sistema
void Frm_principal::on_actionSobre_triggered()
{
    frm_sobre f_sobre ;
    f_sobre.exec();
}

//sair do sistema
void Frm_principal::on_actionSair_triggered()
{
    close();
}

/**FUNÇÕES**/
//relógio da barra de status do sistema
void Frm_principal::atualizaRelogio()
{
    QTime tempoAtual = QTime::currentTime();
    QString tempoTexto = tempoAtual.toString("hh:mm:ss");

    ui->lb_relogio->setText(tempoTexto);
}
