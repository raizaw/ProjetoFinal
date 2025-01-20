#include "../include/jogos.hpp"

Jogos::Jogos(int linhas, int colunas) {
    tabuleiro = new Tabuleiro(linhas, colunas); // Inicializa o tabuleiro
    jogadorAtual = Tabuleiro::Peca::JOGADOR1;
}

void Jogos::exibirTabuleiro() const {
    const auto& matriz = tabuleiro->getTabuleiro();
    
    for (size_t i = 0; i < matriz.size(); ++i) {    // Itera sobre as linhas
        const auto& linha = matriz[i];

        // Exibe as peças da linha com os separadores "|"
        for (size_t j = 0; j < linha.size(); ++j) {
            exibirPeca(linha[j]);                  // Exibe a peça
            if (j < linha.size() - 1) {            // Adiciona "|", exceto no final da linha
                std::cout << " | ";
            }
        }
        std::cout << "\n";

        // Adiciona os separadores entre as linhas, exceto no final do tabuleiro
        if (i < matriz.size() - 1) {
            for (size_t j = 0; j < linha.size(); ++j) {
                std::cout << "---";               // Linha horizontal para cada espaço
                if (j < linha.size() - 1) {       // Adiciona o "|" entre os blocos
                    std::cout << "|";
                }
            }
            std::cout << "\n";
        }
    }
}

void Jogos::trocarJogador() {
    jogadorAtual = (jogadorAtual == Tabuleiro::Peca::JOGADOR1)? Tabuleiro::Peca::JOGADOR2 : Tabuleiro::Peca::JOGADOR1;
}