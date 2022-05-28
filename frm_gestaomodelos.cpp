#include "frm_gestaomodelos.h"
#include "ui_frm_gestaomodelos.h"

frm_modelos::frm_modelos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_modelos)
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

    //combo box marcas
    ui->cb_nv_filtrar->addItem("-");
    ui->cb_nv_filtrar->addItem("Marca");
    ui->txt_nv_marca->setFocus();
    ui->txt_nv_marca->setFocus();

    //combo box gestão modelos
    ui->cb_ge_filtrar->addItem("-");
    ui->cb_ge_filtrar->addItem("Marca");
    ui->cb_ge_filtrar->addItem("Modelo");
    ui->txt_ge_marca->setFocus();
    ui->txt_ge_marca->setFocus();

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //**Estilizando layout da table widget LISTAMARCAS**
    //definindo o tamanho das colunas
    ui->tw_listamarcas->setColumnCount(2);
    ui->tw_listamarcas->setColumnWidth(0, 100);
    ui->tw_listamarcas->setColumnWidth(1, 255);

    //cabeçalhos do table widget
    QStringList cabecalho1={"Código", "Marca"};
    ui->tw_listamarcas->setHorizontalHeaderLabels( cabecalho1 );
    //definindo cor da linha ao ser selecionada
    ui->tw_listamarcas->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listamarcas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listamarcas->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listamarcas->verticalHeader()->setVisible(false);


    //**Estilizando layout da table widget LISTAMODELOS**
    //definindo o tamanho das colunas
    ui->tw_listamodelos->setColumnCount(3);
    ui->tw_listamodelos->setColumnWidth(0, 100);
    ui->tw_listamodelos->setColumnWidth(1, 150);
    ui->tw_listamodelos->setColumnWidth(2, 150);

    //cabeçalhos do table widget
    QStringList cabecalho2={"Código", "Marca", "Modelo"};
    ui->tw_listamodelos->setHorizontalHeaderLabels( cabecalho2 );
    //definindo cor da linha ao ser selecionada
    ui->tw_listamodelos->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listamodelos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listamodelos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listamodelos->verticalHeader()->setVisible(false);

    //**listando MARCAS**
    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_listamarcas );
    //inserir linhas dentro do table widget
    int contlinhas=0;
    //Remover os produtos do table widget
    QSqlQuery query; //query para listar os colaboradores no table widget
    query.prepare("SELECT "
                      "a011_codigo        "
                      ",a011_marca_nome   "
                  "FROM "
                      "a011_marcas "
                  "WHERE "
                      "a011_ativo = true");

    if( query.exec() ) //verifica se ouve algum erro na execução da query
    {
        //enquanto a query tiver retornando next, insere linhas dentro do table widget
        while( query.next() )
        {
            //inserindo com contador de linhas, por index
            ui->tw_listamarcas->insertRow(contlinhas);
            ui->tw_listamarcas->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_listamarcas->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            //definindo o tamanho das linhas
            ui->tw_listamarcas->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar marcas");
    }

}

frm_modelos::~frm_modelos()
{
    con.fechar();
    delete ui;
}

//quando trocar de aba
void frm_modelos::on_tabWidget_currentChanged(int index)
{
    if( index == 0 ) //verifica a interface pelo index das tabs
    {
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_listamarcas );
        //inserir linhas dentro do table widget
        int contlinhas=0;
        //Remover os produtos do table widget
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a011_codigo        "
                          ",a011_marca_nome   "
                      "FROM "
                          "a011_marcas "
                      "WHERE "
                          "a011_ativo = true");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_listamarcas->insertRow(contlinhas);
                ui->tw_listamarcas->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_listamarcas->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                //definindo o tamanho das linhas
                ui->tw_listamarcas->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar marcas");
        }
    }
    else if( index == 1 )
    {
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_listamodelos );
        //inserir linhas dentro do table widget
        int contlinhas=0;
        //Remover os produtos do table widget
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a012_codigo          "
                          "a011_marca_nome      "
                          ",a012_nome_veiculo   "
                      "FROM "
                          "a012_modelos "
                          "JOIN a011_marcas ON ( a011_codigo = a012_fk_codigo_marca) "
                      "WHERE "
                          "a012_ativo = true "
                      "ORDER BY "
                          "a012_codigo ASC");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_listamodelos->insertRow(contlinhas);
                ui->tw_listamodelos->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_listamodelos->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_listamodelos->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                //definindo o tamanho das linhas
                ui->tw_listamodelos->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar modelos");
        }
    }
}

//pega TW marcas
void frm_modelos::on_tw_listamarcas_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_listamarcas->item(ui->tw_listamarcas->currentRow()
                                        , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                    "* "
                  "FROM "
                    "a011_marcas "
                  "WHERE "
                    "a011_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() )
    {
        query.first(); //pega o primeiro
        g_codigo_marca = query.value(0).toString();
        ui->txt_nv_marca->setText(query.value(1).toString());
    }
    else
    {
        qDebug() << "Não foi possível selecionar dado";
    }
}

//filtrar marcas
void frm_modelos::on_txt_nv_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_nv_filtrar->currentText();
    QString txt_filtro = ui->txt_nv_filtrar->text().toUpper();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Marca";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_listamarcas );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_nv_filtrar->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a011_codigo        "
                        ",a011_marca_nome   "
                    "FROM "
                        "a011_marcas "
                    "WHERE "
                        "a011_ativo = true";
        }
        else
        {
            busca = "SELECT "
                        "a011_codigo        "
                        ",a011_marca_nome   "
                    "FROM "
                        "a011_marcas "
                    "WHERE "
                        "a011_ativo = true";
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
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a011_codigo        "
                    ",a011_marca_nome   "
                "FROM "
                    "a011_marcas "
                "WHERE "
                    + filtro_sql +
                    "AND a011_ativo = true ";
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
            ui->tw_listamarcas->insertRow( contlinhas );
            ui->tw_listamarcas->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_listamarcas->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            //definindo o tamanho das linhas
            ui->tw_listamarcas->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar marcas");
    }

    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//btn filtrar marcas
