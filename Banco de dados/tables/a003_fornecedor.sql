create table a003_fornecedor(a003_codigo serial primary key
							,a003_razao_social text
							,a003_nome_fantasia text not null
							,a003_cnpj char(14) not null
							,a003_estado char(2) 
							,a003_cidade varchar(400) not null
							,a003_rua text not null
							,a003_bairro varchar(400)
							,a003_numero_rua int not null
							,a003_porte varchar(100)
							,a003_ocupacao text
							,a003_telefone01 varchar(40) not null
							,a003_telefone02 varchar(40)
							,a003_ativo boolean DEFAULT true);
