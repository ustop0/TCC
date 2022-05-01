#include "frm_gestaofornecedores.h"
#include "ui_frm_gestaofornecedores.h"
#include "Classes/clfornecedor.h"

frm_gestaofornecedores::frm_gestaofornecedores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_gestaofornecedores)
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

    //ui->cb_nv_acesso->addItem("-");
    //ui->cb_nv_acesso->addItem("Administrador");
    ui->txt_nv_cnpj->setFocus();

    //define o Novo Produto de index(0) como aba padrão(que inicia ao ser aberta a interface)
    ui->tabWidget->setCurrentIndex(0);

    //**Estilizando layout da table widget**
    //definindo o tamanho das colunas
    ui->tw_ge_listarFornecedores->setColumnCount(2); //define que o table widget terá duas colunas
    ui->tw_ge_listarFornecedores->setColumnWidth(0, 150); //id colaborador
    ui->tw_ge_listarFornecedores->setColumnWidth(1, 220); //nome colaborador

    //cabeçalhos do table widget
    QStringList cabecalhos={"Código", "Razão Social", "Nome Fantasia", "CNPJ", "Estado"
                           , "Cidade", "Rua", "Bairro", "Numero", "Porte", "Ocupação"
                           , "Telefone1", "Telefone2"};
    ui->tw_ge_listarFornecedores->setHorizontalHeaderLabels(cabecalhos);
    //definindo cor da linha ao ser selecionada
    ui->tw_ge_listarFornecedores->setStyleSheet("QTableView "
                                      "{selection-background-color:red}");

    //desabilita a edição dos registros pelo table widget
    ui->tw_ge_listarFornecedores->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha inteira quando clickar em uma celula
    ui->tw_ge_listarFornecedores->setSelectionBehavior(QAbstractItemView::SelectRows);
    //desabilitando os indices das linhas
    ui->tw_ge_listarFornecedores->verticalHeader()->setVisible(false);
} //**Fim construtor

frm_gestaofornecedores::~frm_gestaofornecedores() //**Inicio destrutor
{
    con.fechar(); //fechando conexao com o banco de dados
    delete ui;
}

//novo cliente
void frm_gestaofornecedores::on_btn_nv_novo_clicked()
{
    ui->txt_nv_cnpj->clear();
    ui->txt_nv_cep->clear();
    ui->txt_nv_uf->clear();
    ui->txt_nv_cidade->clear();
    ui->txt_nv_rua->clear();
    ui->txt_nv_numeroEstabelecimento->clear();
    ui->txt_nv_bairro->clear();
    ui->txt_nv_razaoSocial->clear();
    ui->txt_nv_nomeFantasia->clear();
    ui->txt_nv_porte->clear();
    ui->txt_nv_ocupacao->clear();
    ui->txt_nv_tel1->clear();
    ui->txt_nv_tel2->clear();
    ui->txt_nv_cnpj->setFocus();
}

//validando cnpj
void frm_gestaofornecedores::on_txt_nv_cnpj_returnPressed()
{
    ClFornecedor fornecedor;

    fornecedor.cnpj = ui->txt_nv_cnpj->text(); //armazena o codigo
    validaCNPJ( fornecedor.cnpj ); //validando cep
    fornecedor.cep = ui->txt_nv_cep->text();
    fornecedor.estado = ui->txt_nv_uf->text();
    fornecedor.cidade = ui->txt_nv_cidade->text();
    fornecedor.rua = ui->txt_nv_rua->text();
    fornecedor.numero_estabelecimento = ui->txt_nv_numeroEstabelecimento->text();
    fornecedor.bairro = ui->txt_nv_bairro->text();
    fornecedor.razao_social = ui->txt_nv_razaoSocial->text();
    fornecedor.nome_fantasia = ui->txt_nv_nomeFantasia->text();
    fornecedor.porte_empresa = ui->txt_nv_porte->text();
    fornecedor.ocupacao_empresa = ui->txt_nv_ocupacao->text();
    fornecedor.telefone1 = ui->txt_nv_tel1->text();
}

