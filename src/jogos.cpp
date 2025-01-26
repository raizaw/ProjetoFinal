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

std::string Jogos::strJogador(int jogador) const {
    if (jogador == 1) {
        return "\033[31mJogador 1 (X)\033[0m"; // Jogador 1 em vermelho
    } else if (jogador == 2) {
        return "\033[33mJogador 2 (O)\033[0m"; // Jogador 2 em amarelo
    } else {
        return "Jogador inválido";
    }
}

std::string Jogos::strJogador(Tabuleiro::Peca peca) const {
    switch (peca) {
    case Tabuleiro::Peca::JOGADOR1:
        return "\033[31mJogador 1 (X)\033[0m"; // Jogador 1 em vermelho
    case Tabuleiro::Peca::JOGADOR2:
        return "\033[33mJogador 2 (O)\033[0m"; // Jogador 2 em amarelo
    default:
        return "Vazio ou inválido";
    }
}

// Setters
void Jogos::setApelidoJogador1(std::string apelido) {
    apelidoJogador1 = apelido;
};

void Jogos::setApelidoJogador2(std::string apelido) {
    apelidoJogador2 = apelido;
};