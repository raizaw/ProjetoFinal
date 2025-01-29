/**
 * @file teste_jogador.cpp
 * @brief Testes para a classe Jogador.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/jogador.hpp"

TEST_CASE("Testando a classe Jogador") {

    /**
     * \brief Testa o construtor e os métodos de acesso.
     *
     * Verifica se o construtor da classe Jogador inicializa corretamente os atributos
     * e se os métodos de acesso retornam os valores esperados.
     */
    SUBCASE("Testando construtor e métodos de acesso") {
        Jogador jogador("player1", "Luis Henrique");

        CHECK(jogador.getApelido() == "player1");
        CHECK(jogador.getNome() == "Luis Henrique");
    }

    /**
     * \brief Testa a adição de vitórias e derrotas.
     *
     * Verifica se as vitórias e derrotas são adicionadas corretamente para cada tipo de jogo
     * e se as estatísticas são retornadas conforme esperado.
     */
    SUBCASE("Testando adicionar vitórias e derrotas") {
        Jogador jogador("player1", "Luis Henrique");

        jogador.adicionarVitoria(REVERSI, 2);
        jogador.adicionarDerrota(REVERSI, 1);

        auto estatisticas = jogador.getEstatisticasDoJogo(REVERSI);
        CHECK(estatisticas.first == 2);  // Vitórias
        CHECK(estatisticas.second == 1); // Derrotas

        jogador.adicionarVitoria(LIG4, 3);
        jogador.adicionarDerrota(LIG4, 2);

        estatisticas = jogador.getEstatisticasDoJogo(LIG4);
        CHECK(estatisticas.first == 3);  // Vitórias
        CHECK(estatisticas.second == 2); // Derrotas
    }

    /**
     * \brief Testa exceções para TipoDeJogo inválido.
     *
     * Verifica se exceções são lançadas ao tentar adicionar vitórias, derrotas ou obter
     * estatísticas para um tipo de jogo inválido.
     */
    SUBCASE("Testando exceções para TipoDeJogo inválido") {
        Jogador jogador("player1", "Luis Henrique");

        CHECK_THROWS_AS(jogador.adicionarVitoria(static_cast<TipoDeJogo>(TOTAL_DE_JOGOS)), std::out_of_range);
        CHECK_THROWS_AS(jogador.adicionarDerrota(static_cast<TipoDeJogo>(TOTAL_DE_JOGOS)), std::out_of_range);
        CHECK_THROWS_AS(jogador.getEstatisticasDoJogo(static_cast<TipoDeJogo>(TOTAL_DE_JOGOS)), std::out_of_range);
    }

    /**
     * \brief Testa a formatação dos dados do jogador no formato CSV.
     *
     * Verifica se o método `formatarJogadorComoCSV` retorna uma string no formato CSV
     * corretamente formatada, contendo o apelido, nome e estatísticas do jogador.
     */
    SUBCASE("Testando formatação CSV") {
        Jogador jogador("player1", "Luis Henrique");

        jogador.adicionarVitoria(REVERSI, 2);
        jogador.adicionarDerrota(REVERSI, 1);
        jogador.adicionarVitoria(LIG4, 3);
        jogador.adicionarDerrota(LIG4, 2);

        std::string csv_esperado = "player1,Luis Henrique,2,1,3,2,0,0\n";
        CHECK(jogador.formatarJogadorComoCSV() == csv_esperado);
    }
}