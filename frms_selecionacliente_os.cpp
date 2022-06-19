#include "frms_selecionacliente_os.h"
#include "ui_frms_selecionacliente_os.h"
#include "frm_ordemservico.h" //ordem de serviços

frms_selecionacliente_os::frms_selecionacliente_os(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frms_selecionacliente_os)
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

    ui->txt_filtrarCliente->setFocus();

    //configurando combo box
    ui->cb_filtrar->addItem("-");
    ui->cb_filtrar->addItem("Cliente");
    ui->cb_filtrar->addItem("CPF");
    ui->cb_filtrar->addItem("Cidade");
    ui->cb_filtrar->addItem("Rua");
    ui->cb_filtrar->addItem("Bairro");


    //**Estilizando layout da table widget CLIENTES**
    //definindo o tamanho das colunas
    ui->tw_selecionaCliente->setColumnCount(10);
    ui->tw_selecionaCliente->setColumnWidth(0, 40);
    ui->tw_selecionaCliente->setColumnWidth(1, 150);
    ui->tw_selecionaCliente->setColumnWidth(6, 150);

    //cabeçalhos do table widget
    QStringList cabecalho1={"Código", "Cliente", "CPF", "CEP", "Estado"
                           ,"Cidade", "Rua","Nro. Casa","Bairro", "Telefone"};

    ui->tw_selecionaCliente->setHorizontalHeaderLabels( cabecalho1 );
    //definindo cor da linha ao ser selecionada
    ui->tw_selecionaCliente->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_selecionaCliente->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_selecionaCliente->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_selecionaCliente->verticalHeader()->setVisible(false);

    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_selecionaCliente );
    //inserir linhas dentro do table widget
    int contlinhas = 0;
    //Remover os produtos do table widget
    QSqlQuery query; //query para listar os colaboradores no table widget
    query.prepare("SELECT "
                      "a005_codigo       "
                      ",a005_nome        "
                      ",a005_cpf         "
                      ",a005_cep         "
                      ",a005_estado      "
                      ",a005_cidade      "
                      ",a005_rua         "
                      ",a005_nro_casa    "
                      ",a005_bairro      "
                      ",a005_telefone    "
                  "FROM "
                      "a005_cliente "
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
            ui->tw_selecionaCliente->insertRow( contlinhas );
            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));

            //definindo o tamanho das linhas
            ui->tw_selecionaCliente->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar clientes");
    }

    //**Estilizando layout da table widget VEICULOS**
    //definindo o tamanho das colunas
    ui->tw_selecionaVeiculo->setColumnCount(8);
    ui->tw_selecionaVeiculo->setColumnWidth(0, 40);
    ui->tw_selecionaVeiculo->setColumnWidth(1, 100);
    ui->tw_selecionaVeiculo->setColumnWidth(2, 100);
    ui->tw_selecionaVeiculo->setColumnWidth(8, 200);

    //cabeçalhos do table widget
    //cabeçalhos do table widget
    QStringList cabecalho2={"Código", "Marca", "Modelo", "Motor"
                           ,"Chassi", "Placa", "Cor", "Observação"};

    ui->tw_selecionaVeiculo->setHorizontalHeaderLabels(cabecalho2);
    //definindo cor da linha ao ser selecionada
    ui->tw_selecionaVeiculo->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_selecionaVeiculo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_selecionaVeiculo->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_selecionaVeiculo->verticalHeader()->setVisible(false);

}

frms_selecionacliente_os::~frms_selecionacliente_os() //**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//seleciona item TW cliente
void frms_selecionacliente_os::on_tw_selecionaCliente_itemSelectionChanged()
{
    //pega a linha selecionada
    int id = ui->tw_selecionaCliente->item(ui->tw_selecionaCliente->currentRow()
                                           , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a005_codigo       "
                      ",a005_nome        "
                      ",a005_cpf         "
                      ",a005_cep         "
                      ",a005_estado      "
                      ",a005_cidade      "
                      ",a005_rua         "
                      ",a005_nro_casa    "
                      ",a005_bairro      "
                      ",a005_telefone    "
                  "FROM "
                      "a005_cliente "
                  "WHERE "
                    "a005_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        g_codigo_cliente = query.value(0).toString();
        g_nome_cliente = query.value(1).toString();

        qDebug() << "Código cliente: " << g_codigo_cliente;
        qDebug() << "Nome cliente: " << g_codigo_cliente;


        funcoes_globais::removerLinhas( ui->tw_selecionaVeiculo );
        //inserir linhas dentro do table widget
        int contlinhas = 0;

        QSqlQuery query;
        query.prepare("SELECT "
                          "a004_codigo                            "
                          ",a011_marca_nome                       "
                          ",a012_nome_veiculo                     "
                          ",a004_motor_veiculo                    "
                          ",a004_chassi_veiculo                   "
                          ",a004_placa_veiculo                    "
                          ",a004_cor_veiculo                      "
                          ",COALESCE(a004_observacao, '(NENHUM)') "
                      "FROM "
                          "a005_cliente "
                          "JOIN a004_veiculos ON (a004_fk_codigo_cliente = a005_codigo)  "
                          "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)    "
                          "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca)      "
                      "WHERE "
                          "a004_ativo = true  "
                          "AND a004_codigo = '" +g_codigo_cliente+ "' "
                      "ORDER BY "
                          "a004_codigo DESC");

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
                                            , new QTableWidgetItem(query.value(8).toString()));

                //definindo o tamanho das linhas
                ui->tw_selecionaVeiculo->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar veiculos de clientes");
        }
    }
}

