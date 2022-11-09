--TABELAS (INICIO)--
create table a011_marcas(a011_codigo serial primary key
							 ,a011_marca_nome varchar(400)
							 ,a011_ativo boolean DEFAULT true);
							 
							 			
create table a012_modelos(a012_codigo serial primary key
							 ,a012_nome_veiculo varchar(400)
							 ,a012_motor_veiculo varchar(100)
							 ,a012_ano_veiculo int
							 ,a012_ativo boolean DEFAULT true
						     ,a012_fk_codigo_marca int not null
						     ,constraint fk_marca foreign key(a012_fk_codigo_marca) references a011_marcas(a011_codigo));			


create table a005_cliente(a005_codigo serial primary key
							,a005_nome text not null 
							,a005_cpf char(11) unique
							,a005_cep char(8) not null
							,a005_estado char(2)
							,a005_cidade varchar(400)
							,a005_rua text
							,a005_bairro varchar (400)
							,a005_telefone varchar(40)
							,a005_ativo boolean DEFAULT true);
	
						 	
create table a004_veiculos(a004_codigo serial primary key
						 ,a004_chassi_veiculo varchar(20)
						 ,a004_placa_veiculo varchar(10)
						 ,a004_cor_veiculo varchar(50)
						 ,a004_ocorrencia text
						 ,a004_observacao text
						 ,a004_ativo boolean DEFAULT true
						 ,a004_fk_codigo_modelo int not null
						 ,a004_fk_codigo_cliente int not null
						 ,constraint fk_modelo foreign key(a004_fk_codigo_modelo) references a012_modelos(a012_codigo)
						 ,constraint fk_cliente foreign key(a004_fk_codigo_cliente) references a005_cliente(a005_codigo));
--TABELAS (FIM)--

												 
--inserções a011
insert into a011_marcas(a011_marca_nome) values('BMW')

select * from a011_marcas

--inserções a012
insert into a012_modelos(a012_nome_veiculo, a012_motor_veiculo, a012_ano_veiculo, a012_fk_codigo_marca)
				  values('M3', '4.1-V8', 2012, 1)
				  
select 
	a011_marca_nome as MARCA
	,a012_nome_veiculo as MODELO
	,a012_motor_veiculo as MOTOR
	,a012_ano_veiculo as ANO
from
	a012_modelos
left join a011_marcas on (a011_codigo = a012_fk_codigo_marca)

		
		
--inserções a005
insert into a005_cliente(a005_nome, a005_cpf, a005_cep, a005_rua)
				  values('Thiago', '03887161009', '96400320', 'Santos Souza')		
				  
--inserções a004
insert into a004_veiculos(a004_fk_codigo_modelo, a004_fk_codigo_cliente, a004_chassi_veiculo, a004_placa_veiculo, a004_cor_veiculo)
				  values(1, 1, 'hjk-ghj2022', 'bch2j84', 'Branco');
		
		
--select da tabela clientes
--select da tabela clientes
select
	a011_marca_nome     as MARCA
	,a012_nome_veiculo  as NOME
	,a012_ano_veiculo   aS ANO
	,a004_placa_veiculo as PLACA
	,a005_nome 			as CLIENTE
	,a005_cpf 			as CPF
	,a005_cep			as CEP
	,a005_rua 			as RUA
from
	a005_cliente
join a004_veiculos on (a005_codigo = a004_fk_codigo_cliente)
join a012_modelos on (a012_codigo = a004_fk_codigo_modelo)
join a011_marcas on (a011_codigo = a012_fk_codigo_marca)
						




