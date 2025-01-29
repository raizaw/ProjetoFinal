#include "../include/gestaoDeJogadores.hpp"
#include "../include/lig4.hpp"
#include "../include/jogoDaVelha.hpp"
#include "../include/reversi.hpp"

#include <iostream>
#include <memory>
#include <cctype> // Para usar toupper
#include <limits> // Para std::numeric_limits e std::streamsize

/**
 * @brief Exibe o menu de opcoes para o usuario.
 */
void exibirMenu(){
    std::cout << "-------------------------------" << std::endl;
    std::cout << "[CJ] - Cadastrar Jogador\n" 
              << "[RJ] - Remover Jogador\n" 
              << "[LJ] - Listar Jogadores\n" 
              << "[EP] - Executar Partida\n" 
              << "[M]  - Menu\n" 
              << "[FS] - Finalizar Sistema" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

/**
 * @brief Executa uma partida do jogo escolhido.
 * @param jogo Um ponteiro unico para o jogo que sera executado.
 * @return O codigo do vencedor da partida (1 para jogador 1, 2 para jogador 2, 0 para empate).
 */
int executarPartida(std::unique_ptr<Jogos> jogo) {
    jogo->fraseInicial();
    jogo->exibirTabuleiro();

    while (!jogo->partidaAcabou()) {
        jogo->lerJogada();

        if (jogo->jogadaEValida()) {
            jogo->realizarJogada();
        }
    }
    
    return jogo->indicarFimDaPartida();
}

/**
 * @brief Verifica se uma string e valida para ser usada em um arquivo CSV.
 * @param str A string a ser verificada.
 * @return true se a string nao contem virgulas, false caso contrario.
 */
bool ehValidoParaCSV(const std::string& str){
    // Verifica cada caractere da string
    for (char c : str) {
        // Se encontrar caractere invalido, retorna false
        if (c == ',') {
            return false;
        }
    }
    return true;
}

/**
 * @brief Funcao principal do programa.
 * @return 0 se o programa for executado com sucesso.
 */
int main(){

    const std::string caminhodoArquivo = "./gameData/dados.csv";
    GestaoDeJogadores gestao(caminhodoArquivo);

    std::string comando, apelido, nome;
    char escolhaJogo;

    std::cout << "\n BEM VINDO! INSIRA UM COMANDO:" << std::endl;
    exibirMenu();

    while(std::cin >> comando){

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada

        if (comando == "CJ") {
            do{
                // Solicita o apelido ate que ele seja valido
                do {
                    std::cout << "Digite o apelido (uma unica palavra): ";  // Uma palavra
                    std::cin >> apelido;

                    // Verifica se o apelido e valido
                    if (!ehValidoParaCSV(apelido)) {
                        std::cout << "Erro: O apelido contem caractere invalido (virgula). Tente novamente." << std::endl;
                    } else {
                        break; // Sai do loop quando o apelido for valido
                    }
                } while (true);

                // Solicita o nome ate que ele seja valido
                std::cin.ignore(); // Limpa o buffer de entrada antes de getline.
                do {
                    std::cout << "Digite o nome (pode conter mais de uma palavra): ";  // Pode ter mais de uma palavra
                    std::getline(std::cin >> std::ws, nome);  // `std::ws` ignora espacos em branco a frente da string
                    if(nome.empty()){
                        std::cout << "Erro: Nome nao pode estar vazio." << std::endl;
                    } else if(!ehValidoParaCSV(nome)){
                        std::cout << "Erro: O nome contem caractere invalido (virgula). Tente novamente." << std::endl;
                    } else{
                        break;
                    }
                } while (true);

            } while (!gestao.cadastrarJogador(apelido, nome)); // Tenta cadastrar ate ser bem-sucedido.

        } else if(comando == "RJ"){
            std::cout << "Insira o apelido do jogador a ser removido: " << std::endl;
            std::cin >> apelido;
            gestao.removerJogador(apelido);

        } else if(comando == "LJ"){
            gestao.listarJogadores();

        } else if (comando == "EP") { //EP <Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2>
            //Verifica se o arquivo tem dados para executar partida
            if(!gestao.carregarTodoArquivo()){
                std::cout << "Impossivel executar partida.\n"
                          << "\nInsira um comando: " << std::endl;
                continue;
            }

            int vencedor;
            TipoDeJogo jogo_enum;

            while (true) { // Loop ate que uma escolha valida seja feita
                std::cout << "\nEscolha o jogo:\n";
                std::cout << "---------------------\n";
                std::cout << "[R] - \033[36mReversi\033[0m\n";         //Reversi em ciano
                std::cout << "[V] - \033[35mJogo da Velha\033[0m\n";   //Jogo da Velha em magenta
                std::cout << "[L] - \033[33mLig4\033[0m\n";            //Lig4 em amarelo
                std::cout << "---------------------" << std::endl;

                std::cin >> escolhaJogo;

                // Verifica se a entrada e exatamente um caractere
                if (std::cin.peek() != '\n') {
                    std::cout << "\nEntrada invalida. Digite apenas um caractere.\n";
                    std::cin.clear(); // Limpa o estado de erro do cin
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada
                    continue; // Volta ao inicio do loop
                }

                escolhaJogo = toupper(escolhaJogo); // Converte para maiuscula

                if (escolhaJogo == 'R' || escolhaJogo == 'V' || escolhaJogo == 'L') {
                    std::unique_ptr<Jogos> jogo;

                    // Cria o jogo escolhido

                    try {
                        switch (escolhaJogo) {
                            case 'R':
                                jogo = std::unique_ptr<Reversi>(new Reversi());
                                jogo_enum = REVERSI;
                                break;
                            case 'V':
                                jogo = std::unique_ptr<JogoDaVelha>(new JogoDaVelha());
                                jogo_enum = VELHA;
                                break;
                            case 'L':
                                jogo = std::unique_ptr<lig4>(new lig4());
                                jogo_enum = LIG4;
                                break;
                        }
                    } catch (const std::bad_alloc& e) {
                        std::cerr << "Erro: Falha ao alocar memoria para o jogo. " << e.what() << std::endl;
                        return 1;
                    }

                    // Solicita e valida os apelidos dos jogadores
                    std::string apelidoJogador1, apelidoJogador2;

                    bool apelidosValidos = false;
                    int nErros = 0; // Variavel para armazenar a quantidade de erros

                    do { // Loop ate que os apelidos inseridos sejam validos
                        
                        // Apos 3 tentativas mal-sucedidas, e oferecida a possibilidade de listar jogadores
                        if(nErros == 3) {
                            char resposta;
                            std::cout << "\nMuitos erros, hein?! Deseja listar jogadores?" << std::endl;
                            while(resposta != 'S' && resposta != 'N') {
                                std::cout << "Digite 'S' para sim e 'N' para nao: ";
                                std::cin >> resposta;
                            }
                            if(resposta == 'S'){
                                std::cout << "\n";
                                gestao.listarJogadores();
                                nErros = 0;
                            } else if (resposta == 'N') {
                                nErros = 0;
                            }
                        }

                        std::cout << "\nInsira o apelido do jogador 1: ";
                        std::cin >> apelidoJogador1;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        std::cout << "Insira o apelido do jogador 2: ";
                        std::cin >> apelidoJogador2;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        nErros++;

                        // Verifica se os apelidos sao iguais
                        if (apelidoJogador1 == apelidoJogador2) {
                            std::cout << "Os apelidos nao podem ser iguais. Por favor, insira apelidos diferentes." << std::endl;
                            continue; // Retorna ao inicio do loop para pedir novos apelidos
                        }
                        
                        apelidosValidos  = gestao.carregarDoisJogadores(apelidoJogador1, apelidoJogador2);
                    } while (!apelidosValidos);

                    // Define os apelidos no jogo (se necessario)
                    jogo->setApelidoJogador1(apelidoJogador1);
                    jogo->setApelidoJogador2(apelidoJogador2);

                    // Executa a partida
                    vencedor = executarPartida(std::move(jogo));

                    if (vencedor == 1) {
                        gestao.jogadores_map[apelidoJogador1]->adicionarVitoria(jogo_enum, 1);
                        gestao.jogadores_map[apelidoJogador2]->adicionarDerrota(jogo_enum, 1);
                        gestao.atualizarEstatisticas(gestao.jogadores_map);
                        std::cout << "\nAs estatisticas foram atualizadas!\n" << std::endl;
                    } else if (vencedor == 2) {
                        gestao.jogadores_map[apelidoJogador1]->adicionarDerrota(jogo_enum, 1);
                        gestao.jogadores_map[apelidoJogador2]->adicionarVitoria(jogo_enum, 1);
                        gestao.atualizarEstatisticas(gestao.jogadores_map);
                        std::cout << "\nAs estatisticas foram atualizadas!\n" << std::endl;
                    } else if (vencedor == 0) {
                        std::cout << "\nNenhuma estatistica foi alterada!\n" << std::endl;
                    }

                    break; // Sai do loop apos uma escolha valida
                } else {
                    std::cout << "Escolha invalida. Tente novamente.\n";
                }
            }

        } else if (comando == "M") {
            exibirMenu();

        } else if(comando == "FS"){
            std::cout << "\nSistema Finalizado. Saindo..." << std::endl;
                    break;
            
        } else {
            std::cout << "Comando Invalido. Tente Novamente." << std::endl;
        }

        std::cout << "\nInsira um comando: " << std::endl;
    }
    return 0;
}