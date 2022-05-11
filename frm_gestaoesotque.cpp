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

    //configurando marca modelos
    ui->cb_nv_filtrarmodelos->addItem("-");
    ui->cb_nv_filtrarmodelos->addItem("Marca");
    ui->cb_nv_filtrarmodelos->addItem("Modelo");

    //configurando combo box peças
    ui->cb_ge_filtrar->addItem("-");
    ui->cb_ge_filtrar->addItem("Nc. Peça");
    ui->cb_ge_filtrar->addItem("Denominação");
    ui->cb_ge_filtrar->addItem("Grupo");
    ui->cb_ge_filtrar->addItem("Posição");
    ui->cb_ge_filtrar->addItem("Fornecedor");
    ui->cb_ge_filtrar->addItem("Modelo");

    //**Estilizando layout dos table widgets**
    //--FORNECEDORES--
    ui->tw_nv_listafornecedores->setColumnCount(7);
    ui->tw_nv_listafornecedores->setColumnWidth(0, 100);
    ui->tw_nv_listafornecedores->setColumnWidth(1, 100);

    //cabeçalhos do table widget fornecedores
    QStringList cabecalho1={"Código", "Razão Social", "Nome Fantasia"
                           , "CNPJ","Estado", "Cidade", "Ocupação"};

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

    //--MARCAS/MODELOS--
    ui->tw_nv_listamodelos->setColumnCount(3);
    ui->tw_nv_listamodelos->setColumnWidth(0, 40);
    ui->tw_nv_listamodelos->setColumnWidth(1, 117);
    ui->tw_nv_listamodelos->setColumnWidth(2, 120);

    //cabeçalhos do table widget marcas/modelos
    QStringList cabecalho2={"Código", "Marca", "Modelo"};

    ui->tw_nv_listamodelos->setHorizontalHeaderLabels(cabecalho2);
    //definindo cor da linha ao ser selecionada
    ui->tw_nv_listamodelos->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_nv_listamodelos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_nv_listamodelos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_nv_listamodelos->verticalHeader()->setVisible(false);

    //--PEÇAS--
    ui->tw_ge_listapecas->setColumnCount(10);
    ui->tw_ge_listapecas->setColumnWidth(0, 40);
    ui->tw_ge_listapecas->setColumnWidth(1, 220);

    //cabeçalhos do table widget peças
    QStringList cabecalho3={"Código", "Fornecedor", "Modelo", "Nc. Peça"
                            , "Denominação", "Grupo", "Valor Compra"
                            , "Valor Venda", "Qtde", "Posição"};

    ui->tw_ge_listapecas->setHorizontalHeaderLabels(cabecalho3);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_listapecas->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_listapecas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_listapecas->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_listapecas->verticalHeader()->setVisible(false);


    //Trabalhar no TW de fornecedores, o filtro não está funcionando
    if( ui->tabWidget->currentIndex() == 0 )
    {
        //inserir linhas dentro do table widget
        int contlinhas=0;

        QSqlQuery query;
        query.prepare("SELECT "
                          "a003_codigo                   "
                          ",a003_razao_social            "
                          ",a003_nome_fantasia           "
                          ",a003_cnpj                    "
                          ",a003_estado                  "
                          ",a003_cidade                  "
                          ",a003_porte                   "
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

                //definindo o tamanho das linhas
                ui->tw_nv_listafornecedores->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar fornecedores");
        }

        //listando marcas modelos
        int contlinhas2 = 0;
        QSqlQuery query2;
        query2.prepare("SELECT "
                          "a012_codigo        "
                          ",a011_marca_nome   "
                          ",a012_nome_veiculo "
                      "FROM "
                        "a012_modelos "
                        "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                      "WHERE "
                        "a012_ativo = true");

        if( query2.exec() )
        {
            while( query2.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_nv_listamodelos->insertRow( contlinhas2 );
                ui->tw_nv_listamodelos->setItem(contlinhas2
                                            , 0
                                            , new QTableWidgetItem(query2.value(0).toString()));

                ui->tw_nv_listamodelos->setItem(contlinhas2
                                            , 1
                                            , new QTableWidgetItem(query2.value(1).toString()));
                ui->tw_nv_listamodelos->setItem(contlinhas2
                                            , 2
                                            , new QTableWidgetItem(query2.value(2).toString()));

                //definindo o tamanho das linhas
                ui->tw_nv_listamodelos->setRowHeight(contlinhas2, 20);
                contlinhas2 ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar marcas e modelos");
        }
    }
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
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_nv_listamodelos );
        //inserir linhas dentro do table widget
        int contlinhas = 0;
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a003_codigo                   "
                          ",a003_razao_social            "
                          ",a003_nome_fantasia           "
                          ",a003_cnpj                    "
                          ",a003_estado                  "
                          ",a003_cidade                  "
                          ",a003_ocupacao                "
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

                //definindo o tamanho das linhas
                ui->tw_nv_listafornecedores->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar fornecedores");
        }

        //listando marcas modelos
        int contlinhas2 = 0;
        QSqlQuery query2;
        query2.prepare("SELECT "
                          "a012_codigo        "
                          ",a011_marca_nome   "
                          ",a012_nome_veiculo "
                      "FROM "
                        "a012_modelos "
                        "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                      "WHERE "
                        "a012_ativo = true");

        if( query2.exec() )
        {
            while( query2.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_nv_listamodelos->insertRow( contlinhas2 );
                ui->tw_nv_listamodelos->setItem(contlinhas2
                                            , 0
                                            , new QTableWidgetItem(query2.value(0).toString()));

                ui->tw_nv_listamodelos->setItem(contlinhas2
                                            , 1
                                            , new QTableWidgetItem(query2.value(1).toString()));
                ui->tw_nv_listamodelos->setItem(contlinhas2
                                            , 2
                                            , new QTableWidgetItem(query2.value(2).toString()));

                //definindo o tamanho das linhas
                ui->tw_nv_listamodelos->setRowHeight(contlinhas2, 20);
                contlinhas2 ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar marcas e modelos");
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
                          ",a003_razao_social   "
                          ",a012_nome_veiculo   "
                          ",a002_nc_peca        "
                          ",a002_denomicanao    "
                          ",a002_grupo          "
                          ",a002_valor_compra   "
                          ",a002_valor_venda    "
                          ",a002_qtde_estoque   "
                          ",a002_posicao_peca   "
                      "FROM "
                          "a002_estoque "
                          "JOIN a003_fornecedor ON (a003_codigo = a002_fk_codigo_forncedor) "
                          "JOIN a012_modelos ON (a012_codigo = a002_fk_codigo_modelo) "
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

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 9
                                            , new QTableWidgetItem(query.value(9).toString()));

                ui->tw_ge_listapecas->setItem(contlinhas
                                            , 10
                                            , new QTableWidgetItem(query.value(10).toString()));

                //definindo o tamanho das linhas
                ui->tw_ge_listapecas->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
    }
}

