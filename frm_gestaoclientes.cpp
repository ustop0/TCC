#include "frm_gestaoclientes.h"
#include "ui_frm_gestaoclientes.h"
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

    //chamando função que preenche combo box
    prepararCB();

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas

}//**FIM** construtor

frm_gestaoclientes::~frm_gestaoclientes()//**INICIO** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}


void frm_gestaoclientes::on_btn_nv_gravar_clicked() //salvar novo cliente **DESENVOLVENDO**
{
    //**EM DESENVOLVIMENTO
    ClCliente cliente; //instanciando

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
    QSqlQuery query; //query insersao de colaboradores na tabela tb_colaboradores

    //inserir
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
        QMessageBox::information(this, "GRAVADO", "Cliente salvo com sucesso");
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


//**FUNÇÕES**//
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 21/04/2022                                                                           |
 * Propósito: preencher os combo box com os dados a serem exibidos                            |
 * Chamada: botão gravar cliente                                                              |
 *--------------------------------------------------------------------------------------------
 */
void frm_gestaoclientes::prepararCB()
{
    //instanciar classe e usar atributos
    ClVeiculo vel;

    //pega a linha selecionada
    //int id=ui->tw_ge_listacolab->item(ui->tw_ge_listacolab->currentRow(), 0) ->text().toInt();

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
        qDebug() << "Erro  ao realizar consulta";
    }
    else
    {
        //pegar o numero de colunas
        const int columnCount = query.record().count();
        qDebug() << "_O numero de colunas da tabela é: " << columnCount;

        //query.first();

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
}
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


