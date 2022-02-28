QT       += core gui sql #consultas SQL
QT       += core gui printsupport #para impressora

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    frm_gestaousuarios.cpp \
    frm_login.cpp \
    frm_usuarios.cpp \
    funcoes_gloabais.cpp \
    main.cpp \
    frm_principal.cpp

HEADERS += \
    ConexaoBanco.h \
    frm_gestaousuarios.h \
    frm_login.h \
    frm_principal.h \
    frm_usuarios.h \
    funcoes_gloabais.h

FORMS += \
    frm_gestaousuarios.ui \
    frm_login.ui \
    frm_principal.ui \
    frm_usuarios.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
