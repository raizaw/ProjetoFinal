#ifndef GESTAO_DE_JOGADORES_H
#define GESTAO_DE_JOGADORES_H

#include <string>
#include <map>
#include <set>//atualizarEstatisticas
#include <iostream>
#include <fstream>
#include <sstream>//stringstream
#include <memory>//unique_ptr
#include <iomanip>//stew()
#include "./jogador.hpp"  

class GestaoDeJogadores{
    private:
        const std::string caminhoDoArquivo;

        //Metodos auxiliares
        std::string buscarLinhaDoJogador(const std::string& apelido)const;
        void inserirLinhaNoMapa(const std::string& linha);
        std::string nomeDoJogo(TipoDeJogo jogo);
    public:
        //Mapa de jogadores
        std::map<std::string, std::unique_ptr<Jogador>> jogadores_map;

        //Construtor e destrutor
        GestaoDeJogadores(const std::string &caminhoDoArquivo);
        ~GestaoDeJogadores();

        //Metodos para manipulação de arquivo
        bool carregarTodoArquivo();
        bool carregarDoisJogadores(const std::string& apelido1,const std::string& apelido2);
        bool inserirNovoJogador(const std::unique_ptr<Jogador>& novoJogador);
        bool atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar);
        
        //Metodos para gerenciar jogadores
        bool cadastrarJogador(const std::string &apelido,const std::string &nome);
        bool removerJogador(const std::string &apelido);
        void listarJogadores();

        // Auxiliar visível
        // bool apelidoEstaCadastrado(const std::string& apelido) const;
};
#endif