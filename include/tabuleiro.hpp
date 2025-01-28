#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <vector>
#include <iostream>

/**
 * @class Tabuleiro
 * @brief Classe que representa o tabuleiro do jogo.
 * 
 * Esta classe gerencia o estado do tabuleiro, incluindo a colocação e recuperação de peças.
 */
class Tabuleiro {
public:
    /**
     * @enum Peca
     * @brief Enumeração que representa os tipos de peças no tabuleiro.
     */
    enum class Peca {
       VAZIO = 0,       ///< Representa uma posição vazia no tabuleiro.
       JOGADOR1 = 1,    ///< Representa uma peça do Jogador 1.
       JOGADOR2 = 2,    ///< Representa uma peça do Jogador 2.
       JOGADA_POSSIVEL  ///< Representa uma jogada possível no tabuleiro.
    };

private:
    int linhas; ///< Número de linhas do tabuleiro.
    int colunas; ///< Número de colunas do tabuleiro.
    std::vector<std::vector<Peca>> tabuleiro; ///< Matriz que armazena o estado do tabuleiro.

public:
    /**
     * @brief Construtor que inicializa o tabuleiro com as dimensões especificadas.
     * @param linhas Número de linhas do tabuleiro.
     * @param colunas Número de colunas do tabuleiro.
     */
    Tabuleiro(int linhas, int colunas);

    /**
     * @brief Define o valor de uma posição específica no tabuleiro.
     * @param linha A linha da posição a ser definida.
     * @param coluna A coluna da posição a ser definida.
     * @param peca O valor da peça a ser colocada na posição.
     */
    void setPosicao(int linha, int coluna, Peca peca);

    /**
     * @brief Retorna o valor de uma posição específica no tabuleiro.
     * @param linha A linha da posição a ser consultada.
     * @param coluna A coluna da posição a ser consultada.
     * @return O valor da peça na posição especificada.
     */
    Peca getPosicao(int linha, int coluna) const;

    /**
     * @brief Retorna a matriz que representa o tabuleiro.
     * @return Uma referência constante para a matriz do tabuleiro.
     */
    const std::vector<std::vector<Peca>>& getTabuleiro() const;

    /**
     * @brief Retorna o número de linhas do tabuleiro.
     * @return O número de linhas do tabuleiro.
     */
    int getLinhas() const;

    /**
     * @brief Retorna o número de colunas do tabuleiro.
     * @return O número de colunas do tabuleiro.
     */
    int getColunas() const;
};

#endif