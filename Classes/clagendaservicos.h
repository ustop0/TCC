#ifndef CLAGENDASERVICOS_H
#define CLAGENDASERVICOS_H

#include <QDebug>
#include <QString>

class ClAgendaServicos
{
public:
    QString cliente;
    QString data_hora;
    QString carro_cliente;
    QString servico;
    char status;

public:
    ClAgendaServicos();

    ~ClAgendaServicos();
};

#endif // CLAGENDASERVICOS_H
