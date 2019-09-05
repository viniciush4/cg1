#define NUMERO_SEGMENTOS 50

class Circulo {
public:
	float x;
	float y;
	float r;
	float cor_r;
	float cor_g;
	float cor_b;
	float cor_sobreposicao_r;
	float cor_sobreposicao_g;
	float cor_sobreposicao_b;

	Circulo();
	Circulo(float x, float y, float r, float cor_r, float cor_g, float cor_b);
	void desenhar();
	void desenharPreenchido();
	virtual ~Circulo();
};
