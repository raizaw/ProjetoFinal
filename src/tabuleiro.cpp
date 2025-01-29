#include "../include/tabuleiro.hpp"

// Construtor: cria um tabuleiro com o número de linhas e colunas especificado
Tabuleiro::Tabuleiro(int linhas, int colunas)
    : linhas(linhas), colunas(colunas), tabuleiro(linhas, std::vector<Peca>(colunas, Peca::VAZIO)) {}

// Define uma peça em uma posição específica do tabuleiro, se estiver dentro dos limites
void Tabuleiro::setPosicao(int linha, int coluna, Peca peca) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        tabuleiro[linha][coluna] = peca;
    }
}

// Retorna a peça em uma posição específica do tabuleiro, ou VAZIO se estiver fora dos limites
Tabuleiro::Peca Tabuleiro::getPosicao(int linha, int coluna) const {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        return tabuleiro[linha][coluna];
    }
    return Peca::VAZIO;
}

// Retorna uma referência constante para o tabuleiro (matriz de peças)
const std::vector<std::vector<Tabuleiro::Peca>>& Tabuleiro::getTabuleiro() const {
    return tabuleiro;
}

// Retorna o número de linhas do tabuleiro
int Tabuleiro::getLinhas() const {
    return linhas;
}

// Retorna o número de colunas do tabuleiro
int Tabuleiro::getColunas() const {
    return colunas;
}