create table a012_modelos(a012_codigo serial primary key
							 ,a012_nome_veiculo varchar(400)
							 ,a012_motor_veiculo varchar(100)
							 ,a012_ano_veiculo int
							 ,a012_ativo boolean DEFAULT true
						     ,a012_fk_codigo_marca int not null
						     ,constraint fk_marca foreign key(a012_fk_codigo_marca) references a011_marcas(a011_codigo)); 	
						     
Constrains: a011_marcas


