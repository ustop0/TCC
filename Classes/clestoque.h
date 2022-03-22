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
   double valor_compra;
   double valor_venda;
   double margem_lucro;
   int qtde;
   QString tipo_peca;
   QString posicao_peca;

public:
    ClEstoque();

    ~ClEstoque();
};

#endif // CLESTOQUE_H
