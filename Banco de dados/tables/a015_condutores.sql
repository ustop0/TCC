--a ordem de serviços vai no condutor
create table a015_condutores(a015_codigo serial primary key
							 ,a015_cod_cliente
							 ,a015_cod_Veiculo
							 ,a015_nome_condutor
							 ,a015_data_registro
							 ,a015_ativo boolean DEFAULT true);
							 
-
--o cadastro do cliente vai ser realizado no nome do proprietario do veiculo, exeto em alguna casos						 
tabela condutores
	cod_cliente
	cod_veiculo
	data_registro
	ativo

