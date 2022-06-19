#include "frm_gestaomarcas.h"
#include "ui_frm_gestaomarcas.h"

frm_gestaomarcas::frm_gestaomarcas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaomarcas)
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
    ui->txt_nv_marca->setFocus();
    ui->txt_ge_marca->setFocus();

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_listamarcas->setColumnCount(2);
    ui->tw_listamarcas->setColumnWidth(0, 100);
    ui->tw_listamarcas->setColumnWidth(1, 255);

    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Marca"};
    ui->tw_listamarcas->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_listamarcas->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listamarcas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listamarcas->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listamarcas->verticalHeader()->setVisible(false);

}

frm_gestaomarcas::~frm_gestaomarcas()
{
    con.fechar();
    delete ui;
}

void frm_gestaomarcas::on_btn_nv_novo_clicked()
{
    ui->txt_nv_marca->clear();
    ui->txt_nv_marca->setFocus();
}

//btn salvar marca
void frm_gestaomarcas::on_btn_nv_salvar_clicked()
{
    int incrementaCodigo = 0;

    QSqlQuery query;

    query.prepare("SELECT "
                    "* "
                  "FROM "
                    "a011_marcas "
                  "ORDER BY "
                    "a011_codigo DESC LIMIT 1 ");

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
        qDebug() << "__Erro ao pegar codigo da marca";
    }

    QString codigoDesc = QString::number( incrementaCodigo );

    QString marca = ui->txt_nv_marca->text().toUpper();
    //inserindo a marca
    query.prepare("INSERT INTO "
                    "a011_marcas(a011_codigo, a011_marca_nome) "
                  "VALUES('" +codigoDesc+ "', '" +marca+ "') ");

    if( !query.exec() )
    {
        QMessageBox::information(this, "ERRO", "Não foi possível salvar dados da marca");
    }
    else
    {
        ui->txt_nv_marca->clear();
        ui->txt_nv_marca->setFocus();
        QMessageBox::information(this, "AVISO", "Nova marca cadastrada com sucesso");
    }
}

//quando ocorrer mudança de aba
void frm_gestaomarcas::on_tabWidget_currentChanged(int index)
{
    if( index == 1 ) //verifica a interface pelo index das tabs
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
}

//pegar dados TW
void frm_gestaomarcas::on_tw_listamarcas_itemSelectionChanged()
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
        ui->txt_ge_marca->setText(query.value(1).toString());
    }
    else
    {
        qDebug() << "Não foi possível selecionar dado";
    }
}

//filtrar registros
void frm_gestaomarcas::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text().toUpper();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Marca";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_listamarcas );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_ge_filtrar->text() == "" )
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

//btn filtrar
void frm_gestaomarcas::on_btn_ge_filtrar_clicked()
{
    frm_gestaomarcas::on_txt_ge_filtrar_returnPressed();
}

//btn salvar alterações marca
void frm_gestaomarcas::on_btn_ge_salvar_clicked()
{
    if( ui->tw_listamarcas->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione uma marca");
        return;
    }

    QString id = ui->tw_listamarcas->item(ui->tw_listamarcas->currentRow()
                                              ,0)->text();
    QSqlQuery query;

    QString marca = ui->txt_ge_marca->text();

    query.prepare("UPDATE "
                    "a011_marcas "
                  "SET "
                    "a011_marca_nome    ='" +marca    + "' "
                  "WHERE "
                    "a011_codigo ='" +id+ "'");

    if( query.exec() ) //executa a query
    {
        //pega a linha que está selecionada
        int linha=ui->tw_listamarcas->currentRow();
        //atualizando o table widget com o novo registro
        ui->tw_listamarcas->item(linha, 1)->setText( marca );

        QMessageBox::information(this, "Atualizado", "Marca veículo atualizado com sucesso!");
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar marca veículo");
    }
}

//btn excluir marca
void frm_gestaomarcas::on_btn_ge_excluir_clicked()
{
    if( ui->tw_listamarcas->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione uma marca");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão da marca?"
                                      ,QMessageBox::Yes|QMessageBox::No); //revisar tabulação

    if( opc == QMessageBox::Yes ) //verificando o botao da caixa question
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_listamarcas->currentRow();
        QString id = ui->tw_listamarcas->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a011_marcas "
                      "SET "
                        "a011_ativo = false "
                      "WHERE "
                        "a011_codigo ='" +id+ "'");

        if( query.exec() ) //executa a query
        {
            ui->tw_listamarcas->removeRow( linha );
            QMessageBox::information(this, "EXCLUÍDO", "Marca excluída com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir marca");
        }
    }
}

