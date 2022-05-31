#include "frm_gestaovendas.h"
#include "ui_frm_gestaovendas.h"

frm_gestaovendas::frm_gestaovendas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaovendas)
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

    //**LISTA VENDAS**
    //tornar o cabeçalho horizontal visivel
    ui->tw_listaVendas->horizontalHeader()->setVisible(true);
    //definindo numero de colunas, são seis colunas
    ui->tw_listaVendas->setColumnCount(6);
    ui->tw_listaVendas->setColumnWidth(0, 40);
    ui->tw_listaVendas->setColumnWidth(1, 200);

    QStringList cabe1 = {"Código","Usuário", "Data", "Hora","V.Total", "M.Lucro"};

    //nome dos cabeçalhos do table widget
    ui->tw_listaVendas->setHorizontalHeaderLabels( cabe1 );
    //definindo cor da linha ao ser selecionada
    ui->tw_listaVendas->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //redimenciona de acordo com o tamanho do conteúdo
    ui->tw_listaVendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //coluna
    ui->tw_listaVendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //bloqueando edição do table widget
    ui->tw_listaVendas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //pegando linha selecionada
    ui->tw_listaVendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listaVendas->verticalHeader()->setVisible(false);


    //listando vendas
    int contlinhas = 0;
    QSqlQuery query;
    query.prepare("SELECT "
                      "a007_codigo                             "
                      ",a001_nome                              "
                      ",TO_CHAR(a007_data_venda, 'DD/MM/YYYY') "
                      ",a007_hora_venda                        "
                      ",a007_valor_total                       "
                      ",a007_margem_lucro                      "
                  "FROM "
                    "a007_vendas "
                    "JOIN a001_usuarios ON (a001_codigo = a007_fk_codigo_usuario) "
                  "WHERE "
                    "a007_ativo = true");

    if( !query.exec() ) //verifica se a query tem algum erro e executa ela
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar vendas");

    }
    query.first();

    //inserindo elementos no table widget
    do
    {
        //linha, coluna e item
        ui->tw_listaVendas->insertRow( contlinhas );
        ui->tw_listaVendas->setItem(contlinhas, 0,
                                                new QTableWidgetItem(query.value(0).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 1,
                                                new QTableWidgetItem(query.value(1).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 2,
                                                new QTableWidgetItem(query.value(2).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 3,
                                                new QTableWidgetItem(query.value(3).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 4,
                                                new QTableWidgetItem(query.value(4).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 5,
                                                new QTableWidgetItem(query.value(5).toString()));
        contlinhas++;
    }while( query.next() );

    //**LISTA PRODUTOS**
    ui->tw_listaProdutos->horizontalHeader()->setVisible(true);
    ui->tw_listaProdutos->setColumnCount(6);
    QStringList cabe2 = {"Código Mov", "Produto", "Qtde"
                         , "Val.Uni", "Val.Total", "M.Lucro"};

    ui->tw_listaProdutos->setHorizontalHeaderLabels(cabe2);
    ui->tw_listaProdutos->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    ui->tw_listaProdutos->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_listaProdutos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_listaProdutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_listaProdutos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listaProdutos->verticalHeader()->setVisible(false);

}

frm_gestaovendas::~frm_gestaovendas() //**INICIO** destrutor
{
    con.fechar();
    delete ui;
}

//lista produtos TW
void frm_gestaovendas::on_tw_listaVendas_itemSelectionChanged()
{
    //limpando table widget
    funcoes_globais::removerLinhas( ui->tw_listaProdutos );

    QString codigo_venda = ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(),0)->text();

    int contlinhas = 0;

    QSqlQuery query;
    query.prepare("SELECT "
                    "a006_codigo           "
                    ",a006_denomicanao     "
                    ",a006_qtde_vendida    "
                    ",a006_valor_unitario  "
                    ",a006_valor_total     "
                    ",a006_margem_lucro    "
                  "FROM "
                    "a006_estoque_vendas "
                    "JOIN a007_vendas on (a007_codigo = a006_fk_codigo_venda) "
                  "WHERE "
                    "a006_fk_codigo_venda = '" +codigo_venda+ "'");

    if( !query.exec() )
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar vendas");
        qDebug() << "ERRO: " << query.lastError().text();
    }

    query.first();

    //inserindo elementos no table widget
    do
    {
        //linha, coluna e item
        ui->tw_listaProdutos->insertRow( contlinhas );
        ui->tw_listaProdutos->setItem(contlinhas, 0,
                                                new QTableWidgetItem(query.value(0).toString()));

        ui->tw_listaProdutos->setItem(contlinhas, 1,
                                               new QTableWidgetItem(query.value(1).toString()));

        ui->tw_listaProdutos->setItem(contlinhas, 2,
                                               new QTableWidgetItem(query.value(2).toString()));

        ui->tw_listaProdutos->setItem(contlinhas, 3,
                                               new QTableWidgetItem(query.value(3).toString()));

        ui->tw_listaProdutos->setItem(contlinhas, 4,
                                               new QTableWidgetItem(query.value(4).toString()));

        ui->tw_listaProdutos->setItem(contlinhas, 5,
                                                new QTableWidgetItem(query.value(5).toString()));

        contlinhas++;
    }while( query.next() );
}

//btn filtrar vendas por data
void frm_gestaovendas::on_btn_filtrar_clicked()
{
    //limpando table widget
    funcoes_globais::removerLinhas( ui->tw_listaVendas );

    int contlinhas=0;

    QString data_inicial = ui->de_datainicial->text();
    QString data_final = ui->de_datafinal->text();

    QSqlQuery query;

    //mudar formatação de data no banco de dados, tela novavenda e nos campos de data na interface
    query.prepare("SELECT "
                      "a007_codigo                              "
                      ",a001_nome                               "
                      ",TO_CHAR(a007_data_venda, 'DD/MM/YYYY')  "
                      ",a007_hora_venda                         "
                      ",a007_valor_total                        "
                      ",a007_margem_lucro                       "
                 "FROM "
                     "a007_vendas "
                     "JOIN a001_usuarios ON (a001_codigo = a007_fk_codigo_usuario) "
                 "WHERE "
                    "a007_ativo = true "
                    "AND a007_data_venda "
                  "BETWEEN '" +data_inicial+ "' AND '" +data_final+ "'");

    if( !query.exec() )
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar vendas");

    }
    query.first();

    //inserindo elementos no table widget
    do
    {
        //linha, coluna e item
        ui->tw_listaVendas->insertRow(contlinhas);
        ui->tw_listaVendas->setItem(contlinhas, 0,
                                            new QTableWidgetItem(query.value(0).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 1,
                                            new QTableWidgetItem(query.value(1).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 2,
                                            new QTableWidgetItem(query.value(2).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 3,
                                            new QTableWidgetItem(query.value(3).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 4,
                                            new QTableWidgetItem(query.value(4).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 5,
                                            new QTableWidgetItem(query.value(5).toString()));

        contlinhas++;
    }while( query.next() );
}

//btn mostra todas as vendas
void frm_gestaovendas::on_btn_mostratTodasVendas_clicked()
{
    funcoes_globais::removerLinhas( ui->tw_listaVendas );

    int contlinhas = 0;

//    QStringList cabe2 = {"Código Mov", "Produto", "Qtde"
//                         , "Val.Uni", "Val.Total", "M.Lucro"};

    QSqlQuery query;

    //mudar formatação de data no banco de dados, tela novavenda e nos campos de data na interface
    query.prepare("SELECT "
                      "a007_codigo                              "
                      ",a001_nome                               "
                      ",TO_CHAR(a007_data_venda, 'DD/MM/YYYY')  "
                      ",a007_hora_venda                         "
                      ",a007_valor_total                        "
                      ",a007_margem_lucro                       "
                  "FROM "
                      "a007_vendas "
                      "JOIN a001_usuarios ON (a001_codigo = a007_fk_codigo_usuario) "
                  "WHERE "
                      "a007_ativo = true ");

    if(!query.exec())
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar vendas");

    }
    query.first();

    //inserindo elementos no table widget
    do
    {
        //linha, coluna e item
        ui->tw_listaVendas->insertRow(contlinhas);
        ui->tw_listaVendas->setItem(contlinhas, 0,
                                                new QTableWidgetItem(query.value(0).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 1,
                                                new QTableWidgetItem(query.value(1).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 2,
                                                new QTableWidgetItem(query.value(2).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 3,
                                                new QTableWidgetItem(query.value(3).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 4,
                                                new QTableWidgetItem(query.value(4).toString()));

        ui->tw_listaVendas->setItem(contlinhas, 5,
                                                new QTableWidgetItem(query.value(5).toString()));

        contlinhas++;
    }while( query.next() );
}

//btn gerar relatório de vendas
void frm_gestaovendas::on_btn_relatorio_clicked()
{
    //nome do relatório de acordo com o id da venda
    QString nome = ui->tw_listaVendas->
                  item(ui->tw_listaVendas->currentRow(), 0)->text() + "_vendas.pdf";

    //**Verificar**variavel armazena a pasta local do programa
    QString local = QDir::currentPath() + "/Relatorios";

    //definindo formado do arquivo
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(local + "/" + nome);

    //inserindo conteúdo no arquivo PDF
    QPainter painter;
    if( !painter.begin( &printer ) ) //iniciando o arquivo
    {
        QMessageBox::information(this, "Erro", "Não foi possível emitir relatório");
        qDebug() << "ERRO ao abrir PDF";
        return; //sai do procedimento e executa a proxima parte do código
    }

    //**FORMATANDO PDF**
    //adicionando imagens
    //primeiro valor: eixo horizontal
    //segundo valor: eixo vertical
    painter.drawPixmap( 200, -100, QPixmap(":/Imagens/car.png") );

    //**DADOS DA VENDA (a007)**
    //--Título
    painter.drawText(340,200,"DADOS VENDA");

    //**itens cabeçalho**
    painter.drawText(25, 250,"Código");
    painter.drawText(130,250,"Usuário");
    painter.drawText(295,250,"Data");
    painter.drawText(415,250,"Hora");
    painter.drawText(540,250,"Val. Total");
    painter.drawText(640,250,"Margem Lucro");

    //**itens dados relatorio
    QString codigo_venda = ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 0)->text();
    QString usuario_venda = ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 1)->text();
    QString data_venda = ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 2)->text();
    QString hora_venda = ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 3)->text();
    QString valor_total = ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 4)->text();
    QString lucro = ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(), 5)->text();

    painter.drawText(25, 300, codigo_venda);
    painter.drawText(130,300, usuario_venda);
    painter.drawText(295,300, data_venda);
    painter.drawText(415,300, hora_venda);
    painter.drawText(540,300, valor_total);
    painter.drawText(640,300, lucro);

    //**DADOS DA VENDA ITENS RELATÓRIO (a006)**
    //--Título
    painter.drawText(340,400,"ITENS VENDA");

    //**itens cabeçalho**
    painter.drawText(25, 450,"Código");
    painter.drawText(130,450,"Produto");
    painter.drawText(295,450,"Qtde");
    painter.drawText(415,450,"Val.Uni");
    painter.drawText(540,450,"Val.Total");
    painter.drawText(640,450,"M.Lucro");

    //--Itens venda
    //a006_codigo
    //a006_denomicanao
    //a006_qtde_vendida
    //a006_valor_unitario
    //a006_valor_total
    //a006_margem_lucro

    //informando localização, coluna e linha
    int linha = 500;
    int salto = 20;

    for( int i = 0; i < ui->tw_listaProdutos->rowCount(); i++ )
    {
        //produtos da venda
        painter.drawText(25,linha, ui->tw_listaProdutos->item(i, 0)->text());
        painter.drawText(130,linha, ui->tw_listaProdutos->item(i, 1)->text());
        painter.drawText(295,linha, ui->tw_listaProdutos->item(i, 2)->text());
        painter.drawText(415,linha, ui->tw_listaProdutos->item(i, 3)->text());
        painter.drawText(540,linha, ui->tw_listaProdutos->item(i, 4)->text());
        painter.drawText(640,linha, ui->tw_listaProdutos->item(i, 5)->text());
        linha += salto;
    }

    //adicionando nova página
    //printer.newPage();
    painter.drawText(25, 1000, "Relatório de vendas");

    // finaliza e gera o PDF
    painter.end();

    //abrir o arquivo pdf gerado
    QDesktopServices::openUrl(QUrl("file:///" + local + "/" + nome));
}



