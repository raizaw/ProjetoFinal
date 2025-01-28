#ifndef GESTAO_DE_JOGADORES_H
#define GESTAO_DE_JOGADORES_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream> // Necessário para std::stringstream
#include <memory> // Necessário para unique_ptr
#include <iomanip> // Necessário para std::setw
#include "./jogador.hpp"  

/**
 * @class GestaoDeJogadores
 * @brief Classe responsável pela gestão de jogadores.
 *
 * Esta classe gerencia a lista de jogadores, incluindo operações como carregar, cadastrar, remover e listar jogadores.
 */
class GestaoDeJogadores {
    private:
        const std::string caminhoDoArquivo; ///< Caminho do arquivo onde os dados dos jogadores são armazenados.

        /**
         * @brief Busca a linha correspondente a um jogador no arquivo.
         * @param apelido O apelido do jogador a ser buscado.
         * @return A linha do arquivo correspondente ao jogador.
         */
        std::string buscarLinhaDoJogador(const std::string& apelido) const;

        /**
         * @brief Insere uma linha de dados de jogador no mapa de jogadores.
         * @param linha A linha de dados do jogador a ser inserida.
         */
        void inserirLinhaNoMapa(const std::string& linha);

        /**
         * @brief Retorna o nome do jogo com base no tipo de jogo.
         * @param jogo O tipo de jogo.
         * @return O nome do jogo.
         */
        std::string nomeDoJogo(TipoDeJogo jogo);

    public:
        std::map<std::string, std::unique_ptr<Jogador>> jogadores_map; ///< Mapa que armazena os jogadores, onde a chave é o apelido do jogador.

        /**
         * @brief Construtor da classe GestaoDeJogadores.
         * @param caminhoDoArquivo O caminho do arquivo onde os dados dos jogadores são armazenados.
         */
        GestaoDeJogadores(const std::string &caminhoDoArquivo);

        /**
         * @brief Destrutor da classe GestaoDeJogadores.
         */
        ~GestaoDeJogadores();

        /**
         * @brief Carrega todos os jogadores do arquivo para o mapa.
         * @return Verdadeiro se o carregamento foi bem-sucedido, falso caso contrário.
         */
        bool carregarTodoArquivo();

        /**
         * @brief Carrega dois jogadores específicos do arquivo para o mapa.
         * @param apelido1 O apelido do primeiro jogador.
         * @param apelido2 O apelido do segundo jogador.
         * @return Verdadeiro se o carregamento foi bem-sucedido, falso caso contrário.
         */
        bool carregarDoisJogadores(const std::string& apelido1, const std::string& apelido2);

        /**
         * @brief Insere um novo jogador no arquivo e no mapa.
         * @param novoJogador O novo jogador a ser inserido.
         * @return Verdadeiro se a inserção foi bem-sucedida, falso caso contrário.
         */
        bool inserirNovoJogador(const std::unique_ptr<Jogador>& novoJogador);

        /**
         * @brief Atualiza as estatísticas dos jogadores no arquivo.
         * @param jogadoresParaAtualizar O mapa de jogadores com as estatísticas atualizadas.
         * @return Verdadeiro se a atualização foi bem-sucedida, falso caso contrário.
         */
        bool atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar);

        /**
         * @brief Cadastra um novo jogador no sistema.
         * @param apelido O apelido do jogador.
         * @param nome O nome do jogador.
         * @return Verdadeiro se o cadastro foi bem-sucedido, falso caso contrário.
         */
        bool cadastrarJogador(const std::string &apelido, const std::string &nome);

        /**
         * @brief Remove um jogador do sistema.
         * @param apelido O apelido do jogador a ser removido.
         * @return Verdadeiro se a remoção foi bem-sucedida, falso caso contrário.
         */
        bool removerJogador(const std::string &apelido);

        /**
         * @brief Lista todos os jogadores cadastrados no sistema.
         */
        void listarJogadores();
};

#endif