class Configuracao {
public:
	float circulo_raio;

	float circulo_cor_r;
	float circulo_cor_g;
	float circulo_cor_b;

	float circulo_modelo_cor_r;
	float circulo_modelo_cor_g;
	float circulo_modelo_cor_b;

	float circulo_modelo_cor_sobreposicao_r;
	float circulo_modelo_cor_sobreposicao_g;
	float circulo_modelo_cor_sobreposicao_b;

	float janela_largura;
	float janela_altura;
	float janela_cor_r;
	float janela_cor_g;
	float janela_cor_b;
	const char* janela_titulo;

	Configuracao();
	Configuracao(char* janela_titulo);
	virtual ~Configuracao();
};
