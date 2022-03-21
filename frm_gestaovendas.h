#ifndef FRM_GESTAOVENDAS_H
#define FRM_GESTAOVENDAS_H

#include <QDialog>

namespace Ui {
class frm_gestaovendas;
}

class frm_gestaovendas : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaovendas(QWidget *parent = nullptr);
    ~frm_gestaovendas();

private:
    Ui::frm_gestaovendas *ui;
};

#endif // FRM_GESTAOVENDAS_H
