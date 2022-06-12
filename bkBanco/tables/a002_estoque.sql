create table a002_estoque(a002_codigo serial primary key
						 ,a002_nc_peca int 
						 ,a002_denomicanao varchar(400) not null
						 ,a002_grupo varchar(400) not null
						 ,a002_valor_compra float not null
						 ,a002_valor_venda float
						 ,a002_margem_lucro float
						 ,a002_qtde_estoque int
						 ,a002_ativo boolean DEFAULT true
						 ,a002_codigo_fornecedor int);
						 
alter table a002_estoque
add column a002_tipo_peca char(1); --indica o tipo da peça

alter table a002_estoque
add column a002_posicao_peca varchar(10); --posição na prateleira

--criar classificasao_peca > indica o tipo da peca e onde ela vai, etc...(para o estoque)
