#ifndef FRM_GESTAOCLIENTE_H
#define FRM_GESTAOCLIENTE_H

#include <QDialog>

namespace Ui {
class frm_gestaocliente;
}

class frm_gestaocliente : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaocliente(QWidget *parent = nullptr);
    ~frm_gestaocliente();

private:
    Ui::frm_gestaocliente *ui;
};

#endif // FRM_GESTAOCLIENTE_H
