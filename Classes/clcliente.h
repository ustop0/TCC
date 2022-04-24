#ifndef CLCLIENTE_H
#define CLCLIENTE_H

#include <QDebug>
#include <QString>

class ClCliente
{
public:
    QString codigo;
    QString nome;
    QString cpf;
    QString cep;
    QString estado;
    QString cidade;
    QString rua;
    QString bairro;
    QString telefone1;

public:
    ClCliente();

    //método para validar cpf
    static bool meValidaCPF( int *cpf ); //int &cpf

    ~ClCliente();
};

#endif // CLCLIENTE_H
