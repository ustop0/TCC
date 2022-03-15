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
    //validandoCPF
    QString cliente_cpf = ui->txt_nv_cpf->text();
    std::string conv_cpf = cliente_cpf.toStdString();

    const char *input = conv_cpf.c_str();
    int cpf[11];

    for(unsigned char i = 0; i < 11; i++)
    {
       //Convertendo char para valor absoluto segundo tabela ASCII
        cpf[i] = static_cast<int>(input[i] - 48);

        if(cpf[i] < 0 || cpf[i] > 9)
        {   //Validando a entrada de dados
            //std::cout << "ENTRADA INVÁLIDA" << "\n";
            QMessageBox::warning(this, "Erro", "Entráda inválida");
            return 1;
        }
    }

    int valCpf;
    valCpf = fn_validaCpf::validaCPF( cpf );

    if( valCpf == true )
    {
        qDebug() << "O CPF digitado É válido" << "\n";
    }
    else
    {
        qDebug() << "O CPF digitado NÃO É VÁLIDO" << "\n";
    }

    return false; //essa função não deve retornar nenhum valor específico
}

