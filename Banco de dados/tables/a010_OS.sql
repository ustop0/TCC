create table a010_OS(a010_codigo serial primary key
					,a010_data_abertura timestamp
					,a010_data_fechamento timestamp
					,a010_status char(1)
					,a010_km_veiculo numeric
					,a010_valor_total_servicos numeric
					,a010_valor_total_mercadorias numeric
					,a010_meio_pagamento char(1)
					,a010_garantia_servico text
					,a010_ativo boolean DEFAULT true
					,a010_fk_codigo_veiculo int not null
					,constraint fk_veiculo foreign key(a010_fk_codigo_veiculo) references a004_veiculos(a004_codigo));
					

Constrains: a004_veiculos
