#ifndef JOGADOR_H
#define JOGADOR_H
#include <string>
#include <map>
#include <sstream>

//Definindo os jogos com um enum
enum TipoDeJogo{REVERSI = 0, LIG4, VELHA, TOTAL_DE_JOGOS /*sera sempre o valor do (ultimo jogo + 1)*/};

class Jogador{
    private:
        std::string apelido;
        std::string nome;
        std::map<TipoDeJogo,std::pair<int, int>> estatisticas_map; //mapa (jogo,vitorias,derrotas)

    public:
        //Construtor e destrutor
        Jogador(const std::string& apelido, const std::string& nome);
        ~Jogador();

        //Metodos de acesso
        std::string getNome() const;
        std::string getApelido() const;

        //Metodos de estatistica
        void adicionarVitoria(TipoDeJogo jogo, int quantidade=1);
        void adicionarDerrota(TipoDeJogo jogo, int quantidade=1);
        std::pair<int, int> getEstatisticasDoJogo(TipoDeJogo jogo) const;
        //Metodo auxiliares
        std::string formatarJogadorComoCSV() const;
};
#endif