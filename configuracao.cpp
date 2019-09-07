#include "configuracao.h"

Configuracao::Configuracao(){}

bool Configuracao::validarConfiguracao(){
    if( 
        this->circulo_cor_r < 0.0 || this->circulo_cor_r > 1.0 ||
        this->circulo_cor_g < 0.0 || this->circulo_cor_g > 1.0 ||
        this->circulo_cor_b < 0.0 || this->circulo_cor_b > 1.0 ||

        this->circulo_modelo_cor_r < 0.0 || this->circulo_modelo_cor_r > 1.0 ||
        this->circulo_modelo_cor_g < 0.0 || this->circulo_modelo_cor_g > 1.0 ||
        this->circulo_modelo_cor_b < 0.0 || this->circulo_modelo_cor_b > 1.0 ||

        this->circulo_modelo_cor_sobreposicao_r < 0.0 || this->circulo_modelo_cor_sobreposicao_r > 1.0 ||
        this->circulo_modelo_cor_sobreposicao_g < 0.0 || this->circulo_modelo_cor_sobreposicao_g > 1.0 ||
        this->circulo_modelo_cor_sobreposicao_b < 0.0 || this->circulo_modelo_cor_sobreposicao_b > 1.0 ||

        this->janela_cor_r < 0.0 || this->janela_cor_r > 1.0 ||
        this->janela_cor_g < 0.0 || this->janela_cor_g > 1.0 ||
        this->janela_cor_b < 0.0 || this->janela_cor_b > 1.0
    ){
        return false;
    }
    return true;
}

Configuracao::~Configuracao() {
}
