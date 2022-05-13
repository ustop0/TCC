#include "frm_novavenda.h"
#include "ui_frm_novavenda.h"

QString frm_novavenda::g_codigo_peca;
QString frm_novavenda::g_denominacao;
QString frm_novavenda::g_qtde;
QString frm_novavenda::g_valor_unitario;
QString frm_novavenda::g_valor_total;
QString frm_novavenda::g_valor_comprado;
QString frm_novavenda::g_margem_lucro;

//variável global, verifica se um produto foi alterado
bool g_alterou;

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

    //**Estilizando layout da tw_listapecas**
    //definindo o tamanho das colunas
    ui->tw_listapecas->setColumnCount(10);
    ui->tw_listapecas->setColumnWidth(0, 40);
    ui->tw_listapecas->setColumnWidth(1, 220);

    //cabeçalhos do table widget, seleção de peças
    QStringList cabecalho1={"Código", "Fornecedor", "Modelo", "Nc. Peça"
                            , "Denominação", "Grupo", "Valor Compra"
                            , "Valor Venda", "Qtde", "Posição"};

    ui->tw_listapecas->setHorizontalHeaderLabels( cabecalho1 );
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
    int contlinhas1 = 0;
    //Remover os produtos do table widget
    QSqlQuery query1; //query para listar os colaboradores no table widget
    query1.prepare("SELECT "
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

    if( query1.exec() ) //verifica se ouve algum erro na execução da query
    {
        //enquanto a query tiver retornando next, insere linhas dentro do table widget
        while( query1.next() )
        {
            //inserindo com contador de linhas, por index
            ui->tw_listapecas->insertRow( contlinhas1 );
            ui->tw_listapecas->setItem(contlinhas1
                                        , 0
                                        , new QTableWidgetItem(query1.value(0).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 1
                                        , new QTableWidgetItem(query1.value(1).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 2
                                        , new QTableWidgetItem(query1.value(2).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 3
                                        , new QTableWidgetItem(query1.value(3).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 4
                                        , new QTableWidgetItem(query1.value(4).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 5
                                        , new QTableWidgetItem(query1.value(5).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 6
                                        , new QTableWidgetItem(query1.value(6).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 7
                                        , new QTableWidgetItem(query1.value(7).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 8
                                        , new QTableWidgetItem(query1.value(8).toString()));

            ui->tw_listapecas->setItem(contlinhas1
                                        , 9
                                        , new QTableWidgetItem(query1.value(9).toString()));

            //definindo o tamanho das linhas
            ui->tw_listapecas->setRowHeight(contlinhas1, 20);
            contlinhas1 ++;
        }
    }


    //**Estilizando layout da tw_listaprodutos**
    //definindo o tamanho das colunas
    ui->tw_listaprodutos->setColumnCount(6);
    ui->tw_listaprodutos->setColumnWidth(0, 40);
    ui->tw_listaprodutos->setColumnWidth(1, 220);

    //cabeçalhos do table widget, itens venda
    QStringList cabecalho2 = {"Código", "Produto", "Valor Un.", "Qtde", "Total", "Lucro"};

    ui->tw_listaprodutos->setHorizontalHeaderLabels( cabecalho2 );
    //definindo cor da linha ao ser selecionada
    ui->tw_listaprodutos->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listaprodutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listaprodutos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listaprodutos->verticalHeader()->setVisible(false);

    ui->txt_vd_filtrar->setFocus();

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
                      ",a002_denomicanao  "
                      ",cast(cast(a002_valor_compra  as decimal) as varchar) "
                      ",cast(cast(a002_valor_venda  as decimal) as varchar) "
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
        ui->txt_qtdeEstoque->setText(query.value(4).toString());

        g_codigo_peca = ui->txt_codigopeca->text();
        g_qtde = ui->txt_qtdeEstoque->text();

        g_denominacao = query.value(1).toString();
        g_valor_unitario = query.value(3).toString();
        g_valor_comprado = query.value(2).toString();

        //g_valor_total;
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

//adicionar produto a lista
void frm_novavenda::on_btn_adicionarItem_clicked()
{
    int contlinhas = 0;
    double valor_total;
    double margem_lucro;
    QString qtde_venda;
    QString qtde_estoque = g_qtde;

//    g_codigo_peca;
//    g_qtde;
//    g_denominacao;
//    g_valor_unitario;
//    g_valor_total;
//    QStringList cabecalho2 = {"Código", "Produto", "Valor Un.", "Qtde", "Total", "Lucro"};

    //verifica se a quantidade informada é maior que a quantidade em estoque
    if( ui->txt_qtde->text() > qtde_estoque )
    {
        QMessageBox::information(this
                                 ,"Aviso"
                                 ,"Valor informado para o produto"
                                  " acima do valor do estoque para esse produto");

        ui->txt_qtde->setText("1");
        ui->txt_qtde->setFocus();
    }
    else if( ui->txt_qtde->text() == "" ||  ui->txt_qtde->text() == "0" )
    {
        QMessageBox::information(this
                                 ,"Aviso"
                                 ,"Não foi informado nenhum valor para a quantidade do produto");

        ui->txt_qtde->setText("1");
        ui->txt_qtde->setFocus();
    }
    else
    {
        qtde_venda = ui->txt_qtde->text();

        //calculando o valor total do produto(quantidade * valor_venda)
        valor_total = ui->txt_qtde->text().toDouble() * g_valor_unitario.toDouble();
        margem_lucro = valor_total - g_valor_comprado.toDouble();

        //se valor da query for vazio, produto não encontrado
        if( g_codigo_peca != "")
        {
            //inserindo com contador de linhas, por index
            ui->tw_listaprodutos->insertRow( contlinhas );
            ui->tw_listaprodutos->setItem(contlinhas
                                          , 0
                                          , new QTableWidgetItem( g_codigo_peca ));

            ui->tw_listaprodutos->setItem(contlinhas
                                          , 1
                                          , new QTableWidgetItem( g_denominacao ));

            ui->tw_listaprodutos->setItem(contlinhas
                                          , 2
                                          , new QTableWidgetItem( g_valor_unitario ));

            //qtde produtos
            ui->tw_listaprodutos->setItem(contlinhas
                                          , 3
                                          , new QTableWidgetItem( qtde_venda ));

            ui->tw_listaprodutos->setItem(contlinhas
                                          , 4
                                          , new QTableWidgetItem( QString::number(valor_total) ));

            ui->tw_listaprodutos->setItem(contlinhas
                                          , 5
                                          , new QTableWidgetItem( QString::number(margem_lucro) ));

            ui->tw_listaprodutos->setRowHeight(contlinhas, 20);
            contlinhas ++;

             //**DEBUGAR**, o não está retornando um numero em DOUBLE, manipular string
            //Label que exibe o valor total de todos os produtos(debugar)
            ui->lb_totalvenda->setText("R$ "+QString::number(
                                           calculaTotal(ui->tw_listaprodutos, 4))+",00");

            ui->lb_totallucro->setText("R$ "+QString::number(
                                           calculaTotal(ui->tw_listaprodutos, 5))+",00");

            resetaCampos();

            //atualiza a quantidade de produtos da tabela estoque(sem UPDATE)
             int atualiza_qtde;
             atualiza_qtde = qtde_estoque.toInt() - qtde_venda.toInt();

             //adiciona ao valor da qtde
             g_qtde = QString::number( atualiza_qtde );
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao inserir o produto na lista");
        }
    }
}

//excluir o produto da lista de itens
void frm_novavenda::on_btn_excluirproduto_clicked()
{
    if( ui->tw_listaprodutos->currentColumn() != -1 )
    {
        QMessageBox::StandardButton opc =QMessageBox::question(this
                                                               ,"Exclusão?"
                                                               ,"Confirma exclusão do produto"
                                                               ,QMessageBox::Yes|QMessageBox::No);

        if( opc == QMessageBox::Yes )
        {
            //**REVISAR ESSA FUNÇÃO
            int contlinhas = 0;

            //removendo o produto selecionado e recalculando o total da venda
            ui->tw_listaprodutos->removeRow( ui->tw_listaprodutos->currentRow() );
            ui->lb_totalvenda->setText("R$ "
                                       +QString::number(
                                                   calculaTotal(ui->tw_listaprodutos, 4))+",00");

            ui->lb_totalvenda->setText("R$ "
                                       +QString::number(
                                                   calculaTotal(ui->tw_listaprodutos, 5))+",00");

            contlinhas--; //excluindo linha depois que o produto é excluido

        }
        else
        {

        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Selecione um produto primeiro");
    }
}

void frm_novavenda::on_btn_finalizarvenda_clicked()
{
    /*
    QSqlQuery query;

    query.prepare("UPDATE "
                    "a002_estoque "
                  "SET "
                    "a002_qtde_estoque = '" +g_qtde+ "' "
                  "WHERE "
                    "a002_codigo = '" +g_codigo_peca+ "' ");


    if( !query.exec() )
    {
        QMessageBox::critical(this, "ERRO", "Erro ao atualizar qtde estoque");
    }
    else
    {
        qDebug() << "Sucesso ao atualizar estoque";
    }
    */

    //gravas as informações na tabela de venda e obter o id da venda
    //verifica se tem produtos no table widget, para realizar uma venda
    if( ui->tw_listaprodutos->rowCount() > 0 )
    {
        int idVenda;

        QString msgFimVenda;
        double total = calculaTotal(ui->tw_listaprodutos, 4);
        QString data = QDate::currentDate().toString("yyyy-MM-dd");
        //QString data=QDate::currentDate().toString("dd/MM/yyyy"); //data venda
        QString hora = QTime::currentTime().toString("hh:mm:ss");

        //inserindo dados da venda na tabela de vendas
        QSqlQuery query;
        query.prepare("INSERT INTO "
                        "a007_vendas(a007_data_venda          "
                                    ",a007_hora_venda         "
                                    ",a007_fk_codigo_usuario  "
                                    ",a007_valor_total)       "
                      "VALUES('"+data                                           + "'"
                            ",'"+hora                                           + "'"
                            ",'"+QString::number( variaveis_globais::id_colab ) + "'"
                            ",'"+QString::number( total )                       + "')");

        if( !query.exec() )
        {
            QMessageBox::warning(this, "ERRO", "Erro ao registrar nova venda");
        }
        else
        {
            //obtém o último registro, query limitada a um registro
            query.prepare("SELECT "
                            "a007_codigo "
                          "FROM "
                            "a007_vendas "
                          "ORDER BY "
                            "a007_codigo DESC LIMIT 1");

            query.exec();
            query.first();

            //obtem o id da venda
            idVenda = query.value(0).toInt();

            msgFimVenda="ID Venda: " +QString::number(idVenda)
                                     +"\nValor total da venda: R$ "
                                     +QString::number(total)+",00";

            //inserindo venda na tabela estoque_vendas
            //leitura da quantidade total de linhas
            int totalLinhas = ui->tw_listaprodutos->rowCount();
            int linha = 0; //linha que está fazendo a leitura

            while( linha < totalLinhas ) //percorre o table widget
            {
                QString denominacao = ui->tw_listaprodutos->item(linha,1)->text();
                QString valor_unitario = ui->tw_listaprodutos->item(linha,2)->text();
                QString qtde_vendida = ui->tw_listaprodutos->item(linha,3)->text();
                QString valor_total = ui->tw_listaprodutos->item(linha,4)->text();
                QString margem_lucro = ui->tw_listaprodutos->item(linha,5)->text();

                //DEPURAR NÃO ESTÁ REGISTRANDO AS VENDAS NA TABELA DE VENDAS
                //verificar querys, valores int normal e varchar em '" "'
                query.prepare("INSERT INTO "
                                "a006_estoque_vendas(a006_codigo          "
                                                     ",a006_denomicanao   "
                                                     ",a006_qtde_vendida  "
                                                     ",valor_un           "
                                                     ",valor_total        "
                                                     ",a006_margem_lucro) "
                              "VALUES('"+QString::number(idVenda)  +"'"
                                    ",'"+denominacao               +"'"
                                    ",'"+qtde_vendida              +"'"
                                    ",'"+valor_unitario            +"'"
                                    ",'"+valor_total               +"'"
                                    ",'"+margem_lucro              +"')");

                query.exec(); //executa o sql
                linha++; //incrementa a variável para a próxima linha
            }

            QMessageBox::information(this, "Venda Concluída", msgFimVenda);
            resetaCampos();

            //remove as linhas do table widget
            funcoes_globais::removerLinhas( ui->tw_listaprodutos );
            ui->lb_totalvenda->setText("R$ 0,00");
            ui->lb_totallucro->setText("R$ 0,00");
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Não existem produtos nessa venda\n"
                                           "Primeiro adicione um produto");
    }
}

/**FUNÇÕES**/
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 13/05/2022                                                                           |
 * Propósito: limpar os campos que indicam o codigo e qtde da peça                            |
 * Chamada:                                                        |
 *--------------------------------------------------------------------------------------------
 */
void frm_novavenda::resetaCampos() //Função para resetar campos
{
    //atualizando o valor total da venda e limpando o campo txt_codproduto
    ui->txt_codigopeca->clear();
    ui->txt_qtde->setText("1"); //volta quantidade para 1 no campo quantidade
    ui->txt_vd_filtrar->setFocus();
}
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 13/05/2022                                                                           |
 * Propósito: calcular o valor total da venda, no TW e no label                               |
 * Chamada:                                                           |
 *--------------------------------------------------------------------------------------------
 */
double frm_novavenda::calculaTotal( QTableWidget *tw, int coluna )
{
    int totallinhas; //recebe o numero de linhas (Row Count)
    double total = 0.0; //somatório

    totallinhas = tw->rowCount();
    for( int i=0; i < totallinhas; i++ )
    {
        total += tw->item(i, coluna)->text().toDouble();
    }
    return total;
}
