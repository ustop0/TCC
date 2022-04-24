#include "frms_nv_veiculocliente.h"
#include "ui_frms_nv_veiculocliente.h"
#include "frm_gestaoclientes.h" //gestão dos clientes
#include "Classes/clcliente.h"
#include "Classes/clveiculo.h"

frms_nv_veiculocliente::frms_nv_veiculocliente(QWidget *parent) :
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

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_nv_listaveiculosclientes->setColumnCount(9); //define que o table widget terá duas colunas
    ui->tw_nv_listaveiculosclientes->setColumnWidth(0, 150); //id colaborador
    ui->tw_nv_listaveiculosclientes->setColumnWidth(1, 220); //nome colaborador

    //cabeçalhos do table widget
    QStringList cabecalhos={"ID", "Nome", "CPF", "CEP", "Estado"
                           ,"Cidade", "Rua", "Bairro", "Telefone"};

    ui->tw_nv_listaveiculosclientes->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_nv_listaveiculosclientes->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_nv_listaveiculosclientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_nv_listaveiculosclientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_nv_listaveiculosclientes->verticalHeader()->setVisible(false);


    //carregando os clientes no tablewidget
    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_nv_listaveiculosclientes );

    //inserir linhas dentro do table widget
    int contlinhas=0;

    //essa query deve filtrar com base no cliente cadastrado na tela novo cliente
    QSqlQuery query; //query para listar os colaboradores no table widget
    query.prepare("SELECT "
                      "a005_codigo "
                      ",a005_nome "
                      ",a005_cpf "
                      ",a005_cep "
                      ",a005_estado "
                      ",a005_cidade "
                      ",a005_rua "
                      ",a005_bairro "
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
            ui->tw_nv_listaveiculosclientes->insertRow(contlinhas);
            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_nv_listaveiculosclientes->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            //definindo o tamanho das linhas
            ui->tw_nv_listaveiculosclientes->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar clientes");
    }

    //chamando função que preenche combo box
    prepararCB();

}//**FIM** construtor

frms_nv_veiculocliente::~frms_nv_veiculocliente() //**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados

    delete ui;
}


//pegar dados do cliente selecionado
void frms_nv_veiculocliente::on_tw_nv_listaveiculosclientes_itemSelectionChanged()
{
    ClCliente cliente;

    //pega a linha selecionada, no caso o cpf do cliente
    int cpf = ui->tw_nv_listaveiculosclientes->item(ui->tw_nv_listaveiculosclientes->currentRow()
                                                   , 2) ->text().toInt();

    //armazena o cpf selecionado pelo usuário no atributo cpf da classe clientes
    cliente.cpf = QString::number(cpf);
}

