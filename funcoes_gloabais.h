#ifndef FUNCOES_GLOABAIS_H
#define FUNCOES_GLOABAIS_H

#include <QTableWidget>
#include <QString>
#include <iostream>
//#include <algorithm>
//#include <string>

class funcoes_globais
{
public:
    funcoes_globais();

    //função para remover as linhas do table widget, para reentrar na aba
    static void removerLinhas(QTableWidget *tw);

    //to lower case
    //static QString tLower( QString &str );

    //to upper case
    //static QString tUpper( QString &str );
};

#endif // FUNCOES_GLOABAIS_H
