#include "../include/gestaoDeJogadores.hpp"
#include "../include/lig4.hpp"
#include "../include/jogoDaVelha.hpp"
#include "../include/reversi.hpp"

#include <iostream>
#include <memory>
#include <cctype> // Para usar toupper
#include <limits> // Para std::numeric_limits e std::streamsize

void executarPartida(std::unique_ptr<Jogos> jogo) {
    jogo->exibirTabuleiro();

    while (!jogo->partidaAcabou()) {
        jogo->lerJogada();

        if (jogo->jogadaEValida()) {
            jogo->realizarJogada();
        } else {
            std::cout << "Jogada inválida. Tente novamente.\n";
        }
    }

    jogo->indicarFimDaPartida();
}

int main(){

    const std::string caminhodoArquivo = "dados.csv";
    GestaoDeJogadores gestao(caminhodoArquivo);

    std::string comando, apelido, nome;
    char escolhaJogo;

    while(std::cin >> comando){
        if (comando == "CJ") {
            do {
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
            
        } else if (comando == "EP") { //EP <Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2>
            while (true) { // Loop até que uma escolha válida seja feita
                std::cout << "Escolha o jogo:\n";
                std::cout << "R - Reversi\n";
                std::cout << "V - Jogo da Velha\n";
                std::cout << "L - Lig4\n";
                std::cin >> escolhaJogo;

                // Verifica se a entrada é exatamente um caractere
                if (std::cin.peek() != '\n') {
                    std::cout << "Entrada invalida. Digite apenas um caractere.\n";
                    std::cin.clear(); // Limpa o estado de erro do cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada
                    continue; // Volta ao início do loop
                }

                escolhaJogo = toupper(escolhaJogo); // Converte para maiúscula

                if (escolhaJogo == 'R' || escolhaJogo == 'V' || escolhaJogo == 'L') {
                    std::unique_ptr<Jogos> jogo;

                    switch (escolhaJogo) {
                        case 'R':
                            jogo = std::make_unique<Reversi>();
                            break;
                        case 'V':
                            jogo = std::make_unique<JogoDaVelha>();
                            break;
                        case 'L':
                            jogo = std::make_unique<lig4>();
                            break;
                    }

                        executarPartida(std::move(jogo));
                        break; // Sai do loop após uma escolha válida
                } else {
                    std::cout << "Escolha invalida. Tente novamente.\n";
                }
            }
        } else if(comando == "FS"){
                    break;
        } 
    }
    return 0;
}