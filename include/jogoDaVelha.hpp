#ifndef JOGODAVELHA_H
#define JOGODAVELHA_H

#include "./jogos.hpp"
#include <iostream>

class JogoDaVelha : public Jogos {
public:
    JogoDaVelha() : Jogos(3, 3) {} // Inicializa o tabuleiro com as dimensões apropriadas
    ~JogoDaVelha() {};

    // Métodos para imprimir o tabuleiro
    virtual void exibirTabuleiro() const override; //// sobrescrever para ficar bonito!!!
    virtual void exibirPeca(Tabuleiro::Peca peca) const override; 
    
    // Métodos responsáveis pelas jogadas em cada rodada
    virtual void lerJogada() const override; 
	virtual bool jogadaEValida() const override; 
	virtual void realizarJogada() override; 

    // Métodos que gerenciam o andamento da partida
	virtual bool partidaAcabou() const override; 
	virtual void indicarFimDaPartida() const override;

};

#endif