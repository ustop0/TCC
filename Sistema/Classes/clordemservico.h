#ifndef CLORDEMSERVICO_H
#define CLORDEMSERVICO_H

#include <QDebug>
#include <QString>

class ClOrdemServico
{
public:
    QString data_abertura;
    QString data_fechamento;
    char status;
    double valor_total_servicos;
    double valor_total_mercadoria;
    char meio_pagamento;
    QString garantia_servico;

public:
    ClOrdemServico();

    ~ClOrdemServico();
};

#endif // CLORDEMSERVICO_H
