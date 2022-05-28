#include "frm_agendaservicos.h"
#include "ui_frm_agendaservicos.h"
#include "frms_selecionacliente.h" //formulario de seleção de clientes


frm_agendaservicos::frm_agendaservicos(QWidget *parent, QString c_codigo_cliente
                                                      , QString c_nome_cliente
                                                      , QString c_codigo_veiculo
                                                      , QString c_nome_veiculo) :
    QDialog(parent),
    ui(new Ui::frm_agendaservicos)
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

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //configurando combo box
    ui->cb_ge_filtrar->addItem("-");
    ui->cb_ge_filtrar->addItem("Cliente");
    ui->cb_ge_filtrar->addItem("Modelo Veículo");
    ui->cb_ge_filtrar->addItem("Placa Veículo");
    ui->cb_ge_filtrar->addItem("Serviço");
    ui->cb_ge_filtrar->addItem("Pendente");
    ui->cb_ge_filtrar->addItem("Realizado");
    ui->cb_ge_filtrar->addItem("Cancelado");

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_listaservicos->setColumnCount(9);
    ui->tw_listaservicos->setColumnWidth(0, 40);
    ui->tw_listaservicos->setColumnWidth(1, 200);

    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Cliente", "Modelo Veículo", "Placa Veículo"
                           ,"Data", "Hora", "Serviço", "Observação", "Status"};

    ui->tw_listaservicos->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_listaservicos->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listaservicos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listaservicos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listaservicos->verticalHeader()->setVisible(false);

    //recebendo dados cliente
    ui->txt_nomeCliente->setText( c_nome_cliente );
    g_codigo_cliente = c_codigo_cliente;

    //recebendo dados veiculo
    ui->txt_nomeVeiculo->setText( c_nome_veiculo );
    g_codigo_veiculo = c_codigo_veiculo;

}

frm_agendaservicos::~frm_agendaservicos()//**INICIO** destrutor
{
    con.fechar();
    delete ui;
}

//abre formulário de seleção de clientes
void frm_agendaservicos::on_btn_selecionaCliente_clicked() //frms de seleção de clientes
{
    frms_selecionacliente *fmSelecionaCliente = new frms_selecionacliente();
    fmSelecionaCliente->exec();

    //deletando ponteiro
    try
    {
        delete fmSelecionaCliente;
    }
    catch (...)
    {
        qDebug() << "__Falha ao deletar ponteiro: fmSelecionaCliente na tela de agendaserviços";
    }
}

//btn agendar serviço
void frm_agendaservicos::on_btn_agendarServico_clicked()
{
    if( ui->txt_nomeCliente->text() == "" || ui->txt_nomeCliente->text() == ""
                                          || g_codigo_cliente == ""
                                          || g_codigo_veiculo == "" )
    {
        QMessageBox::information(this, "Erro", "Os campos com os dados do cliente estão vázios");
    }
    else
    {
        //QString aux;

        QString data = ui->de_data->text();
        QString hora = ui->de_hora->text() + ":00";
        QString servico = ui->txt_tipoServico->text();
        QString observacao = ui->txt_tipoServico->text();
        QString status = "Pendente";
        QString codigo_cliente = g_codigo_cliente;
        QString codigo_veiculo = g_codigo_veiculo;

        QString verificaData = QDate::currentDate().toString("dd/MM/yyyy");
        //QString verificaHora = QTime::currentTime().toString("hh:mm:ss");

        //convertendo para ver se a data e hora não são inválidas
        QDate converteData = QDate::fromString(data,"dd/MM/yyyy");
        //QDate converteHora = QDate::fromString(hora,"hh:mm:ss");
        QDate converteVerificaData = QDate::fromString(verificaData,"dd/MM/yyyy");
        //QDate converteVerificahora = QDate::fromString(verificaHora,"hh:mm:ss");

        if( converteData < converteVerificaData )
        {
            QMessageBox::warning(this, "AVISO", "Data inválida");
        }
        else
        {
            qDebug() << "Data: " + data;
            qDebug() << "Hora: " + hora;
            qDebug() << "Serviço: " + servico;
            qDebug() << "Observação: " + observacao;
            qDebug() << "Codigo cliente: " + g_codigo_cliente;
            qDebug() << "Codigo cliente: " + g_codigo_veiculo;

            QSqlQuery query;

            query.prepare("INSERT INTO "
                            "a009_agenda_servicos(a009_data                "
                                                 ",a009_hora               "
                                                 ",a009_servico            "
                                                 ",a009_observacao         "
                                                 ",a009_status             "
                                                 ",a009_fk_codigo_cliente  "
                                                 ",a009_fk_codigo_veiculo) "
                          "VALUES('" +data           + "'"
                                ",'" +hora           + "'"
                                ",'" +servico        + "'"
                                ",'" +observacao     + "'"
                                ",'" +status         + "'"
                                ",'" +codigo_cliente + "'"
                                ",'" +codigo_veiculo + "')");

            if( !query.exec() )
            {
                QMessageBox::warning(this, "ERRO", "Erro ao agendar o serviço");
            }
            else
            {
                ui->txt_nomeCliente->clear();
                ui->txt_nomeVeiculo->clear();
                ui->txt_tipoServico->clear();
                ui->Ptxt_observacao->clear();

                QMessageBox::warning(this, "AVISO", "Serviço agendado com sucesso");
            }
        }
    }

}

