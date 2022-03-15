#ifndef FRM_GESTAOCLIENTES_H
#define FRM_GESTAOCLIENTES_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include "funcoes_gloabais.h"
#include "fn_validacpf.h"

namespace Ui {
class frm_gestaoclientes;
}

class frm_gestaoclientes : public QDialog
{
    Q_OBJECT

public:
    explicit frm_gestaoclientes(QWidget *parent = nullptr);
    ~frm_gestaoclientes();

private slots:
    bool on_btn_nv_gravar_clicked(); //original( void )

private:
    Ui::frm_gestaoclientes *ui;
};

#endif // FRM_GESTAOCLIENTES_H
