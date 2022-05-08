#include "frm_gestaoveiculos.h"
#include "ui_frm_gestaoveiculos.h"

frm_gestaoveiculos::frm_gestaoveiculos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaoveiculos)
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

    ui->cb_ge_filtrar->addItem("-");
    ui->cb_ge_filtrar->addItem("Marca");
    ui->cb_ge_filtrar->addItem("Modelo");
    ui->txt_nv_marca->setFocus();
    ui->txt_ge_marca->setFocus();

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_ge_listaveiculos->setColumnCount(3); //define que o table widget terá duas colunas
    ui->tw_ge_listaveiculos->setColumnWidth(0, 150); //id colaborador
    ui->tw_ge_listaveiculos->setColumnWidth(1, 220); //nome colaborador

    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Marca", "Modelo"};
    ui->tw_ge_listaveiculos->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_listaveiculos->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_listaveiculos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_listaveiculos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_listaveiculos->verticalHeader()->setVisible(false);
}

frm_gestaoveiculos::~frm_gestaoveiculos()//**INICIO** destrutor
{
    delete ui;
}

//novo veiculo
void frm_gestaoveiculos::on_btn_nv_novo_clicked()
{
    ui->txt_nv_marca->clear();
    ui->txt_ge_modelo->clear();
}

//salvar veiculo
void frm_gestaoveiculos::on_btn_nv_salvar_clicked()
{
    QString marca = ui->txt_nv_marca->text();
    QString modelo = ui->txt_nv_modelo->text();

    QSqlQuery query;

    //inserindo a marca
    query.prepare("INSERT INTO "
                    "a011_marcas(a011_marca_nome) "
                  "VALUES('" +marca+ "') ");

    query.exec();

    //pegando chave primaria da marca
    query.prepare("SELECT "
                    "a011_codigo "
                  "FROM "
                    "a011_marcas "
                  "WHERE "
                    "a011_marca_nome = '" +marca+ "'");

    query.exec();

    QString codigo_marca = query.value(0).toString();

    qDebug() << "Marca: " << marca;
    qDebug() << "Modelo: " << modelo;
    qDebug() << "Codigo Marca: " << codigo_marca;

    if( codigo_marca != "" )
    {
        //inserindo modelo
        query.prepare("INSERT INTO "
                        "a012_modelos(a012_nome_veiculo"
                                    ",a012_fk_codigo_marca) "
                      "VALUES('" +modelo      + "' "
                             "'" +codigo_marca+ "'");

        //verifica se a query tem algum erro e executa ela
        if( !query.exec() )
        {
            QMessageBox::critical(this, "ERRO", "Não foi possível salvar o veiculo");
        }
        else
        {
            QMessageBox::information(this, "Salvo", "Veiculo salvo com sucesso");

            ui->txt_nv_marca->clear();
            ui->txt_ge_modelo->clear();
        }
    }
}

//quando ocorrer mudança de aba
void frm_gestaoveiculos::on_tabWidget_currentChanged(int index)
{
    if( index == 1 ) //verifica a interface pelo index das tabs
    {
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_ge_listaveiculos );
        //inserir linhas dentro do table widget
        int contlinhas=0;
        //Remover os produtos do table widget
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a012_codigo        "
                          ",a011_marca_nome   "
                          ",a012_nome_veiculo "
                      "FROM "
                          "a012_modelos "
                          "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                      "WHERE "
                          "a012_ativo = true");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_ge_listaveiculos->insertRow(contlinhas);
                ui->tw_ge_listaveiculos->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_ge_listaveiculos->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_ge_listaveiculos->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                //definindo o tamanho das linhas
                ui->tw_ge_listaveiculos->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar veículos");
        }
    }
}

//mostrar dados da seleção
void frm_gestaoveiculos::on_tw_ge_listaveiculos_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_ge_listaveiculos->item(ui->tw_ge_listaveiculos->currentRow()
                                        , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                    "* "
                  "FROM "
                    "a012_modelos "
                    "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                  "WHERE "
                    "a012_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro
        ui->txt_ge_marca->setText(query.value(1).toString()); //valor 0 é do id
        ui->txt_ge_modelo->setText(query.value(2).toString());
    }
}

//filtrar registros
void frm_gestaoveiculos::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Marca" << "Modelo";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_ge_listaveiculos );

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
            //Modelo
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
            ui->tw_ge_listaveiculos->insertRow( contlinhas );
            ui->tw_ge_listaveiculos->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_ge_listaveiculos->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_ge_listaveiculos->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            //definindo o tamanho das linhas
            ui->tw_ge_listaveiculos->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar Veiculos");
    }

    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}


void frm_gestaoveiculos::on_btn_ge_filtrar_clicked()
{
    frm_gestaoveiculos::on_txt_ge_filtrar_returnPressed();
}

//salvar alterações na marca/veiculo
void frm_gestaoveiculos::on_btn_ge_salvar_clicked()
{
    //**DESENVOLVENDO** a chave estrangeira tem sido um grande problema
    if( ui->tw_ge_listaveiculos->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um usuário");
        return;
    }

    QString id = ui->tw_ge_listaveiculos->item(ui->tw_ge_listaveiculos->currentRow()
                                              ,0)->text();
    QSqlQuery query;

    QString marca = ui->txt_ge_marca->text();
    QString modelo = ui->txt_ge_marca->text();

    query.prepare("UPDATE "
                    "a011_marcas "
                  "SET "
                    "a011_marca_nome    ='" +marca    + "' "
                  "WHERE "
                    "a011_codigo ='" +id+ "'");

    if( query.exec() ) //executa a query
    {
        //pega a linha que está selecionada
        int linha=ui->tw_ge_listaveiculos->currentRow();
        //atualizando o table widget com o novo registro
        ui->tw_ge_listaveiculos->item(linha, 1)->setText( marca );
        ui->tw_ge_listaveiculos->item(linha, 2)->setText( modelo );

        QMessageBox::information(this, "Atualizado", "Marca veículo atualizado com sucesso!");
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar marca veículo");
    }
}

//excluir marca veiculo
void frm_gestaoveiculos::on_btn_ge_excluir_clicked()
{
    if( ui->tw_ge_listaveiculos->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um veiculo");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão do veiculo?"
                                      ,QMessageBox::Yes|QMessageBox::No); //revisar tabulação

    if( opc == QMessageBox::Yes ) //verificando o botao da caixa question
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_ge_listaveiculos->currentRow();
        QString id = ui->tw_ge_listaveiculos->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a011_marcas "
                      "SET "
                        "a011_ativo = false "
                      "WHERE "
                        "a011_codigo ='" +id+ "'");

        if( query.exec() ) //executa a query
        {
            ui->tw_ge_listaveiculos->removeRow( linha );
            QMessageBox::information(this, "DELETADO", "Veículo excluído com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir veículo");
        }
    }
}

