#include "../include/gestaoDeJogadores.hpp"
#include "../include/lig4.hpp"
#include "../include/jogoDaVelha.hpp"
#include "../include/reversi.hpp"

#include <iostream>

int main(){
    const std::string caminhodoArquivo = "dados.csv";
    GestaoDeJogadores gestao(caminhodoArquivo);

    std::string comando, apelido, nome;
    while(std::cin >> comando){
      if(comando == "CJ"){
            std::cin >> apelido >> nome;
            gestao.cadastrarJogador(apelido, nome);
        } else if(comando == "RJ"){
            std::cin >> apelido;
            gestao.removerJogador(apelido);
        } else if(comando == "LJ"){
            gestao.listarJogadores();
        } else if(comando == "E"){
            //EP <Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2>
        } else if(comando == "FS"){
            break;
        }
    }
    return 0;
}