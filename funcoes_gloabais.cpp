#include "funcoes_gloabais.h"

funcoes_globais::funcoes_globais()
{

}

//removerlinhas do table widget
void funcoes_globais::removerLinhas(QTableWidget *tw) //limpa o table Widget
{
    while(tw->rowCount() > 0)
    {
        tw->removeRow(0);
    }
}


/***FUNCOES PARA STRINGS***/
//Converte string para  minusculo
QString funcoes_globais::tLower( QString &str )
{
    std::transform( str.begin(), str.end(), str.begin(), ::tolower );

    return str;
}

//Converte string para  maiusculo
QString funcoes_globais::tUpper( QString &str )
{
    std::transform( str.begin(), str.end(), str.begin(), ::toupper );

    return str;
}
