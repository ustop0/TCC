#include "frm_principal.h"
#include "frm_gestaoclientes.h" //teste do form clientes
#include "frm_login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //formulário principal do sistema
    //Frm_principal w;
    //w.show();

    //fazendo testes na validacao do CPF
    //frm_gestaoclientes w;
    //w.show();

    //formulário de login
    Frm_login w;
    w.show();

    return a.exec();
}
