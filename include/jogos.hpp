#ifndef JOGOS_H
#define JOGOS_H 

#include "tabuleiro.hpp"
#include <iostream>
#include <vector>

// Classe abstrata
class Jogos {
protected:
    Tabuleiro* tabuleiro;

public:
    // Construtor que iniciliza o tabuleiro
    Jogos(int linhas, int colunas);

    // Métodos para imprimir o tabuleiro
    virtual void exibirTabuleiro() const;
    virtual void exibirPeca(Tabuleiro::Peca peca) const = 0;
    
    virtual void lerJogada() const = 0;
	virtual bool jogadaEValida();
	virtual void realizarJogada();
	virtual bool partidaAcabou();
	virtual void indicarFimDaPartida();
	virtual void trocarJogador();


    virtual ~Jogos() {
        delete tabuleiro; // Libera a memória do tabuleiro
    }
};

#endif