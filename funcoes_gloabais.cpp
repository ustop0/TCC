#include "funcoes_gloabais.h"

funcoes_gloabais::funcoes_gloabais()
{

}

void funcoes_globais::removerLinhas(QTableWidget *tw) //limpa o table Widget
{
    while(tw->rowCount() > 0)
    {
        tw->removeRow(0);
    }
}
