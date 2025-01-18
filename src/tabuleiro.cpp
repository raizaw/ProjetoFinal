#include "tabuleiro.hpp"

Tabuleiro::Tabuleiro(int linhas, int colunas) 
    : linhas(linhas), colunas(colunas), tabuleiro(linhas, std::vector<int>(colunas, static_cast<int>(Peca::VAZIO))) {}
