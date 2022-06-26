#include "frms_nv_veiculocliente.h"
#include "ui_frms_nv_veiculocliente.h"
#include "frm_gestaoclientes.h" //gestão dos clientes
#include "Classes/clcliente.h"
#include "Classes/clveiculo.h"
#include "frms_selecionaveiculo.h"


frms_nv_veiculocliente::frms_nv_veiculocliente(QWidget *parent, QString c_codigo_cliente
                                                              , QString c_nome_marca
                                                              , QString c_codigo_modelo
                                                              , QString c_nome_modelo) :
    QDialog(parent),
    ui(new Ui::frms_nv_veiculocliente)
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

    ui->txt_nv_filtrar->setFocus();

    //**Estilizando layout da table widget CLIENTES**
    //configurando combo box clientes
    ui->cb_nv_filtro->addItem("-");
    ui->cb_nv_filtro->addItem("Cliente");
    ui->cb_nv_filtro->addItem("CPF");
    ui->cb_nv_filtro->addItem("Cidade");

    //definindo o tamanho das colunas
    ui->tw_nv_clientes->setColumnCount(10); //define que o table widget terá duas colunas
    ui->tw_nv_clientes->setColumnWidth(0, 40); //id cliente
    ui->tw_nv_clientes->setColumnWidth(1, 150); //nome cliente

    //cabeçalhos do table widget
    QStringList cabecalho1={"Código", "Cliente", "CPF", "CEP", "Estado", "Cidade"
                           ,"Rua", "Nro. Casa", "Bairro", "Telefone"};

    ui->tw_nv_clientes->setHorizontalHeaderLabels( cabecalho1 );
    //definindo cor da linha ao ser selecionada
    ui->tw_nv_clientes->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_nv_clientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_nv_clientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_nv_clientes->verticalHeader()->setVisible(false);


    //carregando os clientes no tablewidget
    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_nv_clientes );

    //inserir linhas dentro do table widget
    int contlinhas = 0;
    QString sql;


    sql = "SELECT "
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
              "a005_ativo = true "
          "ORDER BY "
              "a005_codigo DESC";

    QSqlQuery query;
    query.prepare( sql );

    if( query.exec() ) //verifica se ouve algum erro na execução da query
    {
        //enquanto a query tiver retornando next, insere linhas dentro do table widget
        while( query.next() )
        {
            //inserindo com contador de linhas, por index
            ui->tw_nv_clientes->insertRow(contlinhas);
            ui->tw_nv_clientes->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            ui->tw_nv_clientes->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));

            //definindo o tamanho das linhas
            ui->tw_nv_clientes->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar clientes");
    }

    //**RECEBENDO DADOS VEICULOS
    g_codigo_cliente = c_codigo_cliente;
    g_nome_marca = c_nome_marca;
    g_nome_modelo = c_nome_modelo;
    g_codigo_modelo = c_codigo_modelo;


    if( g_codigo_cliente != "" )
    {
        ui->txt_nv_codcliente->setText( g_codigo_cliente );
    }

    //recebendo dados marca
    ui->txt_nv_marca->setText( g_nome_marca );
    //recebendo dados modelo
    ui->txt_nv_modelo->setText( g_nome_modelo );

}//**FIM** construtor

frms_nv_veiculocliente::~frms_nv_veiculocliente() //**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//pegar item TW cliente
void frms_nv_veiculocliente::on_tw_nv_clientes_itemSelectionChanged()
{
    //pega a linha selecionada, no caso o cpf do cliente
    int id = ui->tw_nv_clientes->item(ui->tw_nv_clientes->currentRow()
                                                   , 0) ->text().toInt();

    //pega os dados da linha selecionada
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
                      "a005_codigo = '" +QString::number(id)+ "' ");

    //verifica se a query foi bem sucedida
    if( query.exec() )
    {
        query.first();

        ui->txt_nv_codcliente->setText( query.value(0).toString() );
    }
    else
    {
        qDebug() << "Erro ao pegar cod_cliente";
    }
}

