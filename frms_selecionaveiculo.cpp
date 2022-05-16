#include "frms_selecionaveiculo.h"
#include "ui_frms_selecionaveiculo.h"
#include "frm_agendaservicos.h" //formulário de agendamento de serviços
#include "ui_frm_agendaservicos.h"

frms_selecionaveiculo::frms_selecionaveiculo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frms_selecionaveiculo)
{
    ui->setupUi(this);

    //abrindo a conexao com o banco
    if( !con.abrir() ) //verificando se a conexao foi aberta
    {
        if( !con.abrir() )
        {
            QMessageBox::warning(this, "ERRO", "Erro ao abrir banco de dados");
        }
    }

    //deixa o botão da validação do cnpj invisivel
    ui->txt_filtrarVeiculo->setFocus();

    //configurando combo box
    ui->cb_filtrar->addItem("-");
    ui->cb_filtrar->addItem("Cliente");
    ui->cb_filtrar->addItem("CPF");
    ui->cb_filtrar->addItem("Veiculo");
    ui->cb_filtrar->addItem("PlacaVeiculo");

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_selecionaVeiculo->setColumnCount(9);
    ui->tw_selecionaVeiculo->setColumnWidth(0, 40);
    ui->tw_selecionaVeiculo->setColumnWidth(1, 200);

    //cabeçalhos do table widget
    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Nome", "CPF", "Veiculo", "Placa"
                           ,"Cidade", "Rua","Nro. Casa","Bairro"};

    ui->tw_selecionaVeiculo->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_selecionaVeiculo->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_selecionaVeiculo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_selecionaVeiculo->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_selecionaVeiculo->verticalHeader()->setVisible(false);


    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_selecionaVeiculo );
    //inserir linhas dentro do table widget
    int contlinhas = 0;
    //Remover os produtos do table widget
    QSqlQuery query; //query para listar os colaboradores no table widget
    query.prepare("SELECT "
                      "a003_codigo                   "
                      ",a003_razao_social            "
                      ",a003_nome_fantasia           "
                      ",a003_cnpj                    "
                      ",a003_estado                  "
                      ",a003_cidade                  "
                      ",a003_rua                     "
                      ",a003_numero_estabelecimento  "
                      ",a003_bairro                  "
                      ",a003_porte                   "
                      ",a003_ocupacao                "
                      ",a003_telefone01              "
                      ",a003_telefone02              "
                  "FROM "
                      "a003_fornecedor "
                  "WHERE "
                    "a003_ativo = true "
                  "ORDER BY "
                      "a003_codigo DESC");

    if( query.exec() ) //verifica se ouve algum erro na execução da query
    {
        //enquanto a query tiver retornando next, insere linhas dentro do table widget
        while( query.next() )
        {
            //inserindo com contador de linhas, por index
            ui->tw_selecionaVeiculo->insertRow( contlinhas );
            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_selecionaVeiculo->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            //definindo o tamanho das linhas
            ui->tw_selecionaVeiculo->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar Veiculos de Clientes");
    }
}

frms_selecionaveiculo::~frms_selecionaveiculo()
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//filtrando veiculos
void frms_selecionaveiculo::on_txt_filtrarVeiculo_returnPressed()
{

}

