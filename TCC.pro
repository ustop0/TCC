QT       += core gui sql #consultas SQL
QT       += core gui printsupport #para impressora

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fn_validacpf.cpp \
    frm_gestaoclientes.cpp \
    frm_gestaousuarios.cpp \
    frm_login.cpp \
    frms_ge_editarcliente.cpp \
    funcoes_gloabais.cpp \
    main.cpp \
    frm_principal.cpp

HEADERS += \
    ConexaoBanco.h \
    fn_validacpf.h \
    frm_gestaoclientes.h \
    frm_gestaousuarios.h \
    frm_login.h \
    frm_principal.h \
    frms_ge_editarcliente.h \
    funcoes_gloabais.h \
    variaveis_globais.h

FORMS += \
    frm_gestaoclientes.ui \
    frm_gestaousuarios.ui \
    frm_login.ui \
    frm_principal.ui \
    frms_ge_editarcliente.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
