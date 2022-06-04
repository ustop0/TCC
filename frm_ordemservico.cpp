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


    //**Estilizando layout da tw_pecasOS**
    //definindo o tamanho das colunas
    ui->tw_pecasOS->setColumnCount(5);
    ui->tw_pecasOS->setColumnWidth(0, 40);
    ui->tw_pecasOS->setColumnWidth(1, 220);

    //cabeçalhos do table widget, itens venda
    QStringList cabecalho2 = {"Código", "Produto", "Valor Un.", "Qtde", "Total"};

    ui->tw_pecasOS->setHorizontalHeaderLabels( cabecalho2 );
    //definindo cor da linha ao ser selecionada
    ui->tw_pecasOS->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_pecasOS->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_pecasOS->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_pecasOS->verticalHeader()->setVisible(false);


    //configurando combo box meio pagamento
    ui->cb_meiopagamento->addItem("-");
    ui->cb_meiopagamento->addItem("À vista");
    ui->cb_meiopagamento->addItem("PIX");
    ui->cb_meiopagamento->addItem("Xeque");
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

//pegando peças TW Modelo
void frm_ordemservico::on_tw_listapecas_itemSelectionChanged()
{
    //pega a linha selecionada
    int id = ui->tw_listapecas->item(ui->tw_listapecas->currentRow()
                                   , 0) ->text().toInt();

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a002_codigo        "
                      ",a002_denomicanao  "
                      ",cast(cast(a002_valor_compra  as decimal) as varchar) "
                      ",cast(cast(a002_valor_venda  as decimal) as varchar) "
                      ",a002_qtde_estoque "
                      ",a002_posicao_peca "
                  "FROM "
                    "a002_estoque "
                    "JOIN a003_fornecedor ON (a003_codigo = a002_fk_codigo_forncedor) "
                    "JOIN a012_modelos ON (a012_codigo = a002_fk_codigo_modelo) "
                  "WHERE "
                    "a002_codigo = '" +QString::number(id)+ "' ");

    if( query.exec() )
    {
        query.first();

        //Não pegamos o nome do fornecedor
        ui->txt_codigopeca->setText(query.value(0).toString());
        ui->txt_qtdeEstoque->setText(query.value(4).toString());

        g_codigo_peca = ui->txt_codigopeca->text();
        g_qtde = ui->txt_qtdeEstoque->text();

        g_denominacao = query.value(1).toString();
        g_valor_unitario = query.value(3).toString();
        g_valor_comprado = query.value(2).toString();

        //g_valor_total;
    }
}

//adicionar produto a lista
void frm_ordemservico::on_btn_adicionarItem_clicked()
{
    int contlinhas = 0;
    double valor_total;
    double margem_lucro;
    QString qtde_venda;
    QString qtde_estoque = g_qtde;


    //verifica se a quantidade informada é maior que a quantidade em estoque
    if( ui->txt_qtde->text() > qtde_estoque )
    {
        QMessageBox::information(this
                                 ,"Aviso"
                                 ,"Valor informado para o produto"
                                  " acima do valor do estoque para esse produto");

        ui->txt_qtde->setText("1");
        ui->txt_qtde->setFocus();
    }
    else if( ui->txt_qtde->text() == "" ||  ui->txt_qtde->text() == "0" )
    {
        QMessageBox::information(this
                                 ,"Aviso"
                                 ,"Não foi informado nenhum valor para a quantidade do produto");

        ui->txt_qtde->setText("1");
        ui->txt_qtde->setFocus();
    }
    else
    {
        qtde_venda = ui->txt_qtde->text();

        //calculando o valor total do produto(quantidade * valor_venda)
        valor_total = ui->txt_qtde->text().toDouble() * g_valor_unitario.toDouble();
        margem_lucro = valor_total - g_valor_comprado.toDouble();

        //se valor da query for vazio, produto não encontrado
        if( g_codigo_peca != "")
        {
            //inserindo com contador de linhas, por index
            ui->tw_pecasOS->insertRow( contlinhas );
            ui->tw_pecasOS->setItem(contlinhas
                                          , 0
                                          , new QTableWidgetItem( g_codigo_peca ));

            ui->tw_pecasOS->setItem(contlinhas
                                          , 1
                                          , new QTableWidgetItem( g_denominacao ));

            ui->tw_pecasOS->setItem(contlinhas
                                          , 2
                                          , new QTableWidgetItem( g_valor_unitario ));

            //qtde produtos
            ui->tw_pecasOS->setItem(contlinhas
                                          , 3
                                          , new QTableWidgetItem( qtde_venda ));

            ui->tw_pecasOS->setItem(contlinhas
                                          , 4
                                          , new QTableWidgetItem( QString::number(valor_total) ));


            ui->tw_pecasOS->setRowHeight(contlinhas, 20);
            contlinhas ++;

             //**DEBUGAR**, o não está retornando um numero em DOUBLE, manipular string
            //Label que exibe o valor total de todos os produtos(debugar)
            ui->lb_totalvenda->setText("R$ "+QString::number(
                                           calculaTotal(ui->tw_pecasOS, 4))+",00");

            /*

            calculaTotal(margem_lucro)+",00";

            */

            //atualiza a quantidade de produtos da tabela estoque(sem UPDATE)
             int atualiza_qtde;
             atualiza_qtde = qtde_estoque.toInt() - qtde_venda.toInt();

             //adiciona ao valor da qtde
             g_qtde = QString::number( atualiza_qtde );
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao inserir o produto na lista");
        }
    }
}