//--CADASTRO DE PEÇAS--
//**FORNECEDORES**
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

//filtro fornecedores
void frm_gestaoesotque::on_txt_nv_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_nv_filtrar->currentText();
    QString txt_filtro = ui->txt_nv_filtrar->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Razão Social" << "Nome Fantasia" << "CNPJ"
           << "Ocupação da empresa" << "Cidade";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_nv_listafornecedores );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_ge_filtrar->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a003_codigo                   "
                        ",a003_razao_social            "
                        ",a003_nome_fantasia           "
                        ",a003_cnpj                    "
                        ",a003_estado                  "
                        ",a003_cidade                  "
                        ",a003_ocupacao                "
                    "FROM "
                        "a003_fornecedor "
                    "WHERE "
                      "a003_ativo = true "
                    "ORDER BY "
                        "a003_codigo DESC";
        }
        else
        {
            busca = "SELECT "
                        "a003_codigo                   "
                        ",a003_razao_social            "
                        ",a003_nome_fantasia           "
                        ",a003_cnpj                    "
                        ",a003_estado                  "
                        ",a003_cidade                  "
                        ",a003_ocupacao                "
                    "FROM "
                        "a003_fornecedor "
                    "WHERE "
                      "a003_ativo = true "
                    "ORDER BY "
                        "a003_codigo DESC";
        }
    }
    else
    {
        //consulta de acordo com a seleção do combo box
        switch( cb_opc.indexOf( cb_filtro ) )
        {
            //Razão Social
            case 0:

                filtro_sql = "a003_razao_social LIKE '%" +txt_filtro+ "%' ";
                break;
            //Nome Fantasia
            case 1:

                filtro_sql = "a003_nome_fantasia LIKE '%" +txt_filtro+ "%' ";
                break;
            //CNPJ
            case 2:

                filtro_sql = "a003_cnpj LIKE '%" +txt_filtro+ "%' ";
                break;
            //Ocupação da empresa
            case 3:

                filtro_sql = "a003_ocupacao LIKE '%" +txt_filtro+ "%' ";
                break;
            //Cidade
            case 4:

                filtro_sql = "a003_cidade LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a003_codigo                   "
                    ",a003_razao_social            "
                    ",a003_nome_fantasia           "
                    ",a003_cnpj                    "
                    ",a003_estado                  "
                    ",a003_cidade                  "
                    ",a003_ocupacao                "
                "FROM "
                    "a003_fornecedor "
                "WHERE "
                    + filtro_sql +
                    "AND a003_ativo = true "
                "ORDER BY "
                    "a003_codigo DESC";
    }

    //contador para percorrer linhas
    int contlinhas=0;
    QSqlQuery query;
    query.prepare( busca );

    if( query.exec() ) //executa a query
    {
        while( query.next() ) //percorrendo query e preenchendo table widget
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

            //definindo o tamanho das linhas
            ui->tw_nv_listafornecedores->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar Fornecedores");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_nv_filtrar->clear();
    ui->txt_nv_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//botão filtrar fornecedores
void frm_gestaoesotque::on_btn_nv_filtrar_clicked()
{
    frm_gestaoesotque::on_txt_nv_filtrar_returnPressed();
}

//**MARCAS/MODELOS**
//pega linha do tw marcas/modelos
void frm_gestaoesotque::on_tw_nv_listamodelos_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_nv_listamodelos->item(ui->tw_nv_listamodelos->currentRow()
                                        , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a012_codigo "
                  "FROM "
                    "a012_modelos "
                    "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                  "WHERE "
                    "a012_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        //considerar inserir um campo para o código
        ui->txt_nv_codigoModelo->setText(query.value(0).toString());
    }
}

//filtrar marcas/modelos
void frm_gestaoesotque::on_txt_nv_filtrarModelos_returnPressed()
{
    QString cb_filtro = ui->cb_nv_filtrarmodelos->currentText();
    QString txt_filtro = ui->txt_nv_filtrarModelos->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Marca" << "Modelo";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_nv_listamodelos );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_nv_filtrarModelos->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a012_codigo          "
                        ",a011_marca_nome     "
                        ",a012_nome_veiculo   "
                    "FROM "
                        "a012_modelos "
                        "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                    "WHERE "
                      "a012_ativo = true";
        }
        else
        {
            busca = "SELECT "
                        "a012_codigo          "
                        ",a011_marca_nome     "
                        ",a012_nome_veiculo   "
                    "FROM "
                        "a012_modelos "
                        "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                    "WHERE "
                      "a012_ativo = true";
        }
    }
    else
    {
        //consulta de acordo com a seleção do combo box
        switch( cb_opc.indexOf( cb_filtro ) )
        {
            //Marca
            case 0:

                filtro_sql = "a011_marca_nome LIKE '%" +txt_filtro+ "%' ";
                break;
            //Modelo
            case 1:

                filtro_sql = "a012_nome_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a012_codigo          "
                    ",a011_marca_nome     "
                    ",a012_nome_veiculo   "
                "FROM "
                    "a012_modelos "
                    "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                "WHERE "
                  + filtro_sql +
                  "a012_ativo = true "
                "ORDER BY "
                    "a012_codigo DESC";

    }

    //contador para percorrer linhas
    int contlinhas=0;
    QSqlQuery query;
    query.prepare( busca );

    if( query.exec() ) //executa a query
    {
        while( query.next() ) //percorrendo query e preenchendo table widget
        {
            //inserindo com contador de linhas, por index
            ui->tw_nv_listamodelos->insertRow( contlinhas );
            ui->tw_nv_listamodelos->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_nv_listamodelos->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_nv_listamodelos->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_nv_listamodelos->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar Marcas/Modelos");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_nv_filtrarModelos->clear();
    ui->txt_nv_filtrarModelos->setFocus(); //posiciona o cursos no campo novamente
}

//botao filtrar marcas/modelos
void frm_gestaoesotque::on_btn_nv_filtrarmodelos_clicked()
{
    frm_gestaoesotque::on_txt_nv_filtrarModelos_returnPressed();
}

//--CADASTRANDO-- nova peça
void frm_gestaoesotque::on_btn_nv_novo_clicked()
{
    ui->txt_nv_codigoFornecedor->clear();
    ui->txt_nv_codigoModelo->clear();
    ui->txt_nv_ncPeca->clear();
    ui->txt_nv_denominacao->clear();
    ui->txt_nv_grupo->clear();
    ui->txt_nv_valorcompra->clear();
    ui->txt_nv_valorvenda->clear();
    ui->txt_nv_qtde->clear();
    ui->txt_nv_posicao->clear();
}

//salvar dados da nova peça
void frm_gestaoesotque::on_btn_nv_salvar_clicked()
{
    QString aux; //converter campo digitado da UI de ',' para '.'

    QString codigo_fornecedor = ui->txt_nv_codigoFornecedor->text();
    QString codigo_modelo = ui->txt_nv_codigoModelo->text();
    QString nc_peca = ui->txt_nv_ncPeca->text();
    QString denominacao = ui->txt_nv_denominacao->text();
    QString grupo = ui->txt_nv_grupo->text();

    aux=ui->txt_nv_valorcompra->text();
    std::replace(aux.begin(), aux.end(), ',', '.'); //substitui valores
    QString valor_compra = aux;

    aux=ui->txt_nv_valorvenda->text();
    std::replace(aux.begin(), aux.end(), ',', '.'); //substitui valores
    QString valor_venda = aux;

    QString qtde = ui->txt_nv_qtde->text();
    QString posicao = ui->txt_nv_posicao->text();

    qDebug() << "Código do fornecedor: " + codigo_fornecedor;
    //verifica se um fornecedor foi selecionado
    if( codigo_fornecedor == "" )
    {
        QMessageBox::information(this, "Fornecedor", "Selecione um fornecedor");
    }

    qDebug() << "Código do fornecedor: " + codigo_modelo;
    //verifica se um fornecedor foi selecionado
    if( codigo_modelo == "" )
    {
        QMessageBox::information(this, "Modelo", "Selecione um modelo");
    }

    QSqlQuery query;
    query.prepare("INSERT INTO "
                    "a002_estoque(a002_nc_peca               "
                                 ",a002_denomicanao          "
                                 ",a002_grupo                "
                                 ",a002_valor_compra         "
                                 ",a002_valor_venda          "
                                 ",a002_qtde_estoque         "
                                 ",a002_posicao_peca         "
                                 ",a002_fk_codigo_forncedor  "
                                 ",a002_fk_codigo_modelo)    "
                    "VALUES('" +QString::number( nc_peca.toInt() )           +  "'"
                          ",'" +denominacao                                  +  "'"
                          ",'" +grupo                                        +  "'"
                          ",'" +QString::number( valor_compra.toFloat() )   +  "'"
                          ",'" +QString::number( valor_venda.toFloat() )    +  "'"
                          ",'" +QString::number( qtde.toInt() )              +  "'"
                          ",'" +posicao                                      +  "'"
                          ",'" +QString::number( codigo_fornecedor.toInt() ) +  "'"
                          ",'" +QString::number( codigo_modelo.toInt() ) +  "') ");

    if( !query.exec() ) //verifica se a query tem algum erro e executa ela
    {
        QMessageBox::critical(this, "ERRO", "Erro ao cadastrar peça");
    }
    else
    {
        ui->txt_nv_codigoFornecedor->clear();
        ui->txt_nv_codigoModelo->clear();
        ui->txt_nv_ncPeca->clear();
        ui->txt_nv_denominacao->clear();
        ui->txt_nv_grupo->clear();
        ui->txt_nv_valorcompra->clear();
        ui->txt_nv_valorvenda->clear();
        ui->txt_nv_qtde->clear();
        ui->txt_nv_posicao->clear();
        ui->txt_nv_ncPeca->setFocus();
    }
}

//--GESTÃO DE PEÇAS--
//pega linha do tw peças
void frm_gestaoesotque::on_tw_ge_listapecas_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_ge_listapecas->item(ui->tw_ge_listapecas->currentRow()
                                     , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a002_codigo        "
                      ",a003_razao_social "
                      ",a012_nome_veiculo "
                      ",a002_nc_peca      "
                      ",a002_denomicanao  "
                      ",a002_grupo        "
                      ",a002_valor_compra "
                      ",a002_valor_venda  "
                      ",a002_qtde_estoque "
                      ",a002_posicao_peca "
                  "FROM "
                    "a002_estoque "
                    "JOIN a003_fornecedor ON (a003_codigo = a002_fk_codigo_forncedor) "
                    "JOIN a012_modelos ON (a012_codigo = a002_fk_codigo_modelo) "
                  "WHERE "
                    "a002_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() )
    {
        query.first();

        //Não pegamos o nome do fornecedor
        ui->txt_ge_codigopeca->setText(query.value(0).toString());
        ui->txt_ge_ncPeca->setText(query.value(3).toString());
        ui->txt_ge_denominacao->setText(query.value(4).toString());
        ui->txt_ge_grupo->setText(query.value(5).toString());
        ui->txt_ge_valorcompra->setText(query.value(6).toString());
        ui->txt_ge_valorvenda->setText(query.value(7).toString());
        ui->txt_ge_qtde->setText(query.value(8).toString());
        ui->txt_ge_posicao->setText(query.value(9).toString());
    }
}

//**DESENVOLVENDO** filtrar peças
void frm_gestaoesotque::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Nc. Peça" << "Denominação" << "Grupo"
           << "Posição"  << "Fornecedor"  << "Modelo";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_ge_listapecas );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_ge_filtrar->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a002_codigo        "
                        ",a003_razao_social "
                        ",a012_nome_veiculo "
                        ",a002_nc_peca      "
                        ",a002_denomicanao  "
                        ",a002_grupo        "
                        ",a002_valor_compra "
                        ",a002_valor_venda  "
                        ",a002_qtde_estoque "
                        ",a002_posicao_peca "
                    "FROM "
                        "a002_estoque "
                        "JOIN a003_fornecedor ON (a003_codigo = a002_fk_codigo_forncedor) "
                        "JOIN a012_modelos ON (a012_codigo = a002_fk_codigo_modelo) "
                    "WHERE "
                        "a002_codigo = true "
                    "ORDER BY "
                        "a002_codigo DESC";
        }
        else
        {
            busca = "SELECT "
                        "a002_codigo        "
                        ",a003_razao_social "
                        ",a012_nome_veiculo "
                        ",a002_nc_peca      "
                        ",a002_denomicanao  "
                        ",a002_grupo        "
                        ",a002_valor_compra "
                        ",a002_valor_venda  "
                        ",a002_qtde_estoque "
                        ",a002_posicao_peca "
                    "FROM "
                        "a002_estoque "
                        "JOIN a003_fornecedor ON (a003_codigo = a002_fk_codigo_forncedor) "
                        "JOIN a012_modelos ON (a012_codigo = a002_fk_codigo_modelo)       "
                    "WHERE "
                        "a002_codigo = true "
                    "ORDER BY "
                        "a002_codigo DESC";
        }
    }
    else
    {
        //consulta de acordo com a seleção do combo box
        switch( cb_opc.indexOf( cb_filtro ) )
        {
            //Nc. Peça
            case 0:

                filtro_sql = "a002_nc_peca LIKE '%" +txt_filtro+ "%' ";
                break;
            //Denominação
            case 1:

                filtro_sql = "a002_denomicanao LIKE '%" +txt_filtro+ "%' ";
                break;
            //Grupo
            case 2:

                filtro_sql = "a002_grupo LIKE '%" +txt_filtro+ "%' ";
                break;
            //Posição
            case 3:

                filtro_sql = "a002_posicao_peca LIKE '%" +txt_filtro+ "%' ";
                break;
            //Fornecedor
            case 4:

                filtro_sql = "a003_razao_social LIKE '%" +txt_filtro+ "%' ";
                break;
            //Modelo
            case 5:

                filtro_sql = "a012_nome_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a002_codigo        "
                    ",a003_razao_social "
                    ",a012_nome_veiculo "
                    ",a002_nc_peca      "
                    ",a002_denomicanao  "
                    ",a002_grupo        "
                    ",a002_valor_compra "
                    ",a002_valor_venda  "
                    ",a002_qtde_estoque "
                    ",a002_posicao_peca "
                "FROM "
                    "a002_estoque "
                    "JOIN a003_fornecedor ON (a003_codigo = a002_fk_codigo_forncedor) "
                    "JOIN a012_modelos ON (a012_codigo = a002_fk_codigo_modelo) "
                "WHERE "
                    + filtro_sql +
                    "AND a002_ativo = true "
                "ORDER BY "
                    "a002_codigo DESC";
    }

    //contador para percorrer linhas
    int contlinhas=0;
    QSqlQuery query;
    query.prepare( busca );

    if( query.exec() ) //executa a query
    {
        while( query.next() ) //percorrendo query e preenchendo table widget
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

            ui->tw_ge_listapecas->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));

