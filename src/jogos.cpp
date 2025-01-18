#include "jogos.hpp"

Jogos::Jogos(int linhas, int colunas) {
    tabuleiro = new Tabuleiro(linhas, colunas); // Inicializa o tabuleiro
    jogadorAtual = Tabuleiro::Peca::JOGADOR1;
}

void Jogos::exibirTabuleiro() const {
    for (const auto& linha : tabuleiro->getTabuleiro()) {
        for (const auto& celula : linha) {
            exibirPeca(celula); // Chama o método virtual puro
        }
        std::cout << "\n";
    }
}

void Jogos::trocarJogador() {
    jogadorAtual = (jogadorAtual == Tabuleiro::Peca::JOGADOR1)? Tabuleiro::Peca::JOGADOR2 : Tabuleiro::Peca::JOGADOR1;
}