#include "frm_principal.h"
#include "frm_gestaoclientes.h" //teste do form clientes
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Frm_principal w;
    //w.show();

    //fazendo testes na validacao do CPF
    frm_gestaoclientes w;
    w.show();

    return a.exec();
}