//filtro clientes
void frms_nv_veiculocliente::on_txt_nv_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_nv_filtro->currentText();
    QString txt_filtro = ui->txt_nv_filtrar->text().toUpper();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Cliente" << "CPF" << "Cidade";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_nv_clientes );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_nv_filtrar->text() == "" )
    {
      if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
      {
          busca = "SELECT "
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
                       "a005_ativo = true "
                    "ORDER BY "
                       "a005_codigo DESC";
      }
      else
      {
          busca = "SELECT "
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
                       "a005_ativo = true "
                    "ORDER BY "
                       "a005_codigo DESC";
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
          //Cidade
          case 2:

              filtro_sql = "a005_cidade LIKE '%" +txt_filtro+ "%' ";
              break;
          default:
              qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
              break;
      }

      busca = "SELECT "
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
                   + filtro_sql +
                   "AND a005_ativo = true "
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
          ui->tw_nv_clientes->insertRow( contlinhas );
          ui->tw_nv_clientes->setItem(contlinhas
                                      , 0
                                      , new QTableWidgetItem(query.value(0).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 1
                                      , new QTableWidgetItem(query.value(1).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 2
                                      , new QTableWidgetItem(query.value(2).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 3
                                      , new QTableWidgetItem(query.value(3).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 4
                                      , new QTableWidgetItem(query.value(4).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 5
                                      , new QTableWidgetItem(query.value(5).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 6
                                      , new QTableWidgetItem(query.value(6).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 7
                                      , new QTableWidgetItem(query.value(7).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 8
                                      , new QTableWidgetItem(query.value(8).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 9
                                      , new QTableWidgetItem(query.value(9).toString()));

          //definindo o tamanho das linhas
          ui->tw_nv_clientes->setRowHeight(contlinhas, 20);
          contlinhas ++;
      }
    }
    else
    {
      QMessageBox::warning(this, "ERRO", "Erro ao filtrar clientes");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_nv_filtrar->clear();
    ui->txt_nv_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//btn filtrar clientes
void frms_nv_veiculocliente::on_btn_nv_filtrar_clicked()
{
    frms_nv_veiculocliente::on_txt_nv_filtrar_returnPressed();
}

//btn formulario de seleção de veiculos
void frms_nv_veiculocliente::on_btn_selecionaVeiculo_clicked()
{
    //fechando formulário após abrir o outro
    close();

    QString codigo_cliente = ui->txt_nv_codcliente->text();

    frms_selecionaveiculo *fmSelecionaVeiculo = new frms_selecionaveiculo( this, codigo_cliente );
    fmSelecionaVeiculo->exec();

    //deletando ponteiro
    try
    {
        delete fmSelecionaVeiculo;
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: fmSelecionaVeiculo na tela de agendaserviços";
    }
}

//salvar novo veiculo de cliente
void frms_nv_veiculocliente::on_btn_nv_salvar_clicked()
{
    QSqlQuery query;

    //veiculo.marca_veiculo = ui->cb_nv_marca->currentText();
    //veiculo.modelo_veiculo = ui->cb_nv_modelo->currentText();
    QString ano_veiculo = ui->txt_nv_ano->text().toUpper();
    QString motor_veiculo = ui->txt_nv_motor->text().toUpper();
    QString cor_veiculo = ui->txt_nv_cor->text().toUpper();
    QString placa_veiculo = ui->txt_nv_placa->text().toUpper();
    QString chassi_veiculo = ui->txt_nv_chassi->text().toUpper();
    QString observacao = ui->ptxt_nv_observacao->toPlainText().toUpper();
    QString codigo_modelo = g_codigo_modelo;
    QString codigo_cliente = ui->txt_nv_codcliente->text();

    QString cod_modelo = crudModelo();
    qDebug() << "codigo_modelo: " << cod_modelo;

    //pegar o cpf do cliente e o nome do modelo do veiculo
    //Inserindo em veiculos, as chaves estrangeiras(cpf e modelo) no sql imbutido
    query.prepare("INSERT INTO "
                       "a004_veiculos(a004_motor_veiculo "
                                     ",a004_ano_veiculo "
                                     ",a004_chassi_veiculo "
                                     ",a004_placa_veiculo "
                                     ",a004_cor_veiculo "
                                     ",a004_observacao "
                                     ",a004_fk_codigo_modelo "
                                     ",a004_fk_codigo_cliente) "
                     "VALUES('" +motor_veiculo         + "'"
                           ",'" +ano_veiculo           + "'"
                           ",'" +chassi_veiculo        + "'"
                           ",'" +placa_veiculo         + "'"
                           ",'" +cor_veiculo           + "'"
                           ",'" +observacao            + "'"
                           ",'" +codigo_modelo         + "'"
                           ",'" +codigo_cliente        + "') ");


    if( !query.exec( ) )
    {
        QMessageBox::critical(this, "ERRO", "Não foi possível salvar os dados do veiculo");
    }
    else
    {
        qDebug() << "_Dados salvos na tabela a004_veiculos";
        QMessageBox::information(this, "CADASTRADO", "Veículo cadastrado com sucesso");

        //limpando todos os campos
        ui->txt_nv_codcliente->clear();
        ui->txt_nv_marca->clear();
        ui->txt_nv_modelo->clear();
        ui->txt_nv_ano->clear();
        ui->txt_nv_motor->clear();
        ui->txt_nv_cor->clear();
        ui->txt_nv_placa->clear();
        ui->txt_nv_chassi->clear();
        ui->ptxt_nv_observacao->clear();
    }
}

//quando mudar alternar entre as tabs
void frms_nv_veiculocliente::on_tabWidget_currentChanged(int index)
{
    if( index == 1 ) //verifica a interface pelo index das tabs
    {
        conf_tw_ge_veiculos();

        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_ge_veiculos );
        //inserir linhas dentro do table widget
        int contlinhas = 0;
        //Remover os produtos do table widget
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a004_codigo                             "
                          ",a005_nome                              "
                          ",a011_marca_nome                        "
                          ",a012_nome_veiculo                      "
                          ",a004_motor_veiculo                     "
                          ",a004_ano_veiculo                       "
                          ",a004_chassi_veiculo                    "
                          ",a004_placa_Veiculo                     "
                          ",a004_cor_veiculo                       "
                          ",COALESCE(a004_observacao, '(NENHUM)')  "
                      "FROM "
                          "a004_veiculos "
                          "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente) "
                          "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)  "
                          "JOIN a011_marcas  ON (a011_codigo = a012_fk_codigo_marca)   "
                      "WHERE "
                          "a004_ativo = true "
                      "ORDER BY "
                          "a004_codigo DESC");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_ge_veiculos->insertRow( contlinhas );
                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 3
                                            , new QTableWidgetItem(query.value(3).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 4
                                            , new QTableWidgetItem(query.value(4).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 5
                                            , new QTableWidgetItem(query.value(5).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 6
                                            , new QTableWidgetItem(query.value(6).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 7
                                            , new QTableWidgetItem(query.value(7).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 8
                                            , new QTableWidgetItem(query.value(8).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 9
                                            , new QTableWidgetItem(query.value(9).toString()));

                //definindo o tamanho das linhas
                ui->tw_ge_veiculos->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar veiculos");
        }

        //**RECEBENDO DADOS VEICULOS
        if( g_codigo_cliente != "" )
        {
            ui->txt_nv_codcliente->setText( g_codigo_cliente );
        }

        //recebendo dados marca
        ui->txt_nv_marca->setText( g_nome_marca );

        //recebendo dados modelo
        ui->txt_nv_modelo->setText( g_nome_modelo );
        g_codigo_modelo;
    }
}

//pegar item tw_ge_veiculos
void frms_nv_veiculocliente::on_tw_ge_veiculos_itemSelectionChanged()
{
    //pega a linha selecionada
    int id = ui->tw_ge_veiculos->item(ui->tw_ge_veiculos->currentRow()
                                           , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a004_codigo                             "
                      ",a005_codigo                            "
                      ",a005_nome                              "
                      ",a011_marca_nome                        "
                      ",a012_nome_veiculo                      "
                      ",a004_motor_veiculo                     "
                      ",a004_ano_veiculo                       "
                      ",a004_chassi_veiculo                    "
                      ",a004_placa_Veiculo                     "
                      ",a004_cor_veiculo                       "
                      ",COALESCE(a004_observacao, '(NENHUM)')  "
                  "FROM "
                      "a004_veiculos "
                      "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente) "
                      "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)  "
                      "JOIN a011_marcas  ON (a011_codigo = a012_fk_codigo_marca)   "
                  "WHERE "
                      "a004_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() )
    {
        query.first();

        //considerar inserir um campo para o código
        ui->txt_ge_codcliente->setText(query.value(1).toString());
        ui->txt_ge_marca->setText(query.value(3).toString());
        ui->txt_ge_modelo->setText(query.value(4).toString());
        ui->txt_ge_motor->setText(query.value(5).toString());
        ui->txt_ge_ano->setText(query.value(6).toString());
        ui->txt_ge_chassi->setText(query.value(7).toString());
        ui->txt_ge_placa->setText(query.value(8).toString());
        ui->txt_ge_cor->setText(query.value(9).toString());
        ui->ptxt_ge_observacao->setPlainText(query.value(10).toString());
    }
}

//filtrar tela de gestão
void frms_nv_veiculocliente::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtro->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text().toUpper();

    QString busca;
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Cliente" << "Marca" << "Modelo"
           << "Ano" << "Placa Veiculo" << "Chassi Veiculo";

    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_nv_clientes );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_nv_filtrar->text() == "" )
    {
      if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
      {
          busca = "SELECT "
                      "a004_codigo                             "
                      ",a005_nome                              "
                      ",a011_marca_nome                        "
                      ",a012_nome_veiculo                      "
                      ",a004_motor_veiculo                     "
                      ",a004_ano_veiculo                       "
                      ",a004_chassi_veiculo                    "
                      ",a004_placa_Veiculo                     "
                      ",a004_cor_veiculo                       "
                      ",COALESCE(a004_observacao, '(NENHUM)')  "
                  "FROM "
                      "a004_veiculos "
                      "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente) "
                      "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)  "
                      "JOIN a011_marcas  ON (a011_codigo = a012_fk_codigo_marca)   "
                  "WHERE "
                      "a004_ativo = true "
                  "ORDER BY "
                      "a004_codigo DESC";
      }
      else
      {
          busca = "SELECT "
                      "a004_codigo                             "
                      ",a005_nome                              "
                      ",a011_marca_nome                        "
                      ",a012_nome_veiculo                      "
                      ",a004_motor_veiculo                     "
                      ",a004_ano_veiculo                       "
                      ",a004_chassi_veiculo                    "
                      ",a004_placa_Veiculo                     "
                      ",a004_cor_veiculo                       "
                      ",COALESCE(a004_observacao, '(NENHUM)')  "
                  "FROM "
                      "a004_veiculos "
                      "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente) "
                      "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)  "
                      "JOIN a011_marcas  ON (a011_codigo = a012_fk_codigo_marca)   "
                  "WHERE "
                      "a004_ativo = true "
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
          //Marca
          case 1:

              filtro_sql = "a011_marca_nome LIKE '%" +txt_filtro+ "%' ";
              break;
          //Modelo
          case 2:

              filtro_sql = "a012_nome_veiculo LIKE '%" +txt_filtro+ "%' ";
              break;
          //Ano
          case 3:

              filtro_sql = "a004_ano_veiculo LIKE '%" +txt_filtro+ "%' ";
              break;
          //Placa
          case 4:

              filtro_sql = "a004_placa_Veiculo LIKE '%" +txt_filtro+ "%' ";
              break;
          //Chassi
          case 5:

              filtro_sql = "a004_chassi_veiculo LIKE '%" +txt_filtro+ "%' ";
              break;
          default:
              qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
              break;
      }

      busca = "SELECT "
                  "a004_codigo                             "
                  ",a005_nome                              "
                  ",a011_marca_nome                        "
                  ",a012_nome_veiculo                      "
                  ",a004_motor_veiculo                     "
                  ",a004_ano_veiculo                       "
                  ",a004_chassi_veiculo                    "
                  ",a004_placa_Veiculo                     "
                  ",a004_cor_veiculo                       "
                  ",COALESCE(a004_observacao, '(NENHUM)')  "
              "FROM "
                  "a004_veiculos "
                  "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente) "
                  "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo)  "
                  "JOIN a011_marcas  ON (a011_codigo = a012_fk_codigo_marca)   "
              "WHERE "
                  + filtro_sql +
                  "AND a004_ativo = true "
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
          ui->tw_nv_clientes->insertRow( contlinhas );
          ui->tw_nv_clientes->setItem(contlinhas
                                      , 0
                                      , new QTableWidgetItem(query.value(0).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 1
                                      , new QTableWidgetItem(query.value(1).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 2
                                      , new QTableWidgetItem(query.value(2).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 3
                                      , new QTableWidgetItem(query.value(3).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 4
                                      , new QTableWidgetItem(query.value(4).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 5
                                      , new QTableWidgetItem(query.value(5).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 6
                                      , new QTableWidgetItem(query.value(6).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 7
                                      , new QTableWidgetItem(query.value(7).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 8
                                      , new QTableWidgetItem(query.value(8).toString()));

          ui->tw_nv_clientes->setItem(contlinhas
                                      , 9
                                      , new QTableWidgetItem(query.value(9).toString()));

          //definindo o tamanho das linhas
          ui->tw_nv_clientes->setRowHeight(contlinhas, 20);
          contlinhas ++;
      }
    }
    else
    {
      QMessageBox::warning(this, "ERRO", "Erro ao filtrar veículos");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//btn filtrar gestao veiculos
void frms_nv_veiculocliente::on_btn_ge_filtrar_clicked()
{
    frms_nv_veiculocliente::on_txt_ge_filtrar_returnPressed();
}

//btn edição, salvar alteração no fornecedor
void frms_nv_veiculocliente::on_btn_ge_salvar_clicked()
{
    if( ui->tw_ge_veiculos->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um veículo");
        return;
    }

    QString id = ui->tw_ge_veiculos->item(ui->tw_ge_veiculos
                                               ->currentRow(),0)->text();
    QSqlQuery query;

    QString motor_veiculo = ui->txt_nv_motor->text().toUpper();
    QString ano_veiculo = ui->txt_nv_ano->text().toUpper();
    QString cor_veiculo = ui->txt_nv_cor->text().toUpper();
    QString placa_veiculo = ui->txt_nv_placa->text().toUpper();
    QString chassi_veiculo = ui->txt_nv_chassi->text().toUpper();
    QString observacao = ui->ptxt_nv_observacao->toPlainText().toUpper();
    QString codigo_modelo = g_codigo_modelo;
    QString codigo_cliente = ui->txt_nv_codcliente->text();

    query.prepare("UPDATE "
                    "a004_veiculos "
                  "SET "
                    "a004_motor_veiculo      ='" +motor_veiculo   + "'"
                    ",a004_ano_veiculo       ='" +ano_veiculo     + "'"
                    ",a004_chassi_veiculo    ='" +chassi_veiculo  + "'"
                    ",a004_placa_veiculo     ='" +placa_veiculo   + "'"
                    ",a004_cor_veiculo       ='" +cor_veiculo     + "'"
                    ",a004_observacao        ='" +observacao      + "'"
                    ",a004_fk_codigo_modelo  ='" +codigo_modelo   + "'"
                    ",a004_fk_codigo_cliente ='" +codigo_cliente  + "'"
                  "WHERE "
                    "a004_codigo ='" +id+ "'");

    if( !query.exec( ) )
    {
        QMessageBox::critical(this, "ERRO", "Não foi possível salvar os dados do veiculo");
    }
    else
    {
        //pega a linha que está selecionada
        int linha = ui->tw_ge_veiculos->currentRow();
        //atualizando o table widget com o novo registro
        ui->tw_ge_veiculos->item(linha, 1)->setText( motor_veiculo );
        ui->tw_ge_veiculos->item(linha, 2)->setText( ano_veiculo );
        ui->tw_ge_veiculos->item(linha, 3)->setText( chassi_veiculo );
        ui->tw_ge_veiculos->item(linha, 4)->setText( placa_veiculo );
        ui->tw_ge_veiculos->item(linha, 5)->setText( cor_veiculo );
        ui->tw_ge_veiculos->item(linha, 6)->setText( observacao );
        ui->tw_ge_veiculos->item(linha, 7)->setText( codigo_modelo );
        ui->tw_ge_veiculos->item(linha, 8)->setText( codigo_cliente );

        QMessageBox::information(this, "Atualizado", "Veículo atualizado com sucesso!");

        //limpando todos os campos
        ui->txt_ge_codcliente->clear();
        ui->txt_ge_marca->clear();
        ui->txt_ge_modelo->clear();
        ui->txt_ge_ano->clear();
        ui->txt_ge_motor->clear();
        ui->txt_ge_cor->clear();
        ui->txt_ge_placa->clear();
        ui->txt_ge_chassi->clear();
        ui->ptxt_ge_observacao->clear();
    }
}

//btn excluir veículo
void frms_nv_veiculocliente::on_btn_ge_excluir_clicked()
{
    if( ui->tw_ge_veiculos->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um veículo");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão do veículo?"
                                      ,QMessageBox::Yes|QMessageBox::No);

    if( opc == QMessageBox::Yes )
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_ge_veiculos->currentRow();
        QString id = ui->tw_ge_veiculos->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a004_veiculos "
                      "SET "
                        "a004_ativo = false "
                      "WHERE "
                        "a004_codigo ='" +id+ "'");

        if( query.exec() ) //executa a query
        {
            ui->tw_ge_veiculos->removeRow( linha );
            QMessageBox::information(this, "EXCLUÍDO", "Fornecedor excluído com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir veículo");
        }
    }
}


//**FUNÇÕES**//
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 06/06/2022                                                                           |
 * Propósito: Essa série de funções servem para configurar os Table widget                    |
 * Chamada:                                                                                   |
 *--------------------------------------------------------------------------------------------
 */
//configura  tw_ge_veiculos
void frms_nv_veiculocliente::conf_tw_ge_veiculos()
{
    //**Estilizando layout da table widget VEICULOS**
    //configurando combo box veiculos
    ui->cb_ge_filtro->addItem("-");
    ui->cb_ge_filtro->addItem("Cliente");
    ui->cb_ge_filtro->addItem("Marca");
    ui->cb_ge_filtro->addItem("Modelo");
    ui->cb_ge_filtro->addItem("Ano");
    ui->cb_ge_filtro->addItem("Placa Veiculo");
    ui->cb_ge_filtro->addItem("Chassi Veiculo");

    //definindo o tamanho das colunas
    ui->tw_ge_veiculos->setColumnCount(10); //define que o table widget terá duas colunas
    ui->tw_ge_veiculos->setColumnWidth(0, 40); //id cliente
    ui->tw_ge_veiculos->setColumnWidth(1, 150); //nome cliente

    //cabeçalhos do table widget
    QStringList cabecalho2={"Código", "Cliente", "Marca", "Modelo", "Motor", "Ano"
                           ,"Chassi", "Placa", "Cor", "Observação"};

    ui->tw_ge_veiculos->setHorizontalHeaderLabels(cabecalho2);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_veiculos->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_veiculos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_veiculos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_veiculos->verticalHeader()->setVisible(false);
}

/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 21/04/2022                                                                           |
 * Propósito: preencher os combo box com os dados a serem exibidos                            |
 * Chamada: construtor da classe                                                              |
 *--------------------------------------------------------------------------------------------
 */
void frms_nv_veiculocliente::prepararCB()
{
    QSqlQuery query;
    query.prepare("SELECT "
                    "a011_codigo     "
                    "a011_marca_nome "
                  "FROM "
                    "a011_marcas "
                  "ORDER BY "
                    "a011_marca_nome ASC ");

    if( !query.exec() )
    {
        qDebug() << "_Erro  ao realizar consulta: prepararCB";
    }
    else
    {
        //pegar o numero de colunas
        //const int columnCount = query.record().count();
        //qDebug() << "_O numero de colunas da tabela é: " << columnCount;

        //codigo_marca = query.record().indexOf("a011_codigo");
        //int modelo = query.record().indexOf("a012_nome_veiculo");
        //int marca = query.record().indexOf("a011_marca_nome");

        while( query.next() )
        {
            g_codigo_marca =  query.value(0).toString();
            //ui->cb_nv_marca->addItem( query.value(1).toString() );
            //ui->cb_nv_modelo->addItem( query.value(modelo).toString() );
        }
    }

    qDebug() << "_Código marca: " << g_codigo_marca;

    //cbFiltro( codigo_marca );

    //Os modelos e seus dados devem ser filtrados de acordo com as marcas
    //talvez seja necessário fazer outra função, que será chamada após essa no construtor

}
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 21/04/2022                                                                           |
 * Propósito: filtrar os combo box pela marca e modelo dos veiculos                           |
 * Chamada: na função prepararCB()                                                            |
 * Status: NÃO FUNCIONA AINDA                                                                 |
 *--------------------------------------------------------------------------------------------
 */
void frms_nv_veiculocliente::cbFiltro( const QString &codigo_marca )
{
   //depurando bloco
    qDebug() << "_Entrou na condição, função cbFiltro()";

    QSqlQuery query;
    query.prepare("SELECT "
                       "a012_nome_veiculo "
                  "FROM "
                       "a012_modelos "
                       "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                  "WHERE "
                       "a011_codigo = '" + codigo_marca   + "'"
                       "AND a012_ativo = true "
                  "ORDER BY "
                       "a012_nome_veiculo ASC");

    if( !query.exec() )
    {
        qDebug() << "_Erro  ao realizar consulta: cbFiltro";
    }
    else
    {
        //int modelo = query.record().indexOf("a012_nome_veiculo");

        while( query.next() )
        {
            //logica para adicionar itens no combobox, verificar e testar muito
            //ui->cb_nv_modelo->addItem( query.value(0).toString() );
        }
    }
}


//função que pega o modelo do veiculo e o cpf do cliente
QString frms_nv_veiculocliente::crudModelo()
{
    QString cod_modelo;
    QSqlQuery query;
    //pegar o nome do modelo do veiculo
    //Inserindo em veiculos, as chaves estrangeiras(cpf e modelo) no sql imbutido
    query.prepare("SELECT "
                    "a012_codigo "
                  "FROM "
                    "a012_modelos "
                  "WHERE "
                    "a012_nome_veiculo = '" +g_veiculo_modelo+ "')");

    if( query.exec() )
    {
        //QString cod_modelo = QString::number(query.record().indexOf("a012_codigo"));
        //query.first();

        while( query.next() )
        {
            query.first();
            qDebug() << query.value(0).toString();
            cod_modelo = QString::number(query.record().indexOf("a012_codigo"));
            //cod_modelo = query.value(0).toString();
        }
    }

    return cod_modelo;
}

