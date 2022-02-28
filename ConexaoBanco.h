#ifndef CONEXAOBANCO_H
#define CONEXAOBANCO_H
#include <QtSql>
#include <QSqlDatabase>

//classe de conexao com o banco de dados
class Conexao
{
    public:
        QSqlDatabase bancoDeDados; //variavel que recebe o drive do banco
        Conexao()
        {
            bancoDeDados=QSqlDatabase::addDatabase("QPSQL"); //drive do postgre
        }

        void fechar() //fecha a conexao com o banco
        {
            bancoDeDados.close();
        }

        bool abrir() //abre a conexao com o banco
        {
            //fazendo conexao com o PostgreSQL
            bancoDeDados.setHostName("localhost");
            bancoDeDados.setUserName("postgres");
            bancoDeDados.setPassword("12meurex");
            bancoDeDados.setDatabaseName("dbAmincar");

            if( !bancoDeDados.open() ) //verifica se o banco de dados foi aberto
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
