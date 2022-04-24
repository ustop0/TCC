#ifndef CLVEICULO_H
#define CLVEICULO_H

#include <QDebug>
#include <QString>

class ClVeiculo
{
public:
    QString marca_veiculo;
    QString modelo_veiculo;
    QString motor_veiculo;
    QString ano_veiculo;
    QString chassi_veiculo;
    QString placa_veiculo;
    QString cor_veiculo;
    QString observacao;

public:
    ClVeiculo();

    ~ClVeiculo();
};

#endif // CLVEICULO_H
