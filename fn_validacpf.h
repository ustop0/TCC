#ifndef FN_VALIDACPF_H
#define FN_VALIDACPF_H

#include <QDebug>
#include <QMessageBox>
#include <iostream>

class fn_validaCpf
{
public:
    fn_validaCpf();

    //validar CPF
    static bool validaCPF( int *cpf ); //int &cpf

    //validar entrada CPF
    //static int entradaCPF(const char *input );
};

#endif // FN_VALIDACPF_H
