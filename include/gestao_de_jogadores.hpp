#ifndef GESTAO_DE_JOGADORES_H
#define GESTAO_DE_JOGADORES_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>//stringstream, ostringstream
#include <memory>//unique_ptr
#include <algorithm>//sort()
#include <iomanip>//stew()
#include "jogador.hpp"  

class GestaoDeJogadores{
    private:
        std::map<std::string, std::unique_ptr<Jogador>> jogadores_map;
        const std::string caminhoDoArquivo;

    public:
        //Construtor e destrutor
        GestaoDeJogadores(const std::string &caminhoDoArquivo);
        ~GestaoDeJogadores();

        //Metodos para manipulação de arquivo
        bool arquivoValidoParaBusca() const;
        std::string buscarLinhaDoJogador(const std::string& apelido) const;
        bool jogadorExiste(const std::string& apelido) const;
        void processarLinha(const std::string& linha);
        void carregarTodoArquivo();
        void carregarDoisJogadores(const std::string& apelido1, const std::string& apelido2);
        bool salvarNovoJogador(const std::unique_ptr<Jogador>& novoJogador);
        bool atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar);
        
        //Metodos para gerenciar jogadores
        bool cadastrarJogador(const std::string &apelido, const std::string &nome);
        bool removerJogador(const std::string &apelido);

        //Metodos auxiliares
        void ordenarJogadores(std::map<std::string, std::unique_ptr<Jogador>> jogadores_desordenados_map); //a implementar
        bool buscaPorApelido(const std::string& apelido, std::streampos* posicao = nullptr) const;
        std::string getNomeDoJogo(TipoDeJogo jogo);
};
#endif