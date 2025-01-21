#ifndef REVERSI_H
#define REVERSI_H

#include "./jogos.hpp"
#include <vector>
#include <iostream>

class Reversi : public Jogos {
private:
    int jogadaLinha;  // Linha da jogada atual
    int jogadaColuna; // Coluna da jogada atual

    // Métodos auxiliares
    bool dentroDosLimites(int linha, int coluna) const;
    bool capturarPecas(int linha, int coluna, Tabuleiro::Peca peca);
    bool direcaoValida(int linha, int coluna, int deltaLinha, int deltaColuna, Tabuleiro::Peca peca) const;

public:
    Reversi();
    ~Reversi() {}

    // Métodos para exibir o tabuleiro
    virtual void exibirPeca(Tabuleiro::Peca peca) const override;

    // Métodos responsáveis pelas jogadas
    virtual void lerJogada() override;
    virtual bool jogadaEValida() const override;
    virtual void realizarJogada() override;

    // Métodos que gerenciam o andamento da partida
    virtual bool partidaAcabou() override;
    virtual void indicarFimDaPartida() const override;

    // Conta as peças de cada jogador no tabuleiro
    std::pair<int, int> contarPecas() const;
};

#endif
