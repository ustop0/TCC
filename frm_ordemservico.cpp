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

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_listapecas->setColumnCount(9);
    ui->tw_listapecas->setColumnWidth(0, 40);
    ui->tw_listapecas->setColumnWidth(1, 200);


    //cabeçalhos do table widget
    QStringList cabecalho1={"Código", "Fornecedor", "Nc. Peça","Denominacao",
                            "Grupo", "Val. Compra", "Val. Venda", "Qtde. Estoque", "Pos. Prateleira"};

    ui->tw_listapecas->setHorizontalHeaderLabels( cabecalho1 );
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
    QStringList cabecalho2 = {"Código", "Denominação", "Valor Un.", "Qtde", "Total"};

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
    ui->cb_meiopagamento->addItem("À VISTA");
    ui->cb_meiopagamento->addItem("PIX");
    ui->cb_meiopagamento->addItem("XEQUE");
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
                    ",a010_km_veiculo               "
                  "FROM "
                    "a010_OS "
                  "ORDER BY "
                    "a010_codigo DESC LIMIT 1");

    //cast(cast(a002_valor_venda  as decimal) as varchar)

    query.exec();
    query.first();

    //obtem o id da venda
    QString codigo_os = query.value(0).toString();
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
    QString km_veiculo = query.value(5).toString();

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
    painter.drawText(25, 480,"Detalhes do Serviço: ");

    QString detalhes = ui->Ptxt_detalhesServico->toPlainText();

    painter.drawText(25, 520, detalhes);

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

    //atualizando o status do serviço
    query.prepare("UPDATE "
                    "a010_OS "
                  "SET "
                    "a010_status = 'CONCLUÍDA' "
                  "WHERE "
                    "a010_codigo ='" +codigo+ "'");

    if( !query.exec() )
    {
        QMessageBox::information(this, "ERRO", "Não foi possível atualizar o status da O.S.");
    }

    //abrir o arquivo pdf gerado
    QDesktopServices::openUrl(QUrl("file:///" + local + "/" + nome));
}

