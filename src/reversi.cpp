#include "../include/reversi.hpp"

Reversi::Reversi() : Jogos(8, 8), jogadaLinha(-1), jogadaColuna(-1) {
    // Inicializa o tabuleiro com as peças iniciais do Reversi
    tabuleiro->setPosicao(3, 3, Tabuleiro::Peca::JOGADOR2);
    tabuleiro->setPosicao(3, 4, Tabuleiro::Peca::JOGADOR1);
    tabuleiro->setPosicao(4, 3, Tabuleiro::Peca::JOGADOR1);
    tabuleiro->setPosicao(4, 4, Tabuleiro::Peca::JOGADOR2);
}

void Reversi::exibirPeca(Tabuleiro::Peca peca) const {
    switch (peca) {
        case Tabuleiro::Peca::VAZIO: 
            std::cout << " . ";
            break;
        case Tabuleiro::Peca::JOGADOR1:
            std::cout << "\033[31m X \033[0m"; // X em vermelho
            break;
        case Tabuleiro::Peca::JOGADOR2:
            std::cout << "\033[33m O \033[0m"; // O em amarelo
            break;
    }
}

void Reversi::lerJogada() {
    std::cout << "Jogador " << strJogador(jogadorAtual) << ", insira a linha e a coluna da sua jogada (ex: 3 4): ";
    std::cin >> jogadaLinha >> jogadaColuna;
    --jogadaLinha; // Ajusta para índice zero
    --jogadaColuna; // Ajusta para índice zero
}

bool Reversi::jogadaEValida() const {
    if (!dentroDosLimites(jogadaLinha, jogadaColuna) || 
        tabuleiro->getPosicao(jogadaLinha, jogadaColuna) != Tabuleiro::Peca::VAZIO) {
        return false;
    }

    Tabuleiro::Peca peca = jogadorAtual;
    // Verifica se há pelo menos uma direção válida para captura
    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if ((deltaLinha != 0 || deltaColuna != 0) && 
                direcaoValida(jogadaLinha, jogadaColuna, deltaLinha, deltaColuna, peca)) {
                return true;
            }
        }
    }
    return false;
}

void Reversi::realizarJogada() {
    if (!jogadaEValida()) return;

    Tabuleiro::Peca peca = jogadorAtual;
    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if ((deltaLinha != 0 || deltaColuna != 0) && 
                direcaoValida(jogadaLinha, jogadaColuna, deltaLinha, deltaColuna, peca)) {
                capturarPecas(jogadaLinha, jogadaColuna, peca);
            }
        }
    }

    tabuleiro->setPosicao(jogadaLinha, jogadaColuna, peca);
    exibirTabuleiro();
    trocarJogador();
}

bool Reversi::partidaAcabou() {
    // Verifica se há jogadas possíveis para ambos os jogadores
    for (int i = 0; i < tabuleiro->getLinhas(); ++i) {
        for (int j = 0; j < tabuleiro->getColunas(); ++j) {
            if (tabuleiro->getPosicao(i, j) == Tabuleiro::Peca::VAZIO) {
                return false;
            }
        }
    }
    return true;
}

std::pair<int, int> Reversi::contarPecas() const {
    int jogador1 = 0, jogador2 = 0;
    for (const auto& linha : tabuleiro->getTabuleiro()) {
        for (const auto& celula : linha) {
            if (celula == Tabuleiro::Peca::JOGADOR1) ++jogador1;
            if (celula == Tabuleiro::Peca::JOGADOR2) ++jogador2;
        }
    }
    return {jogador1, jogador2};
}



void Reversi::indicarFimDaPartida() const {
    // Chamada à função contarPecas, que retorna um std::pair
    std::pair<int, int> pecas = contarPecas();

    // Extrai os valores manualmente
    int pecasJogador1 = pecas.first;
    int pecasJogador2 = pecas.second;

    std::cout << "Partida encerrada!\n";
    std::cout << "Jogador 1 (X): " << pecasJogador1 << " peças\n";
    std::cout << "Jogador 2 (O): " << pecasJogador2 << " peças\n";

    if (pecasJogador1 > pecasJogador2) {
        std::cout << "Parabéns, Jogador 1 (X), você venceu!\n";
    } else if (pecasJogador1 < pecasJogador2) {
        std::cout << "Parabéns, Jogador 2 (O), você venceu!\n";
    } else {
        std::cout << "O jogo terminou empatado!\n";
    }
}



bool Reversi::dentroDosLimites(int linha, int coluna) const {
    return linha >= 0 && linha < tabuleiro->getLinhas() && coluna >= 0 && coluna < tabuleiro->getColunas();
}

bool Reversi::direcaoValida(int linha, int coluna, int deltaLinha, int deltaColuna, Tabuleiro::Peca peca) const {
    linha += deltaLinha;
    coluna += deltaColuna;

    bool encontrouOponente = false;
    while (dentroDosLimites(linha, coluna)) {
        if (tabuleiro->getPosicao(linha, coluna) == Tabuleiro::Peca::VAZIO) {
            return false;
        } else if (tabuleiro->getPosicao(linha, coluna) != peca) {
            encontrouOponente = true;
        } else {
            return encontrouOponente;
        }
        linha += deltaLinha;
        coluna += deltaColuna;
    }
    return false;
}

bool Reversi::capturarPecas(int linha, int coluna, Tabuleiro::Peca peca) {
    bool capturou = false;

    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if ((deltaLinha != 0 || deltaColuna != 0) &&
                direcaoValida(linha, coluna, deltaLinha, deltaColuna, peca)) {

                int x = linha + deltaLinha;
                int y = coluna + deltaColuna;
                while (tabuleiro->getPosicao(x, y) != peca) {
                    tabuleiro->setPosicao(x, y, peca);
                    x += deltaLinha;
                    y += deltaColuna;
                }
                capturou = true;
            }
        }
    }

    return capturou;
}
