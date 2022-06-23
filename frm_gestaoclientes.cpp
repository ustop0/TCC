#include "frm_gestaoclientes.h"
#include "ui_frm_gestaoclientes.h"
#include "frms_nv_veiculocliente.h"
#include "Classes/clcliente.h"
#include "Classes/clveiculo.h"

frm_gestaoclientes::frm_gestaoclientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaoclientes)
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

    //deixa o botão da validação do cep invisivel
    ui->btn_nv_validacep->setVisible(false);
    ui->btn_ge_validacep->setVisible(false);

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //configurando combo box
    ui->cb_ge_filtrar->addItem("-");
    ui->cb_ge_filtrar->addItem("Cliente");
    ui->cb_ge_filtrar->addItem("CPF");
    ui->cb_ge_filtrar->addItem("Veiculo");
    ui->cb_ge_filtrar->addItem("Placa Veiculo");

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_ge_listaclientes->setColumnCount(9); //Nro colunas
    ui->tw_ge_listaclientes->setColumnWidth(0, 20); //id cliente
    ui->tw_ge_listaclientes->setColumnWidth(1, 150); //nome cliente
    ui->tw_ge_listaclientes->setColumnWidth(3, 120); //carro cliente
    ui->tw_ge_listaclientes->setColumnWidth(7, 150); //rua cliente

    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Cliente", "CPF", "Veículo", "Placa","Estado"
                           ,"Cidade", "Rua","Nro. Casa","Bairro", "Telefone"};

    ui->tw_ge_listaclientes->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_listaclientes->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_listaclientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_listaclientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_listaclientes->verticalHeader()->setVisible(false);

    //listava o tabwidget antigo

}//**FIM** construtor

frm_gestaoclientes::~frm_gestaoclientes()//**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//btn valida cep
void frm_gestaoclientes::on_btn_nv_validacep_clicked()
{
    QString cep = ui->txt_nv_cep->text();
    //validando cep
    validaCEP( cep );
}

//pressiona campo cep, chama api
void frm_gestaoclientes::on_txt_nv_cep_returnPressed()
{
    frm_gestaoclientes::on_btn_nv_validacep_clicked();
}

//tela de cadastro de veiculos
void frm_gestaoclientes::on_btn_nv_cadastrarveiculo_clicked()
{
    frms_nv_veiculocliente f_nv_veiculocliente;
    f_nv_veiculocliente.exec();
}

//novo cliente
void frm_gestaoclientes::on_btn_nv_novo_clicked()
{
    //limpando todos os campos
    ui->txt_nv_nome->clear();
    ui->txt_nv_cpf->clear();
    ui->txt_nv_cep->clear();
    ui->txt_nv_estado->clear();
    ui->txt_nv_cidade->clear();
    ui->txt_nv_rua->clear();
    ui->txt_nv_nrocasa->clear();
    ui->txt_nv_bairro->clear();
    ui->txt_nv_telefone->clear();
    ui->txt_nv_nome->setFocus();
}