//salvar clientes
void frm_gestaofornecedores::on_btn_nv_salvar_clicked()
{
    ClFornecedor fornecedor;

    fornecedor.cnpj = ui->txt_nv_cnpj->text(); //armazena o codigo
    fornecedor.cep = ui->txt_nv_cep->text();
    fornecedor.estado = ui->txt_nv_uf->text();
    fornecedor.cidade = ui->txt_nv_cidade->text();
    fornecedor.rua = ui->txt_nv_rua->text();
    fornecedor.numero_estabelecimento = ui->txt_nv_numeroEstabelecimento->text();
    fornecedor.bairro = ui->txt_nv_bairro->text();
    fornecedor.razao_social = ui->txt_nv_razaoSocial->text();
    fornecedor.nome_fantasia = ui->txt_nv_nomeFantasia->text();
    fornecedor.porte_empresa = ui->txt_nv_porte->text();
    fornecedor.ocupacao_empresa = ui->txt_nv_ocupacao->text();
    fornecedor.telefone1 = ui->txt_nv_tel1->text();
    fornecedor.telefone2 = ui->txt_nv_tel2->text();

    QSqlQuery query;
    query.prepare("INSERT INTO "
                    "a003_fornecedor(a003_cnpj                     "
                                     ",a003_estado                 "
                                     ",a003_cidade                 "
                                     ",a003_rua                    "
                                     ",a003_numero_estabelecimento "
                                     ",a003_bairro                 "
                                     ",a003_razao_social           "
                                     ",a003_nome_fantasia          "
                                     ",a003_porte                  "
                                     ",a003_ocupacao               "
                                     ",a003_telefone01             "
                                     ",a003_telefone02)            "
                    "VALUES('" +fornecedor.cnpj                     +  "'"
                          ",'" +fornecedor.cep                      +  "'"
                          ",'" +fornecedor.estado                   +  "'"
                          ",'" +fornecedor.cidade                   +  "'"
                          ",'" +fornecedor.rua                      +  "'"
                          ",'" +fornecedor.numero_estabelecimento   +  "'"
                          ",'" +fornecedor.bairro                   +  "'"
                          ",'" +fornecedor.razao_social             +  "'"
                          ",'" +fornecedor.nome_fantasia            +  "'"
                          ",'" +fornecedor.porte_empresa            +  "'"
                          ",'" +fornecedor.ocupacao_empresa         +  "'"
                          ",'" +fornecedor.telefone1                +  "'"
                          ",'" +fornecedor.telefone2                +  "') ");

    if( !query.exec() ) //verifica se a query tem algum erro e executa ela
    {
        QMessageBox::critical(this, "ERRO", "Erro ao cadastrar fornecedor");
    }
    else
    {
        ui->txt_nv_cnpj->clear();
        ui->txt_nv_cep->clear();
        ui->txt_nv_uf->clear();
        ui->txt_nv_cidade->clear();
        ui->txt_nv_rua->clear();
        ui->txt_nv_numeroEstabelecimento->clear();
        ui->txt_nv_bairro->clear();
        ui->txt_nv_razaoSocial->clear();
        ui->txt_nv_nomeFantasia->clear();
        ui->txt_nv_porte->clear();
        ui->txt_nv_ocupacao->clear();
        ui->txt_nv_tel1->clear();
        ui->txt_nv_tel2->clear();
        ui->txt_nv_cnpj->setFocus();
    }
}



//**FUNÇÕES**//
/*--------------------------------------------------------------------------------------------
 * Autor: Thiago Ianzer                                                                       |
 * Data: 01/05/2022                                                                           |
 * Propósito: receber o cnpj, e faz a validação via API do BrasilAPI                          |
 * Chamada: botão gravar forncedor                                                            |
 *--------------------------------------------------------------------------------------------
 */
void frm_gestaofornecedores::validaCNPJ( const QString &fornecedor_cnpj )
{
    QEventLoop waitLoop;
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(
                QNetworkRequest( QUrl("https://brasilapi.com.br/api/cnpj/v1/" + fornecedor_cnpj)) );

    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
    QJsonObject json(doc.object());

    //validando o cep, e tratando erros
    if( json.find("erro") != json.end() )
    {
        json["erro"].toBool() ?
                    ui->lb_nv_cnpj->setText("CNPJ") : ui->lb_nv_cnpj->setText("CNPJ: inválido");


        ui->lb_nv_cnpj->setText("CNPJ: inválido");
    }
    else
    {
        ui->txt_nv_cnpj->setText(json["cnpj"].toString());
        ui->txt_nv_cep->setText(json["cep"].toString());
        ui->txt_nv_uf->setText(json["uf"].toString());
        ui->txt_nv_cidade->setText(json["municipio"].toString());
        ui->txt_nv_rua->setText(json["logradouro"].toString());
        ui->txt_nv_numeroEstabelecimento->setText(json["numero"].toString());
        ui->txt_nv_bairro->setText(json["bairro"].toString());
        ui->txt_nv_razaoSocial->setText(json["razao_social"].toString());
        ui->txt_nv_nomeFantasia->setText(json["nome_fantasia"].toString());
        ui->txt_nv_porte->setText(json["porte"].toString());
        ui->txt_nv_ocupacao->setText(json["cnae_fiscal_descricao"].toString());
        ui->txt_nv_tel1->setText(json["ddd_telefone_1"].toString());
    }
}




