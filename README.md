# BeeData
Monitoramento de Abelhas

Projeto PCS3100, Engenharia de Computaço 2021, Escola Politécnica - USP.

O objetivo desse projeto é coletar dados de colmeias de abelhas, traçar esses dados e mostrar em um site.

### Quem Somos?
#### Grupo 15 
Gabriel Palassi

João Pedro Arroyo

Mateus Witeck

Victor Renzo

## Circuito
Utilizou-se uma Arduino Uno para concepção do Projeto
### Componentes Utilizados

2 Transistores 2N2222
2 Leds Infravermelhos
2 Fototransistores
1 Fotoresistor LDR
1 Modulo DHT11
9 Resistores (Especificações em "Circuito Arduino.brd")


### Conexões 

Arquivo de Edição ThinkkerCAD: Circuito Arduino.brd
(Todos os valores de resistência estão nesse arquivo)

![image](https://user-images.githubusercontent.com/67548433/125880713-30b155a1-cfe2-434d-b0ab-963e935d8b5e.png)


## Software 


### Blibliotecas 
A única Bliblioteca utilizada foi para usar o módulo DHT11 disponibilizada aqui: github.com/wagner-rambo/arquivos/raw/master/arduino109_WR_files.rar

## Arduino 
Para o arduino temos os seguintes códigos:

"Colmeia (nice to see).ino" Arquivo usado para demonstrar o funcionamento

"Estação de Monitoramento Climático.ino" Gera uma tabela .csv apenas com dados climáticos

"Monitoramento_Colmeia.ino" Gera uma tabela .csv com todos os dados coletados

## Análize de Dados
Na pasta "Ánálize de Dados", o arquivo BeeData.csv é uma coleta de dados climáticos do dia 12/07/2021, das 8:30 da manhã até as 8 da noite.

Nesta mesma pasta está o codigo utilizado para imprimir os gráficos do site.

## Site 

O site pode ser acessado através desse link: https://victorrenzo.github.io/

## Aplicativo 

O Protótipo feito no Figma pode ser acessado aqui: https://www.figma.com/proto/HD2Xoac0MehWESplCQ8QzM/BeeData?node-id=1%3A3&scaling=min-zoom

