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
        static QString nome_colab; //dados do colaborador
        static QString acesso_colab;
        static QString username_colab;
        static int id_colab; //id colaborador
};

#endif // VARIAVEIS_GLOBAIS_H