//remover peça da lista
void frm_ordemservico::on_btn_removerItem_clicked()
{
    if( ui->tw_pecasOS->currentColumn() != -1 )
    {
        QMessageBox::StandardButton opc =QMessageBox::question(this
                                                               ,"Remover peça?"
                                                               ,"Confirma Remoção"
                                                               ,QMessageBox::Yes|QMessageBox::No);

        if( opc == QMessageBox::Yes )
        {
            //**REVISAR ESSA FUNÇÃO
            int contlinhas = 0;

            //removendo o produto selecionado e recalculando o total da venda
            ui->tw_pecasOS->removeRow( ui->tw_pecasOS->currentRow() );
            ui->lb_totalvenda->setText("R$ "
                                       +QString::number(
                                                   calculaTotal(ui->tw_pecasOS, 4))+",00");

            contlinhas--; //excluindo linha depois que o produto é excluido

        }
        else
        {

        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Selecione uma peça primeiro");
    }
}

//Salvar O.S.
void frm_ordemservico::on_btn_salvaros_clicked()
{
    //gravas as informações na tabela de venda e obter o id da venda
    //verifica se tem produtos no table widget, para realizar uma venda
    int codigo_os;

    //**ATENÇÃO** foi adicionada a coluna margem de lucro, inserindo lucro
    QString aux;
    QString msgFimOS;

    QString data = ui->de_entrada->text();
    QString km_veiculo = ui->txt_kmVeiculo->text();
    QString meio_pagamento = ui->cb_meiopagamento->currentText();
    QString valor_mao_obra = ui->txt_valorServico->text();
    QString valor_pecas = ui->lb_totalvenda->text();
    QString detalhes = ui->Ptxt_detalhesServico->toPlainText();

    aux = valor_mao_obra;
    std::replace(aux.begin(), aux.end(), ',', '.'); //substitui valores
    valor_mao_obra = aux;

    //aux = valor_pecas;
    //std::replace(aux.begin(), aux.end(), ',', '.'); //substitui valores
    //valor_pecas = aux;

    double total_servico = valor_mao_obra.toDouble() + valor_pecas.toDouble();


    //inserindo dados da venda na tabela de vendas
    QSqlQuery query;
    query.prepare("INSERT INTO "
                    "a010_OS(a010_data_entrada              "
                            ",a010_km_veiculo               "
                            ",a010_valor_mao_obra           "
                            ",a010_valor_total_mercadorias  "
                            ",a010_valor_total_servico      "
                            ",a010_meio_pagamento           "
                            ",a010_detalhes_servico         "
                            ",a010_fk_codigo_veiculo)       "
                  "VALUES('"+data                                 + "'"
                        ",'"+km_veiculo                           + "'"
                        ",'"+valor_mao_obra                       + "'"
                        ",'"+valor_pecas                          + "'"
                        ",'"+QString::number( total_servico )     + "'"
                        ",'"+meio_pagamento                       + "'"
                        ",'"+detalhes                             + "'"
                        ",'"+g_codigo_veiculo                     + "')");

    if( !query.exec() )
    {
        QMessageBox::warning(this, "ERRO", "Erro ao registrar nova O.S.");
    }
    else
    {
        //obtém o último registro, query limitada a um registro
        query.prepare("SELECT "
                        "a010_codigo "
                      "FROM "
                        "a010_OS "
                      "ORDER BY "
                        "a010_codigo DESC LIMIT 1");

        query.exec();
        query.first();

        //obtem o id da venda
        codigo_os = query.value(0).toInt();

        msgFimOS="ID O.S.: " +QString::number( codigo_os )
                              +"\nValor total da O.S.: R$ "
                              +QString::number( total_servico )+",00";


        //inserindo venda na tabela estoque_vendas
        //leitura da quantidade total de linhas
        int totalLinhas = ui->tw_pecasOS->rowCount();
        int linha = 0; //linha que está fazendo a leitura

        while( linha < totalLinhas ) //percorre o table widget
        {
            QString codigo_peca = ui->tw_pecasOS->item(linha,0)->text();

            //DEPURAR NÃO ESTÁ REGISTRANDO AS VENDAS NA TABELA DE VENDAS
            //verificar querys, valores int normal e varchar em '" "'
            query.prepare("INSERT INTO "
                            "a015_os_itens(a015_fk_codigo_os    "
                                         ",a015_fk_codigo_peca) "
                          "VALUES('" +QString::number( codigo_os )   + "'"
                                ",'" +codigo_peca                    + "') ");

            query.exec();

            //incrementa a variável para a próxima linha
            linha++;
        }

        QMessageBox::information(this, "O.S. gerada", msgFimOS);
        resetaCampos();

        //remove as linhas do table widget
        //funcoes_globais::removerLinhas( ui->tw_listapecas );
        //funcoes_globais::removerLinhas( ui->tw_pecasOS );
    }
}

//btn gerar OS PDF
void frm_ordemservico::on_btn_geraros_clicked()
{
    //salvar a O.S. antes de gerar
    frm_ordemservico::on_btn_salvaros_clicked();

    QSqlQuery query;
    query.prepare("SELECT "
                    "a010_codigo                    "
                    ",a010_valor_mao_obra           "
                    ",a010_valor_total_mercadorias  "
                    ",a010_valor_total_servico      "
                    ",a010_meio_pagamento           "
                  "FROM "
                    "a010_OS "
                  "ORDER BY "
                    "a010_codigo DESC LIMIT 1");

    //cast(cast(a002_valor_venda  as decimal) as varchar)

    query.exec();
    query.first();

    //obtem o id da venda
    QString codigo_os = query.value(0).toString();

    QMessageBox::information(this, "Código OS", "Código OS capturado"
                                   + query.value(0).toString());

    QString data_os = QDate::currentDate().toString("yyyy-MM-dd");

    //nome da OS de acordo com o id da venda
    QString nome = codigo_os + "-" + data_os + "_os.pdf";

    //**Verificar** variavel armazena a pasta local do programa
    QString local = QDir::currentPath() + "/O.S.";

    //definindo formado do arquivo
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(local + "/" + nome);

    //inserindo conteúdo no arquivo PDF
    QPainter painter;
    if( !painter.begin( &printer ) ) //iniciando o arquivo
    {
        QMessageBox::information(this, "Erro", "Não foi possível gerar a O.S.");
        qDebug() << "ERRO ao abrir PDF";
        return; //sai do procedimento e executa a proxima parte do código
    }

    //**FORMATANDO PDF**
    //adicionando imagens
    //primeiro valor: eixo horizontal
    //segundo valor: eixo vertical
    //painter.drawPixmap( 200, -100, QPixmap(":/Imagens/car.png") );
    painter.drawText(270, 50,"AMINCAR: ORDEM DE SERVIÇO");

    //**DADOS DA OS (a010)**
    //--Título
    painter.drawText(330,200,"DADOS O.S.");
    painter.drawText(25,220,"-------------------------------------------------------------"
                            "-------------------------------------------------------------"
                            "--------------------------------------");

    //*Cliente/Veiculo
    //**itens cabeçalho**
    painter.drawText(25, 250,"Código");
    painter.drawText(130,250,"Cliente");
    painter.drawText(295,250,"Veículo");
    painter.drawText(415,250,"Placa");
    painter.drawText(540,250,"Cor");
    painter.drawText(640,250,"KM");

    QString codigo = codigo_os;
    QString cliente = ui->txt_proprietarioVeiculo->text();
    QString modelo_veiculo = ui->txt_nomeVeiculo->text();
    QString placa_veiculo = ui->txt_placaVeiculo->text();
    QString cor_veiculo = ui->txt_corVeiculo->text();
    QString km_veiculo = ui->txt_kmVeiculo->text();

    //esses vetores incrementam as linhas do arquivo automaticamente

    painter.drawText(25, 300, codigo);
    painter.drawText(130,300, cliente);
    painter.drawText(295,300, modelo_veiculo);
    painter.drawText(415,300, placa_veiculo);
    painter.drawText(540,300, cor_veiculo);
    painter.drawText(640,300, km_veiculo);

    //*Informações OS
    //**itens cabeçalho**
    painter.drawText(25,370,"Data");
    painter.drawText(150,370,"V.Mão de Obra");
    painter.drawText(295,370,"V.Peças");
    painter.drawText(415,370,"V.Total Servico");
    painter.drawText(540,370,"M.Pgto");


    QString data_entrada = ui->de_entrada->text();
    QString valor_mao_obra = query.value(1).toString();
    QString valor_total_pecas = query.value(2).toString();
    QString valor_total_servico = query.value(3).toString();
    QString meio_pagamento = query.value(4).toString();;

    painter.drawText(25,410, data_entrada);
    painter.drawText(150,410, valor_mao_obra);
    painter.drawText(295,410, valor_total_pecas);
    painter.drawText(415,410, valor_total_servico);
    painter.drawText(540,410, meio_pagamento);

    //detalhes do serviço
    painter.drawText(25, 460,"Detalhes do Serviço: ");

    QString detalhes = ui->Ptxt_detalhesServico->toPlainText();

    painter.drawText(25, 500, detalhes);

    //**DADOS DA OS ITENS RELATÓRIO (a015)**
    //--Título
    painter.drawText(320,610, "ITENS DO SERVIÇO");
    painter.drawText(25,630,"-------------------------------------------------------------"
                            "-------------------------------------------------------------"
                            "--------------------------------------");


    //**itens cabeçalho**
    //--informações produtos/peças
    painter.drawText(25, 660, "Código");
    painter.drawText(130, 660, "Mercadoria");
    painter.drawText(295, 660, "Valor Un.");
    painter.drawText(415, 660, "Qtde");
    painter.drawText(540, 660, "V.Total");

    //--Itens venda são pegos do tw_pecasOS

    //informando localização, coluna e linha
    int linha = 710;
    int salto = 20;

    for( int i = 0; i < ui->tw_pecasOS->rowCount(); i++ )
    {
        //produtos da venda
        painter.drawText(25,linha, ui->tw_pecasOS->item(i, 0)->text());
        painter.drawText(130,linha, ui->tw_pecasOS->item(i, 1)->text());
        painter.drawText(295,linha, "R$ " + ui->tw_pecasOS->item(i, 2)->text());
        painter.drawText(415,linha, ui->tw_pecasOS->item(i, 3)->text());
        painter.drawText(540,linha, "R$ " + ui->tw_pecasOS->item(i, 4)->text());
        linha += salto;
    }

    //adicionando nova página
    //printer.newPage();
    painter.drawText(25, 1000, "O.S.");

    // finaliza e gera o PDF
    painter.end();

    //abrir o arquivo pdf gerado
    QDesktopServices::openUrl(QUrl("file:///" + local + "/" + nome));
}


/**FUNÇÕES**/
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 02/06/2022                                                                           |
 * Propósito: limpar os campos que indicam o codigo e qtde da peça                            |
 * Chamada:                                                                                   |
 *--------------------------------------------------------------------------------------------
 */
void frm_ordemservico::resetaCampos()
{
    ui->txt_codigopeca->clear();
    ui->txt_qtdeEstoque->clear();
    ui->txt_qtde->setText("1"); //volta quantidade para 1 no campo quantidade

    ui->de_entrada->setDate( QDate::fromString("01/01/2022") );
    ui->txt_kmVeiculo->clear();
    ui->cb_meiopagamento->setCurrentIndex(0);
    ui->txt_valorServico->clear();
    ui->Ptxt_detalhesServico->toPlainText();
    ui->lb_totalvenda->setText("R$ 0,00");
}

/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 02/06/2022                                                                           |
 * Propósito: calcular o valor total das peças, no TW e no label                              |
 * Chamada:                                                                                   |
 *--------------------------------------------------------------------------------------------
 */
double frm_ordemservico::calculaTotal( QTableWidget *tw, int coluna )
{
    //recebe o numero de linhas (Row Count)
    size_t totallinhas;
    //somatório
    double total = 0.0;

    totallinhas = tw->rowCount();
    for( size_t i = 0; i < totallinhas; i++ )
    {
        total += tw->item(i, coluna)->text().toDouble();
    }

    return total;
}
