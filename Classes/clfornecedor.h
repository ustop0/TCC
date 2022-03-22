#ifndef CLFORNECEDOR_H
#define CLFORNECEDOR_H

#include <QDebug>
#include <QString>

class ClFornecedor
{
public:
    QString razao_social;
    QString nome_fantasia;
    QString cnpj;
    int cep;
    QString estado;
    QString cidade;
    QString rua;
    QString bairro;
    int numero_rua;
    QString porte_empresa;
    QString ocupacao_empresa;
    QString telefone1;
    QString telefone2;

public:
    ClFornecedor();

    ~ClFornecedor();
};

#endif // CLFORNECEDOR_H
