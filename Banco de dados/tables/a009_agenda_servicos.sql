create table a009_agenda_servicos(a009_codigo serial primary key
								  ,a009_cliente varchar(400)
								  ,a009_data_hora timestamp
								  ,a009_carro_cliente varchar(400)
								  ,a009_servico varchar(400)
								  ,a009_status char(1)
								  ,a009_ativo boolean DEFAULT true);
