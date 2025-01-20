#include "../include/jogoDaVelha.hpp"

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
    }
};

void JogoDaVelha::lerJogada() {
    std::cout << "Jogador " << strJogador(jogadorAtual) << ", insira a linha e a coluna da sua jogada (ex: 0 1): ";
    std::cin >> jogadaLinha >> jogadaColuna;
}; 

bool JogoDaVelha::jogadaEValida() const {
    // Verifica se a posição está dentro dos limites do tabuleiro
    if (jogadaLinha < 0 || jogadaLinha >= tabuleiro->getLinhas() ||
        jogadaColuna < 0 || jogadaColuna >= tabuleiro->getColunas()) {
        std::cout << "Jogada inválida: posição fora do tabuleiro.\n";
        return false;
    }

    // Verifica se a posição está vazia
    if (tabuleiro->getPosicao(jogadaLinha, jogadaColuna) != Tabuleiro::Peca::VAZIO) {
        std::cout << "Jogada inválida: posição já ocupada.\n";
        return false;
    }

    return true;
}; 

void JogoDaVelha::realizarJogada() {
    // Define a peça do jogador atual na posição indicada
    Tabuleiro::Peca pecaJogador = (jogadorAtual == Tabuleiro::Peca::JOGADOR1) ? Tabuleiro::Peca::JOGADOR1 : Tabuleiro::Peca::JOGADOR2;
    tabuleiro->setPosicao(jogadaLinha, jogadaColuna, pecaJogador);

    // Exibe o estado atualizado do tabuleiro
    exibirTabuleiro();

    // Troca para o próximo jogador
    trocarJogador();
}; 

bool JogoDaVelha::partidaAcabou() {
    // Verifica se algum jogador venceu (linhas, colunas ou diagonais)
    const auto& matriz = tabuleiro->getTabuleiro();

    // Verifica linhas
    for (const auto& linha : matriz) {
        if (linha[0] != Tabuleiro::Peca::VAZIO && 
            linha[0] == linha[1] && linha[1] == linha[2]) {
            vencedor = (linha[0] == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
            return true;
        }
    }

    // Verifica colunas
    for (int col = 0; col < 3; ++col) {
        if (matriz[0][col] != Tabuleiro::Peca::VAZIO && 
            matriz[0][col] == matriz[1][col] && matriz[1][col] == matriz[2][col]) {
            vencedor = (matriz[0][col] == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
            return true;
        }
    }

    // Verifica diagonais
    if (matriz[0][0] != Tabuleiro::Peca::VAZIO && 
        matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2]) {
        vencedor = (matriz[0][0] == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
        return true;
    }

    if (matriz[0][2] != Tabuleiro::Peca::VAZIO && 
        matriz[0][2] == matriz[1][1] && matriz[1][1] == matriz[2][0]) {
        vencedor = (matriz[0][2] == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
        return true;
    }

    // Verifica empate (nenhum espaço vazio)
    for (const auto& linha : matriz) {
        for (const auto& celula : linha) {
            if (celula == Tabuleiro::Peca::VAZIO) {
                return false; // Ainda há espaços disponíveis, o jogo continua
            }
        }
    }

    vencedor = 0; // Indica empate
    return true;
}; 

void JogoDaVelha::indicarFimDaPartida() const {
    if (vencedor == 0) {
        std::cout << "A partida terminou em empate!\n";
    } else {
        std::cout << "Parabéns, Jogador " << vencedor << "! Você venceu!\n";
    }

    std::cout << "Jogo encerrado.\n";
    exibirTabuleiro();
};