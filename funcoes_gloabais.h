#ifndef FUNCOES_GLOABAIS_H
#define FUNCOES_GLOABAIS_H

#include <QTableWidget>

class funcoes_globais
{
public:
    funcoes_globais();

    //função para remover as linhas do table widget, para reentrar na aba
    static void removerLinhas(QTableWidget *tw);
};

#endif // FUNCOES_GLOABAIS_H
