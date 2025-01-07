#include "jogador.hpp"

Jogador::Jogador(const std::string &nome, const std::string &apelido)
    :nome(nome), apelido(apelido) {
    //Inicializa o mapa de estatisticas com 0 vitórias e 0 derrotas para todos os jogos
    for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
        estatisticas_map[static_cast<TipoDeJogo>(i)] = {0, 0};
    }}

std::string Jogador::getNome() const{
    return this->nome;
}
std::string Jogador::getApelido() const{
    return this->apelido;
}

void Jogador::adicionarVitoria(TipoDeJogo jogo, int quantidade){
    if(jogo >= REVERSI && jogo < TOTAL_DE_JOGOS){
        estatisticas_map[jogo].first += quantidade; //Incrementa vitoria
    }
}
void Jogador::adicionarDerrota(TipoDeJogo jogo, int quantidade){
    if(jogo >= REVERSI && jogo < TOTAL_DE_JOGOS){
        estatisticas_map[jogo].second += quantidade; //Incrementa a derrota
    }
}

std::pair<int, int> Jogador::getEstatisticasDoJogo(TipoDeJogo jogo) const{
    if(jogo >= REVERSI && jogo < TOTAL_DE_JOGOS){
        return estatisticas_map.at(jogo);  
    //retorna estatisticas de vitoria e derrota de um jogo especifico
    } throw std::invalid_argument("Numero do jogo invalido ao tentar obter estatisticas do jogo");
}

std::string Jogador::formatarJogadorComoCSV() const{
    std::ostringstream buffer;
    buffer << apelido << "," << nome;
    for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
        auto estatisticas = getEstatisticasDoJogo(static_cast<TipoDeJogo>(i));
        buffer << "," << estatisticas.first << "," << estatisticas.second;
    }
    buffer << "\n";
    return buffer.str();
}