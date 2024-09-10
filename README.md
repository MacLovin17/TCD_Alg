Sistema de Controle de Eventos - Promoter Paracatu
Descrição do Projeto
Este projeto é um sistema para gerenciamento de eventos de um promoter da cidade de Paracatu. O sistema permite o cadastro de eventos, controle de ingressos, cálculo de valores de entradas e acompanhamento de custos, considerando as diferentes categorias de ingressos e tipos de eventos (como festas open bar).

O sistema foi desenvolvido utilizando arrays e estruturas para representar e manipular os dados dos eventos e ingressos.

Funcionalidades
Cadastro de eventos: Cada evento possui um identificador único, nome, local, data, custos de organização, quantidade máxima de ingressos e valores das entradas.
Valores de entradas: Os eventos têm três tipos de ingressos com valores diferenciados:
Entrada básica: calculada com base nos custos de organização.
Entrada normal: valor da entrada básica acrescido de 10%.
Entrada especial: valor da entrada normal acrescido de 15%.
Eventos open bar: Eventos desse tipo incluem a relação de bebidas servidas, cada uma com nome, teor alcoólico e valor unitário. O valor da entrada básica para esses eventos é ajustado com base no custo das bebidas (175% do valor unitário de cada bebida).
Distribuição de ingressos: A quantidade total de ingressos é distribuída entre os três tipos:
50% para entradas básicas.
30% para entradas normais.
20% para entradas especiais.
Finalização do cadastro: O cadastro de eventos pode ser encerrado ao inserir 0 como identificador único.
