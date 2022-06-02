#include "frm_ordemservico.h"
#include "ui_frm_ordemservico.h"
#include "frms_selecionacliente_os.h" //formulario de seleção de clientes

frm_ordemservico::frm_ordemservico(QWidget *parent, QString c_codigo_cliente
                                                  , QString c_nome_cliente
                                                  , QString c_codigo_veiculo
                                                  , QString c_nome_veiculo
                                                  , QString c_placa_veiculo
                                                  , QString c_cor_veiculo) :
    QDialog(parent),
    ui(new Ui::frm_ordemservico)
{
    ui->setupUi(this);

    //abrindo a conexao com o banco
    if( !con.abrir() )
    {
        if( !con.abrir() )
        {
            QMessageBox::warning(this, "ERRO", "Erro ao abrir banco de dados");
        }
    }


    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    /*configurando combo box
    ui->cb_ge_filtrar->addItem("-");
    ui->cb_ge_filtrar->addItem("Razão Social");
    ui->cb_ge_filtrar->addItem("Nome Fantasia");
    ui->cb_ge_filtrar->addItem("CNPJ");
    ui->cb_ge_filtrar->addItem("Ocupação da empresa");
    ui->cb_ge_filtrar->addItem("Cidade");
    */

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_listapecas->setColumnCount(9);
    ui->tw_listapecas->setColumnWidth(0, 40);
    ui->tw_listapecas->setColumnWidth(1, 200);


    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Fornecedor", "Nc. Peça","Denominacao",
                            "Grupo", "Val. Compra", "Val. Venda", "Qtde. Estoque", "Pos. Prateleira"};

    ui->tw_listapecas->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_listapecas->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listapecas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listapecas->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listapecas->verticalHeader()->setVisible(false);

    //***RECEBENDO DADOS DO SELECIONACLIENTE_OS***
    //recebendo dados cliente
    g_codigo_cliente = c_codigo_cliente;
    ui->txt_proprietarioVeiculo->setText( c_nome_cliente );


    //recebendo dados veiculo
    g_codigo_veiculo = c_codigo_veiculo;
    ui->txt_nomeVeiculo->setText( c_nome_veiculo );
    ui->txt_placaVeiculo->setText( c_placa_veiculo );
    ui->txt_corVeiculo->setText( c_cor_veiculo );

    ui->lbl_pecasModelo->setText("Peças: " + c_nome_veiculo);

    if( g_codigo_cliente != "" && g_codigo_veiculo != "" )
    {
        //inserir linhas dentro do table widget
        int contlinhas = 0;

        QSqlQuery query;

        query.prepare("SELECT "
                          "a002_codigo          "
                          ",a003_razao_social   "
                          ",a002_nc_peca        "
                          ",a002_denomicanao    "
                          ",a002_grupo          "
                          ",a002_valor_compra   "
                          ",a002_valor_venda    "
                          ",a002_qtde_estoque   "
                          ",a002_posicao_peca   "
                      "FROM "
                          "a002_estoque "
                          "JOIN a003_fornecedor ON (a003_codigo = a002_fk_codigo_forncedor) "
                          "JOIN a012_modelos    ON (a012_codigo = a002_fk_codigo_modelo)    "
                          "JOIN a004_veiculos   ON (a004_fk_codigo_modelo = a012_codigo)    "
                      "WHERE "
                        "a004_codigo = '" +g_codigo_veiculo+ "' "
                        "AND a002_ativo = true "
                      "ORDER BY "
                          "a002_codigo DESC");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_listapecas->insertRow( contlinhas );
                ui->tw_listapecas->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_listapecas->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_listapecas->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                ui->tw_listapecas->setItem(contlinhas
                                            , 3
                                            , new QTableWidgetItem(query.value(3).toString()));

                ui->tw_listapecas->setItem(contlinhas
                                            , 4
                                            , new QTableWidgetItem(query.value(4).toString()));

                ui->tw_listapecas->setItem(contlinhas
                                            , 5
                                            , new QTableWidgetItem(query.value(5).toString()));

                ui->tw_listapecas->setItem(contlinhas
                                            , 6
                                            , new QTableWidgetItem(query.value(6).toString()));

                ui->tw_listapecas->setItem(contlinhas
                                            , 7
                                            , new QTableWidgetItem(query.value(7).toString()));

                ui->tw_listapecas->setItem(contlinhas
                                            , 8
                                            , new QTableWidgetItem(query.value(8).toString()));

                //definindo o tamanho das linhas
                ui->tw_listapecas->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar as peças do modelo");
        }
    }

}

frm_ordemservico::~frm_ordemservico() //**INICIO** destrutor
{
    con.fechar();
    delete ui;
}

//seleciona dados cliente/veiculo O.S
void frm_ordemservico::on_btn_selecionaveiculo_clicked()
{
    frms_selecionacliente_os *fmSelecionaClienteOS = new frms_selecionacliente_os();

    fmSelecionaClienteOS->exec();

    //deletando ponteiro
    try
    {
        delete fmSelecionaClienteOS;
    }
    catch ( ... )
    {
        qDebug() << "__Falha ao deletar ponteiro: fmSelecionaClienteOS na tela de agendaserviços";
    }

    close();
}

