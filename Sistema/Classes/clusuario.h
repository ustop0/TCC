#ifndef CLUSUARIO_H
#define CLUSUARIO_H

#include <QDebug>
#include <QString>

class ClUsuario
{
public:
    QString nome;
    QString usuario;
    QString senha;
    char tipo_acesso;

public:
    ClUsuario();

    ~ClUsuario();
};

#endif // CLUSUARIO_H
