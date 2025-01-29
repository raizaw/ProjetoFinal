/**
 * @file
 * @brief Implementação de testes para a classe Reversi utilizando a biblioteca doctest.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/reversi.hpp"
#include <iostream>
#include <sstream>

/**
 * @brief Testa os métodos da classe Reversi.
 */
TEST_CASE("Testando a classe Reversi") {

    /**
     * @test Testa o método lerJogada, que lê a jogada do usuário.
     * Simula a entrada do jogador e verifica se os índices de linha e coluna
     * são corretamente ajustados para começar em 0.
     */
    SUBCASE("Testando o método lerJogada") {
        Reversi jogo;
        std::istringstream input("3 4\n"); // Simula a entrada do usuário
        std::cin.rdbuf(input.rdbuf()); // Redireciona o std::cin para o input simulado

        jogo.lerJogada(); // Chama o método lerJogada

        CHECK(jogo.getJogadaLinha() == 2); // Verifica se a linha foi ajustada corretamente (índice 0)
        CHECK(jogo.getJogadaColuna() == 3); // Verifica se a coluna foi ajustada corretamente (índice 0)
    }

    /**
     * @test Testa o método jogadaEValida, que verifica se a jogada é válida.
     * Avalia condições como posições fora dos limites ou posições ocupadas.
     */
    SUBCASE("Testando o método jogadaEValida") {
        Reversi jogo;

        // Testa uma jogada válida
        jogo.setJogadaLinha(2);
        jogo.setJogadaColuna(3);
        CHECK(jogo.jogadaEValida() == true);

        // Testa jogadas inválidas
        jogo.setJogadaLinha(-1); // Fora dos limites
        jogo.setJogadaColuna(3);
        CHECK(jogo.jogadaEValida() == false);

        jogo.setJogadaLinha(8); // Fora dos limites
        jogo.setJogadaColuna(3);
        CHECK(jogo.jogadaEValida() == false);

        // Testa uma posição já ocupada
        jogo.setJogadaLinha(3);
        jogo.setJogadaColuna(3);
        CHECK(jogo.jogadaEValida() == false);
    }

    /**
     * @test Testa o método realizarJogada, que executa uma jogada no tabuleiro.
     * Verifica se a peça foi colocada corretamente após uma jogada válida.
     */
    SUBCASE("Testando o método realizarJogada") {
        Reversi jogo;

        // Simula uma jogada válida
        jogo.setJogadaLinha(2);
        jogo.setJogadaColuna(3);
        jogo.realizarJogada();

        // Verifica se a peça foi colocada na posição correta
        CHECK(jogo.getTabuleiro().getPosicao(2, 3) == Tabuleiro::Peca::JOGADOR1); // Jogador 1 começa
    }

    /**
     * @test Testa o método partidaAcabou, que verifica se o jogo terminou.
     * Simula um tabuleiro cheio e verifica se a partida é detectada como finalizada.
     */
    SUBCASE("Testando o método partidaAcabou") {
        Reversi jogo;

        // Simula um tabuleiro cheio
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                jogo.getTabuleiro().setPosicao(i, j, Tabuleiro::Peca::JOGADOR1);
            }
        }

        CHECK(jogo.partidaAcabou() == true); // Verifica se a partida acabou
    }

    /**
     * @test Testa o método contarPecas, que retorna a quantidade de peças de cada jogador.
     * Simula um tabuleiro com peças de ambos os jogadores e verifica a contagem.
     */
    SUBCASE("Testando o método contarPecas") {
        Reversi jogo;

        // Simula um tabuleiro com algumas peças
        jogo.getTabuleiro().setPosicao(0, 0, Tabuleiro::Peca::JOGADOR1);
        jogo.getTabuleiro().setPosicao(0, 1, Tabuleiro::Peca::JOGADOR2);
        jogo.getTabuleiro().setPosicao(1, 0, Tabuleiro::Peca::JOGADOR1);

        auto contagem = jogo.contarPecas();
        CHECK(contagem.first == 2); // Verifica o número de peças do jogador 1
        CHECK(contagem.second == 1); // Verifica o número de peças do jogador 2
    }

    /**
     * @test Testa o método direcaoValida, que verifica se uma jogada é válida em uma direção.
     * Simula um cenário no qual a direção deve ser considerada válida.
     */
    SUBCASE("Testando o método direcaoValida") {
        Reversi jogo;

        // Simula uma situação onde a direção é válida
        jogo.getTabuleiro().setPosicao(3, 3, Tabuleiro::Peca::JOGADOR2);
        jogo.getTabuleiro().setPosicao(3, 4, Tabuleiro::Peca::JOGADOR1);

        CHECK(jogo.direcaoValida(3, 5, 0, -1, Tabuleiro::Peca::JOGADOR1) == true); // Verifica se a direção é válida
    }

    /**
     * @test Testa o método dentroDosLimites, que verifica se uma posição está dentro dos limites do tabuleiro.
     */
    SUBCASE("Testando o método dentroDosLimites") {
        Reversi jogo;

        // Testa posições dentro dos limites
        CHECK(jogo.dentroDosLimites(0, 0) == true);
        CHECK(jogo.dentroDosLimites(7, 7) == true);

        // Testa posições fora dos limites
        CHECK(jogo.dentroDosLimites(-1, 0) == false);
        CHECK(jogo.dentroDosLimites(8, 0) == false);
        CHECK(jogo.dentroDosLimites(0, -1) == false);
        CHECK(jogo.dentroDosLimites(0, 8) == false);
    }
}