#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <vector>
#include <iostream>

class Tabuleiro {
public:
// Enum encapsulado para representar as peças no tabuleiro
    enum class Peca {
       VAZIO = 0,
       JOGADOR1 = 1,
       JOGADOR2 = 2
    };

private:
    int linhas; 
    int colunas; 
    std::vector<std::vector<Peca>> tabuleiro; // Matriz para representar o tabuleiro

public:
    // Construtor que inicializa o tabuleiro com as dimensões
    Tabuleiro(int linhas, int colunas);

    // // Método para exibir o tabuleiro
    // void imprimirTabuleiro() const;

    // Métodos para manipulação do tabuleiro
    void setPosicao(int linha, int coluna, Peca peca); // Define um valor em uma posição específica
    Peca getPosicao(int linha, int coluna) const;      // Retorna o valor em uma posição específica

    // Getters
    const std::vector<std::vector<Peca>>& getTabuleiro() const;
    int getLinhas() const;
    int getColunas() const;
};

#endif
