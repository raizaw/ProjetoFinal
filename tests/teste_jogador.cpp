#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/jogador.hpp"

TEST_CASE("Testando a classe Jogador") {
    SUBCASE("Testando construtor e métodos de acesso") {
        Jogador jogador("player1", "João Silva");

        CHECK(jogador.getApelido() == "player1");
        CHECK(jogador.getNome() == "João Silva");
    }

    SUBCASE("Testando adicionar vitórias e derrotas") {
        Jogador jogador("player1", "João Silva");

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

    SUBCASE("Testando exceções para TipoDeJogo inválido") {
        Jogador jogador("player1", "João Silva");

        CHECK_THROWS_AS(jogador.adicionarVitoria(static_cast<TipoDeJogo>(TOTAL_DE_JOGOS)), std::out_of_range);
        CHECK_THROWS_AS(jogador.adicionarDerrota(static_cast<TipoDeJogo>(TOTAL_DE_JOGOS)), std::out_of_range);
        CHECK_THROWS_AS(jogador.getEstatisticasDoJogo(static_cast<TipoDeJogo>(TOTAL_DE_JOGOS)), std::out_of_range);
    }

    SUBCASE("Testando formatação CSV") {
        Jogador jogador("player1", "João Silva");

        jogador.adicionarVitoria(REVERSI, 2);
        jogador.adicionarDerrota(REVERSI, 1);
        jogador.adicionarVitoria(LIG4, 3);
        jogador.adicionarDerrota(LIG4, 2);

        std::string csv_esperado = "player1,João Silva,2,1,3,2,0,0\n";
        CHECK(jogador.formatarJogadorComoCSV() == csv_esperado);
    }
}