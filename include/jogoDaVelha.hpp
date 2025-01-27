#ifndef JOGODAVELHA_H
#define JOGODAVELHA_H

#include "./jogos.hpp"
#include <iostream>

class JogoDaVelha : public Jogos {
private:
    int jogadaLinha;  // Armazena a linha da jogada atual
    int jogadaColuna; // Armazena a coluna da jogada atual
    int vencedor;     // 0 para empate, 1 para Jogador 1, 2 para Jogador 2

public:
    JogoDaVelha() : Jogos(3, 3), jogadaLinha(-1), jogadaColuna(-1), vencedor(0) {}
    ~JogoDaVelha() {};

    // Métodos para impressão
    virtual void fraseInicial() override;
    virtual void exibirTabuleiro() const override;
    virtual void exibirPeca(Tabuleiro::Peca peca) const override;
    std::string cor (int jogador);
    
    // Métodos responsáveis pelas jogadas em cada rodada
    virtual void lerJogada() override; 
	virtual bool jogadaEValida() const override; 
	virtual void realizarJogada() override; 

    // Métodos que gerenciam o andamento da partida
	virtual bool partidaAcabou() override; 
	virtual int indicarFimDaPartida() override;

};

#endif