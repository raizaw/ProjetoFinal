/**
 * @file teste_tabuleiro.cpp
 * @brief Arquivo de testes para a classe Tabuleiro.
 */

#include "tabuleiro.hpp"
#include "doctest.h"

/**
 * @brief Teste de inicialização do tabuleiro.
 * 
 * Verifica se o tabuleiro é corretamente inicializado com as dimensões especificadas e se todas as posições estão vazias.
 */
TEST_CASE("Teste de inicialização do tabuleiro") {
    Tabuleiro tab(8, 8);

    CHECK(tab.getLinhas() == 8);
    CHECK(tab.getColunas() == 8);

    for (int i = 0; i < tab.getLinhas(); ++i) {
        for (int j = 0; j < tab.getColunas(); ++j) {
            CHECK(tab.getPosicao(i, j) == Tabuleiro::Peca::VAZIO);
        }
    }
}

/**
 * @brief Teste de colocação e recuperação de peças.
 * 
 * Verifica se as peças são corretamente colocadas e recuperadas do tabuleiro.
 */
TEST_CASE("Teste de colocação e recuperação de peças") {
    Tabuleiro tab(8, 8);

    tab.setPosicao(0, 0, Tabuleiro::Peca::JOGADOR1);
    CHECK(tab.getPosicao(0, 0) == Tabuleiro::Peca::JOGADOR1);

    tab.setPosicao(7, 7, Tabuleiro::Peca::JOGADOR2);
    CHECK(tab.getPosicao(7, 7) == Tabuleiro::Peca::JOGADOR2);

    tab.setPosicao(3, 4, Tabuleiro::Peca::JOGADA_POSSIVEL);
    CHECK(tab.getPosicao(3, 4) == Tabuleiro::Peca::JOGADA_POSSIVEL);
}

/**
 * @brief Teste de acesso fora dos limites do tabuleiro.
 * 
 * Verifica se o tabuleiro retorna Peca::VAZIO ao tentar acessar posições fora dos limites.
 */
TEST_CASE("Teste de acesso fora dos limites do tabuleiro") {
    Tabuleiro tab(8, 8);

    CHECK(tab.getPosicao(-1, 0) == Tabuleiro::Peca::VAZIO);
    CHECK(tab.getPosicao(0, -1) == Tabuleiro::Peca::VAZIO);
    CHECK(tab.getPosicao(8, 0) == Tabuleiro::Peca::VAZIO);
    CHECK(tab.getPosicao(0, 8) == Tabuleiro::Peca::VAZIO);
}

/**
 * @brief Teste de obtenção da matriz do tabuleiro.
 * 
 * Verifica se a matriz retornada por getTabuleiro() reflete corretamente o estado atual do tabuleiro.
 */
TEST_CASE("Teste de obtenção da matriz do tabuleiro") {
    Tabuleiro tab(8, 8);

    tab.setPosicao(0, 0, Tabuleiro::Peca::JOGADOR1);
    tab.setPosicao(7, 7, Tabuleiro::Peca::JOGADOR2);

    const auto& matriz = tab.getTabuleiro();
    CHECK(matriz[0][0] == Tabuleiro::Peca::JOGADOR1);
    CHECK(matriz[7][7] == Tabuleiro::Peca::JOGADOR2);
}

/**
 * @brief Teste de dimensões do tabuleiro.
 * 
 * Verifica se as dimensões do tabuleiro são corretamente retornadas.
 */
TEST_CASE("Teste de dimensões do tabuleiro") {
    Tabuleiro tab(10, 10);

    CHECK(tab.getLinhas() == 10);
    CHECK(tab.getColunas() == 10);
}