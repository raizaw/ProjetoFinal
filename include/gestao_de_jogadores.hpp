#ifndef GESTAO_DE_JOGADORES_H
#define GESTAO_DE_JOGADORES_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>//stringstream, ostringstream
#include <algorithm>//sort()
#include <iomanip>//stew()
#include "jogador.hpp"  

class GestaoDeJogadores{
    private:
    std::vector<Jogador*> jogadores_vec;
    const std::string caminhoDoArquivo;


    public:
        //Construtor e destrutor
        GestaoDeJogadores(const std::string &caminho);
        ~GestaoDeJogadores();

        //Metodos para manipulacao de arquivo
        void carregarDoArquivo(const std::string& apelido1 = "", const std::string& apelido2 = "");
        bool salvarNovoJogador(const Jogador* novoJogador);
        void salvarNovasEstatisticas(const std::vector<Jogador*>& jogadoresParaAtualizar);
        
        //Metodos para gerenciar jogadores
        bool cadastrarJogador(const std::string &_apelido, const std::string &_nome);
        bool removerJogador(const std::string &_apelido);
        void listarJogadores();

        //Metodos auxiliares
        std::string getNomeDoJogo(TipoDeJogo jogo);
        bool buscaPorApelido(const std::string& apelido, std::streampos* posicao = nullptr) const;
};

#endif