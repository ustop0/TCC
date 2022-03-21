#ifndef FRM_AGENDASERVICOS_H
#define FRM_AGENDASERVICOS_H

#include <QDialog>

namespace Ui {
class frm_agendaservicos;
}

class frm_agendaservicos : public QDialog
{
    Q_OBJECT

public:
    explicit frm_agendaservicos(QWidget *parent = nullptr);
    ~frm_agendaservicos();

private:
    Ui::frm_agendaservicos *ui;
};

#endif // FRM_AGENDASERVICOS_H
