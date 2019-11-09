# Meus círculos que arrastam

Trata-se de um programa que permite que o usuário crie e arraste círculos dentro de uma janela. As configurações (cor de preenchimento dos círculos, tamanho do raio dos círculos, cor de sobreposição, dimensões, cor de fundo  e título da janela) são lidas de um arquivo XML.

<img src="https://github.com/viniciush4/cg1/blob/master/vokoscreen-2019-11-08_22-03-20.gif?raw=true" width="500">
<img src="https://github.com/viniciush4/cg1/blob/master/vokoscreen-2019-11-08_22-05-31.gif?raw=true" width="500">

## Iniciando


As instruções a seguir te auxiliarão a obter uma cópia do projeto em execução na sua máquina local para fins de desenvolvimento e teste.

### Pré-requisitos

Você precisará ter instalada em sua máquina a biblioteca GLUT, além de um compilador C++. Para a biblioteca GLUT, veja [codebind.com](http://www.codebind.com/linux-tutorials/install-opengl-ubuntu-linux/ "codebind.com"):

```
$ sudo apt-get update
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

Para o compilador de C++, veja [linuxconfig.org](https://linuxconfig.org/how-to-install-g-the-c-compiler-on-ubuntu-18-04-bionic-beaver-linux "linuxconfig.org"):

```
$ sudo apt install g++
$ sudo apt install build-essential
```

### Instalando

Baixe o conteúdo do repositório e rode o makefile na raiz do projeto (isso irá compilar e linkar os códigos, gerando um programa chamado *trabalhocg*):

```
$ make
```

Execute o programa passando o caminho relativo (em relação à raiz do projeto) de onde se encontra o arquivo de configurações *config.xml*:

```
$ ./trabalhocg ./Test_1/
```
