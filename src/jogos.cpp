#include "../include/jogos.hpp"

Jogos::Jogos(int linhas, int colunas) {
    tabuleiro = new Tabuleiro(linhas, colunas); // Inicializa o tabuleiro
    jogadorAtual = Tabuleiro::Peca::JOGADOR1;
}

void Jogos::exibirTabuleiro() const {
//     for (const auto& linha : tabuleiro->getTabuleiro()) {
//         for (const auto& celula : linha) {
//             exibirPeca(celula); // Chama o método virtual puro
//             std::cout << " | ";
//         }
//         std::cout << "\n";
//     }
// }
    const auto& matriz = tabuleiro->getTabuleiro();
    for (size_t i = 0; i < matriz.size(); ++i) {    // Itera sobre as linhas
        const auto& linha = matriz[i];
        for (size_t j = 0; j < linha.size(); ++j) { // Itera sobre as colunas
            exibirPeca(linha[j]);                  // Chama o método que exibe a peça
            if (j < linha.size() - 1) {            // Adiciona "|", exceto no final da linha
                std::cout << " | ";
            }
        }
        std::cout << "\n";
        if (i < matriz.size() - 1) {               // Adiciona "-", exceto no final do tabuleiro
            std::cout << "--------\n";             // ATENÇÃO: É necessário alterar o tamanho dependendo do jogo!
        }
    }
}

void Jogos::trocarJogador() {
    jogadorAtual = (jogadorAtual == Tabuleiro::Peca::JOGADOR1)? Tabuleiro::Peca::JOGADOR2 : Tabuleiro::Peca::JOGADOR1;
}