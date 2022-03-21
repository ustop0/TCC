#ifndef FRM_GESTAOESOTQUE_H
#define FRM_GESTAOESOTQUE_H

#include <QDialog>

namespace Ui {
class frm_gestaoesotque;
}

class frm_gestaoesotque : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaoesotque(QWidget *parent = nullptr);
    ~frm_gestaoesotque();

private:
    Ui::frm_gestaoesotque *ui;
};

#endif // FRM_GESTAOESOTQUE_H
