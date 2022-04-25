create table a007_vendas(a007_codigo serial primary key
						 ,a007_data_venda date
						 ,a007_hora_venda time
						 ,a007_codigo_usuario int
						 ,a007_valor_total numeric
						 ,a007_codigo_tipo_pagamento varchar(200)
						 ,a007_ativo boolean DEFAULT true);
