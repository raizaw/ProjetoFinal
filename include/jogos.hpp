#ifndef JOGOS_H
#define JOGOS_H 

#include "./tabuleiro.hpp"
#include <iostream>
#include <vector>
#include <string>

// Classe abstrata
class Jogos {
protected:
    Tabuleiro* tabuleiro;
    Tabuleiro::Peca jogadorAtual;

public:
    // Construtor que inicializa o tabuleiro
    Jogos(int linhas, int colunas);

    // Métodos para imprimir o tabuleiro
    virtual void exibirTabuleiro() const;
    virtual void exibirPeca(Tabuleiro::Peca peca) const = 0; // Exibição das peças depende do jogo em questão
    
    // Métodos responsáveis pelas jogadas em cada rodada
    virtual void lerJogada() = 0; // Lê jogada a depender do jogo em questão
	virtual bool jogadaEValida() const = 0; // Verifica se jogada é válida a depender das regras do jogo em questão
	virtual void realizarJogada() = 0; // Realiza a jogada a depender do jogo em questão

    // Métodos que gerenciam o andamento da partida
    virtual void trocarJogador();
	virtual bool partidaAcabou() = 0; // Verifica se a partida pode ou não continuar
	virtual void indicarFimDaPartida() const = 0;

    std::string strJogador(int jogador) const;
    std::string strJogador(Tabuleiro::Peca peca) const;

    virtual ~Jogos() {
        delete tabuleiro; // Libera a memória do tabuleiro
    }
};

#endif