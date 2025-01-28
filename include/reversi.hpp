#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "jogos.hpp"
#include "tabuleiro.hpp"
#include <iostream>
#include <utility>

/**
 * @class Reversi
 * @brief Classe que implementa o jogo Reversi.
 * 
 * Esta classe herda da classe Jogos e implementa as regras e funcionalidades específicas do jogo Reversi.
 */
class Reversi : public Jogos {
public:
    /**
     * @brief Construtor padrão da classe Reversi.
     */
    Reversi();

    /**
     * @brief Exibe o tabuleiro do jogo.
     */
    void exibirTabuleiro() const override;

    /**
     * @brief Exibe a frase inicial do jogo.
     */
    void fraseInicial() override;

    /**
     * @brief Exibe uma peça do tabuleiro.
     * @param peca A peça a ser exibida.
     */
    void exibirPeca(Tabuleiro::Peca peca) const override;

    /**
     * @brief Lê a jogada do jogador.
     */
    void lerJogada() override;

    /**
     * @brief Verifica se a jogada é válida.
     * @return true se a jogada for válida, false caso contrário.
     */
    bool jogadaEValida() const override;

    /**
     * @brief Realiza a jogada no tabuleiro.
     */
    void realizarJogada() override;

    /**
     * @brief Verifica se a partida acabou.
     * @return true se a partida acabou, false caso contrário.
     */
    bool partidaAcabou() override;

    /**
     * @brief Indica o fim da partida e retorna o resultado.
     * @return O código que indica o resultado da partida.
     */
    int indicarFimDaPartida() override;

    /**
     * @brief Indica as possíveis jogadas para o jogador atual.
     */
    void indicarPossiveisJogadas();

private:
    int jogadaLinha; ///< Linha da jogada atual.
    int jogadaColuna; ///< Coluna da jogada atual.

    /**
     * @brief Conta o número de peças de cada jogador no tabuleiro.
     * @return Um par de inteiros onde o primeiro é o número de peças do jogador 1 e o segundo do jogador 2.
     */
    std::pair<int, int> contarPecas() const;

    /**
     * @brief Verifica se uma posição está dentro dos limites do tabuleiro.
     * @param linha A linha a ser verificada.
     * @param coluna A coluna a ser verificada.
     * @return true se a posição estiver dentro dos limites, false caso contrário.
     */
    bool dentroDosLimites(int linha, int coluna) const;

    /**
     * @brief Verifica se uma direção é válida para capturar peças.
     * @param linha A linha da posição inicial.
     * @param coluna A coluna da posição inicial.
     * @param deltaLinha O incremento na direção das linhas.
     * @param deltaColuna O incremento na direção das colunas.
     * @param peca A peça do jogador atual.
     * @return true se a direção for válida para captura, false caso contrário.
     */
    bool direcaoValida(int linha, int coluna, int deltaLinha, int deltaColuna, Tabuleiro::Peca peca) const;

    /**
     * @brief Captura as peças do oponente na direção especificada.
     * @param linha A linha da posição inicial.
     * @param coluna A coluna da posição inicial.
     * @param peca A peça do jogador atual.
     * @return true se alguma peça foi capturada, false caso contrário.
     */
    bool capturarPecas(int linha, int coluna, Tabuleiro::Peca peca);

    /**
     * @brief Verifica se há jogadas possíveis para o jogador atual.
     * @return true se houver jogadas possíveis, false caso contrário.
     */
    bool haJogadasPossiveis();

    /**
     * @brief Retorna a cor do jogador.
     * @param jogador O número do jogador (1 ou 2).
     * @return A cor do jogador como uma string.
     */
    std::string cor(int jogador);
};

#endif