//salvar novo cliente **DESENVOLVENDO**
void frm_gestaoclientes::on_btn_nv_gravar_clicked()
{
    //**EM DESENVOLVIMENTO
    ClCliente cliente;

    cliente.nome = ui->txt_nv_nome->text();
    cliente.cpf = ui->txt_nv_cpf->text();
    if( recebeCPF( cliente.cpf ) == false ) //**EM TESTES**recebendo e tratando o cpf
    {
        qDebug() << "cpf inválido para sql";
    }

    cliente.cep = ui->txt_nv_cep->text().toUpper();
    cliente.estado = ui->txt_nv_estado->text().toUpper();
    cliente.cidade = ui->txt_nv_cidade->text().toUpper();
    cliente.rua = ui->txt_nv_rua->text().toUpper();
    cliente.nro_casa = ui->txt_nv_nrocasa->text().toUpper();
    cliente.bairro = ui->txt_nv_bairro->text().toUpper();
    cliente.telefone1 = ui->txt_nv_telefone->text().toUpper();

    //DESENVOLVENDO CRUD COM O BANCO
    QSqlQuery query;

    //inserir na tabela clientes
    query.prepare("INSERT INTO "
                    "a005_cliente(a005_nome           "
                                     ",a005_cpf       "
                                     ",a005_cep       "
                                     ",a005_estado    "
                                     ",a005_cidade    "
                                     ",a005_rua       "
                                     ",a005_nro_casa  "
                                     ",a005_bairro    "
                                     ",a005_telefone) "
                    "VALUES('" +cliente.nome      +  "'"
                          ",'" +cliente.cpf       +  "'"
                          ",'" +cliente.cep       +  "'"
                          ",'" +cliente.estado    +  "'"
                          ",'" +cliente.cidade    +  "'"
                          ",'" +cliente.rua       +  "'"
                          ",'" +cliente.nro_casa  +  "'"
                          ",'" +cliente.bairro    +  "'"
                          ",'" +cliente.telefone1 + "') ");


    if( !query.exec() ) //verifica se a query tem algum erro e executa ela
    {
        QMessageBox::critical(this, "ERRO", "Não foi possível salvar os dados do cliente");
    }
    else
    {
        qDebug() << "_Dados salvos na tabela a005_cliente";

        //pergunta se o usuário quer cadastrar um veiculo para o cliente
        QMessageBox::StandardButton opc =QMessageBox::question(
                                          this,"Veículo"
                                          ,"Cliente salvo com sucesso, "
                                           "deseja cadastrar um veículo para este cliente?"
                                          ,QMessageBox::Yes|QMessageBox::No);

        if( opc == QMessageBox::Yes ) //verificando o botao da caixa question
        {
            frms_nv_veiculocliente f_nv_veiculocliente;
            f_nv_veiculocliente.exec();
        }
        else
        {
            //limpando todos os campos
            ui->txt_nv_nome->clear();
            ui->txt_nv_cpf->clear();
            ui->txt_nv_cep->clear();
            ui->txt_nv_estado->clear();
            ui->txt_nv_cidade->clear();
            ui->txt_nv_rua->clear();
            ui->txt_nv_nrocasa->clear();
            ui->txt_nv_bairro->clear();
            ui->txt_nv_telefone->clear();
            ui->txt_nv_nome->setFocus();
        }
    }
}

//quando trocar o tab widget, atualiza o table widget
void frm_gestaoclientes::on_tabWidget_currentChanged(int index)
{
    //verifica a interface pelo index das tabs
    if( index == 1 )
    {
        //carregando os clientes no tablewidget
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_ge_listaclientes );

        //inserir linhas dentro do table widget
        int contlinhas = 0;

        //essa query deve filtrar com base no cliente cadastrado na tela novo cliente
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a005_codigo                               "
                          ",a005_nome                                "
                          ",a005_cpf                                 "
                          ",COALESCE(a012_nome_veiculo, '(NENHUM)')  "
                          ",COALESCE(a004_placa_Veiculo, '(NENHUM)') "
                          ",a005_estado                              "
                          ",a005_cidade                              "
                          ",a005_rua                                 "
                          ",a005_nro_casa                            "
                          ",a005_bairro                              "
                          ",a005_telefone                            "
                      "FROM "
                          "a005_cliente "
                          "FULL OUTER JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                          "FULL OUTER JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                          "FULL OUTER JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca)     "
                      "WHERE "
                          "a005_ativo = true "
                      "ORDER BY "
                          "a005_codigo DESC");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_ge_listaclientes->insertRow(contlinhas);
                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 3
                                            , new QTableWidgetItem(query.value(3).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 4
                                            , new QTableWidgetItem(query.value(4).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 5
                                            , new QTableWidgetItem(query.value(5).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 6
                                            , new QTableWidgetItem(query.value(6).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 7
                                            , new QTableWidgetItem(query.value(7).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 8
                                            , new QTableWidgetItem(query.value(8).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 9
                                            , new QTableWidgetItem(query.value(9).toString()));

                ui->tw_ge_listaclientes->setItem(contlinhas
                                            , 10
                                            , new QTableWidgetItem(query.value(10).toString()));

                //definindo o tamanho das linhas
                ui->tw_ge_listaclientes->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar clientes");
        }
    }
}

//**TAB Gestão clientes**
//selecionar cliente da grid, para usar no formulario que edita dados dos clientes
void frm_gestaoclientes::on_tw_ge_listaclientes_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_ge_listaclientes->item(ui->tw_ge_listaclientes->currentRow()
                                        , 0) ->text().toInt();

    //pega o cliente selecionado e envia para a tela de edição de clientes
    QSqlQuery query;
    query.prepare("SELECT "
                      "a005_codigo    "
                      ",a005_nome     "
                      ",a005_cpf      "
                      ",a005_cep      "
                      ",a005_estado   "
                      ",a005_cidade   "
                      ",a005_rua      "
                      ",a005_nro_casa "
                      ",a005_bairro   "
                      ",a005_telefone "
                  "FROM "
                      "a005_cliente "
                  "WHERE "
                    "a005_codigo = '" +QString::number(id)+ "'"
                    "AND a005_ativo = true "
                  "ORDER BY "
                      "a005_codigo DESC");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        ui->txt_ge_codigo->setText(query.value(0).toString());
        ui->txt_ge_nome->setText(query.value(1).toString());
        ui->txt_ge_cpf->setText(query.value(2).toString());
        ui->txt_ge_cep->setText(query.value(3).toString());
        ui->txt_ge_estado->setText(query.value(4).toString());
        ui->txt_ge_cidade->setText(query.value(5).toString());
        ui->txt_ge_rua->setText(query.value(6).toString());
        ui->txt_ge_nrocasa->setText(query.value(7).toString());
        ui->txt_ge_bairro->setText(query.value(8).toString());
        ui->txt_ge_telefone->setText(query.value(9).toString());
    }
}

