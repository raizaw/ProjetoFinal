#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <vector>
#include <iostream>

class Tabuleiro {
private:
    int linhas;   // Número de linhas do tabuleiro
    int colunas;  // Número de colunas do tabuleiro
    std::vector<std::vector<char>> tab; // Matriz para representar o tabuleiro

public:
    // Construtor que inicializa o tabuleiro com as dimensões
    Tabuleiro(int linhas, int colunas);

    // Método para exibir o tabuleiro
    void imprimirTabuleiro() const;

    // Métodos para manipulação do tabuleiro
    void setPosicao(int linha, int coluna, char valor); // Define um valor em uma posição específica
    char getPosicao(int linha, int coluna) const;       // Retorna o valor em uma posição específica
};

#endif // TABULEIRO_H
