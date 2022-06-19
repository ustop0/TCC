#include "frm_gestaousuarios.h"
#include "ui_frm_gestaousuarios.h"
//#include "frms_nv_veiculocliente.h" // verificar

frm_gestaousuarios::frm_gestaousuarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaousuarios)
{
    ui->setupUi(this);

    //abrindo a conexao com o banco
    if( !con.abrir() ) //verificando se a conexao foi aberta
    {
        if( !con.abrir() )
        {
            QMessageBox::warning(this, "ERRO", "Erro ao abrir banco de dados");
        }
    }

    //COMBO BOX ACESSO DOS USUÁRIOS
    ui->cb_nv_acesso->addItem("-");
    ui->cb_nv_acesso->addItem("Administrador");
    ui->cb_nv_acesso->addItem("Funcionário");
    ui->cb_ge_acesso->addItem("-");
    ui->cb_ge_acesso->addItem("Administrador");
    ui->cb_ge_acesso->addItem("Funcionário");
    ui->txt_nv_nome->setFocus();

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_ge_listausuario->setColumnCount(3); //define que o table widget terá duas colunas
    ui->tw_ge_listausuario->setColumnWidth(0, 40); //id colaborador
    ui->tw_ge_listausuario->setColumnWidth(1, 220); //nome colaborador
    ui->tw_ge_listausuario->setColumnWidth(2, 202); //nome usuario

    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Nome", "Usuario", "Senha", "Tipo de Acesso"};
    ui->tw_ge_listausuario->setHorizontalHeaderLabels( cabecalhos );
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_listausuario->setStyleSheet("QTableView "
                                      "{selection-background-color:#F7BA4D}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_listausuario->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_listausuario->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_listausuario->verticalHeader()->setVisible(false);

}//**FIM construtor

frm_gestaousuarios::~frm_gestaousuarios()//** destrutor
{
    con.fechar(); //fechando conexao com o banco de dados

    delete ui;
}

//novo usuário
void frm_gestaousuarios::on_btn_nv_novo_clicked()
{
    ui->txt_nv_nome->clear();
    ui->txt_nv_usuario->clear();
    ui->txt_nv_senha->clear();
    ui->cb_nv_acesso->setCurrentIndex(0); //deixa o A por padrão no combo box;
    ui->txt_nv_nome->setFocus();
}

//salvar novo usuário
void frm_gestaousuarios::on_btn_nv_gravar_clicked()
{
    QString nome = ui->txt_nv_nome->text(); //armazena o codigo
    QString usuario = ui->txt_nv_usuario->text();
    QString senha = ui->txt_nv_senha->text();
    QString acesso = ui->cb_nv_acesso->currentText(); //combo box

    //define o acesso para os tipos do banco de dados
    acesso = funcoes_globais::ajustaTipoAcesso( acesso );

    QSqlQuery query; //query insersao de colaboradores na tabela tb_colaboradores

    //inserir
    query.prepare("INSERT INTO "
                    "a001_usuarios(a001_nome            "
                                 ",a001_usuario         "
                                 ",a001_senha           "
                                 ",a001_tipo_acesso)    "
                  "VALUES('" +nome      +  "'"
                        ",'" +usuario   +  "'"
                        ",'" +senha     +  "'"
                        ",'" +acesso    +  "') ");

    if( !query.exec() ) //verifica se a query tem algum erro e executa ela
    {
        QMessageBox::critical(this, "ERRO", "Nome de usuário já existe, escolha outro");
    }
    else
    {
        QMessageBox::information(this, "Salvo", "Usuario salvo com sucesso");
        ui->txt_nv_nome->clear(); //armazena o codigo
        ui->txt_nv_usuario->clear();
        ui->txt_nv_senha->clear();
        ui->cb_nv_acesso->setCurrentIndex(0); //padrão do combobox
        ui->txt_nv_nome->setFocus();
    }
}

//quando ocorrer mudança na aba
void frm_gestaousuarios::on_tabWidget_currentChanged(int index)
{
    if( index == 1 ) //verifica a interface pelo index das tabs
    {
        //configurando combo box filtro
        ui->cb_ge_filtrar->addItem("-");
        ui->cb_ge_filtrar->addItem("Nome");
        ui->cb_ge_filtrar->addItem("Usuário");

        ui->txt_ge_filtrar->setFocus();

        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_ge_listausuario );
        //inserir linhas dentro do table widget
        int contlinhas=0;
        //Remover os produtos do table widget
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a001_codigo    "
                          ",a001_nome     "
                          ",a001_usuario  "
                      "FROM "
                          "a001_usuarios "
                      "WHERE "
                        "a001_ativo = true "
                      "ORDER BY "
                          "a001_codigo DESC");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_ge_listausuario->insertRow(contlinhas);
                ui->tw_ge_listausuario->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_ge_listausuario->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_ge_listausuario->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                //definindo o tamanho das linhas
                ui->tw_ge_listausuario->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar usuarios");
        }
    }
    else if( index == 0 )
    {
        funcoes_globais::removerLinhas( ui->tw_ge_listausuario );

        ui->txt_ge_nome->clear();
        ui->txt_ge_usuario->clear();
        ui->txt_ge_senha->clear();
        ui->cb_ge_acesso->setCurrentIndex(0);
    }
}

