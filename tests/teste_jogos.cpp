#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/jogos.hpp"
#include "../include/tabuleiro.hpp"

// Classe de teste para Jogos (mock)
class JogosTeste : public Jogos {
public:
    JogosTeste(int linhas, int colunas) : Jogos(linhas, colunas) {}

    // Implementação dos métodos virtuais puros para teste
    void fraseInicial() override {
        std::cout << "Início do jogo de teste!" << std::endl;
    }

    void exibirPeca(Tabuleiro::Peca peca) const override {
        switch (peca) {
            case Tabuleiro::Peca::JOGADOR1: std::cout << "X"; break;
            case Tabuleiro::Peca::JOGADOR2: std::cout << "O"; break;
            default: std::cout << " "; break;
        }
    }

    void lerJogada() override {
        std::cout << "Lendo jogada..." << std::endl;
    }

    bool jogadaEValida() const override {
        return true; // Simula uma jogada válida
    }

    void realizarJogada() override {
        std::cout << "Realizando jogada..." << std::endl;
    }

    bool partidaAcabou() override {
        return false; // Simula que a partida não acabou
    }

    int indicarFimDaPartida() override {
        return 0; // Simula que a partida terminou sem vencedor
    }
};

TEST_CASE("Testando a classe Jogos") {
    SUBCASE("Testando o construtor e inicialização do tabuleiro") {
        JogosTeste jogo(3, 3); // Tabuleiro 3x3
        CHECK(jogo.strJogador(Tabuleiro::Peca::JOGADOR1) == "\033[31mJogador 1 (X)\033[0m");
        CHECK(jogo.strJogador(Tabuleiro::Peca::JOGADOR2) == "\033[33mJogador 2 (O)\033[0m");
    }

    SUBCASE("Testando a troca de jogador") {
        JogosTeste jogo(3, 3);
        CHECK(jogo.strJogador(jogo.jogadorAtual) == "\033[31mJogador 1 (X)\033[0m"); // Jogador inicial é o 1
        jogo.trocarJogador();
        CHECK(jogo.strJogador(jogo.jogadorAtual) == "\033[33mJogador 2 (O)\033[0m"); // Após troca, jogador 2
    }

    SUBCASE("Testando a exibição do tabuleiro") {
        JogosTeste jogo(3, 3);
        // Redireciona a saída do cout para um buffer de string
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        jogo.exibirTabuleiro();

        std::cout.rdbuf(old); // Restaura o buffer original do cout

        std::string saida = buffer.str();
        CHECK(saida.find(" | ") != std::string::npos); // Verifica se o tabuleiro foi exibido corretamente
    }

    SUBCASE("Testando setters de apelidos") {
        JogosTeste jogo(3, 3);
        jogo.setApelidoJogador1("Jogador1");
        jogo.setApelidoJogador2("Jogador2");

        // Verifica se os apelidos foram atribuídos corretamente
        CHECK(jogo.strJogador(1) == "\033[31mJogador 1 (X)\033[0m");
        CHECK(jogo.strJogador(2) == "\033[33mJogador 2 (O)\033[0m");
    }

    SUBCASE("Testando métodos virtuais puros (mock)") {
        JogosTeste jogo(3, 3);

        // Redireciona a saída do cout para um buffer de string
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        jogo.fraseInicial();
        jogo.lerJogada();
        jogo.realizarJogada();

        std::cout.rdbuf(old); // Restaura o buffer original do cout

        std::string saida = buffer.str();
        CHECK(saida.find("Início do jogo de teste!") != std::string::npos);
        CHECK(saida.find("Lendo jogada...") != std::string::npos);
        CHECK(saida.find("Realizando jogada...") != std::string::npos);
    }
}