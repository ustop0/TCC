#ifndef FRMS_SELECIONACLIENTE_H
#define FRMS_SELECIONACLIENTE_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class frms_selecionacliente;
}

class frms_selecionacliente : public QDialog
{
    Q_OBJECT

public:
    explicit frms_selecionacliente(QWidget *parent = nullptr);
    ~frms_selecionacliente();

private slots:

    void on_btn_confirmarCliente_clicked();

    void on_btn_filtrarCliente_clicked();

private:
    Ui::frms_selecionacliente *ui;
};

#endif // FRMS_SELECIONACLIENTE_H
