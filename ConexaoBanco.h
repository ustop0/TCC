#ifndef CONEXAOBANCO_H
#define CONEXAOBANCO_H

#include <QtSql>
#include <QSqlDatabase>

//classe de conexao com o banco de dados
class Conexao
{
    public:
        QSqlDatabase bancoDeDados;
        QString banco_host = "localhost";
        QString banco_usuario = "postgres";
        QString banco_senha = "12meurex";
        QString banco_nome = "dbAmincar";

        Conexao()
        {
            //drive do postgre
            bancoDeDados = QSqlDatabase::addDatabase("QPSQL");
        }

        inline void fechar() //fecha a conexao com o banco
        {
            bancoDeDados.close();
        }

        inline bool abrir() //abre a conexao com o banco
        {
            //fazendo conexao com o PostgreSQL
            bancoDeDados.setHostName( banco_host );
            bancoDeDados.setUserName( banco_usuario );
            bancoDeDados.setPassword( banco_senha );
            bancoDeDados.setDatabaseName( banco_nome );

            //verifica se o banco de dados foi aberto
            if( !bancoDeDados.open() )
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        bool aberto() //verifica se o banco está aberto ou fechado
        {
            if( bancoDeDados.isOpen() )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};
#endif // CONEXAOBANCO_H
