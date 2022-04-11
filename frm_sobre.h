#ifndef FRM_SOBRE_H
#define FRM_SOBRE_H

#include <QDialog>

namespace Ui {
class frm_sobre;
}

class frm_sobre : public QDialog
{
    Q_OBJECT

public:
    explicit frm_sobre(QWidget *parent = nullptr);
    ~frm_sobre();

private:
    Ui::frm_sobre *ui;
};

#endif // FRM_SOBRE_H
