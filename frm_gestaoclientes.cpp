#include "frm_gestaoclientes.h"
#include "ui_frm_gestaoclientes.h"

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


bool frm_gestaoclientes::on_btn_nv_gravar_clicked() //gravar novo cliente **DESENVOLVENDO**
{
    //recebendo o cpf por QString e convertendo para std::string
    QString cliente_cpf = ui->txt_nv_cpf->text();
    std::string conv_cpf = cliente_cpf.toStdString();

    //convertendo para const char array
    const char *input = conv_cpf.c_str();
    int cpf[11];

    //verificando se a entrada é válida
    for(unsigned char i = 0; i < 11; i++)
    {
       //Convertendo char para valor absoluto segundo tabela ASCII
        cpf[i] = static_cast<int>(input[i] - 48);

        if(cpf[i] < 0 || cpf[i] > 9)
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
        }
        else
        {
            //**DESENVOLVENDO**
            qDebug() << "O CPF digitado NÃO É VÁLIDO" << "\n";
            QMessageBox::warning(this, "Erro", "O CPF digitado é inválido");

            //limpa o campo de cpf
            ui->txt_nv_cpf->clear();
            break;
        }
    }while(valCpf == false);

    return false; //essa função não deve retornar nenhum valor específico
}

