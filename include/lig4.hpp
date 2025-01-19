#ifndef LIG4_H
#define LIG4_H

#include "jogos.hpp"
#include <iostream>



class lig4 : public Jogos {
public:
    lig4() : Jogos(6, 7) {} // tabuleiro de 6 linhas e 7 colunas para o lig 4
    ~lig4() {}


    // metodos para imprimir o tabuleiro
    virtual void exibirTabuleiro() const override;
    virtual void exibirPeca(Tabuleiro::Peca peca) const override;

    // metodos responsaveis pelas jogadas em cada rodada
    virtual void lerJogada() const override;
    virtual bool jogadaEValida() const override;
    virtual void realizarJogada() override;

    // metodos que gerenciam o andamento da partida
    virtual bool partidaAcabou() const override;
    virtual void indicarFimDaPartida() const override;
private:
    mutable int colunaEscolhida; // coluna escolhida pelo jogador atual
    bool verificarVitoria(int linha, int coluna) const;
    bool dentroDosLimites(int linha, int coluna) const;

};

#endif