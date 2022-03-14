#ifndef VARIAVEIS_GLOBAIS_H
#define VARIAVEIS_GLOBAIS_H

#include <QMainWindow>
#include <QtSql> //banco de dados
#include <QMessageBox>

class  variaveis_globais
{
    public:
        //static mantém a variável por toda vida útil do programa
        static bool logado;
        static QString nome_colab, acesso_colab, username_colab; //dados colaborador
        static int id_colab; //id colaborador
};

#endif // VARIAVEIS_GLOBAIS_H
