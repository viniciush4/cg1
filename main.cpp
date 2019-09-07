#include <iostream>
#include <math.h>
#include "circulo.h"
#include "configuracao.h"
#include "tinyxml2.h"
#include <GL/glut.h>
#include <vector>

using namespace tinyxml2;
using namespace std;

Configuracao configuracao;
vector<Circulo> circulos;
Circulo circulo_modelo;
bool exibir_circulo_modelo = false;
int indice_circulo_selecionado = -1;

void display(void){

	// Limpa buffers para predefinir valores
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Desenha todos os circulos
	for(int i=0; i < circulos.size(); i++){
		circulos.at(i).desenharPreenchido();
	}
	
	// Desenha o circulo modelo
	if(exibir_circulo_modelo){
		circulo_modelo.desenhar();
	}

	// Força a execução de comandos na fila
	glFlush();
}

bool detectarColisao(float x, float y){
	for(int i=0; i < circulos.size(); i++){

		float distancia = sqrt(pow(x-circulos.at(i).x,2) + pow(y-circulos.at(i).y,2));

		if(distancia < (configuracao.circulo_raio*2.0f))
			return true;
	}
	return false;
}

void adicionarCirculo(float x, float y){
	if(!detectarColisao(x, y))
		circulos.push_back(Circulo(
			x, y, 
			configuracao.circulo_raio,
			configuracao.circulo_cor_r,
			configuracao.circulo_cor_g,
			configuracao.circulo_cor_b
		));
}

void selecionarCirculo(float x, float y){
	for(int i=0; i < circulos.size(); i++){

		float distancia = sqrt(pow(x-circulos.at(i).x,2) + pow(y-circulos.at(i).y,2));

		if(distancia < configuracao.circulo_raio)
			indice_circulo_selecionado = i;
	}
}

void idle(void){

	// Marca a janela atual como precisando ser reexibida
	glutPostRedisplay();
}

// Este callback é chamado quando o mouse se move 
// dentro da janela enquanto um ou mais botões do 
// mouse são pressionados
void motion(int x, int y){
	if(indice_circulo_selecionado != -1){
		circulos.at(indice_circulo_selecionado).x = x;
		circulos.at(indice_circulo_selecionado).y = configuracao.janela_altura - y;
	}
	circulo_modelo.x = x;
	circulo_modelo.y = configuracao.janela_altura - y;
}

// Este callback é chamado quando o mouse se move 
// dentro da janela enquanto nenhum botão do 
// mouse é pressionado
void passiveMotion(int x, int y){
	circulo_modelo.x = x;
	circulo_modelo.y = configuracao.janela_altura - y;
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

	if(button == 0 && state == 0){
		adicionarCirculo(x, configuracao.janela_altura - y);
	}

	if(button == 2 && state == 0){
		selecionarCirculo(x, configuracao.janela_altura - y);
	}

	if(button == 2 && state == 1){
		indice_circulo_selecionado = -1;
	}
}

int main(int argc, char** argv){
	XMLDocument doc;
    doc.LoadFile(strcat(argv[1],"config.xml"));

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

	if(!configuracao.validarConfiguracao()){
		cout << "Erro: As cores no arquivo de configuração devem estar no intervalo [0,1]" << endl;
		return 1;
	}

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
	glClearColor(configuracao.janela_cor_r, configuracao.janela_cor_g, configuracao.janela_cor_b, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, configuracao.janela_largura, 0.0, configuracao.janela_altura, -1.0, 1.0);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passiveMotion);
	glutMainLoop();

	return 0;
}
