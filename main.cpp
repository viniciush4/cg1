#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include "circulo.h"
#include "configuracao.h"
#include "tinyxml2.h"
#include <GL/glut.h>

using namespace tinyxml2;
using namespace std;

float deltax = 0.0;
float deltay = 0.0;
bool exibir_circulo_modelo = false;

Configuracao configuracao;
Circulo circulo_modelo;
Circulo circulos[20];
int indice_circulos = 0;
int indice_circulo_selecionado = -1;

void display(void){
	/* Limpar todos os pixels */
	glClear(GL_COLOR_BUFFER_BIT);

	if(exibir_circulo_modelo){
		circulo_modelo.desenhar();
	}

	for(int i=0; i < indice_circulos; i++){
		circulos[i].desenharPreenchido();
	}

	/* Não esperar! */
	glFlush();
	// glutSwapBuffers();

}

bool detectarColisao(float x, float y){
	for(int i=0; i < indice_circulos; i++){

		float distancia = sqrt(pow(x-circulos[i].x,2) + pow(y-circulos[i].y,2));

		if(distancia < (configuracao.circulo_raio*2.0f)){
			return true;
		}
	}
	return false;
}

void adicionarCirculo(float x, float y){
	for(int i=0; i < indice_circulos; i++){

		float distancia = sqrt(pow(x-circulos[i].x,2) + pow(y-circulos[i].y,2));

		if(distancia < (configuracao.circulo_raio*2.0f)){
			return;
		}
	}
	circulos[indice_circulos] = Circulo(
		deltax, deltay, 
		configuracao.circulo_raio,
		configuracao.circulo_cor_r,
		configuracao.circulo_cor_g,
		configuracao.circulo_cor_b
	);
	indice_circulos++;
}

void selecionarCirculo(float x, float y){
	for(int i=0; i < indice_circulos; i++){

		float distancia = sqrt(pow(x-circulos[i].x,2) + pow(y-circulos[i].y,2));

		if(distancia < configuracao.circulo_raio){
			indice_circulo_selecionado = i;
		}
	}
}

void init(void){
	/* Selecionar cor de fundo (preto) */
	glClearColor(configuracao.janela_cor_r, configuracao.janela_cor_g, configuracao.janela_cor_b, 0.0);

	/* inicializar sistema de viz. */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void idle(void){
	//Redesenha após as modificações
	glutPostRedisplay();
}

// Este callback é chamado quando o mouse se move 
// dentro da janela enquanto um ou mais botões do 
// mouse são pressionados
void motion(int x, int y){
	if(indice_circulo_selecionado != -1){
		circulos[indice_circulo_selecionado].x = x / 500.0;
		circulos[indice_circulo_selecionado].y = (500 - y) / 500.0;

		circulo_modelo.x = x / 500.0;
		circulo_modelo.y = (500 - y) / 500.0;
	}
}

// Este callback é chamado quando o mouse se move 
// dentro da janela enquanto nenhum botão do 
// mouse é pressionado
void passiveMotion(int x, int y){
	circulo_modelo.x = x / 500.0;
	circulo_modelo.y = (500 - y) / 500.0;
	if(detectarColisao(circulo_modelo.x, circulo_modelo.y)){
		circulo_modelo.cor_r = configuracao.circulo_modelo_cor_sobreposicao_r;
		circulo_modelo.cor_g = configuracao.circulo_modelo_cor_sobreposicao_g;
		circulo_modelo.cor_b = configuracao.circulo_modelo_cor_sobreposicao_b;
	} else {
		circulo_modelo.cor_r = configuracao.circulo_modelo_cor_r;
		circulo_modelo.cor_g = configuracao.circulo_modelo_cor_g;
		circulo_modelo.cor_b = configuracao.circulo_modelo_cor_b;
	}
	exibir_circulo_modelo = true;
}

void mouse(int button, int state, int x, int y){

	//Não entendi muito bem essa parte, 
	// tem que ajustar mais alguma coisa 
	// pro quadrado ser desenhado aonde clicar. 
	deltay = (500 - y) / 500.0;
	deltax = x / 500.0;

	if(button == 0 && state == 0){
		adicionarCirculo(deltax, deltay);
	}

	if(button == 2 && state == 0){
		selecionarCirculo(deltax, deltay);
	}

	if(button == 2 && state == 1){
		indice_circulo_selecionado = -1;
	}
}

int main(int argc, char** argv){
	XMLDocument doc;
    doc.LoadFile(argv[1]);

	XMLElement* xml_janela = doc.FirstChildElement()->FirstChildElement( "janela" );
	configuracao.janela_titulo = xml_janela->FirstChildElement( "titulo" )->GetText();
	xml_janela->FirstChildElement( "dimensao" )->QueryFloatAttribute( "largura", &configuracao.janela_largura );
	xml_janela->FirstChildElement( "dimensao" )->QueryFloatAttribute( "altura", &configuracao.janela_altura );
	xml_janela->FirstChildElement( "fundo" )->QueryFloatAttribute( "corR", &configuracao.janela_cor_r );
	xml_janela->FirstChildElement( "fundo" )->QueryFloatAttribute( "corG", &configuracao.janela_cor_g );
	xml_janela->FirstChildElement( "fundo" )->QueryFloatAttribute( "corB", &configuracao.janela_cor_b );

	XMLElement* xml_circulo = doc.FirstChildElement()->FirstChildElement( "circulo" );
    xml_circulo->QueryFloatAttribute( "raio", &configuracao.circulo_raio );
	xml_circulo->QueryFloatAttribute( "corR", &configuracao.circulo_cor_r );
	xml_circulo->QueryFloatAttribute( "corG", &configuracao.circulo_cor_g );
	xml_circulo->QueryFloatAttribute( "corB", &configuracao.circulo_cor_b );

	XMLElement* xml_circulo_modelo = doc.FirstChildElement()->FirstChildElement( "circuloModelo" );
	xml_circulo_modelo->QueryFloatAttribute( "corR", &configuracao.circulo_modelo_cor_r );
	xml_circulo_modelo->QueryFloatAttribute( "corG", &configuracao.circulo_modelo_cor_g );
	xml_circulo_modelo->QueryFloatAttribute( "corB", &configuracao.circulo_modelo_cor_b );
	xml_circulo_modelo->QueryFloatAttribute( "corSobreposicaoR", &configuracao.circulo_modelo_cor_sobreposicao_r );
	xml_circulo_modelo->QueryFloatAttribute( "corSobreposicaoG", &configuracao.circulo_modelo_cor_sobreposicao_g );
	xml_circulo_modelo->QueryFloatAttribute( "corSobreposicaoB", &configuracao.circulo_modelo_cor_sobreposicao_b );

	circulo_modelo = Circulo(
		0,0,
		configuracao.circulo_raio,
		configuracao.circulo_modelo_cor_r,
		configuracao.circulo_modelo_cor_g,
		configuracao.circulo_modelo_cor_b
	);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(configuracao.janela_largura, configuracao.janela_altura);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(configuracao.janela_titulo);
	init();
	glutDisplayFunc(display);

	glutIdleFunc(idle);

	glutMouseFunc(mouse);

	glutMotionFunc(motion);

	glutPassiveMotionFunc(passiveMotion);

	//Manda rodar tudo
	glutMainLoop();

	return 0;
}