//filtrar
void frm_gestaoclientes::on_txt_ge_filtro_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtro->text().toUpper();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Cliente" << "CPF" << "Veiculo" << "Placa Veiculo";

    funcoes_globais::removerLinhas( ui->tw_ge_listaclientes ); //remove as linhas o table widget

    if( ui->txt_ge_filtro->text() == "" ) //verificando se algo foi digitado no campo de filtro
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a005_codigo         "
                        ",a005_nome          "
                        ",a005_cpf           "
                        ",a012_nome_veiculo  "
                        ",a004_placa_veiculo "
                        ",a005_estado        "
                        ",a005_cidade        "
                        ",a005_rua           "
                        ",a005_nro_casa      "
                        ",a005_bairro        "
                        ",a005_telefone      "
                    "FROM "
                        "a005_cliente "
                        "FULL OUTER JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                        "FULL OUTER JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                        "FULL OUTER JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca)     "
                    "WHERE "
                      "a005_ativo = true "
                    "ORDER BY "
                        "a005_codigo DESC";

        }
        else
        {
            busca = "SELECT "
                        "a005_codigo         "
                        ",a005_nome          "
                        ",a005_cpf           "
                        ",a012_nome_veiculo  "
                        ",a004_placa_veiculo "
                        ",a005_estado        "
                        ",a005_cidade        "
                        ",a005_rua           "
                        ",a005_nro_casa      "
                        ",a005_bairro        "
                        ",a005_telefone      "
                    "FROM "
                        "a005_cliente "
                        "FULL OUTER JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                        "FULL OUTER JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                        "FULL OUTER JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca)     "
                    "WHERE "
                      "a005_ativo = true "
                    "ORDER BY "
                        "a005_codigo DESC";
        }
    }
    else
    {
        //consulta de acordo com a seleção do combo box
        switch( cb_opc.indexOf(cb_filtro) )
        {
            //cliente
            case 0:
                filtro_sql = "a005_nome LIKE '%" +txt_filtro+ "%' ";
                break;
            //cpf
            case 1:

                filtro_sql = "a005_cpf LIKE '%" +txt_filtro+ "%' ";
                break;
            //Carro
            case 2:

                filtro_sql = "a012_nome_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            //Placa
            case 3:

                filtro_sql = "a004_placa_Veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a005_codigo           "
                    ",a005_nome            "
                    ",a005_cpf             "
                    ",a012_nome_veiculo    "
                    ",a004_placa_veiculo   "
                    ",a005_estado          "
                    ",a005_cidade          "
                    ",a005_rua             "
                    ",a005_nro_casa        "
                    ",a005_bairro          "
                    ",a005_telefone        "
                "FROM "
                    "a005_cliente "
                    "FULL OUTER JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                    "FULL OUTER JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                    "FULL OUTER JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca)     "
                "WHERE "
                  + filtro_sql +
                  "AND a005_ativo = true "
                "ORDER BY "
                    "a005_codigo DESC";
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
            ui->tw_ge_listaclientes->insertRow(contlinhas);
            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));

            ui->tw_ge_listaclientes->setItem(contlinhas
                                        , 10
                                        , new QTableWidgetItem(query.value(10).toString()));

            //definindo o tamanho das linhas
            ui->tw_ge_listaclientes->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar Clientes");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_ge_filtro->clear();
    ui->txt_ge_filtro->setFocus(); //posiciona o cursos no campo novamente
}