//alternar entre os tab widgets
void frm_agendaservicos::on_tabWidget_currentChanged(int index)
{
    if( index == 1 ) //verifica a interface pelo index das tabs
    {
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_listaservicos );
        //inserir linhas dentro do table widget
        int contlinhas = 0;
        //Remover os produtos do table widget
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a009_codigo           "
                          ",a005_nome            "
                          ",a012_nome_veiculo    "
                          ",a004_placa_veiculo   "
                          ",a009_data            "
                          ",a009_hora            "
                          ",a009_servico         "
                          ",a009_observacao      "
                          ",a009_status          "
                      "FROM "
                          "a009_agenda_servicos "
                          "JOIN a005_cliente ON (a005_codigo = a009_fk_codigo_cliente)  "
                          "JOIN a004_veiculos ON (a004_codigo = a009_fk_codigo_veiculo) "
                          "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                      "WHERE "
                        "a009_status = 'Pendente' "
                        "AND a009_ativo = true    "
                      "ORDER BY "
                          "a009_codigo DESC");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_listaservicos->insertRow( contlinhas );
                ui->tw_listaservicos->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_listaservicos->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_listaservicos->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                ui->tw_listaservicos->setItem(contlinhas
                                            , 3
                                            , new QTableWidgetItem(query.value(3).toString()));

                ui->tw_listaservicos->setItem(contlinhas
                                            , 4
                                            , new QTableWidgetItem(query.value(4).toString()));

                ui->tw_listaservicos->setItem(contlinhas
                                            , 5
                                            , new QTableWidgetItem(query.value(5).toString()));

                ui->tw_listaservicos->setItem(contlinhas
                                            , 6
                                            , new QTableWidgetItem(query.value(6).toString()));

                ui->tw_listaservicos->setItem(contlinhas
                                            , 7
                                            , new QTableWidgetItem(query.value(7).toString()));

                ui->tw_listaservicos->setItem(contlinhas
                                            , 8
                                            , new QTableWidgetItem(query.value(8).toString()));

                //definindo o tamanho das linhas
                ui->tw_listaservicos->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar serviços");
        }
    }
}

//pega linha do tw
void frm_agendaservicos::on_tw_listaservicos_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_listaservicos->item(ui->tw_listaservicos->currentRow()
                                        , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      ",a005_nome           "
                      ",a012_nome_veiculo   "
                      ",a004_placa_veiculo  "
                      ",a009_data           "
                      ",a009_hora           "
                      ",a009_servico        "
                      ",a009_observacao     "
                      ",a009_status         "
                  "FROM "
                    "a009_agenda_servicos "
                    "JOIN a005_cliente ON (a005_codigo = a009_fk_codigo_cliente)  "
                    "JOIN a004_veiculos ON (a004_codigo = a009_fk_codigo_veiculo) "
                    "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                  "WHERE "
                    "a009_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro

        //considerar inserir um campo para o código
        ui->txt_ge_nomeCliente->setText(query.value(0).toString());
        ui->txt_ge_nomeVeiculo->setText(query.value(1).toString());
        ui->txt_ge_tipoServico->setText(query.value(5).toString());
        //ui->Ptxt_ge_observacao->setText(query.value(6).toString());
    }
}

