#include "frms_nv_veiculocliente.h"
#include "ui_frms_nv_veiculocliente.h"
#include "frm_gestaoclientes.h" //gestão dos clientes
#include "Classes/clcliente.h"
#include "Classes/clveiculo.h"
#include "frms_selecionaveiculo.h"

//pegando os valores para as chaves estrangeiras

frms_nv_veiculocliente::frms_nv_veiculocliente(QWidget *parent, QString c_codigo_marca
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
    QStringList cabecalho1={"ID", "Cliente", "CPF", "CEP", "Estado", "Cidade"
                           ,"Rua", "Nro. Casa", "Bairro", "Telefone"};

    ui->tw_nv_clientes->setHorizontalHeaderLabels( cabecalho1 );
    //definindo cor da linha ao ser selecionada
    ui->tw_nv_clientes->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

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

    //essa query deve filtrar com base no cliente cadastrado na tela novo cliente
    QSqlQuery query; //query para listar os colaboradores no table widget
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
                      "a005_ativo = true "
                  "ORDER BY "
                      "a005_codigo DESC");

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


    //**Estilizando layout da table widget VEICULOS**
    //configurando combo box veiculos
    ui->cb_ge_filtro->addItem("-");
    ui->cb_ge_filtro->addItem("Cliente");
    ui->cb_ge_filtro->addItem("Marca");
    ui->cb_ge_filtro->addItem("Modelo");
    ui->cb_ge_filtro->addItem("Ano");
    ui->cb_ge_filtro->addItem("Placa Veiculo");

    //definindo o tamanho das colunas
    ui->tw_ge_veiculos->setColumnCount(13); //define que o table widget terá duas colunas
    ui->tw_ge_veiculos->setColumnWidth(0, 40); //id cliente
    ui->tw_ge_veiculos->setColumnWidth(1, 150); //nome cliente

    //cabeçalhos do table widget
    QStringList cabecalho2={"Código", "Cliente", "Marca", "Modelo", "Motor", "Ano"
                           ,"Chassi", "Placa", "Cor", "Observação"};

    ui->tw_ge_veiculos->setHorizontalHeaderLabels(cabecalho2);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_veiculos->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_veiculos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_veiculos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_veiculos->verticalHeader()->setVisible(false);

    //recebendo dados marca
    ui->txt_nv_marca->setText( c_nome_marca );
    g_codigo_marca = c_codigo_marca;

    //recebendo dados modelo
    ui->txt_nv_modelo->setText( c_nome_modelo );
    g_codigo_modelo = c_codigo_modelo;

}//**FIM** construtor

frms_nv_veiculocliente::~frms_nv_veiculocliente() //**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//quando mudar alternar entre as tabs
void frms_nv_veiculocliente::on_tabWidget_currentChanged(int index)
{
    if( index == 1 ) //verifica a interface pelo index das tabs
    {
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
                          ",coalesce(a004_observacao, '(NENHUM)')  "
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

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 10
                                            , new QTableWidgetItem(query.value(10).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 11
                                            , new QTableWidgetItem(query.value(11).toString()));

                ui->tw_ge_veiculos->setItem(contlinhas
                                            , 12
                                            , new QTableWidgetItem(query.value(12).toString()));

                //definindo o tamanho das linhas
                ui->tw_ge_veiculos->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar veiculos");
        }
    }
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
    QString txt_filtro = ui->txt_nv_filtrar->text();

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
      cb_opc << "Cliente" << "CPF" << "Cidade";
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
    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//btn filtrar clientes
void frms_nv_veiculocliente::on_btn_nv_filtrar_clicked()
{
    frms_nv_veiculocliente::on_txt_nv_filtrar_returnPressed();
}

//bnt seleciona cliente/veiculo
void frms_nv_veiculocliente::on_btn_selecionaCliente_clicked()
{
    frms_selecionaveiculo *fmSelecionaVeiculo = new frms_selecionaveiculo();
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
    ClCliente cliente;
    ClVeiculo veiculo;

    //veiculo.marca_veiculo = ui->cb_nv_marca->currentText();
    //veiculo.modelo_veiculo = ui->cb_nv_modelo->currentText();
    veiculo.ano_veiculo = ui->txt_nv_ano->text();
    veiculo.motor_veiculo = ui->txt_nv_motor->text();
    veiculo.cor_veiculo = ui->txt_nv_cor->text();
    veiculo.placa_veiculo = ui->txt_nv_placa->text();
    veiculo.chassi_veiculo = ui->txt_nv_chassi->text();
    veiculo.observacao = ui->ptxt_nv_observacao->toPlainText();
    QString g_codigo_cliente = ui->txt_nv_codcliente->text();

    qDebug() << "Veiculo chassi: " << veiculo.chassi_veiculo;
    qDebug() << "Veiculo placa: " << veiculo.placa_veiculo;
    qDebug() << "Veiculo cor: " << veiculo.cor_veiculo;
    qDebug() << "Veiculo observação: " << veiculo.observacao;
    qDebug() << "Veiculo modelo: " << veiculo.modelo_veiculo;
    qDebug() << "Codigo cliente: " << g_codigo_cliente;

    veiculo_modelo = veiculo.modelo_veiculo;
    qDebug() << "Veiculo modelo Global: " << veiculo_modelo;

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
                     "VALUES('" +veiculo.motor_veiculo         + "'"
                           ",'" +veiculo.ano_veiculo           + "'"
                           ",'" +veiculo.chassi_veiculo        + "'"
                           ",'" +veiculo.placa_veiculo         + "'"
                           ",'" +veiculo.cor_veiculo           + "'"
                           ",'" +veiculo.observacao            + "'"
                           ",'" +cod_modelo                    + "'"
                           ",'" +g_codigo_cliente              + "') ");


    if( !query.exec( ) )
    {
        QMessageBox::critical(this, "ERRO", "Não foi possível salvar os dados do veiculo");
    }
    else
    {
        qDebug() << "_Dados salvos na tabela a004_veiculos";

        //limpando todos os campos
        //ui->cb_nv_marca->clear();
        //ui->cb_nv_modelo->clear();
        ui->txt_nv_ano->clear();
        ui->txt_nv_motor->clear();
        ui->txt_nv_cor->clear();
        ui->txt_nv_placa->clear();
        ui->txt_nv_chassi->clear();
        ui->ptxt_nv_observacao->clear();
    }
}


//**FUNÇÕES**//
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
                    "a012_nome_veiculo = '" +veiculo_modelo+ "')");

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
