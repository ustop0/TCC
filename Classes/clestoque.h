#ifndef CLESTOQUE_H
#define CLESTOQUE_H

#include <QDebug>
#include <QString>

class ClEstoque
{
public:
   int nc_peca;
   QString denominacao;
   QString grupo;
   QString tipo_peca;
   double valor_compra;
   double valor_venda;
   int qtde_estoque;
   QString posicao_peca;

public:
    ClEstoque();

    ~ClEstoque();
};

#endif // CLESTOQUE_H
