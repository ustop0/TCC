#ifndef FRM_NOVAVENDA_H
#define FRM_NOVAVENDA_H

#include <QDialog>

namespace Ui {
class frm_novavenda;
}

class frm_novavenda : public QDialog
{
    Q_OBJECT

public:
    explicit frm_novavenda(QWidget *parent = nullptr);
    ~frm_novavenda();

private:
    Ui::frm_novavenda *ui;
};

#endif // FRM_NOVAVENDA_H
