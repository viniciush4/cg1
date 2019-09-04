#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include "circulo.h"
#include <GL/glut.h>

using namespace std;

float deltax = 0.0;
float deltay = 0.0;

Circulo circulo_modelo = Circulo(0,0,0.2);
int indice_circulo_selecionado;
Circulo circulos[20];
int indice_circulos = 0;

void display(void)
{
	/* Limpar todos os pixels */
	glClear(GL_COLOR_BUFFER_BIT);


	/* Desenhar um polígono branco (retângulo) */
/*	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.25 + deltax, 0.25 + deltay, 0.0);
		glVertex3f(0.75 + deltax, 0.25 + deltay, 0.0);
		glVertex3f(0.75 + deltax, 0.75 + deltay, 0.0);
		glVertex3f(0.25 + deltax, 0.75 + deltay, 0.0);
	glEnd();
*/
	//Assim o quadrado é desenhado aonde clicar
	// glColor3f(1.0, 1.0, 1.0);
	// glBegin(GL_POLYGON);
	// 	glVertex3f(-0.25 + deltax, -0.25 + deltay, 0.0);
	// 	glVertex3f(0.25 + deltax, -0.25 + deltay, 0.0);
	// 	glVertex3f(0.25 + deltax, 0.25 + deltay, 0.0);
	// 	glVertex3f(-0.25 + deltax, 0.25 + deltay, 0.0);
	// glEnd();

	// DrawCircle(deltax, deltay, 0.2, 50);

	circulo_modelo.desenhar();

	for(int i=0; i < indice_circulos; i++){
		circulos[i].desenharPreenchido();
	}

	/* Não esperar! */
	glFlush();

}

void adicionarCirculo(float x, float y){
	for(int i=0; i < indice_circulos; i++){

		float distancia = sqrt(pow(x-circulos[i].x,2) + pow(y-circulos[i].y,2));

		if(distancia < 0.4){
			// cout << "Colisão!" << endl;
			return;
		}
	}
	circulos[indice_circulos] = Circulo(deltax, deltay, 0.2);
	indice_circulos++;
}

void selecionarCirculo(float x, float y){
	for(int i=0; i < indice_circulos; i++){

		float distancia = sqrt(pow(x-circulos[i].x,2) + pow(y-circulos[i].y,2));

		if(distancia < 0.2){
			// cout << "Seleção!" << endl;
			indice_circulo_selecionado = i;
		}
	}
}


void init(void)
{
	/* Selecionar cor de fundo (preto) */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* inicializar sistema de viz. */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

//Função que é chamada o tempo todo
void idle(void)
{
	//Redesenha após as modificações
	glutPostRedisplay();
}

// Este callback é chamado quando o mouse se move 
// dentro da janela enquanto um ou mais botões do 
// mouse são pressionados
void motion(int x, int y){
	// cout << x << "  " << y << endl;
	circulos[indice_circulo_selecionado].x = x / 500.0;
	circulos[indice_circulo_selecionado].y = (500 - y) / 500.0;

	circulo_modelo.x = x / 500.0;
	circulo_modelo.y = (500 - y) / 500.0;
}

// Este callback é chamado quando o mouse se move 
// dentro da janela enquanto nenhum botão do 
// mouse é pressionado
void passiveMotion(int x, int y){
	// cout << x << "  " << y << endl;
	circulo_modelo.x = x / 500.0;
	circulo_modelo.y = (500 - y) / 500.0;
}

void mouse(int button, int state, int x, int y)
{
	//Valores das variáveis do mouse
	// cout << "Antes: " << state << "  " << x << "  " << y << "  " << button << endl;

	//É necessário ajustar o eixo y de acordo com o tamanho da janela criada
	// cout << "Depois: " << state << "  " << x << "  " << 500 - y << "  " << button << endl;

	if(button == 0 && state == 1)
	{
		
		//Não entendi muito bem essa parte, 
		// tem que ajustar mais alguma coisa 
		// pro quadrado ser desenhado aonde clicar. 
		deltay = (500 - y) / 500.0;
		deltax = x / 500.0;

		adicionarCirculo(deltax, deltay);

		selecionarCirculo(deltax, deltay);
	}
	else
	{

	}


	//Redesenha após as modificações
	glutPostRedisplay();

}

int main(int argc, char** argv)
{
	// Ler xml


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Desenhando um Quadrado!");
	init();
	glutDisplayFunc(display);

	//Manda redesenhar toda hora
	glutIdleFunc(idle);

	// Instala callback mouse
	glutMouseFunc(mouse);

	glutMotionFunc(motion);

	glutPassiveMotionFunc(passiveMotion);

	//Manda rodar tudo
	glutMainLoop();

	return 0;
}
