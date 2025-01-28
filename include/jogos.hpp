#ifndef JOGOS_H
#define JOGOS_H

#include "./tabuleiro.hpp"
#include <iostream>
#include <vector>
#include <string>

/**
 * @class Jogos
 * @brief Classe abstrata que define a interface para jogos de tabuleiro.
 *
 * Esta classe serve como base para implementação de diferentes jogos de tabuleiro.
 * Ela define métodos virtuais puros que devem ser implementados pelas classes derivadas.
 */
class Jogos {
protected:
    Tabuleiro* tabuleiro; ///< Ponteiro para o tabuleiro do jogo.
    Tabuleiro::Peca jogadorAtual; ///< Representa o jogador atual (peca do jogador 1 ou 2).
    std::string apelidoJogador1; ///< Apelido do jogador 1.
    std::string apelidoJogador2; ///< Apelido do jogador 2.

public:
    /**
     * @brief Construtor da classe Jogos.
     * @param linhas Número de linhas do tabuleiro.
     * @param colunas Número de colunas do tabuleiro.
     */
    Jogos(int linhas, int colunas);

    // Métodos de impressão

    /**
     * @brief Exibe a frase inicial do jogo.
     * @note Método puro virtual, deve ser implementado pelas classes derivadas.
     */
    virtual void fraseInicial() = 0;

    /**
     * @brief Exibe o tabuleiro do jogo.
     */
    virtual void exibirTabuleiro() const;

    /**
     * @brief Exibe a peça no tabuleiro.
     * @param peca A peça a ser exibida.
     * @note Método puro virtual, deve ser implementado pelas classes derivadas.
     */
    virtual void exibirPeca(Tabuleiro::Peca peca) const = 0;

    // Métodos responsáveis pelas jogadas em cada rodada

    /**
     * @brief Lê a jogada do jogador atual.
     * @note Método puro virtual, deve ser implementado pelas classes derivadas.
     */
    virtual void lerJogada() = 0;

    /**
     * @brief Verifica se a jogada é válida.
     * @return Verdadeiro se a jogada for válida, falso caso contrário.
     * @note Método puro virtual, deve ser implementado pelas classes derivadas.
     */
    virtual bool jogadaEValida() const = 0;

    /**
     * @brief Realiza a jogada no tabuleiro.
     * @note Método puro virtual, deve ser implementado pelas classes derivadas.
     */
    virtual void realizarJogada() = 0;

    // Métodos que gerenciam o andamento da partida

    /**
     * @brief Alterna o jogador atual.
     */
    virtual void trocarJogador();

    /**
     * @brief Verifica se a partida acabou.
     * @return Verdadeiro se a partida acabou, falso caso contrário.
     * @note Método puro virtual, deve ser implementado pelas classes derivadas.
     */
    virtual bool partidaAcabou() = 0;

    /**
     * @brief Indica o fim da partida e retorna o vencedor.
     * @return O número do jogador vencedor (1 ou 2) ou 0 para empate.
     * @note Método puro virtual, deve ser implementado pelas classes derivadas.
     */
    virtual int indicarFimDaPartida() = 0;

    // Métodos auxiliares

    /**
     * @brief Retorna uma string representando o jogador.
     * @param jogador O número do jogador (1 ou 2).
     * @return Uma string representando o jogador.
     */
    std::string strJogador(int jogador) const;

    /**
     * @brief Retorna uma string representando a peça do jogador.
     * @param peca A peça do jogador.
     * @return Uma string representando a peça do jogador.
     */
    std::string strJogador(Tabuleiro::Peca peca) const;

    // Setters

    /**
     * @brief Define o apelido do jogador 1.
     * @param apelido O apelido do jogador 1.
     */
    virtual void setApelidoJogador1(std::string apelido);

    /**
     * @brief Define o apelido do jogador 2.
     * @param apelido O apelido do jogador 2.
     */
    virtual void setApelidoJogador2(std::string apelido);

    /**
     * @brief Destrutor da classe Jogos.
     * Libera a memória alocada para o tabuleiro.
     */
    virtual ~Jogos() {
        delete tabuleiro;
    }
};

#endif