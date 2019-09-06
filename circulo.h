#define NUMERO_SEGMENTOS 50

class Circulo {
public:
	float x;
	float y;
	float r;
	float cor_r;
	float cor_g;
	float cor_b;

	Circulo();
	Circulo(float x, float y, float r, float cor_r, float cor_g, float cor_b);
	void desenhar();
	void desenharPreenchido();
	virtual ~Circulo();
};
