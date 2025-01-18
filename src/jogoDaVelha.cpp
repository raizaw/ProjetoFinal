#include "jogoDaVelha.hpp"

void JogoDaVelha::exibirPeca(Tabuleiro::Peca peca) const {
    switch (peca) {
    case Tabuleiro::Peca::VAZIO:
        std::cout << " ";
        break;
    case Tabuleiro::Peca::JOGADOR1:
        std::cout << "\033[31mX\033[0m"; // X em vermelho
        break;
    case Tabuleiro::Peca::JOGADOR2:
        std::cout << "\033[33mO\033[0m"; // O em amarelo
        break;
};