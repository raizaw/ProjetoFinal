#ifndef JOGODAVELHA_H
#define JOGODAVELHA_H

#include "./jogos.hpp"
#include <iostream>

/**
 * @class JogoDaVelha
 * @brief Classe que implementa o jogo da velha.
 *
 * Esta classe herda da classe base `Jogos` e implementa as regras e funcionalidades específicas do jogo da velha.
 */
class JogoDaVelha : public Jogos {
private:
    int jogadaLinha;  ///< Armazena a linha da jogada atual.
    int jogadaColuna; ///< Armazena a coluna da jogada atual.
    int vencedor;     ///< Armazena o vencedor da partida: 0 para empate, 1 para Jogador 1, 2 para Jogador 2.

public:
    /**
     * @brief Construtor da classe JogoDaVelha.
     * Inicializa o tabuleiro 3x3 e define os valores iniciais das jogadas e do vencedor.
     */
    JogoDaVelha() : Jogos(3, 3), jogadaLinha(-1), jogadaColuna(-1), vencedor(0) {}

    /**
     * @brief Destrutor da classe JogoDaVelha.
     */
    ~JogoDaVelha() {};

    // Métodos para impressão

    /**
     * @brief Exibe a frase inicial do jogo da velha.
     */
    virtual void fraseInicial() override;

    /**
     * @brief Exibe o tabuleiro do jogo da velha.
     */
    virtual void exibirTabuleiro() const override;

    /**
     * @brief Exibe a peça no tabuleiro.
     * @param peca A peça a ser exibida.
     */
    virtual void exibirPeca(Tabuleiro::Peca peca) const override;

    /**
     * @brief Retorna a cor associada a um jogador.
     * @param jogador O número do jogador (1 ou 2).
     * @return A cor correspondente ao jogador.
     */
    std::string cor(int jogador);

    // Métodos responsáveis pelas jogadas em cada rodada

    /**
     * @brief Lê a jogada do jogador atual.
     */
    virtual void lerJogada() override;

    /**
     * @brief Verifica se a jogada é válida.
     * @return Verdadeiro se a jogada for válida, falso caso contrário.
     */
    virtual bool jogadaEValida() const override;

    /**
     * @brief Realiza a jogada no tabuleiro.
     */
    virtual void realizarJogada() override;

    // Métodos que gerenciam o andamento da partida

    /**
     * @brief Verifica se a partida acabou.
     * @return Verdadeiro se a partida acabou, falso caso contrário.
     */
    virtual bool partidaAcabou() override;

    /**
     * @brief Indica o fim da partida e retorna o vencedor.
     * @return O número do jogador vencedor (1 ou 2) ou 0 para empate.
     */
    virtual int indicarFimDaPartida() override;
};

#endif