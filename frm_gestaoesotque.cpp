#include "frm_gestaoesotque.h"
#include "ui_frm_gestaoesotque.h"

frm_gestaoesotque::frm_gestaoesotque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaoesotque)
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

    ui->txt_nv_ncPeca->setFocus();

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //configurando combo box fornecedores
    ui->cb_nv_filtrar->addItem("-");
    ui->cb_nv_filtrar->addItem("Razão Social");
    ui->cb_nv_filtrar->addItem("Nome Fantasia");
    ui->cb_nv_filtrar->addItem("CNPJ");
    ui->cb_nv_filtrar->addItem("Ocupação da empresa");
    ui->cb_nv_filtrar->addItem("Cidade");

    //configurando combo box peças
    ui->cb_nv_filtrar->addItem("Nc. Peça");
    ui->cb_nv_filtrar->addItem("Denominação");
    ui->cb_nv_filtrar->addItem("Grupo");
    ui->cb_nv_filtrar->addItem("Tipo Peça");
    ui->cb_nv_filtrar->addItem("Posição");

    //**Estilizando layout dos table widgets**
    //--FORNECEDORES--
    ui->tw_nv_listafornecedores->setColumnCount(13); //define que o table widget terá duas colunas
    ui->tw_nv_listafornecedores->setColumnWidth(0, 150); //id colaborador
    ui->tw_nv_listafornecedores->setColumnWidth(1, 220); //nome colaborador7

    //cabeçalhos do table widget
    QStringList cabecalho1={"Código", "Razão Social", "Nome Fantasia", "CNPJ","Estado"
                           ,"Cidade", "Rua", "Bairro", "Numero", "Porte"
                           ,"Ocupação", "Telefone1", "Telefone2"};

    ui->tw_nv_listafornecedores->setHorizontalHeaderLabels(cabecalho1);
    //definindo cor da linha ao ser selecionada
    ui->tw_nv_listafornecedores->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_nv_listafornecedores->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_nv_listafornecedores->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_nv_listafornecedores->verticalHeader()->setVisible(false);

    //--PEÇAS--
    ui->tw_ge_listapecas->setColumnCount(9); //define que o table widget terá duas colunas
    ui->tw_ge_listapecas->setColumnWidth(0, 150); //id colaborador
    ui->tw_ge_listapecas->setColumnWidth(1, 220); //nome colaborador

    //cabeçalhos do table widget
    QStringList cabecalho2={"Nc. Peça", "Denominação", "Grupo", "Tipo"
                            ,"Valor Compra", "Valor Venda", "Qtde", "Posição"};

    ui->tw_ge_listapecas->setHorizontalHeaderLabels(cabecalho2);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_listapecas->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_listapecas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_listapecas->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_listapecas->verticalHeader()->setVisible(false);
}

frm_gestaoesotque::~frm_gestaoesotque()//**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//quando ocorrer mudança na aba
void frm_gestaoesotque::on_tabWidget_currentChanged(int index)
{
    //estudar colocar o index 0 no construtor
    if( index == 0 ) //verifica a interface pelo index das tabs
    {
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_nv_listafornecedores );
        //inserir linhas dentro do table widget
        int contlinhas=0;
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
                ui->tw_nv_listafornecedores->insertRow( contlinhas );
                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 3
                                            , new QTableWidgetItem(query.value(3).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 4
                                            , new QTableWidgetItem(query.value(4).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 5
                                            , new QTableWidgetItem(query.value(5).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 6
                                            , new QTableWidgetItem(query.value(6).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 7
                                            , new QTableWidgetItem(query.value(7).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 8
                                            , new QTableWidgetItem(query.value(8).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 9
                                            , new QTableWidgetItem(query.value(9).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 10
                                            , new QTableWidgetItem(query.value(10).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 11
                                            , new QTableWidgetItem(query.value(11).toString()));

                ui->tw_nv_listafornecedores->setItem(contlinhas
                                            , 12
                                            , new QTableWidgetItem(query.value(12).toString()));

                //definindo o tamanho das linhas
                ui->tw_nv_listafornecedores->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar fornecedores");
        }
    }
    else if(index == 1)
    {
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_ge_listapecas );
        //inserir linhas dentro do table widget
        int contlinhas=0;
        //Remover os produtos do table widget
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a002_codigo          "
                          ",a002_nc_peca        "
                          ",a002_denomicanao    "
                          ",a002_grupo          "
                          ",a002_tipo_peca      "
                          ",a002_valor_compra   "
                          ",a002_valor_venda    "
                          ",a002_qtde_estoque   "
                          ",a002_posicao_peca   "
                      "FROM "
                          "a002_estoque "
                      "WHERE "
                        "a002_ativo = true "
                      "ORDER BY "
                          "a002_codigo DESC");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_ge_listapecas->insertRow( contlinhas );
                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 3
                                            , new QTableWidgetItem(query.value(3).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 4
                                            , new QTableWidgetItem(query.value(4).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 5
                                            , new QTableWidgetItem(query.value(5).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 6
                                            , new QTableWidgetItem(query.value(6).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 7
                                            , new QTableWidgetItem(query.value(7).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 8
                                            , new QTableWidgetItem(query.value(8).toString()));

                //definindo o tamanho das linhas
                ui->tw_ge_listapecas->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
    }
}

//pega linha do tw fornecedores
void frm_gestaoesotque::on_tw_nv_listafornecedores_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_nv_listafornecedores->item(ui->tw_nv_listafornecedores->currentRow()
                                             , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a003_codigo "
                  "FROM "
                    "a003_fornecedor "
                  "WHERE "
                    "a003_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        //considerar inserir um campo para o código
        ui->txt_nv_codigoFornecedor->setText(query.value(0).toString());
    }
}

//pega linha do tw peças
void frm_gestaoesotque::on_tw_ge_listapecas_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_nv_listafornecedores->item(ui->tw_nv_listafornecedores->currentRow()
                                             , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      ",a002_nc_peca "
                      ",a002_denomicanao "
                      ",a002_grupo "
                      ",a002_tipo_peca "
                      ",a002_valor_compra "
                      ",a002_valor_venda "
                      ",a002_qtde_estoque "
                      ",a002_posicao_peca "
                  "FROM "
                    "a002_estoque "
                  "WHERE "
                    "a002_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        //considerar inserir um campo para o código
        ui->txt_ge_ncPeca->setText(query.value(0).toString());
        ui->txt_ge_denominacao->setText(query.value(1).toString());
        ui->txt_ge_grupo->setText(query.value(2).toString());
        ui->txt_ge_tipoPeca->setText(query.value(3).toString());
        ui->txt_ge_valorcompra->setText(query.value(4).toString());
        ui->txt_ge_valorvenda->setText(query.value(5).toString());
        ui->txt_ge_qtde->setText(query.value(6).toString());

        //preenchendo o combo box com a posição da prateleira
        ui->cb_ge_posicao_prateleira->setText(query.value(7).toString());
    }
}

