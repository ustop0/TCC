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
    QStringList cabecalhos={"ID", "Nome", "CPF", "Veiculo", "Placa",
                            "Estado","Cidade", "Rua", "Bairro", "Telefone"};

    ui->tw_ge_listaclientes->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_listaclientes->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_listaclientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_listaclientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_listaclientes->verticalHeader()->setVisible(false);


    //carregando os clientes no tablewidget
    //limpa as linhas do table widget
    funcoes_globais::removerLinhas( ui->tw_ge_listaclientes );

    //inserir linhas dentro do table widget
    int contlinhas=0;

    //essa query deve filtrar com base no cliente cadastrado na tela novo cliente
    QSqlQuery query; //query para listar os colaboradores no table widget
    query.prepare("SELECT "
                      "a005_codigo "
                      ",a005_nome "
                      ",a005_cpf "
                      ",a012_nome_veiculo "
                      ",a004_placa_Veiculo "
                      ",a005_estado "
                      ",a005_cidade "
                      ",a005_rua "
                      ",a005_bairro "
                      ",a005_telefone "
                  "FROM "
                      "a005_cliente "
                      "JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                      "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo) "
                      "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
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

            //definindo o tamanho das linhas
            ui->tw_ge_listaclientes->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar clientes");
    }

}//**FIM** construtor

frm_gestaoclientes::~frm_gestaoclientes()//**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

void frm_gestaoclientes::on_btn_nv_gravar_clicked() //salvar novo cliente **DESENVOLVENDO**
{
    //**EM DESENVOLVIMENTO
    ClCliente cliente;

    cliente.nome = ui->txt_nv_nome->text();
    cliente.cpf = ui->txt_nv_cpf->text();
    if( recebeCPF( cliente.cpf ) == false ) //**EM TESTES**recebendo e tratando o cpf
    {
        qDebug() << "cpf inválido para sql";
    }

    cliente.cep = ui->txt_nv_cep->text();
    cliente.estado = ui->txt_nv_estado->text();
    cliente.cidade = ui->txt_nv_cidade->text();
    cliente.rua = ui->txt_nv_rua->text();
    cliente.bairro = ui->txt_nv_bairro->text();
    cliente.telefone1 = ui->txt_nv_telefone->text();

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
                                     ",a005_bairro    "
                                     ",a005_telefone) "
                    "VALUES('" +cliente.nome      +  "'"
                          ",'" +cliente.cpf       +  "'"
                          ",'" +cliente.cep       +  "'"
                          ",'" +cliente.estado    +  "'"
                          ",'" +cliente.cidade    +  "'"
                          ",'" +cliente.rua       +  "'"
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
                                          ,QMessageBox::Yes|QMessageBox::No); //revisar tabulação

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
            ui->txt_nv_bairro->clear();
            ui->txt_nv_telefone->clear();
            ui->txt_nv_nome->setFocus();
        }
    }
}

void frm_gestaoclientes::on_txt_nv_cep_returnPressed()//pressiona campo cep
{
    ClCliente cliente;

    cliente.cep = ui->txt_nv_cep->text();
    validaCEP( cliente.cep ); //validando cep
    cliente.estado = ui->txt_nv_estado->text();
    cliente.cidade = ui->txt_nv_cidade->text();
    cliente.rua = ui->txt_nv_rua->text();
    cliente.bairro = ui->txt_nv_bairro->text();
    cliente.telefone1 = ui->txt_nv_telefone->text();
}

void frm_gestaoclientes::on_btn_nv_cadastrarveiculo_clicked()//tela de cadastro de veiculos
{
    frms_nv_veiculocliente f_nv_veiculocliente;
    f_nv_veiculocliente.exec();
}

//**TAB Gestão clientes**
//selecionar cliente da grid
void frm_gestaoclientes::on_tw_ge_listaclientes_itemSelectionChanged()
{

}

