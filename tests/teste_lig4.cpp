#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/lig4.hpp"
#include <iostream>
#include <sstream>

TEST_CASE("Testando a classe lig4") {
    SUBCASE("Testando o método lerJogada") {
        lig4 jogo;
        std::istringstream input("4\n"); // Simula a entrada do usuário
        std::cin.rdbuf(input.rdbuf()); // Redireciona o std::cin para o input simulado

        jogo.lerJogada(); // Chama o método lerJogada

        CHECK(jogo.getColunaEscolhida() == 3); // Verifica se a coluna foi ajustada corretamente (índice 0)
    }

    SUBCASE("Testando o método jogadaEValida") {
        lig4 jogo;

        // Testa uma jogada válida
        jogo.setColunaEscolhida(3); // Coluna 4 (índice 3)
        CHECK(jogo.jogadaEValida() == true);

        // Testa uma jogada inválida (coluna fora dos limites)
        jogo.setColunaEscolhida(-1); // Coluna inválida
        CHECK(jogo.jogadaEValida() == false);

        jogo.setColunaEscolhida(7); // Coluna inválida
        CHECK(jogo.jogadaEValida() == false);
    }

    SUBCASE("Testando o método realizarJogada") {
        lig4 jogo;

        // Simula uma jogada na coluna 4 (índice 3)
        jogo.setColunaEscolhida(3);
        jogo.realizarJogada();

        // Verifica se a peça foi colocada na posição correta
        CHECK(jogo.getTabuleiro().getPosicao(5, 3) == Tabuleiro::Peca::JOGADOR1); // Jogador 1 começa
    }

    SUBCASE("Testando o método partidaAcabou") {
        lig4 jogo;

        // Simula uma vitória do jogador 1
        for (int i = 0; i < 4; ++i) {
            jogo.setColunaEscolhida(i);
            jogo.realizarJogada(); // Jogador 1
            jogo.setColunaEscolhida(i);
            jogo.realizarJogada(); // Jogador 2
        }

        CHECK(jogo.partidaAcabou() == true); // Verifica se a partida acabou
        CHECK(jogo.indicarFimDaPartida() == 1); // Verifica se o jogador 1 venceu
    }

    SUBCASE("Testando o método verificarVitoria") {
        lig4 jogo;

        // Simula uma vitória horizontal do jogador 1
        for (int i = 0; i < 4; ++i) {
            jogo.getTabuleiro().setPosicao(5, i, Tabuleiro::Peca::JOGADOR1);
        }

        CHECK(jogo.verificarVitoria(5, 0) == true); // Verifica se há vitória
    }

    SUBCASE("Testando o método dentroDosLimites") {
        lig4 jogo;

        // Testa posições dentro dos limites
        CHECK(jogo.dentroDosLimites(0, 0) == true);
        CHECK(jogo.dentroDosLimites(5, 6) == true);

        // Testa posições fora dos limites
        CHECK(jogo.dentroDosLimites(-1, 0) == false);
        CHECK(jogo.dentroDosLimites(6, 0) == false);
        CHECK(jogo.dentroDosLimites(0, -1) == false);
        CHECK(jogo.dentroDosLimites(0, 7) == false);
    }
}