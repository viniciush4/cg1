#include "circulo.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

Circulo::Circulo(){
	this->x = 0.;
	this->y = 0.;
	this->r = 0.;
}

Circulo::Circulo(float x, float y, float r){
	this->x = x;
	this->y = y;
	this->r = r;
}

void Circulo::desenhar(){
	glBegin(GL_LINE_LOOP);
    for(int i=0; i < NUMERO_SEGMENTOS; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(NUMERO_SEGMENTOS);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glVertex2f(x + this->x, y + this->y);
    }
    glEnd();
}

void Circulo::desenharPreenchido(){
	glBegin(GL_POLYGON);
    for(int i=0; i < NUMERO_SEGMENTOS; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(NUMERO_SEGMENTOS);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glVertex2f(x + this->x, y + this->y);
    }
    glEnd();
}

Circulo::~Circulo() {
}
