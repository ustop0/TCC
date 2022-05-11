#include "frm_novavenda.h"
#include "ui_frm_novavenda.h"

frm_novavenda::frm_novavenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_novavenda)
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

    ui->txt_vd_filtrar->setFocus();

    //configurando combo box peças
    ui->cb_vd_filtrar->addItem("-");
    ui->cb_vd_filtrar->addItem("Nc. Peça");
    ui->cb_vd_filtrar->addItem("Denominação");
    ui->cb_vd_filtrar->addItem("Grupo");
    ui->cb_vd_filtrar->addItem("Posição");
    ui->cb_vd_filtrar->addItem("Fornecedor");
    ui->cb_vd_filtrar->addItem("Modelo");

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_listapecas->setColumnCount(10);
    ui->tw_listapecas->setColumnWidth(0, 40);
    ui->tw_listapecas->setColumnWidth(1, 220);

    //cabeçalhos do table widget
    QStringList cabecalho={"Código", "Fornecedor", "Modelo", "Nc. Peça"
                            , "Denominação", "Grupo", "Valor Compra"
                            , "Valor Venda", "Qtde", "Posição"};

    ui->tw_listapecas->setHorizontalHeaderLabels( cabecalho );
    //definindo cor da linha ao ser selecionada
    ui->tw_listapecas->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listapecas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listapecas->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listapecas->verticalHeader()->setVisible(false);

    //Carregando as peças
    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_listapecas );
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
            ui->tw_listapecas->insertRow( contlinhas );
            ui->tw_listapecas->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 10
                                        , new QTableWidgetItem(query.value(10).toString()));

            //definindo o tamanho das linhas
            ui->tw_listapecas->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }

} //**Fim construtor

frm_novavenda::~frm_novavenda()//**Inicio destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//pega linha do tw peças
void frm_novavenda::on_tw_listapecas_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_listapecas->item(ui->tw_listapecas->currentRow()
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
        ui->txt_codigopeca->setText(query.value(0).toString());
        ui->txt_qtdeEstoque->setText(query.value(8).toString());
    }
}

//filtrando peças
void frm_novavenda::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_vd_filtrar->currentText();
    QString txt_filtro = ui->txt_vd_filtrar->text();

    QString busca;
    QString filtro_sql;

    //Dados do combo box
    QStringList cb_opc;
    cb_opc << "Nc. Peça" << "Denominação" << "Grupo"
           << "Posição"  << "Fornecedor"  << "Modelo";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_listapecas );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_vd_filtrar->text() == "" )
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
                        "a002_ativo = true "
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
                        "a002_ativo = true "
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
            ui->tw_listapecas->insertRow( contlinhas );
            ui->tw_listapecas->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            ui->tw_listapecas->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));


            //definindo o tamanho das linhas
            ui->tw_listapecas->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar peças");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_vd_filtrar->clear();
    ui->txt_vd_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//botao filtrar peças
void frm_novavenda::on_btn_pesquisarproduto_clicked()
{
    frm_novavenda::on_txt_ge_filtrar_returnPressed();
}

