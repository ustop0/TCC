#ifndef CLVEICULO_H
#define CLVEICULO_H

#include <QDebug>
#include <QString>

class ClVeiculo
{
public:
    QString marca_veiculo;
    QString nome_veiculo;
    QString motor_veiculo;
    int ano_veiculo;
    QString chassi_veiculo;
    float km_veiculo;
    QString placa_veiculo;
    QString cor_veiculo;
    QString ocorrencia;
    QString observacao;

public:
    ClVeiculo();

    ~ClVeiculo();
};

#endif // CLVEICULO_H
