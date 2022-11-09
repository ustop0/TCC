create table a004_veiculos(a004_codigo serial primary key
						 ,a004_chassi_veiculo varchar(20)
						 ,a004_placa_veiculo varchar(10)
						 ,a004_cor_veiculo varchar(50)
						 ,a004_observacao text
						 ,a004_ativo boolean DEFAULT true
						 ,a004_fk_codigo_modelo int not null
						 ,a004_fk_codigo_cliente int not null
						 ,constraint fk_modelo foreign key(a004_fk_codigo_modelo) references a012_modelos(a012_codigo)
						 ,constraint fk_cliente foreign key(a004_fk_codigo_cliente) references a005_cliente(a004_codigo));
						 
						 
						 
Constrains: a012_modelos, a010_OS


