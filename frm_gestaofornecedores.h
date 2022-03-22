#ifndef FRM_GESTAOFORNECEDORES_H
#define FRM_GESTAOFORNECEDORES_H

#include <QDialog>

namespace Ui {
class frm_gestaofornecedores;
}

class frm_gestaofornecedores : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaofornecedores(QWidget *parent = nullptr);
    ~frm_gestaofornecedores();

private:
    Ui::frm_gestaofornecedores *ui;
};

#endif // FRM_GESTAOFORNECEDORES_H
