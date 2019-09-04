#define NUMERO_SEGMENTOS 50

class Circulo {
public:
	float x;
	float y;
	float r;

	Circulo();
	Circulo(float x, float y, float r);
	void desenhar();
	void desenharPreenchido();
	virtual ~Circulo();
};