//mostrar dados TW
void frm_gestaousuarios::on_tw_ge_listausuario_itemSelectionChanged()
{
    //pega a linha selecionada
    int id=ui->tw_ge_listausuario->item(ui->tw_ge_listausuario->currentRow()
                                        , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                    "* "
                  "FROM "
                    "a001_usuarios "
                  "WHERE "
                    "a001_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() ) //verifica se a query foi bem sucedida
    {
        query.first(); //pega o primeiro
        ui->txt_ge_nome->setText(query.value(1).toString()); //valor 0 é do id
        ui->txt_ge_usuario->setText(query.value(2).toString());
        ui->txt_ge_senha->setText(query.value(3).toString());
        QString verificaStatus = query.value(4).toString();

        //verifica o status do seriço e muda o indice do combo box
        if( verificaStatus == "A" )
        {
            ui->cb_ge_acesso->setCurrentIndex(1);
            //ui->cb_ge_acesso->currentIndexChanged(1);
        }
        else if( verificaStatus == "B" )
        {
            ui->cb_ge_acesso->setCurrentIndex(2);
        }
    }
}

//filtrar registros
void frm_gestaousuarios::on_txt_ge_filtro_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Nome" << "Usuário";


    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_ge_listausuario );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_ge_filtrar->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                       "a001_codigo       "
                       ",a001_nome        "
                       ",a001_usuario     "
                   "FROM "
                       "a001_usuarios "
                   "WHERE "
                       "a001_ativo = true "
                   "ORDER BY "
                       "a001_codigo DESC";
        }
        else
        {
            busca = "SELECT "
                       "a001_codigo       "
                       ",a001_nome        "
                       ",a001_usuario     "
                   "FROM "
                       "a001_usuarios "
                   "WHERE "
                       "a001_ativo = true "
                   "ORDER BY "
                       "a001_codigo DESC";
        }
    }
    else
    {
        cb_opc << "Nome" << "Usuário" << "Tipo Acesso";
        //consulta de acordo com a seleção do combo box
        switch( cb_opc.indexOf( cb_filtro ) )
        {
            //Nome
            case 0:

                filtro_sql = "a001_nome LIKE '%" +txt_filtro+ "%' ";
                break;
            //Usuário
            case 1:

                filtro_sql = "a001_usuario LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                   "a001_codigo       "
                   ",a001_nome        "
                   ",a001_usuario     "
               "FROM "
                   "a001_usuarios "
               "WHERE "
                   + filtro_sql +
                   "AND a001_ativo = true "
               "ORDER BY "
                   "a001_codigo DESC";
    }

    //contador para percorrer linhas
    int contlinhas = 0;
    QSqlQuery query;
    query.prepare( busca );

    if( query.exec() ) //executa a query
       {
           while( query.next() ) //percorrendo query e preenchendo table widget
           {
               //inserindo com contador de linhas, por index
               ui->tw_ge_listausuario->insertRow(contlinhas);
               ui->tw_ge_listausuario->setItem(contlinhas
                                           , 0
                                           , new QTableWidgetItem(query.value(0).toString()));

               ui->tw_ge_listausuario->setItem(contlinhas
                                           , 1
                                           , new QTableWidgetItem(query.value(1).toString()));

               ui->tw_ge_listausuario->setItem(contlinhas
                                           , 2
                                           , new QTableWidgetItem(query.value(2).toString()));

               //definindo o tamanho das linhas
               ui->tw_ge_listausuario->setRowHeight(contlinhas, 20);
               contlinhas ++;
           }
       }
       else
       {
           QMessageBox::warning(this, "ERRO", "Erro ao filtrar usuários");
       }

       ui->txt_ge_filtrar->clear();
       ui->txt_ge_filtrar->setFocus();
}

//botao filtrar registros
void frm_gestaousuarios::on_btn_ge_filtrar_clicked()
{
    frm_gestaousuarios::on_txt_ge_filtro_returnPressed();
}

//gravar alteração no usuário
void frm_gestaousuarios::on_btn_ge_salvar_clicked()
{
    if( ui->tw_ge_listausuario->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um usuário");
        return;
    }

    QString id = ui->tw_ge_listausuario->item(ui->tw_ge_listausuario->currentRow()
                                              ,0)->text();
    QSqlQuery query;

    QString nome = ui->txt_ge_nome->text();
    QString usuario = ui->txt_ge_usuario->text();
    QString senha = ui->txt_ge_senha->text();
    QString acesso = ui->cb_ge_acesso->currentText();

    acesso = funcoes_globais::ajustaTipoAcesso( acesso );

    query.prepare("UPDATE "
                    "a001_usuarios "
                  "SET "
                    "a001_nome          ='" +nome    + "' "
                    ",a001_usuario      ='" +usuario + "' "
                    ",a001_senha        ='" +senha   + "' "
                    ",a001_tipo_acesso  ='" +acesso  + "' "
                  "WHERE "
                    "a001_codigo ='" +id+ "'");

    if( query.exec() ) //executa a query
    {
        //pega a linha que está selecionada
        int linha=ui->tw_ge_listausuario->currentRow();
        //atualizando o table widget com o novo registro
        ui->tw_ge_listausuario->item(linha, 1)->setText( nome );

        QMessageBox::information(this, "Atualizado", "Usuário atualizado com sucesso!");
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao atualizar usuário");
    }
}

//excluir colaborador
void frm_gestaousuarios::on_btn_ge_excluir_clicked()
{
    if( ui->tw_ge_listausuario->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um usuário");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão do usuario?"
                                      ,QMessageBox::Yes|QMessageBox::No); //revisar tabulação

    if( opc == QMessageBox::Yes ) //verificando o botao da caixa question
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_ge_listausuario->currentRow();
        QString id = ui->tw_ge_listausuario->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a001_usuarios "
                      "SET "
                        "a001_ativo = false "
                      "WHERE "
                        "a001_codigo ='" +id+ "'");

        if( query.exec() ) //executa a query
        {
            ui->tw_ge_listausuario->removeRow( linha );
            QMessageBox::information(this, "DELETADO", "Usuario excluído com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir usuario");
        }
    }
}


