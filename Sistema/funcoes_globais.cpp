#include "funcoes_globais.h"

funcoes_globais::funcoes_globais()
{

}

//removerlinhas do table widget
void funcoes_globais::removerLinhas( QTableWidget *tw ) //limpa o table Widget
{
    while( tw->rowCount() > 0 )
    {
        tw->removeRow(0);
    }
}

/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 16/04/2022                                                                           |
 * Propósito: No banco é utilizado o tipo CHAR,                                               |
 * sendo A para administrador e B para funcionário, os campos CB recebem valores de STRING.   |
 *--------------------------------------------------------------------------------------------
 */
QString funcoes_globais::ajustaTipoAcesso( QString acesso ) //Altera o tipo acesso dos campos CB
{
    if( acesso == "Administrador")
    {
        acesso = "A";
    }
    else if( acesso == "Funcionário" )
    {
        acesso = "B";
    }

    return acesso;
}

/***FUNCOES PARA STRINGS***/
//Converte string para  minusculo
//QString funcoes_globais::tLower( QString &str )
//{
//    std::transform( str.begin(), str.end(), str.begin(), ::tolower );

//    return str;
//}

////Converte string para  maiusculo
//QString funcoes_globais::tUpper( QString &str )
//{
//    std::transform( str.begin(), str.end(), str.begin(), ::toupper );

//    return str;
//}