//botão filtrar
void frm_gestaoclientes::on_btn_ge_filtrar_clicked()
{
    frm_gestaoclientes::on_txt_ge_filtro_returnPressed();
}

//validando cep, gestão clientes
void frm_gestaoclientes::on_txt_ge_cep_returnPressed()
{
    frm_gestaoclientes::on_btn_ge_validacep_clicked();
}

void frm_gestaoclientes::on_btn_ge_validacep_clicked()
{
    QString cep = ui->txt_ge_cep->text();
    //validando cep
    validaCEP( cep );
}

//salvar dados do cliente editado gestão clientes
void frm_gestaoclientes::on_btn_ge_salvar_clicked()
{
    //**EM DESENVOLVIMENTO
    ClCliente cliente;

    cliente.codigo = ui->txt_ge_codigo->text().toUpper();
    cliente.nome = ui->txt_ge_nome->text().toUpper();
    cliente.cpf = ui->txt_ge_cpf->text().toUpper();
    if( recebeCPF( cliente.cpf ) == false ) //**EM TESTES**recebendo e tratando o cpf
    {
        qDebug() << "cpf inválido para sql";
    }

    cliente.cep = ui->txt_ge_cep->text().toUpper();
    cliente.estado = ui->txt_ge_estado->text().toUpper();
    cliente.cidade = ui->txt_ge_cidade->text().toUpper();
    cliente.rua = ui->txt_ge_rua->text().toUpper();
    cliente.nro_casa = ui->txt_ge_nrocasa->text().toUpper();
    cliente.bairro = ui->txt_ge_bairro->text().toUpper();
    cliente.telefone1 = ui->txt_ge_telefone->text().toUpper();


    //DESENVOLVENDO CRUD COM O BANCO
    QSqlQuery query;

    //inserir na tabela clientes
    query.prepare("UPDATE "
                    "a005_cliente "
                  "SET "
                    "a005_nome      = '" +cliente.nome      + "'"
                    ",a005_cpf      = '" +cliente.cpf       + "'"
                    ",a005_cep      = '" +cliente.cep       + "'"
                    ",a005_estado   = '" +cliente.estado    + "'"
                    ",a005_cidade   = '" +cliente.cidade    + "'"
                    ",a005_rua      = '" +cliente.rua       + "'"
                    ",a005_nro_casa = '" +cliente.nro_casa  + "'"
                    ",a005_bairro   = '" +cliente.bairro    + "'"
                    ",a005_telefone = '" +cliente.telefone1 + "'"
                  "WHERE "
                    "a005_codigo = '" +cliente.codigo+ "'");


    if( !query.exec() ) //verifica se a query tem algum erro e executa ela
    {
        QMessageBox::critical(this, "ERRO", "Não foi possível salvar os dados do cliente");
    }
    else
    {
        //pega a linha que está selecionada
        int linha = ui->tw_ge_listaclientes->currentRow();
        //atualizando o table widget com o novo registro
        ui->tw_ge_listaclientes->item(linha, 1)->setText(cliente.nome);
        ui->tw_ge_listaclientes->item(linha, 2)->setText(cliente.cpf);
        ui->tw_ge_listaclientes->item(linha, 3)->setText(cliente.cep);
        ui->tw_ge_listaclientes->item(linha, 4)->setText(cliente.estado);
        ui->tw_ge_listaclientes->item(linha, 5)->setText(cliente.cidade);
        ui->tw_ge_listaclientes->item(linha, 6)->setText(cliente.rua);
        ui->tw_ge_listaclientes->item(linha, 7)->setText(cliente.nro_casa);
        ui->tw_ge_listaclientes->item(linha, 8)->setText(cliente.bairro);
        ui->tw_ge_listaclientes->item(linha, 9)->setText(cliente.telefone1);

        QMessageBox::information(this, "Atualizado", "Cliente atualizado com sucesso!");

        //pergunta se o usuário quer cadastrar um veiculo para o cliente
        QMessageBox::StandardButton opc =QMessageBox::question(
                                          this,"Veículo"
                                          ,"Dados do cliente alterados com sucesso, "
                                           "deseja editar o veículo deste cliente?"
                                          ,QMessageBox::Yes|QMessageBox::No); //revisar tabulação

        if( opc == QMessageBox::Yes ) //verificando o botao da caixa question
        {
            frms_nv_veiculocliente *f_nv_veiculocliente = new frms_nv_veiculocliente();

            f_nv_veiculocliente->exec();

            try
            {
                delete f_nv_veiculocliente;
            }
            catch ( ... )
            {
                qDebug() << "__Erro ao deletar objeto f_nv_veiculocliente";
            }
        }
        else
        {
            //limpando todos os campos da GE
            ui->txt_ge_codigo->clear();
            ui->txt_ge_nome->clear();
            ui->txt_ge_cpf->clear();
            ui->txt_ge_cep->clear();
            ui->txt_ge_estado->clear();
            ui->txt_ge_cidade->clear();
            ui->txt_ge_rua->clear();
            ui->txt_ge_nrocasa->clear();
            ui->txt_ge_bairro->clear();
            ui->txt_ge_telefone->clear();
            ui->txt_ge_nome->setFocus();

            //limpando os campos da NV
            ui->txt_nv_nome->clear();
            ui->txt_nv_cpf->clear();
            ui->txt_nv_cep->clear();
            ui->txt_nv_estado->clear();
            ui->txt_nv_cidade->clear();
            ui->txt_nv_rua->clear();
            ui->txt_nv_nrocasa->clear();
            ui->txt_nv_bairro->clear();
            ui->txt_nv_telefone->clear();
            ui->txt_nv_nome->setFocus();
        }
    }
}

