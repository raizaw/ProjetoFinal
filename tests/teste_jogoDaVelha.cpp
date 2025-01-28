#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/jogoDaVelha.hpp"

TEST_CASE("Testando o método jogadaEValida") {
    JogoDaVelha jogo;

    SUBCASE("Jogada válida") {
        jogo.lerJogada(); // Simula uma entrada válida, como "1 1"
        CHECK(jogo.jogadaEValida() == true);
    }

    SUBCASE("Jogada fora do tabuleiro") {
        jogo.lerJogada(); // Simula uma entrada inválida, como "4 4"
        CHECK(jogo.jogadaEValida() == false);
    }

    SUBCASE("Jogada em posição já ocupada") {
        jogo.lerJogada(); // Simula uma entrada válida, como "1 1"
        jogo.realizarJogada(); // Realiza a jogada
        jogo.lerJogada(); // Tenta jogar na mesma posição novamente
        CHECK(jogo.jogadaEValida() == false);
    }
}

TEST_CASE("Testando o método partidaAcabou") {
    JogoDaVelha jogo;

    SUBCASE("Partida não acabou") {
        CHECK(jogo.partidaAcabou() == false);
    }

    SUBCASE("Partida acabou com vitória na linha") {
        jogo.lerJogada(); // Jogador 1 joga em "1 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "2 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "1 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "2 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "1 3"
        jogo.realizarJogada();
        CHECK(jogo.partidaAcabou() == true);
    }

    SUBCASE("Partida acabou com empate") {
        // Simula uma sequência de jogadas que resulta em empate
        jogo.lerJogada(); // Jogador 1 joga em "1 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "1 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "1 3"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "2 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "2 3"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "2 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "3 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "3 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "3 3"
        jogo.realizarJogada();
        CHECK(jogo.partidaAcabou() == true);
    }
}

TEST_CASE("Testando o método indicarFimDaPartida") {
    JogoDaVelha jogo;

    SUBCASE("Partida terminou em empate") {
        // Simula uma sequência de jogadas que resulta em empate
        jogo.lerJogada(); // Jogador 1 joga em "1 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "1 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "1 3"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "2 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "2 3"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "2 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "3 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "3 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "3 3"
        jogo.realizarJogada();
        CHECK(jogo.indicarFimDaPartida() == 0);
    }

    SUBCASE("Partida terminou com vitória do Jogador 1") {
        jogo.lerJogada(); // Jogador 1 joga em "1 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "2 1"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "1 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 2 joga em "2 2"
        jogo.realizarJogada();
        jogo.lerJogada(); // Jogador 1 joga em "1 3"
        jogo.realizarJogada();
        CHECK(jogo.indicarFimDaPartida() == 1);
    }
}