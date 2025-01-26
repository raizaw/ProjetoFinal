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
    std::string apelidoJogador1, apelidoJogador2;

public:
    // Construtor que inicializa o tabuleiro
    Jogos(int linhas, int colunas);

    // Métodos de impressão
    virtual void fraseInicial() = 0;
    virtual void exibirTabuleiro() const;
    virtual void exibirPeca(Tabuleiro::Peca peca) const = 0; // Exibição das peças depende do jogo em questão
    
    // Métodos responsáveis pelas jogadas em cada rodada
    virtual void lerJogada() = 0; // Lê jogada a depender do jogo em questão
	virtual bool jogadaEValida() const = 0; // Verifica se jogada é válida a depender das regras do jogo em questão
	virtual void realizarJogada() = 0; // Realiza a jogada a depender do jogo em questão

    // Métodos que gerenciam o andamento da partida
    virtual void trocarJogador();
	virtual bool partidaAcabou() = 0; // Verifica se a partida pode ou não continuar
	virtual void indicarFimDaPartida() = 0;


    // Métodos auxiliares
    std::string strJogador(int jogador) const;
    std::string strJogador(Tabuleiro::Peca peca) const;

    // Setters
    virtual void setApelidoJogador1(std::string apelido);
    virtual void setApelidoJogador2(std::string apelido);

    virtual ~Jogos() {
        delete tabuleiro; // Libera a memória do tabuleiro
    }
};

#endif