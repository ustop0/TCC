#ifndef FRM_GESTAOUSUARIOS_H
#define FRM_GESTAOUSUARIOS_H

#include <QDialog>

namespace Ui {
class frm_gestaousuarios;
}

class frm_gestaousuarios : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaousuarios(QWidget *parent = nullptr);
    ~frm_gestaousuarios();

private:
    Ui::frm_gestaousuarios *ui;
};

#endif // FRM_GESTAOUSUARIOS_H
