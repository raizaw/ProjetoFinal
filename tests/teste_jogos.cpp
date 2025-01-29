/**
 * @file
 * @brief Implementação de testes para a classe Jogos utilizando a biblioteca doctest.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/jogos.hpp"
#include "../include/tabuleiro.hpp"

/**
 * @class JogosTeste
 * @brief Classe derivada de Jogos usada para testes (mock).
 * 
 * Implementa os métodos virtuais puros da classe base `Jogos` de forma simulada,
 * permitindo que a lógica dos testes seja focada na validação da interface e comportamento.
 */
class JogosTeste : public Jogos {
public:
    /**
     * @brief Construtor da classe JogosTeste.
     * 
     * @param linhas Número de linhas do tabuleiro.
     * @param colunas Número de colunas do tabuleiro.
     */
    JogosTeste(int linhas, int colunas) : Jogos(linhas, colunas) {}

    /**
     * @brief Implementação simulada para exibir a frase inicial do jogo.
     */
    void fraseInicial() override {
        std::cout << "Início do jogo de teste!" << std::endl;
    }

    /**
     * @brief Implementação simulada para exibir uma peça no tabuleiro.
     * 
     * @param peca A peça que será exibida (JOGADOR1, JOGADOR2 ou vazia).
     */
    void exibirPeca(Tabuleiro::Peca peca) const override {
        switch (peca) {
            case Tabuleiro::Peca::JOGADOR1: std::cout << "X"; break;
            case Tabuleiro::Peca::JOGADOR2: std::cout << "O"; break;
            default: std::cout << " "; break;
        }
    }

    /**
     * @brief Implementação simulada para ler uma jogada.
     * 
     * Neste caso, apenas exibe uma mensagem indicando que a jogada está sendo lida.
     */
    void lerJogada() override {
        std::cout << "Lendo jogada..." << std::endl;
    }

    /**
     * @brief Simula a validação de uma jogada.
     * 
     * @return Sempre retorna `true` indicando que a jogada é válida.
     */
    bool jogadaEValida() const override {
        return true; // Simula uma jogada válida
    }

    /**
     * @brief Simula a realização de uma jogada.
     * 
     * Apenas exibe uma mensagem indicando que a jogada foi realizada.
     */
    void realizarJogada() override {
        std::cout << "Realizando jogada..." << std::endl;
    }

    /**
     * @brief Simula a verificação se a partida terminou.
     * 
     * @return Sempre retorna `false`, indicando que a partida não acabou.
     */
    bool partidaAcabou() override {
        return false; // Simula que a partida não acabou
    }

    /**
     * @brief Simula a indicação do resultado da partida.
     * 
     * @return Sempre retorna `0`, indicando que a partida terminou em empate.
     */
    int indicarFimDaPartida() override {
        return 0; // Simula que a partida terminou sem vencedor
    }
};

/**
 * @brief Testa os métodos da classe Jogos utilizando a implementação simulada (mock).
 */
TEST_CASE("Testando a classe Jogos") {
    /**
     * @test Testa o construtor e a inicialização do tabuleiro.
     */
    SUBCASE("Testando o construtor e inicialização do tabuleiro") {
        JogosTeste jogo(3, 3); // Tabuleiro 3x3
        CHECK(jogo.strJogador(Tabuleiro::Peca::JOGADOR1) == "\033[31mJogador 1 (X)\033[0m");
        CHECK(jogo.strJogador(Tabuleiro::Peca::JOGADOR2) == "\033[33mJogador 2 (O)\033[0m");
    }

    /**
     * @test Testa a troca do jogador atual.
     */
    SUBCASE("Testando a troca de jogador") {
        JogosTeste jogo(3, 3);
        CHECK(jogo.strJogador(jogo.jogadorAtual) == "\033[31mJogador 1 (X)\033[0m"); // Jogador inicial é o 1
        jogo.trocarJogador();
        CHECK(jogo.strJogador(jogo.jogadorAtual) == "\033[33mJogador 2 (O)\033[0m"); // Após troca, jogador 2
    }

    /**
     * @test Testa a exibição do tabuleiro no console.
     */
    SUBCASE("Testando a exibição do tabuleiro") {
        JogosTeste jogo(3, 3);

        // Redireciona a saída padrão (std::cout) para um buffer de string
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        jogo.exibirTabuleiro();

        std::cout.rdbuf(old); // Restaura o buffer original do std::cout

        std::string saida = buffer.str();
        CHECK(saida.find(" | ") != std::string::npos); // Verifica se o tabuleiro foi exibido corretamente
    }

    /**
     * @test Testa os setters para os apelidos dos jogadores.
     */
    SUBCASE("Testando setters de apelidos") {
        JogosTeste jogo(3, 3);
        jogo.setApelidoJogador1("Jogador1");
        jogo.setApelidoJogador2("Jogador2");

        // Verifica se os apelidos foram atribuídos corretamente
        CHECK(jogo.strJogador(1) == "\033[31mJogador 1 (X)\033[0m");
        CHECK(jogo.strJogador(2) == "\033[33mJogador 2 (O)\033[0m");
    }

    /**
     * @test Testa os métodos virtuais puros utilizando a implementação mock.
     */
    SUBCASE("Testando métodos virtuais puros (mock)") {
        JogosTeste jogo(3, 3);

        // Redireciona a saída padrão (std::cout) para um buffer de string
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        jogo.fraseInicial();
        jogo.lerJogada();
        jogo.realizarJogada();

        std::cout.rdbuf(old); // Restaura o buffer original do std::cout

        std::string saida = buffer.str();
        CHECK(saida.find("Início do jogo de teste!") != std::string::npos);
        CHECK(saida.find("Lendo jogada...") != std::string::npos);
        CHECK(saida.find("Realizando jogada...") != std::string::npos);
    }
}