//btn excluir cliente
void frm_gestaoclientes::on_btn_ge_excluir_clicked()
{
    if( ui->tw_ge_listaclientes->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um cliente");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão do cliente?"
                                      ,QMessageBox::Yes|QMessageBox::No);

    if( opc == QMessageBox::Yes )
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_ge_listaclientes->currentRow();
        QString id = ui->tw_ge_listaclientes->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a005_cliente "
                      "SET "
                        "a005_ativo = false "
                      "WHERE "
                        "a005_codigo ='" +id+ "'");

        if( query.exec() ) //executa a query
        {
            ui->tw_ge_listaclientes->removeRow( linha );
            QMessageBox::information(this, "DELETADO", "Cliente excluído com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir cliente");
        }
    }
}

//**FUNÇÕES**//
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 18/04/2022                                                                           |
 * Propósito: receber o cpf, e realizar chamar a função que valida o mesmo                    |
 * Chamada: botão gravar cliente                                                              |
 *--------------------------------------------------------------------------------------------
 */
bool frm_gestaoclientes::recebeCPF( const QString &cliente_cpf )
{
    //recebendo o cpf por QString e convertendo para std::string
    std::string conv_cpf = cliente_cpf.toStdString();

    //convertendo para const char array
    const char *input = conv_cpf.c_str();
    int cpf[11];

    //TESTES** verificando se tem menos que 11 digitos
    for( size_t i = 0; i < 11; i++ )
     {
         cpf[i] = i;

         //verifica de acordo com o indice do tab
         int totalNumeros = 0;
         totalNumeros += cpf[i];
         if( totalNumeros != 11 )
         {
             qDebug() << "_O CPF digitado NÃO É VÁLIDO, tem menos de 11 digitos" << "\n";
             ui->lb_nv_cpf->setText("CPF: inválido");
         }
         else if( totalNumeros != 11 &&  ui->lb_nv_cpf->text() == "" ) //**TESTES
         {
             qDebug() << "_O CPF digitado NÃO É VÁLIDO, tem menos de 11 digitos" << "\n";
             ui->lb_ge_cpf->setText("CPF: inválido");
         }
     }

    //verificando se a entrada é válida
    for( unsigned char i = 0; i < 11; i++ )
    {
       //Convertendo char para valor absoluto segundo tabela ASCII
        cpf[i] = static_cast<int>( input[i] - 48 );

        if( cpf[i] < 0 || cpf[i] > 9 )
        {
            return 1;
        }
    }

    //chamando a função que realiza a validação do cpf
    int valCpf;
    valCpf = fn_validaCpf::validaCPF( cpf );

    //trata de acordo com o retorno da função, true e false
    do
    {
        if( valCpf == true )
        {
            qDebug() << "_O CPF digitado É válido" << "\n";
            ui->lb_nv_cpf->setText("CPF");
            ui->lb_ge_cpf->setText("CPF");
            return valCpf; //teste
        }
        else
        {
            qDebug() << "_O CPF digitado NÃO É VÁLIDO" << "\n";
            QMessageBox::warning(this, "Erro", "O CPF digitado é inválido");

            //Informa que o cpf é inválido, nas duas tabs
            if( ui->lb_nv_cep->text() != "" )
            {
                ui->lb_nv_cpf->setText("CPF: inválido");
            }
            else
            {
               ui->lb_ge_cpf->setText("CPF: inválido");
            }

            break;
        }
    }while( valCpf == false );

    return valCpf; //essa função não deve retornar nenhum valor específico
}

