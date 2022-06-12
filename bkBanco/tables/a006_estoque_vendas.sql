create table a006_estoque_vendas(a006_codigo serial primary key
								 ,a006_denomicanao varchar(400) not null
								 ,a006_qtde int not null
								 ,a006_valor_un numeric
								 ,a006_valor_total numeric
								 ,a006_ativo boolean DEFAULT true
								 ,a006_codigo_venda int);
