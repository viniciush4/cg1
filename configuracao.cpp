#include "configuracao.h"
#include "tinyxml2.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace tinyxml2;
using namespace std;

Configuracao::Configuracao(){}
Configuracao::Configuracao(char* janela_titulo){
    this->janela_titulo = janela_titulo;
}

Configuracao::~Configuracao() {
}
