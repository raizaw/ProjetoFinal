/**
 * @file teste_gestaoDeJogadores.cpp
 * @brief Testes para a classe Gestão de Jogadores.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/gestaoDeJogadores.hpp"
#include <filesystem>

/**
 * \brief Função auxiliar para remover um arquivo, caso ele exista.
 *
 * \param nomeDoArquivo O nome do arquivo a ser removido.
 */
void removerArquivoSeExistir(const std::string& nomeDoArquivo) {
    if (std::filesystem::exists(nomeDoArquivo)) {
        std::filesystem::remove(nomeDoArquivo);
    }
}

/**
 * \brief Testes para a classe GestaoDeJogadores.
 *
 * Este conjunto de testes verifica o funcionamento dos métodos da classe GestaoDeJogadores,
 * incluindo cadastro, remoção, listagem e atualização de jogadores.
 */
TEST_CASE("Testando a classe GestaoDeJogadores") {
    const std::string caminhoArquivoTeste = "./test_jogadores.csv";
    removerArquivoSeExistir(caminhoArquivoTeste); // Garante que o arquivo não exista antes dos testes

    /**
     * \brief Testa o cadastro de jogadores e o carregamento do arquivo.
     *
     * Verifica se os jogadores são cadastrados corretamente e se o arquivo é carregado
     * com sucesso, mantendo o estado esperado.
     */
    SUBCASE("Testando cadastrarJogador e carregarTodoArquivo") {
        GestaoDeJogadores gestao(caminhoArquivoTeste);

        CHECK(gestao.cadastrarJogador("player1", "Luis"));
        CHECK(gestao.cadastrarJogador("player2", "Raiza"));

        CHECK(gestao.carregarTodoArquivo());
        CHECK(gestao.jogadores_map.size() == 2);
        CHECK(gestao.jogadores_map.find("player1") != gestao.jogadores_map.end());
        CHECK(gestao.jogadores_map.find("player2") != gestao.jogadores_map.end());
    }

    /**
     * \brief Testa a remoção de um jogador.
     *
     * Verifica se um jogador é removido corretamente e se o estado do sistema
     * reflete essa remoção.
     */
    SUBCASE("Testando removerJogador") {
        GestaoDeJogadores gestao(caminhoArquivoTeste);

        CHECK(gestao.cadastrarJogador("player1", "Arthur"));
        CHECK(gestao.cadastrarJogador("player2", "Raiza"));

        CHECK(gestao.removerJogador("player1"));
        CHECK(gestao.jogadores_map.size() == 1);
        CHECK(gestao.jogadores_map.find("player1") == gestao.jogadores_map.end());
        CHECK(gestao.jogadores_map.find("player2") != gestao.jogadores_map.end());
    }

    /**
     * \brief Testa a listagem de jogadores.
     *
     * Verifica se a função `listarJogadores` exibe corretamente os jogadores cadastrados.
     */
    SUBCASE("Testando listarJogadores") {
        GestaoDeJogadores gestao(caminhoArquivoTeste);

        CHECK(gestao.cadastrarJogador("player1", "Arthur"));
        CHECK(gestao.cadastrarJogador("player2", "Raiza"));

        // Redireciona cout para um stringstream para capturar a saída
        std::stringstream buffer;
        std::streambuf* antigo = std::cout.rdbuf(buffer.rdbuf());

        gestao.listarJogadores();

        std::cout.rdbuf(antigo); // Restaura cout

        std::string saida = buffer.str();
        CHECK(saida.find("Luis") != std::string::npos);
        CHECK(saida.find("Raiza") != std::string::npos);
    }

    /**
     * \brief Testa o carregamento de dois jogadores específicos.
     *
     * Verifica se a função `carregarDoisJogadores` carrega apenas os jogadores especificados,
     * ignorando os demais.
     */
    SUBCASE("Testando carregarDoisJogadores") {
        GestaoDeJogadores gestao(caminhoArquivoTeste);

        CHECK(gestao.cadastrarJogador("player1", "Luis"));
        CHECK(gestao.cadastrarJogador("player2", "Raiza"));
        CHECK(gestao.cadastrarJogador("player3", "Marco"));

        CHECK(gestao.carregarDoisJogadores("player1", "player2"));
        CHECK(gestao.jogadores_map.size() == 2);
        CHECK(gestao.jogadores_map.find("player1") != gestao.jogadores_map.end());
        CHECK(gestao.jogadores_map.find("player2") != gestao.jogadores_map.end());
        CHECK(gestao.jogadores_map.find("player3") == gestao.jogadores_map.end());
    }

    /**
     * \brief Testa a atualização de estatísticas dos jogadores.
     *
     * Verifica se as estatísticas dos jogadores são atualizadas corretamente e se
     * o estado do sistema reflete essas mudanças.
     */
    SUBCASE("Testando atualizarEstatisticas") {
        GestaoDeJogadores gestao(caminhoArquivoTeste);

        CHECK(gestao.cadastrarJogador("player1", "Luis"));
        CHECK(gestao.cadastrarJogador("player2", "Raiza"));

        // Simula a atualização de estatísticas
        std::map<std::string, std::unique_ptr<Jogador>> jogadoresParaAtualizar;
        jogadoresParaAtualizar["player1"] = std::make_unique<Jogador>("player1", "Luis");
        jogadoresParaAtualizar["player1"]->adicionarVitoria(REVERSI, 5);
        jogadoresParaAtualizar["player1"]->adicionarDerrota(REVERSI, 3);

        CHECK(gestao.atualizarEstatisticas(jogadoresParaAtualizar));

        CHECK(gestao.carregarTodoArquivo());
        auto& jogadorAtualizado = gestao.jogadores_map["player1"];
        auto estatisticas = jogadorAtualizado->getEstatisticasDoJogo(REVERSI);
        CHECK(estatisticas.first == 5);  // Vitórias
        CHECK(estatisticas.second == 3); // Derrotas
    }

    removerArquivoSeExistir(caminhoArquivoTeste); // Limpa após os testes
}