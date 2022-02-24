#ifndef FRM_LOGIN_H
#define FRM_LOGIN_H

#include <QDialog>

namespace Ui {
class Frm_login;
}

class Frm_login : public QDialog
{
    Q_OBJECT

public:
    explicit Frm_login(QWidget *parent = nullptr);
    ~Frm_login();

private:
    Ui::Frm_login *ui;
};

#endif // FRM_LOGIN_H