//pega valor TW veiculos
void frms_selecionacliente_os::on_tw_selecionaVeiculo_itemSelectionChanged()
{
    //pega a linha selecionada
    int id = ui->tw_selecionaVeiculo->item(ui->tw_selecionaVeiculo->currentRow()
                                           , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a004_codigo                            "
                      ",a011_marca_nome                       "
                      ",a012_nome_veiculo                     "
                      ",a004_motor_veiculo                    "
                      ",a004_chassi_veiculo                   "
                      ",a004_placa_veiculo                    "
                      ",a004_cor_veiculo                      "
                      ",COALESCE(a004_observacao, '(NENHUM)') "
                  "FROM "
                      "a005_cliente "
                      "JOIN a004_veiculos ON (a004_fk_codigo_cliente = a005_codigo)  "
                      "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)    "
                      "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca)      "
                  "WHERE "
                    "a004_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        g_codigo_veiculo = query.value(0).toString();
        g_nome_veiculo = query.value(2).toString();
        g_placa_veiculo = query.value(5).toString();
        g_cor_veiculo = query.value(6).toString();
    }
}

//filtrando clientes
void frms_selecionacliente_os::on_txt_filtrarCliente_returnPressed()
{
    QString cb_filtro = ui->cb_filtrar->currentText();
    QString txt_filtro = ui->txt_filtrarCliente->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Cliente" << "CPF" << "Cidade" << "Rua" << "Bairro";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_selecionaCliente );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_filtrarCliente->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a005_codigo       "
                        ",a005_nome        "
                        ",a005_cpf         "
                        ",a005_cep         "
                        ",a005_estado      "
                        ",a005_cidade      "
                        ",a005_rua         "
                        ",a005_nro_casa    "
                        ",a005_bairro      "
                        ",a005_telefone    "
                    "FROM "
                        "a005_cliente "
                    "WHERE "
                        "a005_ativo = true  "
                    "ORDER BY "
                        "a005_codigo DESC";
        }
        else
        {
            busca = "SELECT "
                        "a005_codigo       "
                        ",a005_nome        "
                        ",a005_cpf         "
                        ",a005_cep         "
                        ",a005_estado      "
                        ",a005_cidade      "
                        ",a005_rua         "
                        ",a005_nro_casa    "
                        ",a005_bairro      "
                        ",a005_telefone    "
                    "FROM "
                        "a005_cliente "
                    "WHERE "
                        "a005_ativo = true  "
                    "ORDER BY "
                        "a005_codigo DESC";
        }
    }
    else
    {
        cb_opc << "Cliente" << "CPF" << "Cidade" << "Rua" << "Bairro";
        //consulta de acordo com a seleção do combo box
        switch( cb_opc.indexOf( cb_filtro ) )
        {
            //Cliente
            case 0:

                filtro_sql = "a005_nome LIKE '%" +txt_filtro+ "%' ";
                break;
            //CPF
            case 1:

                filtro_sql = "a005_cpf LIKE '%" +txt_filtro+ "%' ";
                break;
            //Cidade
            case 2:

                filtro_sql = "a005_cidade LIKE '%" +txt_filtro+ "%' ";
                break;
            //Rua
            case 3:

                filtro_sql = "a005_rua LIKE '%" +txt_filtro+ "%' ";
                break;
             //bairro
            case 4:

                filtro_sql = "a005_bairro LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a005_codigo       "
                    ",a005_nome        "
                    ",a005_cpf         "
                    ",a005_cep         "
                    ",a005_estado      "
                    ",a005_cidade      "
                    ",a005_rua         "
                    ",a005_nro_casa    "
                    ",a005_bairro      "
                    ",a005_telefone    "
                "FROM "
                    "a005_cliente "
                "WHERE "
                    + filtro_sql +
                    "a005_ativo = true  "
                "ORDER BY "
                    "a005_codigo DESC";

    }

    //contador para percorrer linhas
    int contlinhas = 0;
    QSqlQuery query;
    query.prepare( busca );

    if( query.exec() ) //executa a query
    {
        while( query.next() ) //percorrendo query e preenchendo table widget
        {
            //inserindo com contador de linhas, por index
            ui->tw_selecionaCliente->insertRow( contlinhas );
            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            ui->tw_selecionaCliente->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));

            //definindo o tamanho das linhas
            ui->tw_selecionaCliente->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar clientes");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_filtrarCliente->clear();
    ui->txt_filtrarCliente->setFocus(); //posiciona o cursos no campo novamente
}

//btn filtrar
void frms_selecionacliente_os::on_btn_filtrarCliente_clicked()
{
    frms_selecionacliente_os::on_txt_filtrarCliente_returnPressed();
}

//btn confirma dados cliente e veiculos
void frms_selecionacliente_os::on_btn_confirmarCliente_clicked()
{
    if( ui->tw_selecionaCliente->currentRow() == -1 ||  ui->tw_selecionaVeiculo->currentRow() == -1  )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um cliente e um veículo");
        return;
    }

    //enviando nome e codigo do cliente selecionado para o campo do modelo no agendaservicos
    frm_ordemservico *fm_ordemservico  = new frm_ordemservico(this, g_codigo_cliente
                                                                  , g_nome_cliente
                                                                  , g_codigo_veiculo
                                                                  , g_nome_veiculo
                                                                  , g_placa_veiculo
                                                                  , g_cor_veiculo);
    fm_ordemservico->exec();

    //deletando ponteiro
    try
    {
        delete fm_ordemservico ;
    }
    catch (...)
    {
        qDebug() << "__Falha ao deletar ponteiro: fm_ordemservico  na tela de selecaocliente";
    }

    close();
}

