#ifndef FRM_NOVAVENDA_H
#define FRM_NOVAVENDA_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include "ConexaoBanco.h"
#include "funcoes_globais.h"
#include "variaveis_globais.h"

namespace Ui {
class frm_novavenda;
}

class frm_novavenda : public QDialog
{
    Q_OBJECT

public:
    explicit frm_novavenda(QWidget *parent = nullptr);
    ~frm_novavenda();

    //instanciando conexao com o banco de dados
    Conexao con;

    //variáveis globais para a edição de produtos em nova venda
    static QString g_codigo_peca;
    static QString g_denominacao;
    static QString g_qtde;
    static QString g_valor_unitario;
    static QString g_valor_total;
    static QString g_valor_comprado;
    static QString g_margem_lucro;

    //variável global, verifica se um produto foi alterado
    static bool g_alterou;

    //função para resetar campos
    inline void resetaCampos();

    //função para calculo do valor total
    double calculaTotal( QTableWidget *tw, int coluna );

private slots:
    void on_tw_listapecas_itemSelectionChanged();

    void on_txt_ge_filtrar_returnPressed();

    void on_btn_pesquisarproduto_clicked();

    void on_btn_adicionarItem_clicked();

    void on_btn_excluirproduto_clicked();

    void on_btn_finalizarvenda_clicked();

private:
    Ui::frm_novavenda *ui;
};

#endif // FRM_NOVAVENDA_H
