#include "frm_gestaofornecedores.h"
#include "ui_frm_gestaofornecedores.h"
#include "Classes/clfornecedor.h"

frm_gestaofornecedores::frm_gestaofornecedores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaofornecedores)
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

    ui->btn_validacnpj->setVisible(false); //or true - later in the code
    ui->txt_nv_cnpj->setFocus();

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //configurando combo box
    ui->cb_ge_filtrar->addItem("-");
    ui->cb_ge_filtrar->addItem("Razão Social");
    ui->cb_ge_filtrar->addItem("Nome Fantasia");
    ui->cb_ge_filtrar->addItem("CNPJ");
    ui->cb_ge_filtrar->addItem("Ocupação da empresa");
    ui->cb_ge_filtrar->addItem("Cidade");

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_ge_listarFornecedores->setColumnCount(13); //define que o table widget terá duas colunas
    ui->tw_ge_listarFornecedores->setColumnWidth(0, 150); //id colaborador
    ui->tw_ge_listarFornecedores->setColumnWidth(1, 220); //nome colaborador7

    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Razão Social", "Nome Fantasia", "CNPJ","Estado"
                           ,"Cidade", "Rua", "Bairro", "Numero", "Porte"
                           ,"Ocupação", "Telefone1", "Telefone2"};

    ui->tw_ge_listarFornecedores->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_listarFornecedores->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_listarFornecedores->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_listarFornecedores->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_listarFornecedores->verticalHeader()->setVisible(false);

} //**Fim construtor

frm_gestaofornecedores::~frm_gestaofornecedores() //**Inicio destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//novo cliente
void frm_gestaofornecedores::on_btn_nv_novo_clicked()
{
    ui->txt_nv_cnpj->clear();
    ui->txt_nv_uf->clear();
    ui->txt_nv_cidade->clear();
    ui->txt_nv_rua->clear();
    ui->txt_nv_numeroEstabelecimento->clear();
    ui->txt_nv_bairro->clear();
    ui->txt_nv_razaoSocial->clear();
    ui->txt_nv_nomeFantasia->clear();
    ui->txt_nv_porte->clear();
    ui->txt_nv_ocupacao->clear();
    ui->txt_nv_tel1->clear();
    ui->txt_nv_tel2->clear();
    ui->txt_nv_cnpj->setFocus();
}

//salvar clientes
void frm_gestaofornecedores::on_btn_nv_salvar_clicked()
{
    ClFornecedor fornecedor;

    fornecedor.cnpj = ui->txt_nv_cnpj->text(); //armazena o codigo
    fornecedor.estado = ui->txt_nv_uf->text();
    fornecedor.cidade = ui->txt_nv_cidade->text();
    fornecedor.rua = ui->txt_nv_rua->text();
    fornecedor.numero_estabelecimento = ui->txt_nv_numeroEstabelecimento->text();
    fornecedor.bairro = ui->txt_nv_bairro->text();
    fornecedor.razao_social = ui->txt_nv_razaoSocial->text();
    fornecedor.nome_fantasia = ui->txt_nv_nomeFantasia->text();
    fornecedor.porte_empresa = ui->txt_nv_porte->text();
    fornecedor.ocupacao_empresa = ui->txt_nv_ocupacao->text();
    fornecedor.telefone1 = ui->txt_nv_tel1->text();
    fornecedor.telefone2 = ui->txt_nv_tel2->text();

    QSqlQuery query;
    query.prepare("INSERT INTO "
                    "a003_fornecedor(a003_cnpj                     "
                                     ",a003_estado                 "
                                     ",a003_cidade                 "
                                     ",a003_rua                    "
                                     ",a003_numero_estabelecimento "
                                     ",a003_bairro                 "
                                     ",a003_razao_social           "
                                     ",a003_nome_fantasia          "
                                     ",a003_porte                  "
                                     ",a003_ocupacao               "
                                     ",a003_telefone01             "
                                     ",a003_telefone02)            "
                    "VALUES('" +fornecedor.cnpj                     +  "'"
                          ",'" +fornecedor.estado                   +  "'"
                          ",'" +fornecedor.cidade                   +  "'"
                          ",'" +fornecedor.rua                      +  "'"
                          ",'" +fornecedor.numero_estabelecimento   +  "'"
                          ",'" +fornecedor.bairro                   +  "'"
                          ",'" +fornecedor.razao_social             +  "'"
                          ",'" +fornecedor.nome_fantasia            +  "'"
                          ",'" +fornecedor.porte_empresa            +  "'"
                          ",'" +fornecedor.ocupacao_empresa         +  "'"
                          ",'" +fornecedor.telefone1                +  "'"
                          ",'" +fornecedor.telefone2                +  "') ");

    if( !query.exec() ) //verifica se a query tem algum erro e executa ela
    {
        QMessageBox::critical(this, "ERRO", "Erro ao cadastrar fornecedor");
    }
    else
    {
        ui->txt_nv_cnpj->clear();
        ui->txt_nv_uf->clear();
        ui->txt_nv_cidade->clear();
        ui->txt_nv_rua->clear();
        ui->txt_nv_numeroEstabelecimento->clear();
        ui->txt_nv_bairro->clear();
        ui->txt_nv_razaoSocial->clear();
        ui->txt_nv_nomeFantasia->clear();
        ui->txt_nv_porte->clear();
        ui->txt_nv_ocupacao->clear();
        ui->txt_nv_tel1->clear();
        ui->txt_nv_tel2->clear();
        ui->txt_nv_cnpj->setFocus();
    }
}