//quando ocorrer mudança na aba do tab widget
void frm_ordemservico::on_tabWidget_currentChanged(int index)
{
    if( index == 1 ) //verifica a interface pelo index das tabs
    {
        //funções que configuram os TWs
        conf_tw_ge_listaOS();
        conf_tw_ge_pecasOS();

        //**PREENCHENDO TW_listaOS**
        //limpa as linhas do table widget
        funcoes_globais::removerLinhas( ui->tw_listaOS );
        //inserir linhas dentro do table widget
        int contlinhas = 0;
        //Remover os produtos do table widget
        QSqlQuery query; //query para listar os colaboradores no table widget
        query.prepare("SELECT "
                          "a010_codigo                    "
                          ",a005_nome                     "
                          ",a012_nome_veiculo             "
                          ",a004_placa_veiculo            "
                          ",a004_cor_veiculo              "
                          ",a010_km_veiculo               "
                          ",a010_data_entrada             "
                          ",a010_status                   "
                          ",a010_valor_mao_obra           "
                          ",a010_valor_total_mercadorias  "
                          ",a010_valor_total_servico      "
                          ",a010_meio_pagamento           "
                          ",a010_detalhes_servico         "
                      "FROM "
                          "a010_OS "
                          "JOIN a004_veiculos ON (a004_codigo = a010_fk_codigo_veiculo) "
                          "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente)  "
                          "JOIN a012_modelos ON (a012_Codigo = a004_fk_codigo_modelo)   "
                      "WHERE "
                        "a010_ativo = true "
                      "ORDER BY "
                          "a010_codigo DESC");

        if( query.exec() ) //verifica se ouve algum erro na execução da query
        {
            //enquanto a query tiver retornando next, insere linhas dentro do table widget
            while( query.next() )
            {
                //inserindo com contador de linhas, por index
                ui->tw_listaOS->insertRow( contlinhas );
                ui->tw_listaOS->setItem(contlinhas
                                            , 0
                                            , new QTableWidgetItem(query.value(0).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 1
                                            , new QTableWidgetItem(query.value(1).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 2
                                            , new QTableWidgetItem(query.value(2).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 3
                                            , new QTableWidgetItem(query.value(3).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 4
                                            , new QTableWidgetItem(query.value(4).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 5
                                            , new QTableWidgetItem(query.value(5).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 6
                                            , new QTableWidgetItem(query.value(6).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 7
                                            , new QTableWidgetItem(query.value(7).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 8
                                            , new QTableWidgetItem(query.value(8).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 9
                                            , new QTableWidgetItem(query.value(9).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 10
                                            , new QTableWidgetItem(query.value(10).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 11
                                            , new QTableWidgetItem(query.value(11).toString()));

                ui->tw_listaOS->setItem(contlinhas
                                            , 12
                                            , new QTableWidgetItem(query.value(12).toString()));

                //definindo o tamanho das linhas
                ui->tw_listaOS->setRowHeight(contlinhas, 20);
                contlinhas ++;
            }
        }
        else
        {
            QMessageBox::warning(this, "ERRO", "Erro ao listar Ordens de Serviço");
        }
    }
}

//filtrar gestão OS
void frm_ordemservico::on_txt_ge_filtrar_returnPressed()
{
    QString cb_filtro = ui->cb_ge_filtrar->currentText();
    QString txt_filtro = ui->txt_ge_filtrar->text();

    QString busca; //armazena busca
    QString filtro_sql;

    QStringList cb_opc; //Dados do combo box
    cb_opc << "Cliente" << "Placa" << "Status" << "M.Pgto";


    //remove as linhas o table widget
    funcoes_globais::removerLinhas( ui->tw_listaOS );

    //verificando se algo foi digitado no campo de filtro
    if( ui->txt_ge_filtrar->text() == "" )
    {
        if( cb_filtro == "" ) //consulta de acordo com o radio selecionado
        {
            busca = "SELECT "
                        "a010_codigo                    "
                        ",a005_nome                     "
                        ",a012_nome_veiculo             "
                        ",a004_placa_veiculo            "
                        ",a004_cor_veiculo              "
                        ",a010_km_veiculo               "
                        ",a010_data_entrada             "
                        ",a010_status                   "
                        ",a010_valor_mao_obra           "
                        ",a010_valor_total_mercadorias  "
                        ",a010_valor_total_servico      "
                        ",a010_meio_pagamento           "
                        ",a010_detalhes_servico         "
                    "FROM "
                        "a010_OS "
                        "JOIN a004_veiculos ON (a004_codigo = a010_fk_codigo_veiculo) "
                        "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente)  "
                        "JOIN a012_modelos ON (a012_Codigo = a004_fk_codigo_modelo)   "
                    "WHERE "
                        "a010_ativo = true "
                    "ORDER BY "
                        "a010_codigo DESC";
        }
        else
        {
            busca = "SELECT "
                        "a010_codigo                    "
                        ",a005_nome                     "
                        ",a012_nome_veiculo             "
                        ",a004_placa_veiculo            "
                        ",a004_cor_veiculo              "
                        ",a010_km_veiculo               "
                        ",a010_data_entrada             "
                        ",a010_status                   "
                        ",a010_valor_mao_obra           "
                        ",a010_valor_total_mercadorias  "
                        ",a010_valor_total_servico      "
                        ",a010_meio_pagamento           "
                        ",a010_detalhes_servico         "
                    "FROM "
                        "a010_OS "
                        "JOIN a004_veiculos ON (a004_codigo = a010_fk_codigo_veiculo) "
                        "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente)  "
                        "JOIN a012_modelos ON (a012_Codigo = a004_fk_codigo_modelo)   "
                    "WHERE "
                        "a010_ativo = true "
                    "ORDER BY "
                        "a010_codigo DESC";
        }
    }
    else
    {
        cb_opc << "Cliente" << "Placa" << "Status" << "M.Pgto";
        //consulta de acordo com a seleção do combo box
        switch( cb_opc.indexOf( cb_filtro ) )
        {
            //Cliente
            case 0:

                filtro_sql = "a005_nome LIKE '%" +txt_filtro+ "%' ";
                break;
            //Placa
            case 1:

                filtro_sql = "a004_placa_veiculo LIKE '%" +txt_filtro+ "%' ";
                break;
            //Status
            case 2:

                filtro_sql = "a010_status LIKE '%" +txt_filtro+ "%' ";
                break;
            //M.Pgto
            case 3:

                filtro_sql = "a010_meio_pagamento LIKE '%" +txt_filtro+ "%' ";
                break;
            default:
                qDebug() << "_Houve um problema ao filtrar realizar o filtro(swith case)";
                break;
        }

        busca = "SELECT "
                    "a010_codigo                    "
                    ",a005_nome                     "
                    ",a012_nome_veiculo             "
                    ",a004_placa_veiculo            "
                    ",a004_cor_veiculo              "
                    ",a010_km_veiculo               "
                    ",a010_data_entrada             "
                    ",a010_status                   "
                    ",a010_valor_mao_obra           "
                    ",a010_valor_total_mercadorias  "
                    ",a010_valor_total_servico      "
                    ",a010_meio_pagamento           "
                    ",a010_detalhes_servico         "
                "FROM "
                    "a010_OS "
                    "JOIN a004_veiculos ON (a004_codigo = a010_fk_codigo_veiculo) "
                    "JOIN a005_cliente ON (a005_codigo = a004_fk_codigo_cliente)  "
                    "JOIN a012_modelos ON (a012_Codigo = a004_fk_codigo_modelo)   "
                "WHERE "
                    + filtro_sql +
                    "AND a010_ativo = true "
                "ORDER BY "
                    "a010_codigo DESC";
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
            ui->tw_listaOS->insertRow( contlinhas );
            ui->tw_listaOS->setItem(contlinhas
                                        , 0
                                        , new QTableWidgetItem(query.value(0).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 1
                                        , new QTableWidgetItem(query.value(1).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 2
                                        , new QTableWidgetItem(query.value(2).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 3
                                        , new QTableWidgetItem(query.value(3).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 4
                                        , new QTableWidgetItem(query.value(4).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 5
                                        , new QTableWidgetItem(query.value(5).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 6
                                        , new QTableWidgetItem(query.value(6).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 7
                                        , new QTableWidgetItem(query.value(7).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 8
                                        , new QTableWidgetItem(query.value(8).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 9
                                        , new QTableWidgetItem(query.value(9).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 10
                                        , new QTableWidgetItem(query.value(10).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 11
                                        , new QTableWidgetItem(query.value(11).toString()));

            ui->tw_listaOS->setItem(contlinhas
                                        , 12
                                        , new QTableWidgetItem(query.value(12).toString()));

            //definindo o tamanho das linhas
            ui->tw_listaOS->setRowHeight(contlinhas, 20);
            contlinhas ++;
        }
    }
    else
    {
        QMessageBox::warning(this, "ERRO", "Erro ao filtrar ordens de serviçoo");
    }

    //apagar conteudo do campo txt_ge_filtrar toda vez que clickar em filtrar
    ui->txt_ge_filtrar->clear();
    ui->txt_ge_filtrar->setFocus(); //posiciona o cursos no campo novamente
}

//btn ge filtrar
void frm_ordemservico::on_btn_ge_filtrar_clicked()
{
    frm_ordemservico::on_txt_ge_filtrar_returnPressed();
}

//Seleciona OS e lista os itens incluidos da OS
void frm_ordemservico::on_tw_listaOS_itemSelectionChanged()
{
    //limpando table widget
    funcoes_globais::removerLinhas( ui->tw_listaPecasOS );

    QString codigo_os = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(),0)->text();

    int contlinhas = 0;

    //exibe os dados da linha selecionada
    QSqlQuery query;
    query.prepare("SELECT "
                      "a002_codigo                                           "
                      ",a002_denomicanao                                     "
                      ",cast(cast(a002_valor_venda  as decimal) as varchar)  "
                      ",a002_qtde_estoque                                    "
                      ",a002_posicao_peca                                    "
                  "FROM "
                    "a010_OS "
                    "JOIN a015_os_itens ON (a015_fk_codigo_os = a010_codigo)   "
                    "JOIN a002_estoque ON  (a002_codigo = a015_fk_codigo_peca) "
                  "WHERE "
                    "a015_codigo = '" +codigo_os+ "' ");


    if( !query.exec() )
    {
        QMessageBox::warning(this, "ERRO", "Erro ao listar itens O.S.");
        qDebug() << "ERRO: " << query.lastError().text();
    }

    query.first();

    double valor_total = query.value(3).toDouble() * query.value(2).toDouble();

    //inserindo elementos no table widget
    do
    {
        //linha, coluna e item
        ui->tw_listaPecasOS->insertRow( contlinhas );
        ui->tw_listaPecasOS->setItem(contlinhas, 0,
                                                new QTableWidgetItem(query.value(0).toString()));

        ui->tw_listaPecasOS->setItem(contlinhas, 1,
                                               new QTableWidgetItem(query.value(1).toString()));

        ui->tw_listaPecasOS->setItem(contlinhas, 2,
                                               new QTableWidgetItem(query.value(2).toString()));

        ui->tw_listaPecasOS->setItem(contlinhas, 3,
                                               new QTableWidgetItem(query.value(3).toString()));

        ui->tw_listaPecasOS->setItem(contlinhas, 4,
                                               new QTableWidgetItem( valor_total ));

        ui->tw_listaPecasOS->setItem(contlinhas, 5,
                                                new QTableWidgetItem(query.value(5).toString()));

        contlinhas++;
    }while( query.next() );
}

//gestão gerar O.S
void frm_ordemservico::on_btn_ge_geraros_clicked()
{
    //nome da OS de acordo com o id da venda
    QString codigo_os = ui->tw_listaOS->
                  item(ui->tw_listaOS->currentRow(), 0)->text();

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

    QString codigo = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 0)->text();
    QString cliente = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 1)->text();
    QString modelo_veiculo = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 2)->text();
    QString placa_veiculo = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 3)->text();
    QString cor_veiculo = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 4)->text();
    QString km_veiculo = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 5)->text();

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

    QString data_entrada = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 6)->text();
    QString valor_mao_obra = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 8)->text();
    QString valor_total_pecas = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 9)->text();
    QString valor_total_servico = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 10)->text();
    QString meio_pagamento = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 11)->text();

    painter.drawText(25,410, data_entrada);
    painter.drawText(150,410, valor_mao_obra);
    painter.drawText(295,410, valor_total_pecas);
    painter.drawText(415,410, valor_total_servico);
    painter.drawText(540,410, meio_pagamento);

    //detalhes do serviço
    painter.drawText(25, 480,"Detalhes do Serviço: ");

    QString detalhes = ui->tw_listaOS->item(ui->tw_listaOS->currentRow(), 12)->text();

    painter.drawText(25, 520, detalhes);

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

    for( int i = 0; i < ui->tw_listaPecasOS->rowCount(); i++ )
    {
        //produtos da venda
        painter.drawText(25,linha, ui->tw_listaPecasOS->item(i, 0)->text());
        painter.drawText(130,linha, ui->tw_listaPecasOS->item(i, 1)->text());
        painter.drawText(295,linha, "R$ " + ui->tw_listaPecasOS->item(i, 2)->text());
        painter.drawText(415,linha, ui->tw_listaPecasOS->item(i, 3)->text());
        painter.drawText(540,linha, "R$ " + ui->tw_listaPecasOS->item(i, 4)->text());
        painter.drawText(540,linha, "R$ " + ui->tw_listaPecasOS->item(i, 5)->text());
        linha += salto;
    }

    //adicionando nova página
    //printer.newPage();
    painter.drawText(25, 1000, "O.S.");

    // finaliza e gera o PDF
    painter.end();

    //atualizando o status do serviço
    QSqlQuery query;
    query.prepare("UPDATE "
                    "a010_OS "
                  "SET "
                    "a010_status = 'CONCLUÍDA' "
                  "WHERE "
                    "a010_codigo ='" +codigo+ "'");

    if( !query.exec() )
    {
        QMessageBox::information(this, "ERRO", "Não foi possível atualizar o status da O.S.");
    }
    else
    {
        int linha = ui->tw_listaOS->currentRow();
        ui->tw_listaOS->item(linha, 7)->setText( "CONCLUÍDA" );
    }

    //abrir o arquivo pdf gerado
    QDesktopServices::openUrl(QUrl("file:///" + local + "/" + nome));
}

// gestão excluir O.S.
void frm_ordemservico::on_btn_ge_excluir_clicked()
{
    if( ui->tw_listaOS->currentRow() == -1 )
    {
        QMessageBox::warning(this, "ERRO", "Selecione um fornecedor");
        return;
    }

    //pergunta se o usuário realmente quer excluir o registro
    QMessageBox::StandardButton opc =QMessageBox::question(
                                      this,"Exclusão"
                                      ,"Confirma exclusão da O.S.?"
                                      ,QMessageBox::Yes|QMessageBox::No);

    if( opc == QMessageBox::Yes )
    {
        //pegando a linha corrent(atual), no caso o id(index(0))
        int linha = ui->tw_listaOS->currentRow();
        QString id = ui->tw_listaOS->item(linha, 0)->text();

        QSqlQuery query;

        query.prepare("UPDATE "
                        "a010_OS "
                      "SET "
                        "a010_ativo = false "
                      "WHERE "
                        "a010_codigo ='" +id+ "'");

        if( query.exec() )
        {
            ui->tw_listaOS->removeRow( linha );
            QMessageBox::information(this, "EXCLUÍDA", "Ordem de serviço excluída com sucesso");
        }
        else
        {
             QMessageBox::warning(this, "ERRO", "Erro ao excluir ordem de serviço");
        }
    }
}

/**FUNÇÕES**/
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 04/06/2022                                                                           |
 * Propósito: Essa série de funções servem para configurar os Table widget                    |
 * Chamada:                                                                                   |
 *--------------------------------------------------------------------------------------------
 */
//configurar tw_listaOS
void frm_ordemservico::conf_tw_ge_listaOS()
{
    //***CONFGIRUANDO tw_listaOS***
    //configurando combo box
    ui->cb_ge_filtrar->addItem("-");
    ui->cb_ge_filtrar->addItem("Cliente");
    ui->cb_ge_filtrar->addItem("Placa");
    ui->cb_ge_filtrar->addItem("Status");
    ui->cb_ge_filtrar->addItem("M.Pgto");

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_listaOS->setColumnCount(13);
    ui->tw_listaOS->setColumnWidth(0, 40);
    ui->tw_listaOS->setColumnWidth(1, 150);

    //cabeçalhos do table widget
    QStringList cabecalho3={"Código", "Cliente", "Veículo", "Placa","Cor"
                           ,"Km", "Data entrada", "Status", "V.Mão de obra"
                           , "V.Peças", "V.Total Serviço","M.Pgto", "Detalhes"};

    ui->tw_listaOS->setHorizontalHeaderLabels( cabecalho3 );
    //definindo cor da linha ao ser selecionada
    ui->tw_listaOS->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listaOS->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listaOS->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listaOS->verticalHeader()->setVisible(false);
}

//configurar tw_listaPecasOS
void frm_ordemservico::conf_tw_ge_pecasOS()
{
    //***CONFGIRUANDO tw_listaPecasOS***
    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_listaPecasOS->setColumnCount(6);
    ui->tw_listaPecasOS->setColumnWidth(0, 40);
    ui->tw_listaPecasOS->setColumnWidth(1, 150);

    //cabeçalhos do table widget
     QStringList cabecalho4 = {"Código", "Denominação", "Valor Un."
                               , "Qtde", "V.Total", "Pos.Prateleira"};

    ui->tw_listaPecasOS->setHorizontalHeaderLabels( cabecalho4 );
    //definindo cor da linha ao ser selecionada
    ui->tw_listaPecasOS->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_listaPecasOS->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_listaPecasOS->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_listaPecasOS->verticalHeader()->setVisible(false);
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