//filtrar
void frm_agendaservicos::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Cliente" << "Modelo Veículo" << "Placa Veículo"
           << "Serviço" << "Pendente" << "Realizado" << "Cancelado";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_listaservicos );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_ge_filtrar->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a009_codigo           "
                        ",a005_nome            "
                        ",a012_nome_veiculo    "
                        ",a004_placa_veiculo   "
                        ",a009_data            "
                        ",a009_hora            "
                        ",a009_servico         "
                        ",a009_observacao      "
                        ",a009_status          "
                    "FROM "
                        "a009_agenda_servicos "
                        "JOIN a005_cliente ON (a005_codigo = a009_fk_codigo_cliente)  "
                        "JOIN a004_veiculos ON (a004_codigo = a009_fk_codigo_veiculo) "
                        "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                    "WHERE "
                      "a009_status = 'Pendente' "
                      "AND a009_ativo = true    "
                    "ORDER BY "
                        "a009_codigo DESC";
        }
        else
        {
            busca = "SELECT "
                        "a009_codigo           "
                        ",a005_nome            "
                        ",a012_nome_veiculo    "
                        ",a004_placa_veiculo   "
                        ",a009_data            "
                        ",a009_hora            "
                        ",a009_servico         "
                        ",a009_observacao      "
                        ",a009_status          "
                    "FROM "
                        "a009_agenda_servicos "
                        "JOIN a005_cliente ON (a005_codigo = a009_fk_codigo_cliente)  "
                        "JOIN a004_veiculos ON (a004_codigo = a009_fk_codigo_veiculo) "
                        "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                    "WHERE "
                      "a009_status = 'Pendente' "
                      "AND a009_ativo = true    "
                    "ORDER BY "
                        "a009_codigo DESC";
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
            //Modelo Veículo
            case 1:

                filtro_sql = "a012_nome_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            //Placa Veículo
            case 2:

                filtro_sql = "a004_placa_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            //Serviço
            case 3:

                filtro_sql = "a009_servico LIKE '%" +txt_filtro+ "%' ";
                break;
            //cancelado
            case 4:

                filtro_sql = "a009_status LIKE 'Pendente' ";
                break;
            //Realizado
            case 5:

                filtro_sql = "a009_status LIKE 'Realizado' ";
                break;
            //Cancelado
            case 6:

                filtro_sql = "a009_status LIKE 'Cancelado' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a009_codigo           "
                    ",a005_nome            "
                    ",a012_nome_veiculo    "
                    ",a004_placa_veiculo   "
                    ",a009_data            "
                    ",a009_hora            "
                    ",a009_servico         "
                    ",a009_observacao      "
                    ",a009_status          "
                "FROM "
                    "a009_agenda_servicos "
                    "JOIN a005_cliente ON (a005_codigo = a009_fk_codigo_cliente)  "
                    "JOIN a004_veiculos ON (a004_codigo = a009_fk_codigo_veiculo) "
                    "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)   "
                "WHERE "
                  + filtro_sql +
                  "AND a009_ativo = true    "
                "ORDER BY "
                    "a009_codigo DESC";
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
            ui->tw_listaservicos->insertRow( contlinhas );
            ui->tw_listaservicos->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_listaservicos->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            //definindo o tamanho das linhas
            ui->tw_listaservicos->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar serviços");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//btn filtrar
void frm_agendaservicos::on_btn_ge_filtrar_clicked()
{
    frm_agendaservicos::on_txt_ge_filtrar_returnPressed();
}

//edição, salvar alteração no serviço
void frm_agendaservicos::on_btn_ge_salvar_2_clicked()
{
    if( ui->tw_listaservicos->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um serviço");
        return;
    }

    QString id = ui->tw_listaservicos->item(ui->tw_listaservicos
                                                   ->currentRow(),0)->text();
    QSqlQuery query;

    //estudar retringir cnpj
    QString nome_cliente = ui->txt_ge_nomeCliente->text();
    QString nome_veiculo = ui->txt_ge_nomeVeiculo->text();
    QString servico = ui->txt_ge_tipoServico->text();
    QString observacao = ui->Ptxt_ge_observacao->text();

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
        int linha=ui->tw_listaservicos->currentRow();
        //atualizando o table widget com o novo registro
        ui->tw_listaservicos->item(linha, 1)->setText( razao_social );
        ui->tw_listaservicos->item(linha, 2)->setText( nome_fantasia );
        ui->tw_listaservicos->item(linha, 3)->setText( cnpj );
        ui->tw_listaservicos->item(linha, 4)->setText( estado );
        ui->tw_listaservicos->item(linha, 5)->setText( cidade );
        ui->tw_listaservicos->item(linha, 6)->setText( rua );
        ui->tw_listaservicos->item(linha, 7)->setText( numero_estabelecimento );
        ui->tw_listaservicos->item(linha, 8)->setText( bairro );
        ui->tw_listaservicos->item(linha, 9)->setText( porte_empresa );
        ui->tw_listaservicos->item(linha, 10)->setText( ocupacao_empresa );
        ui->tw_listaservicos->item(linha, 11)->setText( telefone1 );
        ui->tw_listaservicos->item(linha, 12)->setText( telefone2 );

        QMessageBox::information(this, "Atualizado", "Serviço atualizado com sucesso!");

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
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar serviço");
    }
}