//validando cnpj
void frm_gestaofornecedores::on_txt_nv_cnpj_returnPressed()
{
    frm_gestaofornecedores::on_btn_validacnpj_clicked();
}

//btn valida cnpj(fica invisivel)
void frm_gestaofornecedores::on_btn_validacnpj_clicked()
{
    validaCNPJ();
}

//quando ocorrer mudança na aba
void frm_gestaofornecedores::on_tabWidget_currentChanged(int index)
{
    if( index == 1 ) //verifica a interface pelo index das tabs
    {
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_ge_listarFornecedores );
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
                ui->tw_ge_listarFornecedores->insertRow( contlinhas );
                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 3
                                            , new QTableWidgetItem(query.value(3).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 4
                                            , new QTableWidgetItem(query.value(4).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 5
                                            , new QTableWidgetItem(query.value(5).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 6
                                            , new QTableWidgetItem(query.value(6).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 7
                                            , new QTableWidgetItem(query.value(7).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 8
                                            , new QTableWidgetItem(query.value(8).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 9
                                            , new QTableWidgetItem(query.value(9).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 10
                                            , new QTableWidgetItem(query.value(10).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 11
                                            , new QTableWidgetItem(query.value(11).toString()));

                ui->tw_ge_listarFornecedores->setItem(contlinhas
                                            , 12
                                            , new QTableWidgetItem(query.value(12).toString()));

                //definindo o tamanho das linhas
                ui->tw_ge_listarFornecedores->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar fornecedores");
        }
    }
}

//pega linha do tw
void frm_gestaofornecedores::on_tw_ge_listarFornecedores_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_ge_listarFornecedores->item(ui->tw_ge_listarFornecedores->currentRow()
                                             , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a003_cnpj                     "
                      ",a003_razao_social            "
                      ",a003_nome_fantasia           "
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
                    "a003_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        //considerar inserir um campo para o código
        ui->txt_ge_cnpj->setText(query.value(0).toString());
        ui->txt_ge_razaoSocial->setText(query.value(1).toString());
        ui->txt_ge_nomeFantasia->setText(query.value(2).toString());
        ui->txt_ge_uf->setText(query.value(3).toString());
        ui->txt_ge_cidade->setText(query.value(4).toString());
        ui->txt_ge_rua->setText(query.value(5).toString());
        ui->txt_ge_numeroEstabelecimento->setText(query.value(6).toString());
        ui->txt_ge_bairro->setText(query.value(7).toString());
        ui->txt_ge_porte->setText(query.value(8).toString());
        ui->txt_ge_ocupacao->setText(query.value(9).toString());
        ui->txt_ge_tel1->setText(query.value(10).toString());
        ui->txt_ge_tel2->setText(query.value(11).toString());
    }
}

//filtrar
void frm_gestaofornecedores::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Razão Social" << "Nome Fantasia" << "CNPJ"
           << "Ocupação da empresa" << "Cidade";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_ge_listarFornecedores );

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
            ui->tw_ge_listarFornecedores->insertRow( contlinhas );
            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 10
                                        , new QTableWidgetItem(query.value(10).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 11
                                        , new QTableWidgetItem(query.value(11).toString()));

            ui->tw_ge_listarFornecedores->setItem(contlinhas
                                        , 12
                                        , new QTableWidgetItem(query.value(12).toString()));

            //definindo o tamanho das linhas
            ui->tw_ge_listarFornecedores->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar Fornecedores");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//botão filtrar
void frm_gestaofornecedores::on_btn_ge_filtrar_clicked()
{
  frm_gestaofornecedores::on_txt_ge_filtrar_returnPressed();
}

//edição, salvar alteração no fornecedor
void frm_gestaofornecedores::on_btn_ge_salvar_clicked()
{
    if( ui->tw_ge_listarFornecedores->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um fornecedor");
        return;
    }

    QString id = ui->tw_ge_listarFornecedores->item(ui->tw_ge_listarFornecedores
                                                    ->currentRow(),0)->text();
    QSqlQuery query;

    //estudar retringir cnpj
    QString razao_social = ui->txt_ge_razaoSocial->text();
    QString nome_fantasia = ui->txt_ge_nomeFantasia->text();
    QString cnpj = ui->txt_ge_cnpj->text();
    //validaCNPJ( cnpj );
    QString estado = ui->txt_ge_uf->text();
    QString cidade = ui->txt_ge_cidade->text();
    QString rua = ui->txt_ge_rua->text();
    QString numero_estabelecimento = ui->txt_ge_numeroEstabelecimento->text();
    QString bairro = ui->txt_ge_bairro->text();
    QString porte_empresa = ui->txt_ge_porte->text();
    QString ocupacao_empresa = ui->txt_ge_ocupacao->text();
    QString telefone1 = ui->txt_ge_tel1->text();
    QString telefone2 = ui->txt_ge_tel2->text();

    //**verificar** está quebrando a o registro quando da update
    query.prepare("UPDATE "
                    "a003_fornecedor "
                  "SET "
                    "a003_razao_social             ='" +razao_social            + "'"
                    ",a003_nome_fantasia           ='" +nome_fantasia           + "'"
                    ",a003_cnpj                    ='" +cnpj                    + "'"
                    ",a003_estado                  ='" +estado                  + "'"
                    ",a003_cidade                  ='" +cidade                  + "'"
                    ",a003_rua                     ='" +rua                     + "'"
                    ",a003_numero_estabelecimento  ='" +numero_estabelecimento  + "'"
                    ",a003_bairro                  ='" +bairro                  + "'"
                    ",a003_porte                   ='" +porte_empresa           + "'"
                    ",a003_ocupacao                ='" +ocupacao_empresa        + "'"
                    ",a003_telefone01              ='" +telefone1               + "'"
                    ",a003_telefone02              ='" +telefone2               + "'"
                  "WHERE "
                    "a003_codigo ='" +id+ "'");

    if( query.exec() ) //executa a query
    {
        //pega a linha que está selecionada
        int linha=ui->tw_ge_listarFornecedores->currentRow();
        //atualizando o table widget com o novo registro
        ui->tw_ge_listarFornecedores->item(linha, 1)->setText( razao_social );
        ui->tw_ge_listarFornecedores->item(linha, 2)->setText( nome_fantasia );
        ui->tw_ge_listarFornecedores->item(linha, 3)->setText( cnpj );
        ui->tw_ge_listarFornecedores->item(linha, 4)->setText( estado );
        ui->tw_ge_listarFornecedores->item(linha, 5)->setText( cidade );
        ui->tw_ge_listarFornecedores->item(linha, 6)->setText( rua );
        ui->tw_ge_listarFornecedores->item(linha, 7)->setText( numero_estabelecimento );
        ui->tw_ge_listarFornecedores->item(linha, 8)->setText( bairro );
        ui->tw_ge_listarFornecedores->item(linha, 9)->setText( porte_empresa );
        ui->tw_ge_listarFornecedores->item(linha, 10)->setText( ocupacao_empresa );
        ui->tw_ge_listarFornecedores->item(linha, 11)->setText( telefone1 );
        ui->tw_ge_listarFornecedores->item(linha, 12)->setText( telefone2 );

        QMessageBox::information(this, "Atualizado", "Fornecedor atualizado com sucesso!");

        ui->txt_nv_razaoSocial->clear();
        ui->txt_nv_nomeFantasia->clear();
        ui->txt_nv_cnpj->clear();
        //validaCNPJ( cnpj );
        ui->txt_nv_uf->clear();
        ui->txt_nv_cidade->clear();
        ui->txt_nv_rua->clear();
        ui->txt_nv_numeroEstabelecimento->clear();
        ui->txt_nv_bairro->clear();
        ui->txt_nv_porte->clear();
        ui->txt_nv_ocupacao->clear();
        ui->txt_nv_tel1->clear();
        ui->txt_nv_tel2->clear();
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar fornecedor");
    }
}

//botão excluir
void frm_gestaofornecedores::on_btn_ge_excluir_clicked()
{
    if( ui->tw_ge_listarFornecedores->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um fornecedor");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão do fornecedor?"
                                      ,QMessageBox::Yes|QMessageBox::No); //revisar tabulação

    if( opc == QMessageBox::Yes ) //verificando o botao da caixa question
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_ge_listarFornecedores->currentRow();
        QString id = ui->tw_ge_listarFornecedores->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a003_fornecedor "
                      "SET "
                        "a003_ativo = false "
                      "WHERE "
                        "a003_codigo ='" +id+ "'");

        if( query.exec() ) //executa a query
        {
            ui->tw_ge_listarFornecedores->removeRow( linha );
            QMessageBox::information(this, "DELETADO", "Fornecedor excluído com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir fornecedor");
        }
    }
}

//**FUNÇÕES**//
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 01/05/2022                                                                           |
 * Propósito: receber o cnpj, e faz a validação via API do BrasilAPI                          |
 * Chamada: botão gravar forncedor                                                            |
 *--------------------------------------------------------------------------------------------
 */
void frm_gestaofornecedores::validaCNPJ()
{
    QString cnpj;

    if( ui->txt_nv_cnpj->text() != "" )
    {
        cnpj = ui->txt_nv_cnpj->text();
    }
    else if ( ui->txt_nv_cnpj->text() == "" )
    {
        cnpj = ui->txt_ge_cnpj->text();
    }

    QEventLoop waitLoop;
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(
                QNetworkRequest( QUrl("https://brasilapi.com.br/api/cnpj/v1/"
                                      + cnpj)) );

    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
    QJsonObject json(doc.object());

    //validando o cep, e tratando erros
    if( json.find("erro") != json.end() )
    {
        json["erro"].toBool() ?
                    ui->lb_nv_cnpj->setText("CNPJ") : ui->lb_nv_cnpj->setText("CNPJ: inválido");


        //i->lb_nv_cnpj->setText("CNPJ: inválido");
    }
    else
    {
        ui->txt_nv_cnpj->setText(json["cnpj"].toString());
        ui->txt_nv_uf->setText(json["uf"].toString());
        ui->txt_nv_cidade->setText(json["municipio"].toString());
        ui->txt_nv_rua->setText(json["logradouro"].toString());
        ui->txt_nv_numeroEstabelecimento->setText(json["numero"].toString());
        ui->txt_nv_bairro->setText(json["bairro"].toString());
        ui->txt_nv_razaoSocial->setText(json["razao_social"].toString());
        ui->txt_nv_nomeFantasia->setText(json["nome_fantasia"].toString());
        ui->txt_nv_porte->setText(json["porte"].toString());
        ui->txt_nv_ocupacao->setText(json["cnae_fiscal_descricao"].toString());
        ui->txt_nv_tel1->setText(json["ddd_telefone_1"].toString());
        ui->txt_nv_tel2->setText(json["ddd_telefone_2"].toString());
    }
}