//filtrar
void frm_gestaoclientes::on_txt_ge_filtro_returnPressed()
{
    QString busca; //armazena busca
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtro->text();

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Cliente" << "CPF" << "Veiculo" << "Placa Veiculo";

    funcoes_globais::removerLinhas( ui->tw_ge_listaclientes ); //remove as linhas o table widget

    if( ui->txt_ge_filtro->text() == "" ) //verificando se algo foi digitado no campo de filtro
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a005_codigo "
                        ",a005_nome "
                        ",a005_cpf "
                        ",a012_nome_veiculo "
                        ",a004_placa_Veiculo "
                        ",a005_estado "
                        ",a005_cidade "
                        ",a005_rua "
                        ",a005_bairro "
                        ",a005_telefone "
                    "FROM "
                        "a005_cliente "
                        "JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                        "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo) "
                        "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                    "WHERE "
                      "a005_ativo = true "
                    "ORDER BY "
                        "a005_codigo DESC";

        }
        else
        {
            busca = "SELECT "
                        "a005_codigo "
                        ",a005_nome "
                        ",a005_cpf "
                        ",a012_nome_veiculo "
                        ",a004_placa_Veiculo "
                        ",a005_estado "
                        ",a005_cidade "
                        ",a005_rua "
                        ",a005_bairro "
                        ",a005_telefone "
                    "FROM "
                        "a005_cliente "
                        "JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                        "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo) "
                        "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
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
                busca = "SELECT "
                            "a005_codigo "
                            ",a005_nome "
                            ",a005_cpf "
                            ",a012_nome_veiculo "
                            ",a004_placa_Veiculo "
                            ",a005_estado "
                            ",a005_cidade "
                            ",a005_rua "
                            ",a005_bairro "
                            ",a005_telefone "
                        "FROM "
                            "a005_cliente "
                            "JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                            "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo) "
                            "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                        "WHERE "
                          "a005_nome LIKE '%" +txt_filtro+ "%'"
                          "AND a005_ativo = true "
                        "ORDER BY "
                            "a005_codigo DESC";
                break;
            //cpf
            case 1:
                busca = "SELECT "
                            "a005_codigo "
                            ",a005_nome "
                            ",a005_cpf "
                            ",a012_nome_veiculo "
                            ",a004_placa_Veiculo "
                            ",a005_estado "
                            ",a005_cidade "
                            ",a005_rua "
                            ",a005_bairro "
                            ",a005_telefone "
                        "FROM "
                            "a005_cliente "
                            "JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                            "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo) "
                            "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                        "WHERE "
                          "a005_cpf LIKE '%" +txt_filtro+ "%'"
                          "AND a005_ativo = true "
                        "ORDER BY "
                            "a005_codigo DESC";
                break;
            //Carro
            case 2:
                busca = "SELECT "
                            "a005_codigo "
                            ",a005_nome "
                            ",a005_cpf "
                            ",a012_nome_veiculo "
                            ",a004_placa_Veiculo "
                            ",a005_estado "
                            ",a005_cidade "
                            ",a005_rua "
                            ",a005_bairro "
                            ",a005_telefone "
                        "FROM "
                            "a005_cliente "
                            "JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                            "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo) "
                            "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                        "WHERE "
                          "a012_nome_veiculo LIKE '%" +txt_filtro+ "%'"
                          "AND a005_ativo = true "
                        "ORDER BY "
                            "a005_codigo DESC";
                break;
            //Placa
            case 3:
                busca = "SELECT "
                            "a005_codigo "
                            ",a005_nome "
                            ",a005_cpf "
                            ",a012_nome_veiculo "
                            ",a004_placa_Veiculo "
                            ",a005_estado "
                            ",a005_cidade "
                            ",a005_rua "
                            ",a005_bairro "
                            ",a005_telefone "
                        "FROM "
                            "a005_cliente "
                            "JOIN a004_veiculos ON (a005_codigo = a004_fk_codigo_cliente) "
                            "JOIN a012_modelos ON (a012_codigo = a004_fk_codigo_modelo) "
                            "JOIN a011_marcas ON (a011_codigo = a012_fk_codigo_marca) "
                        "WHERE "
                          "a004_placa_Veiculo LIKE '%" +txt_filtro+ "%'"
                          "AND a005_ativo = true "
                        "ORDER BY "
                            "a005_codigo DESC";

                break;
            default:
                qDebug() << "Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }
    }

    //contador para percorrer linhas
    int contlinhas=0;
    QSqlQuery query;
    query.prepare(busca);

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

         int totalNumeros = 0;
         totalNumeros += cpf[i];
         if( totalNumeros != 11 )
         {
             qDebug() << "_O CPF digitado NÃO É VÁLIDO, tem menos de 11 digitos" << "\n";
             ui->lb_nv_cpf->setText("CPF: inválido");
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
            return valCpf; //teste
        }
        else
        {
            //**DESENVOLVENDO**
            qDebug() << "_O CPF digitado NÃO É VÁLIDO" << "\n";
            QMessageBox::warning(this, "Erro", "O CPF digitado é inválido");

            //Informa que o cpf é inválido
            ui->lb_nv_cpf->setText("CPF: inválido");

            break;
        }
    }while( valCpf == false );

    return valCpf; //essa função não deve retornar nenhum valor específico
}

/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 18/04/2022                                                                           |
 * Propósito: receber o cep, e faz a validação via API do BrasilAPI                    |
 * Chamada: botão gravar cliente                                                              |
 *--------------------------------------------------------------------------------------------
 */
void frm_gestaoclientes::validaCEP( const QString &cliente_cep )
{
    QEventLoop waitLoop;
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(
                QNetworkRequest( QUrl("https://brasilapi.com.br/api/cep/v1/" + cliente_cep)) );

    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
    QJsonObject json(doc.object());

    //validando o cep, e tratando erros
    if( json.find("erro") != json.end() )
    {
        json["erro"].toBool() ?
                    ui->lb_nv_cep->setText("CEP") : ui->lb_nv_cep->setText("CEP: inválido");

        //limpando os campos
        ui->txt_nv_estado->clear();
        ui->txt_nv_cidade->clear();
        ui->txt_nv_bairro->clear();
        ui->txt_nv_rua->clear();
        ui->lb_nv_cep->setText("CEP: inválido");
    }
    else
    {
        ui->txt_nv_cep->setText(json["cep"].toString());
        ui->txt_nv_estado->setText(json["state"].toString());
        ui->txt_nv_cidade->setText(json["city"].toString());
        ui->txt_nv_bairro->setText(json["neighborhood"].toString());
        ui->txt_nv_rua->setText(json["street"].toString());
    }
}
