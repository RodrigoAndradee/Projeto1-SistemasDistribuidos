# Projeto Sistemas Integrados Grupo 3

## Materiais Utilizados:

* Arduino Uno
* Ethernet Shield w5100
* Cabo de Rede cat45

## Objetivo

Apresentar um Dashboard indicando o status de um LED

## Resolução do problema

Utilizando o arduino como um servidor web é possível receber requisições do tipo POST e GET.
Sendo assim sempre que o servidor recebe uma requisição /acende uma nova coluna é adicinada na tabela

![](https://github.com/RodrigoAndradee/Projeto1-SistemasDistribuidos/blob/master/ligado.png)

Quando o servidor recebe uma requisição /apaga uma nova coluna é adicionada na tabela

![](https://github.com/RodrigoAndradee/Projeto1-SistemasDistribuidos/blob/master/desligado.png)

## Acessando o dashboard

**Utilize o ip mostrado no serial do arduino** com a porta **80** no seu navegador para acessar o dashboard
```
192.168.15.1:80
```

## Dashboard após algumas requisições

![](https://github.com/RodrigoAndradee/Projeto1-SistemasDistribuidos/blob/master/teste.png)

## Documentação original do projeto

![](https://github.com/RodrigoAndradee/Projeto1-SistemasDistribuidos/blob/master/img.png)





