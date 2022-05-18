#include "frms_selecionaveiculo.h"
#include "ui_frms_selecionaveiculo.h"
#include "frm_agendaservicos.h" //formulário de agendamento de serviços

QString g_nomeVeiculo;
QString g_codigoVeiculo;

frms_selecionaveiculo::frms_selecionaveiculo(QWidget *parent, QString c_codigoCliente) :
    QDialog(parent),
    ui(new Ui::frms_selecionaveiculo)
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

    //recebendo dados do agendaserviços c_codigo_cliente é recebido do agendaservicos

    //deixa o botão da validação do cnpj invisivel
    ui->txt_filtrarVeiculo->setFocus();

    //configurando combo box
    ui->cb_filtrar->addItem("-");
    ui->cb_filtrar->addItem("Cliente");
    ui->cb_filtrar->addItem("CPF");
    ui->cb_filtrar->addItem("Veiculo");
    ui->cb_filtrar->addItem("Placa Veiculo");

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_selecionaVeiculo->setColumnCount(7);
    ui->tw_selecionaVeiculo->setColumnWidth(0, 40);
    ui->tw_selecionaVeiculo->setColumnWidth(1, 200);

    //cabeçalhos do table widget
    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Cliente", "CPF", "Marca"
                           ,"Veiculo", "Placa", "Observação"};

    ui->tw_selecionaVeiculo->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_selecionaVeiculo->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_selecionaVeiculo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_selecionaVeiculo->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_selecionaVeiculo->verticalHeader()->setVisible(false);

    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_selecionaVeiculo );
    //inserir linhas dentro do table widget
    int contlinhas = 0;
    //Remover os produtos do table widget
    QSqlQuery query; //query para listar os colaboradores no table widget
    query.prepare("SELECT "
                      "a004_codigo          "
                      ",a005_nome           "
                      ",a005_cpf            "
                      ",a011_marca_nome     "
                      ",a012_nome_veiculo   "
                      ",a004_placa_veiculo  "
                      ",a004_observacao     "
                  "FROM "
                      "a005_cliente "
                      "JOIN a004_veiculos ON (a004_fk_codigo_cliente = a005_codigo)  "
                      "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)    "
                      "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca)      "
                  "WHERE "
                      "a004_ativo = true  "
                      "AND a004_codigo = '" +c_codigoCliente+ "' "
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

frms_selecionaveiculo::~frms_selecionaveiculo()
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//selecionar veiculo TW
void frms_selecionaveiculo::on_tw_selecionaVeiculo_itemSelectionChanged()
{
    //pega a linha selecionada
    int id = ui->tw_selecionaVeiculo->item(ui->tw_selecionaVeiculo->currentRow()
                                           , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a004_codigo          "
                      ",a005_nome           "
                      ",a005_cpf            "
                      ",a011_marca_nome     "
                      ",a012_nome_veiculo   "
                      ",a004_placa_veiculo  "
                      ",a004_observacao     "
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

        g_codigoVeiculo = query.value(0).toString();
        g_nomeVeiculo = query.value(4).toString();

        qDebug() << "Código Veículo: " << g_codigoVeiculo;
        qDebug() << "Nome Veículo: " << g_nomeVeiculo;
    }
}

//filtrando veiculos
void frms_selecionaveiculo::on_txt_filtrarVeiculo_returnPressed()
{
    QString cb_filtro = ui->cb_filtrar->currentText();
    QString txt_filtro = ui->txt_filtrarVeiculo->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Cliente" << "CPF" << "Veiculo" << "Placa Veiculo";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_selecionaVeiculo );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_filtrarVeiculo->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a004_codigo          "
                        ",a005_nome           "
                        ",a005_cpf            "
                        ",a011_marca_nome     "
                        ",a012_nome_veiculo   "
                        ",a004_placa_veiculo  "
                        ",a004_observacao     "
                    "FROM "
                        "a004_veiculos "
                        "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)  "
                        "JOIN a011_marcas ON (a012_codigo = a012_fk_codigo_marca)    "
                        "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente) "
                    "WHERE "
                        "a004_ativo = true  "
                    "ORDER BY "
                        "a004_codigo DESC";
        }
        else
        {
            busca = "SELECT "
                        "a004_codigo          "
                        ",a005_nome           "
                        ",a005_cpf            "
                        ",a011_marca_nome     "
                        ",a012_nome_veiculo   "
                        ",a004_placa_veiculo  "
                        ",a004_observacao     "
                    "FROM "
                        "a004_veiculos "
                        "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)  "
                        "JOIN a011_marcas ON (a012_codigo = a012_fk_codigo_marca)    "
                        "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente) "
                    "WHERE "
                        "a004_ativo = true  "
                    "ORDER BY "
                        "a004_codigo DESC";
        }
    }
    else
    {
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
            //Veiculo
            case 2:

                filtro_sql = "a012_nome_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            //Placa Veiculo
            case 3:

                filtro_sql = "a004_placa_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a004_codigo          "
                    ",a005_nome           "
                    ",a005_cpf            "
                    ",a011_marca_nome     "
                    ",a012_nome_veiculo   "
                    ",a004_placa_veiculo  "
                    ",a004_observacao     "
                "FROM "
                    "a004_veiculos "
                    "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)  "
                    "JOIN a011_marcas ON (a012_codigo = a012_fk_codigo_marca)    "
                    "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente) "
                "WHERE "
                    + filtro_sql +
                    "a004_ativo = true  "
                "ORDER BY "
                    "a004_codigo DESC";
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

            //definindo o tamanho das linhas
            ui->tw_selecionaVeiculo->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar veículos");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_filtrarVeiculo->clear();
    ui->txt_filtrarVeiculo->setFocus(); //posiciona o cursos no campo novamente
}

//botao filtrar veiculos
void frms_selecionaveiculo::on_btn_filtrarVeiculo_clicked()
{
    frms_selecionaveiculo::on_txt_filtrarVeiculo_returnPressed();
}

//Define o veiculo selecionado
void frms_selecionaveiculo::on_btn_confirmarVeiculo_clicked()
{
    //enviando nome e codigo do veiculo selecionado para o campo do modelo no agendaservicos
    //frm_agendaservicos fm_agendaveiculos(this, "", "" ,g_codigoVeiculo, g_nomeVeiculo);
    //fm_agendaveiculos.parent();


    frm_agendaservicos *fm_agendaveiculos = new frm_agendaservicos();
    fm_agendaveiculos->g_nome_veiculo = g_nomeVeiculo;
    fm_agendaveiculos->g_nome_veiculo = g_nomeVeiculo;
    //fm_agendaveiculos->show();

    //deletando ponteiro
    try
    {
        delete fm_agendaveiculos;
    }
    catch (...)
    {
        qDebug() << "__Erro ao deletar ponteiro: fm_agendaveiculos na tela de selecaoveiculo";
    }

    close();
}

