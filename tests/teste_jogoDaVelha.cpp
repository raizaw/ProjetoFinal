/**
 * @file
 * @brief Implementação dos testes para a classe JogoDaVelha utilizando a biblioteca doctest.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/jogoDaVelha.hpp"

/**
 * @brief Simula uma sequência de jogadas.
 * 
 * @param jogo Objeto da classe JogoDaVelha.
 * @param jogadas Vetor de pares de inteiros representando as jogadas (linha, coluna).
 */
void simularJogadas(JogoDaVelha& jogo, const std::vector<std::pair<int, int>>& jogadas) {
    for (const auto& jogada : jogadas) {
        jogo.setJogada(jogada.first, jogada.second); /**< Define a jogada diretamente. */
        jogo.realizarJogada(); /**< Realiza a jogada no tabuleiro. */
    }
}

/**
 * @brief Testa o método jogadaEValida da classe JogoDaVelha.
 */
TEST_CASE("Testando o método jogadaEValida") {
    JogoDaVelha jogo;

    SUBCASE("Jogada válida em uma posição desocupada") {
        jogo.setJogada(1, 1); /**< Configura a jogada na posição "1 1". */
        CHECK_MESSAGE(jogo.jogadaEValida(), "A jogada deveria ser válida para uma posição desocupada.");
    }

    SUBCASE("Jogada fora do tabuleiro") {
        jogo.setJogada(4, 4); /**< Configura a jogada em uma posição fora do tabuleiro. */
        CHECK_MESSAGE(!jogo.jogadaEValida(), "A jogada deveria ser inválida para uma posição fora do tabuleiro.");
    }

    SUBCASE("Jogada em posição já ocupada") {
        jogo.setJogada(1, 1);
        jogo.realizarJogada(); /**< Realiza uma jogada na posição "1 1". */
        jogo.setJogada(1, 1); /**< Tenta jogar novamente na mesma posição. */
        CHECK_MESSAGE(!jogo.jogadaEValida(), "A jogada deveria ser inválida para uma posição ocupada.");
    }
}

/**
 * @brief Testa o método partidaAcabou da classe JogoDaVelha.
 */
TEST_CASE("Testando o método partidaAcabou") {
    JogoDaVelha jogo;

    SUBCASE("Partida não acabou no início do jogo") {
        CHECK_MESSAGE(!jogo.partidaAcabou(), "A partida não deveria ter acabado no início do jogo.");
    }

    SUBCASE("Partida acaba com vitória em uma linha") {
        simularJogadas(jogo, {
            {1, 1}, {2, 1}, // Jogador 1 e Jogador 2
            {1, 2}, {2, 2}, // Jogador 1 e Jogador 2
            {1, 3}          // Jogador 1 (vitória)
        });
        CHECK_MESSAGE(jogo.partidaAcabou(), "A partida deveria ter acabado com vitória.");
    }

    SUBCASE("Partida acaba em empate") {
        simularJogadas(jogo, {
            {1, 1}, {1, 2},
            {1, 3}, {2, 1},
            {2, 3}, {2, 2},
            {3, 1}, {3, 3},
            {3, 2} // Última jogada para empate
        });
        CHECK_MESSAGE(jogo.partidaAcabou(), "A partida deveria ter acabado em empate.");
    }
}

/**
 * @brief Testa o método indicarFimDaPartida da classe JogoDaVelha.
 */
TEST_CASE("Testando o método indicarFimDaPartida") {
    JogoDaVelha jogo;

    SUBCASE("Partida termina em empate") {
        simularJogadas(jogo, {
            {1, 1}, {1, 2},
            {1, 3}, {2, 1},
            {2, 3}, {2, 2},
            {3, 1}, {3, 3},
            {3, 2} // Última jogada para empate
        });
        CHECK_MESSAGE(jogo.indicarFimDaPartida() == 0, "O método deveria indicar empate (0).");
    }

    SUBCASE("Partida termina com vitória do Jogador 1") {
        simularJogadas(jogo, {
            {1, 1}, {2, 1}, // Jogador 1 e Jogador 2
            {1, 2}, {2, 2}, // Jogador 1 e Jogador 2
            {1, 3}          // Jogador 1 (vitória)
        });
        CHECK_MESSAGE(jogo.indicarFimDaPartida() == 1, "O método deveria indicar vitória do Jogador 1 (1).");
    }
}
