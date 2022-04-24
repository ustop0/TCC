QT       += core gui sql #consultas SQL
QT       += core gui printsupport #para impressora
QT       += core gui network #consultas APIs

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Classes/clagendaservicos.cpp \
    Classes/clcliente.cpp \
    Classes/clestoque.cpp \
    Classes/clfornecedor.cpp \
    Classes/clordemservico.cpp \
    Classes/clusuario.cpp \
    Classes/clveiculo.cpp \
    Classes/usuario.cpp \
    fn_validacpf.cpp \
    frm_agendaservicos.cpp \
    frm_gestaoclientes.cpp \
    frm_gestaoesotque.cpp \
    frm_gestaofornecedores.cpp \
    frm_gestaousuarios.cpp \
    frm_gestaoveiculos.cpp \
    frm_gestaovendas.cpp \
    frm_login.cpp \
    frm_novavenda.cpp \
    frm_ordemservico.cpp \
    frm_sobre.cpp \
    frms_ge_editarcliente.cpp \
    frms_nv_veiculocliente.cpp \
    frms_selecionacliente.cpp \
    funcoes_globais.cpp \
    main.cpp \
    frm_principal.cpp

HEADERS += \
    Classes/clagendaservicos.h \
    Classes/clcliente.h \
    Classes/clestoque.h \
    Classes/clfornecedor.h \
    Classes/clordemservico.h \
    Classes/clusuario.h \
    Classes/clveiculo.h \
    Classes/usuario.h \
    ConexaoBanco.h \
    fn_validacpf.h \
    frm_agendaservicos.h \
    frm_gestaoclientes.h \
    frm_gestaoesotque.h \
    frm_gestaofornecedores.h \
    frm_gestaousuarios.h \
    frm_gestaoveiculos.h \
    frm_gestaovendas.h \
    frm_login.h \
    frm_novavenda.h \
    frm_ordemservico.h \
    frm_principal.h \
    frm_sobre.h \
    frms_ge_editarcliente.h \
    frms_nv_veiculocliente.h \
    frms_selecionacliente.h \
    funcoes_globais.h \
    variaveis_globais.h

FORMS += \
    frm_agendaservicos.ui \
    frm_gestaoclientes.ui \
    frm_gestaoesotque.ui \
    frm_gestaofornecedores.ui \
    frm_gestaousuarios.ui \
    frm_gestaoveiculos.ui \
    frm_gestaovendas.ui \
    frm_login.ui \
    frm_novavenda.ui \
    frm_ordemservico.ui \
    frm_principal.ui \
    frm_sobre.ui \
    frms_ge_editarcliente.ui \
    frms_nv_veiculocliente.ui \
    frms_selecionacliente.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Imagens/splash.png

RESOURCES += \
    Imagens.qrc