/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 18/04/2022                                                                           |
 * Propósito: receber o cep, e faz a validação via API do BrasilAPI                           |
 * Chamada: botão gravar cliente                                                              |
 *--------------------------------------------------------------------------------------------
 */
void frm_gestaoclientes::validaCEP( const QString &cep  )
{
    /*
    if( ui->txt_nv_cep->text() != "" )
    {
        cep = ui->txt_nv_cep->text();
    }
    else if ( ui->txt_ge_cep->text() != "" )
    {
        cep = ui->txt_ge_cep->text();
    }
    */

    QEventLoop waitLoop;
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(
                QNetworkRequest( QUrl("https://brasilapi.com.br/api/cep/v1/" + cep) ) );

    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
    QJsonObject json(doc.object());


    //validando o cep, e tratando erros
    if( json.find("erro") != json.end() )
    {
        json["erro"].toBool() ?
                    ui->lb_nv_cep->setText("CEP") : ui->lb_nv_cep->setText("CEP: inválido");

    }
    else
    {
        QString cep = json["cep"].toString();
        QString estado = json["state"].toString();
        QString cidade = json["city"].toString();
        QString bairro = json["neighborhood"].toString();
        QString rua = json["street"].toString();

        qDebug() << "Bairro: " << bairro;
        qDebug() << "Rua: " << rua;

        ui->txt_nv_cep->setText( cep );
        ui->txt_nv_estado->setText( estado );
        ui->txt_nv_cidade->setText( cidade );
        ui->txt_nv_bairro->setText( bairro );
        ui->txt_nv_rua->setText( rua );

        /*
        ui->txt_nv_cep->setText(json["cep"].toString());
        ui->txt_nv_estado->setText(json["state"].toString());
        ui->txt_nv_cidade->setText(json["city"].toString());
        ui->txt_nv_bairro->setText(json["neighborhood"].toString());
        ui->txt_nv_rua->setText(json["street"].toString());
        */

        /*
        ui->txt_ge_cep->setText(json["cep"].toString());
        ui->txt_ge_estado->setText(json["state"].toString());
        ui->txt_ge_cidade->setText(json["city"].toString());
        ui->txt_ge_bairro->setText(json["neighborhood"].toString());
        ui->txt_ge_rua->setText(json["street"].toString());
        */
    }
}
