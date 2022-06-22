#include "frm_principal.h"
#include "ui_frm_principal.h"
#include "frm_gestaousuarios.h"
#include "frm_gestaoclientes.h"
#include "frm_gestaofornecedores.h"
#include "frm_gestaoesotque.h"
#include "frm_gestaomarcas.h"
#include "frm_gestaomodelos.h"
#include "frms_nv_veiculocliente.h" //estudando
#include "frm_novavenda.h"
#include "frm_gestaovendas.h"
#include "frm_ordemservico.h"
#include "frm_agendamentoservicos.h"
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

    //**Desabilita a maximixação do formulário
    setFixedSize(this->geometry().width(),this->geometry().height());


     //**Barra de status**
    //**ATENÇÃO** Função atualizaRelogio() não pode ser chamada diretamento
    //--Configurando barra de status--
    tempo = new QTimer(this);
    connect( tempo, SIGNAL( timeout() ),this, SLOT( atualizaRelogio() ) );
    tempo->start( 1000 );

    //utilizando variaveis_globais e atributos da ConexaoBanco
    QString nome_usuario = "Usuário: " + variaveis_globais::username_colab;
    QString base_dados = "Base de dados: " + con.banco_nome;

    ui->lb_nome_usuario->setText( nome_usuario );
    ui->lb_base_dados->setText( base_dados );
    ui->lb_data->setText( "Data: " + QDate::currentDate().toString("dd/MM/yyyy") );

    ui->line_2->setStyleSheet("color: grey");
    ui->line_3->setStyleSheet("color: grey");
    ui->line_4->setStyleSheet("color: grey");

    ui->statusbar->setStyleSheet("QStatusBar{border-top: 1px outset grey; border: 1px outset grey;}");
    ui->statusbar->addPermanentWidget( ui->lb_nome_usuario );
    ui->statusbar->addPermanentWidget( ui->line_2 );
    ui->statusbar->addPermanentWidget( ui->lb_base_dados );
    ui->statusbar->addPermanentWidget( ui->line_3 );
    ui->statusbar->addPermanentWidget( ui->lb_data );
    ui->statusbar->addPermanentWidget( ui->line_4 );
    ui->statusbar->addPermanentWidget( ui->lb_relogio );

    //ui->statusbar->showMessage("TESTE", 4000);

    //**Configuranto TW**
    conf_tw_listaservicos();
}

Frm_principal::~Frm_principal()//**INICIO** destrutor
{
    delete ui;
}

//abre a tela de usuários
void Frm_principal::on_actionUsu_rios_triggered()
{
    if(variaveis_globais::acesso_colab == 'A') //verifica a permissao de acesso do colaborador
    {
        //frm_gestaousuarios f_gestaousuarios;
        //f_gestaousuarios.exec();

        frm_gestaousuarios *f_gestaousuarios = new frm_gestaousuarios();
        f_gestaousuarios->exec();

        try
        {
            delete f_gestaousuarios;
        }
        catch ( ... )
        {
            qDebug() << "__Falha ao deletar ponteiro: f_gestaousuarios na tela principal";
        }
    }
    else
    {
        QMessageBox::information(this, "ACESSO", "Acesso não permitido");
    }
}

//abre a tela de clientes
void Frm_principal::on_actionClientes_triggered()
{
    frm_gestaoclientes *f_gestaoclientes = new frm_gestaoclientes();
    f_gestaoclientes->exec();

    try
    {
        delete f_gestaoclientes;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_gestaoclientes na tela principal";
    }
}

//abre a tela de fornecedores
void Frm_principal::on_actionFornecedores_triggered()
{    
    frm_gestaofornecedores *f_gestaofornecedores = new frm_gestaofornecedores();
    f_gestaofornecedores->exec();

    try
    {
        delete f_gestaofornecedores;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_gestaofornecedores na tela principal";
    }
}

//abre tela de cadastro de marcas
void Frm_principal::on_actionCadastro_de_Marcas_triggered()
{   
    frm_gestaomarcas *f_gestaomarcas = new frm_gestaomarcas();
    f_gestaomarcas->exec();

    try
    {
        delete f_gestaomarcas;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_gestaomarcas na tela principal";
    }
}

//abre tela de cadastro de modelos
void Frm_principal::on_actionCadastro_de_Modelos_triggered()
{   
    frm_modelos *f_gestaomodelos = new frm_modelos();
    f_gestaomodelos->exec();

    try
    {
        delete f_gestaomodelos;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_gestaomodelos na tela principal";
    }
}

//abre tela de cadastro de veiculos de clientes
void Frm_principal::on_actionCadastro_de_Ve_culos_de_Clientes_triggered()
{   
    frms_nv_veiculocliente *f_veiculocliente = new frms_nv_veiculocliente();
    f_veiculocliente->exec();

    try
    {
        delete f_veiculocliente;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_veiculocliente na tela principal";
    }
}

//abre a tela de estoque
void Frm_principal::on_actionEstoque_triggered()
{   
    frm_gestaoesotque *f_gestaoesotque = new frm_gestaoesotque();
    f_gestaoesotque->exec();

    try
    {
        delete f_gestaoesotque;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_gestaoesotque na tela principal";
    }
}

//abre tela de nova venda
void Frm_principal::on_actionNova_Venda_triggered()
{   
    frm_novavenda *f_novavenda = new frm_novavenda();
    f_novavenda->exec();

    try
    {
        delete f_novavenda;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_novavenda na tela principal";
    }
}

