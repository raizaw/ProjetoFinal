#ifndef LIG4_H
#define LIG4_H

#include "./jogos.hpp"
#include <iostream>

/**
 * @class lig4
 * @brief Classe que implementa o jogo Lig 4.
 *
 * Esta classe herda da classe base `Jogos` e implementa as regras e funcionalidades específicas do jogo Lig 4.
 */
class lig4 : public Jogos {
private:
    int vencedor; ///< Armazena o vencedor da partida: 0 para empate, 1 para Jogador 1, 2 para Jogador 2.

public:
    /**
     * @brief Construtor da classe lig4.
     * Inicializa o tabuleiro com 6 linhas e 7 colunas, e define o vencedor inicial como 0 (empate).
     */
    lig4() : Jogos(6, 7), vencedor(0) {}

    /**
     * @brief Destrutor da classe lig4.
     */
    ~lig4() {}

    // Métodos para impressão

    /**
     * @brief Exibe a frase inicial do jogo Lig 4.
     */
    virtual void fraseInicial() override;

    /**
     * @brief Exibe o tabuleiro do jogo Lig 4.
     */
    virtual void exibirTabuleiro() const override;

    /**
     * @brief Exibe a peça no tabuleiro.
     * @param peca A peça a ser exibida.
     */
    virtual void exibirPeca(Tabuleiro::Peca peca) const override;

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

private:
    mutable int colunaEscolhida; ///< Armazena a coluna escolhida pelo jogador atual.

    /**
     * @brief Verifica se há uma vitória a partir de uma posição específica.
     * @param linha A linha da última jogada.
     * @param coluna A coluna da última jogada.
     * @return Verdadeiro se houver uma vitória, falso caso contrário.
     */
    bool verificarVitoria(int linha, int coluna) const;

    /**
     * @brief Verifica se uma posição está dentro dos limites do tabuleiro.
     * @param linha A linha a ser verificada.
     * @param coluna A coluna a ser verificada.
     * @return Verdadeiro se a posição estiver dentro dos limites, falso caso contrário.
     */
    bool dentroDosLimites(int linha, int coluna) const;

    /**
     * @brief Retorna a cor associada a um jogador.
     * @param jogador O número do jogador (1 ou 2).
     * @return A cor correspondente ao jogador.
     */
    std::string cor(int jogador);
};

#endif