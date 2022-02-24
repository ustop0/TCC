#include "frm_principal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Frm_principal w;
    w.show();
    return a.exec();
}