//abre tela de gestão de vendas
void Frm_principal::on_actionGestao_Vendas_triggered()
{    
    frm_gestaovendas *f_gestaovendas = new frm_gestaovendas();
    f_gestaovendas->exec();

    try
    {
        delete f_gestaovendas;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_gestaovendas na tela principal";
    }
}

//abre tela de agendar serviço
void Frm_principal::on_actionAgendar_Servi_o_triggered()
{    
    frm_agendamentoservicos *f_agendamentoservicos = new frm_agendamentoservicos();
    f_agendamentoservicos->exec();

    try
    {
        delete f_agendamentoservicos;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_agendamentoservicos na tela principal";
    }
}

//abre tela de ordem de serviço
void Frm_principal::on_actionOrdem_de_Servi_o_triggered()
{    
    frm_ordemservico *f_ordemservico = new frm_ordemservico();
    f_ordemservico->exec();

    try
    {
        delete f_ordemservico;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_ordemservico na tela principal";
    }
}

//abre tela de sobre, informações sistema
void Frm_principal::on_actionSobre_triggered()
{    
    frm_sobre *f_sobre = new frm_sobre();
    f_sobre->exec();

    try
    {
        delete f_sobre;
        qDebug() << "Deletando ponteiro";
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: f_sobre na tela principal";
    }
}

//sair do sistema
void Frm_principal::on_actionSair_triggered()
{
    close();
}

/**FUNÇÕES**/
/*
 *--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 13/03/2022                                                                           |
 * Propósito: Relógio da barra de status do sistema                                           |
 * Chamada: Construtor da classe                                                              |
 *--------------------------------------------------------------------------------------------
 */
void Frm_principal::atualizaRelogio()
{
    QTime tempoAtual = QTime::currentTime();
    QString tempoTexto = tempoAtual.toString("hh:mm:ss");

    ui->lb_relogio->setText("Relógio: " +tempoTexto);
}
/*
 *--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 19/06/2022                                                                           |
 * Propósito: Configurar tw_listaservicos                                                     |
 * Chamada: Construtor da classe                                                              |
 *--------------------------------------------------------------------------------------------
 */
void Frm_principal::conf_tw_listaservicos()
{
    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_listaservicos->setColumnCount(9);
    ui->tw_listaservicos->setColumnWidth(0, 40);
    ui->tw_listaservicos->setColumnWidth(1, 150);
    ui->tw_listaservicos->setColumnWidth(4, 150);
    ui->tw_listaservicos->setColumnWidth(5, 150);
    ui->tw_listaservicos->setColumnWidth(7, 200);
    ui->tw_listaservicos->setColumnWidth(8, 130); //status

    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Cliente","Data", "Hora", "Serviço"
                            ,"Modelo Veículo", "Placa Veículo", "Observação", "Status"};

    ui->tw_listaservicos->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_listaservicos->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listaservicos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listaservicos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listaservicos->verticalHeader()->setVisible(false);


    //abrindo a conexao com o banco
    if( !con.abrir() )
    {
        if( !con.abrir() )
        {
            QMessageBox::warning(this, "ERRO", "Erro ao abrir banco de dados");
        }
    }

    //**Listando serviços no TW**
    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_listaservicos );

    //inserir linhas dentro do table widget
    int contlinhas = 0;
    //Remover os produtos do table widget

    //filtra pelas datas equivalentes a um período de 7 dias
    QSqlQuery query;
    query.prepare("SELECT "
                      "a009_codigo                        "
                      ",a005_nome                         "
                      ",TO_CHAR(a009_data, 'DD/MM/YYYY')  "
                      ",a009_hora                         "
                      ",a009_servico                      "
                      ",a012_nome_veiculo                 "
                      ",a004_placa_veiculo                "
                      ",a009_observacao                   "
                      ",a009_status                       "
                  "FROM "
                      "a009_agenda_servicos "
                      "JOIN a005_cliente ON (a005_codigo = a009_fk_codigo_cliente)  "
                      "JOIN a004_veiculos ON (a004_codigo = a009_fk_codigo_veiculo) "
                      "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                  "WHERE "
                    "a009_data BETWEEN CURRENT_DATE  AND   CURRENT_DATE + 6 "
                    "AND a009_status = 'Pendente'                           "
                    "AND a009_ativo = true                                  "
                  "ORDER BY "
                      "a009_data ASC, a009_hora ASC");

    if( query.exec() ) //verifica se ouve algum erro na execução da query
    {
        //enquanto a query tiver retornando next, insere linhas dentro do table widget
        while( query.next() )
        {
            //inserindo com contador de linhas, por index
            ui->tw_listaservicos->insertRow( contlinhas );
            ui->tw_listaservicos->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            //definindo o tamanho das linhas
            ui->tw_listaservicos->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar serviços");
    }

    //fechando conexao
    con.fechar();
}

/*
 *--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 12/06/2022                                                                           |
 * Propósito: Faz um backup do banco de dados quando o programa for fechado                   |
 * Chamada: quando fechar frm principal                                                       |
 *--------------------------------------------------------------------------------------------
void Frm_principal::closeEvent( QCloseEvent *event )
{
    QMessageBox::StandardButton resposta = QMessageBox::question(
                this,
                tr("Saindo do sistema"),
                tr("Você deseja fazer um backup do banco de dados?"),
                QMessageBox::Yes | QMessageBox::No);

    if( resposta == QMessageBox::Yes )
    {
        QString bk = "cd /home/ustop/QTProjects/build-TCC-Desktop_Qt_6_2_2_GCC_64bit-Debug/ "
                     "bkBanco && ./scriptBk.sh";

        QProcess::execute( bk );

        event->accept();
    }
    else
    {
        close();
        //event->ignore();
    }
}
*/

