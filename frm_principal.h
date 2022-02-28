#ifndef FRM_PRINCIPAL_H
#define FRM_PRINCIPAL_H

#include <QMainWindow>
#include <QtSql> //banco de dados
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Frm_principal; }
QT_END_NAMESPACE

class Frm_principal : public QMainWindow
{
    Q_OBJECT

public:
    Frm_principal(QWidget *parent = nullptr);
    ~Frm_principal();

private slots:
    void on_actionUsuario_triggered();

private:
    Ui::Frm_principal *ui;
};
#endif // FRM_PRINCIPAL_H