void frms_nv_veiculocliente::on_btn_salvarveiculo_clicked() //salvar novo veiculo de cliente
{
    QSqlQuery query;
    ClCliente cliente;
    ClVeiculo veiculo;

    //devo pegar
    veiculo.marca_veiculo = ui->cb_nv_marca->currentText();
    veiculo.modelo_veiculo = ui->cb_nv_modelo->currentText();
    veiculo.ano_veiculo = ui->cb_nv_ano->currentText();
    veiculo.motor_veiculo = ui->cb_nv_motor->currentText();
    veiculo.cor_veiculo = ui->txt_nv_cor->text();
    veiculo.placa_veiculo = ui->txt_nv_placa->text();
    veiculo.chassi_veiculo = ui->txt_nv_chassi->text();
    veiculo.observacao = ui->txt2_nv_observacao->currentText();

    //pegar o cpf do cliete e o nome do modelo do veiculo
    //Inserindo em veiculos, as chaves estrangeiras(cpf e modelo) no sql imbutido
    query.prepare("INSERT INTO "
                    "a004_veiculos(a004_chassi_veiculo "
                                  ",a004_placa_veiculo "
                                  ",a004_cor_veiculo "
                                  ",a004_observacao "
                                  ",a004_fk_codigo_modelo "
                                  ",a004_fk_codigo_cliente "
                  "VALUES('" +veiculo.chassi_veiculo           + "'"
                        ",'" +veiculo.placa_veiculo            + "'"
                        ",'" +veiculo.cor_veiculo              + "'"
                        ",'" +veiculo.observacao               + "'"
                        ",(SELECT "
                            "a012_codigo "
                          "FROM "
                            "a012_modelos "
                          "WHERE "
                            "a012_nome_veiculo = '" +veiculo.modelo_veiculo+ "') "
                        ",(SELECT "
                            "a005_codigo "
                           "FROM "
                            "a005_cliente "
                           "WHERE "
                            "a005_cpf = '" +cliente.cpf+ "')");

    //ddepurando o cpf e o modelo do veiculos das constrains
    qDebug() << "A constrain do modelo é: " << veiculo.modelo_veiculo;
    qDebug() << "A constrain do cliente é: " << cliente.cpf;


    if( !query.exec( ) )
    {
        QMessageBox::critical(this, "ERRO", "Não foi possível salvar os dados do veiculo");
    }
    else
    {
        qDebug() << "_Dados salvos na tabela a004_veiculos";

        //limpando todos os campos
        ui->cb_nv_marca->clear();
        ui->cb_nv_modelo->clear();
        ui->cb_nv_ano->clear();
        ui->cb_nv_motor->clear();
        ui->txt_nv_cor->clear();
        ui->txt_nv_placa->clear();
        ui->txt_nv_chassi->clear();
        ui->txt2_nv_observacao->clear();
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
                    "a011_marca_nome "
                    ",a012_nome_veiculo "
                    ",a012_ano_veiculo "
                    ",a012_motor_veiculo "
                  "FROM "
                    "a012_modelos "
                    "JOIN a011_marcas ON (a011_codigo = a012_codigo) "
                  "ORDER BY "
                    "a011_marca_nome "
                    ",a012_nome_veiculo DESC");

    if( !query.exec() )
    {
        qDebug() << "_Erro  ao realizar consulta: prepararCB";
    }
    else
    {
        //pegar o numero de colunas
        //const int columnCount = query.record().count();
        //qDebug() << "_O numero de colunas da tabela é: " << columnCount;

        int marca = query.record().indexOf("a011_marca_nome");
        int modelo = query.record().indexOf("a012_nome_veiculo");
        int ano = query.record().indexOf("a012_ano_veiculo");
        int motor = query.record().indexOf("a012_motor_veiculo");

        while( query.next() )
        {
            //logica para adicionar itens no combobox, verificar e testar muito
            ui->cb_nv_marca->addItem( query.value(marca).toString() );
            ui->cb_nv_modelo->addItem( query.value(modelo).toString() );
            ui->cb_nv_ano->addItem( query.value(ano).toString() );
            ui->cb_nv_motor->addItem( query.value(motor).toString() );
        }
    }

    //filtrando modelo, chamando a funcao cbFiltro
    QString cb_marca_change = ui->cb_nv_marca->currentText();
    if( cb_marca_change != ui->cb_nv_marca->currentText() )
    {
        QString nome_marca = ui->cb_nv_marca->currentText();
        QString nome_modelo = ui->cb_nv_modelo->currentText();
        cbFiltro( nome_marca, nome_modelo );
    }
    //Os modelos e seus dados devem ser filtrados de acordo com as marcas
    //talvez seja necessário fazer outra função, que será chamada após essa no construtor
}

//**FUNÇÕES**//
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 21/04/2022                                                                           |
 * Propósito: filtrar os combo box pela marca e modelo dos veiculos                           |
 * Chamada: na função prepararCB()                                                            |
 * Status: NÃO FUNCIONA AINDA                                                                 |
 *--------------------------------------------------------------------------------------------
 */
void frms_nv_veiculocliente::cbFiltro( const QString &nome_marca, const QString &nome_veiculo )
{
   //depurando bloco
    qDebug() << "_Entrou na condição, função cbFiltro()";

    ui->cb_nv_ano->clear();
    ui->cb_nv_motor->clear();

    QSqlQuery query;
    query.prepare("SELECT "
                       "a011_marca_nome "
                       "a012_nome_veiculo "
                       ",a012_ano_veiculo "
                       ",a012_motor_veiculo "
                  "FROM "
                       "a012_modelos "
                       "JOIN a011_marcas ON (a011_codigo = a012_codigo) "
                  "WHERE "
                       "a011_marca_nome       = '" + nome_marca   + "'"
                       "AND a012_nome_veiculo = '" + nome_veiculo + "'"
                  "ORDER BY "
                       "a012_nome_veiculo DESC");

    if( !query.exec() )
    {
        qDebug() << "_Erro  ao realizar consulta: cbFiltro";
    }
    else
    {
        int modelo = query.record().indexOf("a012_nome_veiculo");
        int ano = query.record().indexOf("a012_ano_veiculo");
        int motor = query.record().indexOf("a012_motor_veiculo");

        while( query.next() )
        {
            //logica para adicionar itens no combobox, verificar e testar muito
            ui->cb_nv_modelo->addItem( query.value(modelo).toString() );
            ui->cb_nv_ano->addItem( query.value(ano).toString() );
            ui->cb_nv_motor->addItem( query.value(motor).toString() );
        }
    }
}



