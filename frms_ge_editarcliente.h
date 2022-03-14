#ifndef FRMS_GE_EDITARCLIENTE_H
#define FRMS_GE_EDITARCLIENTE_H

#include <QDialog>

namespace Ui {
class frms_ge_editarcliente;
}

class frms_ge_editarcliente : public QDialog
{
    Q_OBJECT

public:
    explicit frms_ge_editarcliente(QWidget *parent = nullptr);
    ~frms_ge_editarcliente();

private:
    Ui::frms_ge_editarcliente *ui;
};

#endif // FRMS_GE_EDITARCLIENTE_H
