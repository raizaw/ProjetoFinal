#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include <map>
#include <sstream>

/**
 * @enum TipoDeJogo
 * @brief Enumeração que define os tipos de jogos disponíveis.
 */
enum TipoDeJogo {
    REVERSI = 0, ///< Jogo Reversi.
    LIG4,       ///< Jogo Lig 4.
    VELHA,      ///< Jogo da Velha.
    TOTAL_DE_JOGOS ///< Valor que representa o total de jogos (útil para iteração).
};

/**
 * @class Jogador
 * @brief Classe que representa um jogador e suas estatísticas.
 *
 * Esta classe armazena informações sobre um jogador, como apelido, nome e estatísticas de vitórias e derrotas em diferentes jogos.
 */
class Jogador {
    private:
        std::string apelido; ///< Apelido único do jogador.
        std::string nome;    ///< Nome completo do jogador.
        std::map<TipoDeJogo, std::pair<int, int>> estatisticas_map; ///< Mapa que armazena estatísticas de vitórias e derrotas por jogo.

    public:
        /**
         * @brief Construtor da classe Jogador.
         * @param apelido O apelido do jogador.
         * @param nome O nome completo do jogador.
         */
        Jogador(const std::string& apelido, const std::string& nome);

        /**
         * @brief Destrutor da classe Jogador.
         */
        ~Jogador();

        /**
         * @brief Retorna o nome do jogador.
         * @return O nome do jogador.
         */
        std::string getNome() const;

        /**
         * @brief Retorna o apelido do jogador.
         * @return O apelido do jogador.
         */
        std::string getApelido() const;

        /**
         * @brief Adiciona vitórias ao jogador em um jogo específico.
         * @param jogo O tipo de jogo.
         * @param quantidade A quantidade de vitórias a adicionar (padrão é 1).
         */
        void adicionarVitoria(TipoDeJogo jogo, int quantidade = 1);

        /**
         * @brief Adiciona derrotas ao jogador em um jogo específico.
         * @param jogo O tipo de jogo.
         * @param quantidade A quantidade de derrotas a adicionar (padrão é 1).
         */
        void adicionarDerrota(TipoDeJogo jogo, int quantidade = 1);

        /**
         * @brief Retorna as estatísticas de vitórias e derrotas do jogador em um jogo específico.
         * @param jogo O tipo de jogo.
         * @return Um par de inteiros representando vitórias e derrotas, respectivamente.
         */
        std::pair<int, int> getEstatisticasDoJogo(TipoDeJogo jogo) const;

        /**
         * @brief Formata os dados do jogador no formato CSV.
         * @return Uma string no formato CSV contendo apelido, nome e estatísticas.
         */
        std::string formatarJogadorComoCSV() const;
};

#endif