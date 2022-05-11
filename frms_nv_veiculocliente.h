#ifndef FRMS_NV_VEICULOCLIENTE_H
#define FRMS_NV_VEICULOCLIENTE_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <thread> //gerar threads
#include "ConexaoBanco.h"
#include "funcoes_globais.h"

namespace Ui {
class frms_nv_veiculocliente;
}

class frms_nv_veiculocliente : public QDialog
{
    Q_OBJECT

public:
    explicit frms_nv_veiculocliente(QWidget *parent = nullptr);
    ~frms_nv_veiculocliente();

    //instanciando conexao com o banco de dados
    Conexao con;

    //a chave estrangeira é feita por uma query que precisa do cpf para o filtro where
    static QString veiculo_modelo;
    static QString cliente_cpf;

public slots:

    void prepararCB();

    void cbFiltro( const QString &nome_marca );

    QString crudModelo();

    QString crudCliente();

private slots:
    void on_tw_nv_listaveiculosclientes_itemSelectionChanged();

    void on_btn_salvarveiculo_clicked();

private:
    Ui::frms_nv_veiculocliente *ui;
};

#endif // FRMS_NV_VEICULOCLIENTE_H