//            ui->tw_ge_listapecas->setItem(contlinhas
//                                        , 10
//                                        , new QTableWidgetItem(query.value(10).toString()));

            //definindo o tamanho das linhas
            ui->tw_ge_listapecas->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar peças");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//botão filtrar peças
void frm_gestaoesotque::on_btn_ge_filtrar_clicked()
{
    frm_gestaoesotque::on_txt_ge_filtrar_returnPressed();
}

//edição salvar alteração dados peças
void frm_gestaoesotque::on_btn_ge_salvar_clicked()
{
    if( ui->tw_ge_listapecas->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione uma peça");
        return;
    }

    QString id = ui->tw_ge_listapecas->item(ui->tw_ge_listapecas
                                                    ->currentRow(),0)->text();

    QString aux; //converter campo digitado da UI de ',' para '.'

    QString nc_peca = ui->txt_ge_ncPeca->text();
    QString denominacao = ui->txt_ge_denominacao->text();
    QString grupo = ui->txt_ge_grupo->text();
    QString valor_compra = ui->txt_ge_valorcompra->text();
    QString valor_venda = ui->txt_ge_valorvenda->text();
    QString qtde_estoque = ui->txt_ge_qtde->text();
    QString posicao_peca = ui->txt_ge_posicao->text();

//    aux=ui->txt_nv_valorcompra->text();
//    std::replace(aux.begin(), aux.end(), ',', '.'); //substitui valores
//    valor_compra = aux;

//    aux=ui->txt_nv_valorvenda->text();
//    std::replace(aux.begin(), aux.end(), ',', '.');
//    valor_venda = aux;

    QSqlQuery query;

    query.prepare("UPDATE "
                    "a002_estoque "
                  "SET "
                    "a002_nc_peca        ='" +QString::number( nc_peca.toInt() )         + "'"
                    ",a002_denomicanao   ='" +denominacao                                + "'"
                    ",a002_grupo         ='" +grupo                                      + "'"
                    ",a002_valor_compra  ='" +QString::number( valor_compra.toFloat() )  + "'"
                    ",a002_valor_venda   ='" +QString::number( valor_venda.toFloat() )   + "'"
                    ",a002_qtde_estoque  ='" +QString::number( qtde_estoque.toInt() )    + "'"
                    ",a002_posicao_peca  ='" +posicao_peca                               + "'"
                  "WHERE "
                    "a002_codigo ='" +id+ "'");

    if( query.exec() ) //executa a query
    {
        //pega a linha que está selecionada
        int linha = ui->tw_ge_listapecas->currentRow();

        //atualizando o table widget com o novo registro
        ui->tw_ge_listapecas->item(linha, 3)->setText( nc_peca );
        ui->tw_ge_listapecas->item(linha, 4)->setText( denominacao );
        ui->tw_ge_listapecas->item(linha, 5)->setText( grupo );
        ui->tw_ge_listapecas->item(linha, 6)->setText( valor_compra );
        ui->tw_ge_listapecas->item(linha, 7)->setText( valor_venda );
        ui->tw_ge_listapecas->item(linha, 8)->setText( qtde_estoque );
        ui->tw_ge_listapecas->item(linha, 9)->setText( posicao_peca );

        QMessageBox::information(this, "Atualizado", "Dados da peça atualizados com sucesso!");

        ui->txt_ge_codigopeca->clear();
        ui->txt_ge_ncPeca->clear();
        ui->txt_ge_denominacao->clear();
        ui->txt_ge_grupo->clear();
        ui->txt_ge_valorcompra->clear();
        ui->txt_ge_valorvenda->clear();
        ui->txt_ge_qtde->clear();
        ui->txt_ge_posicao->clear();
        ui->txt_ge_ncPeca->setFocus();
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar dados da peça");
    }
}

//excluir peça selecionada
void frm_gestaoesotque::on_btn_ge_excluir_clicked()
{
    if( ui->tw_ge_listapecas->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione uma peça");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão da peça?"
                                      ,QMessageBox::Yes|QMessageBox::No);

    if( opc == QMessageBox::Yes )
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_ge_listapecas->currentRow();
        QString id = ui->tw_ge_listapecas->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a002_estoque "
                      "SET "
                        "a002_ativo = false "
                      "WHERE "
                        "a002_codigo ='" +id+ "'");

        if( query.exec() ) //executa a query
        {
            ui->tw_ge_listapecas->removeRow( linha );
            QMessageBox::information(this, "DELETADO", "Peça excluído com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir peça");
        }
    }
}

//**FUNÇÕES**
