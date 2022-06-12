create table a001_usuarios(a001_codigo serial primary key
						 ,a001_nome text not null
						 ,a001_usuario varchar(50) unique not null
						 ,a001_senha varchar(50) not null	
						 ,a001_tipo_acesso char(1) not null
						 ,a001_ativo boolean DEFAULT true);
						 
						 

insert into 
	a001_usuarios(a001_nome, a001_usuario, a001_senha, a001_tipo_acesso)
values('Thiago Ianzer', 'amincar', '12meurex', 'A');

	
