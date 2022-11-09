create table a005_cliente(a005_codigo serial primary key
							,a005_nome text not null 
							,a005_cpf char(11) unique
							,a005_cep char(8) not null
							,a005_estado char(2)
							,a005_cidade varchar(400)
							,a005_rua text
							,a005_bairro varchar (400)
							,a005_telefone varchar(40)
							,a005_ativo boolean DEFAULT true
							,a005_fk_codigo_estado INT NOT NULL
							,CONSTRAINT fk_estado FOREIGN KEY(a005_fk_codigo_estado) REFERENCES a013_estado(a013_codigo));
						 	
						 	
						 	