void frm_modelos::on_btn_nv_filtrar_clicked()
{
    frm_modelos::on_txt_nv_filtrar_returnPressed();
}

//novo modelo
void frm_modelos::on_btn_nv_novo_clicked()
{
    ui->txt_ge_modelo->clear();
    ui->txt_ge_modelo->setFocus();
}

//salvar modelo
void frm_modelos::on_btn_nv_salvar_clicked()
{
    int incrementaCodigo = 0;

    QSqlQuery query;

    query.prepare("SELECT "
                    "* "
                  "FROM "
                    "a012_modelos "
                  "ORDER BY "
                    "a012_codigo DESC LIMIT 1 ");

    if( query.exec() ) //verifica se ouve algum erro na execução da query
    {
        //enquanto a query tiver retornando next, insere linhas dentro do table widget
        while( query.next() )
        {
            incrementaCodigo = query.value(0).toInt() + 1;
        }
    }
    else
    {
        qDebug() << "__Erro ao pegar codigo do modelo";
    }

    QString codigoDesc = QString::number( incrementaCodigo );
    QString modelo = ui->txt_nv_modelo->text().toUpper();

    //inserindo a marca
    query.prepare("INSERT INTO "
                    "a012_modelos(a012_codigo, a012_nome_veiculo, a012_fk_codigo_marca) "
                  "VALUES('" +codigoDesc+ "', '" +modelo+ "', '" +g_codigo_marca+ "') ");

    if( !query.exec() )
    {
        QMessageBox::information(this, "ERRO", "Não foi possível salvar dados do modelo");
    }
    else
    {
        ui->txt_nv_marca->clear();
        ui->txt_nv_modelo->clear();
        ui->txt_nv_marca->setFocus();
        QMessageBox::information(this, "AVISO", "Novo modelo cadastrada com sucesso");
    }
}

//pega TW modelos
void frm_modelos::on_tw_listamodelos_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_listamodelos->item(ui->tw_listamodelos->currentRow()
                                        , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                    "a011_marca_nome "
                    "a012_nome_veiculo "
                  "FROM "
                    "a012_modelos "
                    "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca)"
                  "WHERE "
                    "a012_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() )
    {
        query.first(); //pega o primeiro
        ui->txt_ge_marca->setText(query.value(0).toString());
        ui->txt_ge_modelo->setText(query.value(1).toString());
    }
    else
    {
        qDebug() << "Não foi possível selecionar dado";
    }
}

//filtrar marcas/modelos
void frm_modelos::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text().toUpper();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Marca" << "Modelo";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_listamodelos );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_ge_filtrar->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a012_codigo        "
                        ",a011_marca_nome   "
                        ",a012_nome_veiculo "
                    "FROM "
                        "a012_modelos "
                        "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                    "WHERE "
                        "a012_ativo = true";
        }
        else
        {
            busca = "SELECT "
                        "a012_codigo        "
                        ",a011_marca_nome   "
                        ",a012_nome_veiculo "
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
                //Marca
            case 1:

                filtro_sql = "a012_nome_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a012_codigo        "
                    ",a011_marca_nome   "
                    ",a012_nome_veiculo "
                "FROM "
                    "a012_modelos "
                    "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                "WHERE "
                    + filtro_sql +
                    "AND a012_ativo = true ";
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
            ui->tw_listamodelos->insertRow( contlinhas );
            ui->tw_listamodelos->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_listamodelos->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_listamodelos->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));
            //definindo o tamanho das linhas
            ui->tw_listamodelos->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar marcas/modelos");
    }

    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//btn filtrar marcas/modelos
void frm_modelos::on_btn_ge_filtrar_clicked()
{
    frm_modelos::on_txt_ge_filtrar_returnPressed();
}

//salvar editar, modelos
void frm_modelos::on_btn_ge_salvar_clicked()
{
    if( ui->tw_listamodelos->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um modelo");
        return;
    }

    QString id = ui->tw_listamodelos->item(ui->tw_listamodelos->currentRow()
                                              ,0)->text();
    QSqlQuery query;

    QString modelo = ui->txt_ge_modelo->text();

    query.prepare("UPDATE "
                    "a012_modelos "
                  "SET "
                    "a012_nome_veiculo ='" +modelo+ "' "
                  "WHERE "
                    "a012_codigo ='" +id+ "'");

    if( query.exec() ) //executa a query
    {
        //pega a linha que está selecionada
        int linha=ui->tw_listamodelos->currentRow();
        //atualizando o table widget com o novo registro
        ui->tw_listamodelos->item(linha, 1)->setText( modelo );

        QMessageBox::information(this, "Atualizado", "Modelo veículo atualizado com sucesso!");
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar modelo veículo");
    }
}

//btn excluir modelo
void frm_modelos::on_btn_ge_excluir_clicked()
{
    if( ui->tw_listamodelos->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um modelo");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão do modelo?"
                                      ,QMessageBox::Yes|QMessageBox::No);

    if( opc == QMessageBox::Yes )
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_listamodelos->currentRow();
        QString id = ui->tw_listamodelos->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a012_modelos "
                      "SET "
                        "a012_ativo = false "
                      "WHERE "
                        "a012_codigo ='" +id+ "'");

        if( query.exec() )
        {
            ui->tw_listamodelos->removeRow( linha );
            QMessageBox::information(this, "DELETADO", "Modelo excluída com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir modelo");
        }
    }
}

