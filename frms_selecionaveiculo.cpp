#include "frms_selecionaveiculo.h"
#include "ui_frms_selecionaveiculo.h"
#include "frms_nv_veiculocliente.h"

//QString g_nomeVeiculo;
//QString g_codigoVeiculo;

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

    //recebendo codigo do cliente
    g_codigo_cliente = c_codigoCliente;

    //recebendo dados do agendaserviços c_codigo_cliente é recebido do agendaservicos
    //deixa o botão da validação do cnpj invisivel
    ui->txt_filtrarVeiculo->setFocus();

    //configurando combo box
    ui->cb_filtrar->addItem("-");
    ui->cb_filtrar->addItem("Marca");
    ui->cb_filtrar->addItem("Modelo");

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_selecionaVeiculo->setColumnCount(3);
    ui->tw_selecionaVeiculo->setColumnWidth(0, 40);
    ui->tw_selecionaVeiculo->setColumnWidth(1, 150);
    ui->tw_selecionaVeiculo->setColumnWidth(2, 150);

    //cabeçalhos do table widget
    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Marca", "Modelo"};

    ui->tw_selecionaVeiculo->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_selecionaVeiculo->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

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
                      "a012_codigo          "
                      ",a011_marca_nome     "
                      ",a012_nome_veiculo   "
                  "FROM "
                      "a012_modelos "
                      "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                  "WHERE "
                      "a011_ativo = true  "
                      "AND a012_ativo = true  ");

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

            //definindo o tamanho das linhas
            ui->tw_selecionaVeiculo->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar Marcas/Modelos");
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
                      "a012_codigo          "
                      ",a011_marca_nome     "
                      ",a012_nome_veiculo   "
                  "FROM "
                      "a012_modelos "
                      "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                  "WHERE "
                      "a012_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        g_codigoVeiculo = query.value(0).toString();
        g_nomeMarca = query.value(1).toString();
        g_nomeVeiculo = query.value(2).toString();

        qDebug() << "Código Veículo: " << g_codigoVeiculo;
        qDebug() << "Marca Veículo: " << g_nomeMarca;
        qDebug() << "Modelo Veículo: " << g_nomeVeiculo;
    }

}

//filtrando veiculos
void frms_selecionaveiculo::on_txt_filtrarVeiculo_returnPressed()
{
    QString cb_filtro = ui->cb_filtrar->currentText();
    QString txt_filtro = ui->txt_filtrarVeiculo->text();

    QString busca;
    QString filtro_sql;

    QStringList cb_opc;
    cb_opc << "Marca" << "Modelo";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_selecionaVeiculo );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_filtrarVeiculo->text() == "" )
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
                        "a011_ativo = true      "
                        "AND a012_ativo = true  ";
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
                        "a011_ativo = true      "
                        "AND a012_ativo = true  ";
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
                    "AND a011_ativo = true "
                    "AND a012_ativo = true "
                "ORDER BY "
                    "a012_nome_veiculo ASC";
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
    //frm_agendaservicos *fm_agendaservicos = new frm_agendaservicos(this, "", "" ,g_codigoVeiculo, g_nomeVeiculo);
    //fm_agendaveiculos->exec();

    //fm_agendaservicos->setModal(true);
    //fm_agendaservicos->show();

    //TESTES SIGNAL
    //frm_agendaservicos *fm_agendaservicos = new frm_agendaservicos();

    //connect(this, SIGNAL( sendData( QString ) ), fm_agendaservicos, SLOT( receiveData( QString ) ) );

    //emit sendData( g_nomeVeiculo );


    frms_nv_veiculocliente *fm_nv_veiculocliente = new frms_nv_veiculocliente( this
                                                                              ,g_codigo_cliente
                                                                              ,g_nomeMarca
                                                                              ,g_codigoVeiculo
                                                                              ,g_nomeVeiculo );
    fm_nv_veiculocliente->close();
    fm_nv_veiculocliente->exec();


    //deletando ponteiro
    try
    {
        delete fm_nv_veiculocliente;
    }
    catch (...)
    {
        qDebug() << "__Falha ao deletar ponteiro: fm_nv_veiculocliente na tela de selecaoveiculo";
    }

    close();
}

//**FUNÇÕES**
