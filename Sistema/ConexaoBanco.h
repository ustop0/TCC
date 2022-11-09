#ifndef CONEXAOBANCO_H
#define CONEXAOBANCO_H

#include <QtSql>
#include <QSqlDatabase>

//classe de conexao com o banco de dados
class Conexao
{
    public:
        //QSqlDatabase bancoDeDados = QSqlDatabase::database();
        QSqlDatabase bancoDeDados;
        QString banco_host = "localhost";
        QString banco_usuario = "postgres";
        QString banco_senha = "12meurex";
        QString banco_nome = "dbAmincar";


        Conexao()
        {
            //drive do postgre
            bancoDeDados = QSqlDatabase::addDatabase( "QPSQL" );
        }

        //fecha a conexao com o banco
        inline void fechar()
        {
            bancoDeDados.close();
            QSqlDatabase::removeDatabase( banco_nome );
        }

        //abre a conexao com o banco
        inline bool abrir()
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

        //verifica se o banco está aberto ou fechado
        inline bool aberto()
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
