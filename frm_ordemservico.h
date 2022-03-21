#ifndef FRM_ORDEMSERVICO_H
#define FRM_ORDEMSERVICO_H

#include <QDialog>

namespace Ui {
class frm_ordemservico;
}

class frm_ordemservico : public QDialog
{
    Q_OBJECT

public:
    explicit frm_ordemservico(QWidget *parent = nullptr);
    ~frm_ordemservico();

private:
    Ui::frm_ordemservico *ui;
};

#endif // FRM_ORDEMSERVICO_H
