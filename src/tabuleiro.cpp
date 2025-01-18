#include "tabuleiro.hpp"

Tabuleiro::Tabuleiro(int linhas, int colunas)
    : linhas(linhas), colunas(colunas), tabuleiro(linhas, std::vector<Peca>(colunas, Peca::VAZIO)) {}

// void Tabuleiro::imprimirTabuleiro() const {
//     for (const auto& linha : tabuleiro) {
//         for (const auto& celula : linha) {
//             switch (celula) {
//             case Peca::VAZIO:
//                 std::cout << "  ";
//                 break;
//             case Peca::JOGADOR1:
//                 std::cout << "X ";
//                 break;
//             case Peca::JOGADOR2:
//                 std::cout << "O ";
//                 break;
//             }
//         }
//         std::cout << "\n";
//     }
// }

void Tabuleiro::setPosicao(int linha, int coluna, Peca peca) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        tabuleiro[linha][coluna] = peca;
    }
}

Tabuleiro::Peca Tabuleiro::getPosicao(int linha, int coluna) const {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        return tabuleiro[linha][coluna];
    }
    return Peca::VAZIO;
}

const std::vector<std::vector<Tabuleiro::Peca>>& Tabuleiro::getTabuleiro() const {
    return tabuleiro;
}