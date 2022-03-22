#ifndef FRM_GESTAOVEICULOS_H
#define FRM_GESTAOVEICULOS_H

#include <QDialog>

namespace Ui {
class frm_gestaoveiculos;
}

class frm_gestaoveiculos : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaoveiculos(QWidget *parent = nullptr);
    ~frm_gestaoveiculos();

private:
    Ui::frm_gestaoveiculos *ui;
};

#endif // FRM_GESTAOVEICULOS_H
