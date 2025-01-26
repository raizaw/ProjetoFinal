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
            std::cout << "Jogada invalida. Tente novamente.\n";
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

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada

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
                // std::cout << "Escolha o jogo:\n";
                // std::cout << "R - Reversi\n";
                // std::cout << "V - Jogo da Velha\n";
                // std::cout << "L - Lig4\n";

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

                    // Cria o jogo escolhido
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

                    // Solicita e valida os apelidos dos jogadores
                    std::string apelidoJogador1, apelidoJogador2;
                    bool apelidosValidos = false;

                    while (!apelidosValidos) {
                        std::cin >> apelidoJogador1 >> apelidoJogador2;

                        // Verifica se os apelidos estão cadastrados
                        bool jogador1Valido = gestao.apelidoEstaCadastrado(apelidoJogador1);
                        bool jogador2Valido = gestao.apelidoEstaCadastrado(apelidoJogador2);

                        if (!jogador1Valido && !jogador2Valido) {
                            std::cout << "Os apelidos '" << apelidoJogador1 << "' e '" << apelidoJogador2 << "' não estão cadastrados.\n";
                        } else if (!jogador1Valido) {
                            std::cout << "O apelido '" << apelidoJogador1 << "' não está cadastrado.\n";
                        } else if (!jogador2Valido) {
                            std::cout << "O apelido '" << apelidoJogador2 << "' não está cadastrado.\n";
                        } else {
                            apelidosValidos = true; // Ambos os apelidos são válidos
                        }

                        if (!apelidosValidos) {
                            std::cout << "Por favor, insira apelidos válidos.\n";
                        }
                    }

                    // Define os apelidos no jogo (se necessário)
                    jogo->setApelidoJogador1(apelidoJogador1);
                    jogo->setApelidoJogador2(apelidoJogador2);

                    // Executa a partida
                    executarPartida(std::move(jogo));
                    break; // Sai do loop após uma escolha válida
                } else {
                    std::cout << "Escolha inválida. Tente novamente.\n";
                }
            }

        } else if(comando == "FS"){
                    break;
                    
        } else {
            std::cout << "Comando Invalido. Tente Novamente";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}