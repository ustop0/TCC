#include "frm_gestaoclientes.h"
#include "ui_frm_gestaoclientes.h"
#include "Classes/clcliente.h"

frm_gestaoclientes::frm_gestaoclientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaoclientes)
{
    ui->setupUi(this);
}

frm_gestaoclientes::~frm_gestaoclientes()
{
    delete ui;
}


void frm_gestaoclientes::on_btn_nv_gravar_clicked() //gravar novo cliente **DESENVOLVENDO**
{
    //**EM DESENVOLVIMENTO
    ClCliente cliente; //instanciando

    cliente.nome = ui->txt_nv_nome->text();
    cliente.cpf = ui->txt_nv_cpf->text();
    recebeCPF( cliente.cpf ); //validando cpf
    cliente.telefone1 = ui->txt_nv_telefone->text();
    cliente.cep = ui->txt_nv_cep->text();
    validaCEP( cliente.cep ); //validando cep
    cliente.estado = ui->txt_nv_estado->text();
    cliente.cidade = ui->txt_nv_cidade->text();
    cliente.bairro = ui->txt_nv_bairro->text();
    cliente.rua = ui->txt_nv_rua->text();

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

    //verificando se a entrada é válida
    for(unsigned char i = 0; i < 11; i++)
    {
       //Convertendo char para valor absoluto segundo tabela ASCII
        cpf[i] = static_cast<int>(input[i] - 48);

        if( cpf[i] < 0 || cpf[i] > 9 )
        {
            return 1;
        }
    }

    int valCpf;
    valCpf = fn_validaCpf::validaCPF( cpf );

    do
    {
        if( valCpf == true )
        {
            qDebug() << "O CPF digitado É válido" << "\n";
            ui->lb_nv_cpf->setText("CPF");
        }
        else
        {
            //**DESENVOLVENDO**
            qDebug() << "O CPF digitado NÃO É VÁLIDO" << "\n";
            QMessageBox::warning(this, "Erro", "O CPF digitado é inválido");

            //Informa que o cpf é inválido
            ui->lb_nv_cpf->setText("CPF: inválido");

            break;
        }
    }while( valCpf == false );

    return false; //essa função não deve retornar nenhum valor específico
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
