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
        if (comando == "CJ") {
            do{
                //preciso ver como o progresso é interferido no caso de caracteres especiais e de outros , . \n \t "" ''
                std::cout << "Digite o apelido (uma unica palavra): "; //uma palavra
                std::cin >> apelido;
                std::cin.ignore(); // Limpa o buffer de entrada antes de getline.
                std::cout << "Digite o nome (pode conter mais de uma palavra): "; //pode ter mais de uma palavra
                std::getline(std::cin, nome);
                while(nome.empty()){
                    std::cout << "Nome nao pode estar vazio. Tente novamente." << std::endl;
                    std::getline(std::cin, nome);
                }
            } while (!gestao.cadastrarJogador(apelido, nome)); // Tenta cadastrar até ser bem-sucedido.
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