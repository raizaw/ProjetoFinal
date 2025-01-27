#include "../include/jogoDaVelha.hpp"

#include <iomanip>

#define fimCor "\033[0m"

std::string JogoDaVelha::cor(int jogador){
    if (jogador == 1){
        return "\033[31m"; // Vermelho
    } else if (jogador == 2){
        return "\033[33m"; // Amarelo
    } else{
        return "";
    }
}

void JogoDaVelha::exibirPeca(Tabuleiro::Peca peca) const {
    switch (peca) {
    case Tabuleiro::Peca::VAZIO:
        std::cout << " ";
        break;
    case Tabuleiro::Peca::JOGADOR1:
        std::cout << "\033[31mX\033[0m"; // X em vermelho
        break;
    case Tabuleiro::Peca::JOGADOR2:
        std::cout << "\033[33mO\033[0m"; // O em amarelo
        break;
    }
};

void JogoDaVelha::exibirTabuleiro() const {

    const auto& matriz = tabuleiro->getTabuleiro();
        // Exibe os números das colunas com um espaço extra no começo
        std::cout << "    1   2   3\n";

        for (size_t i = 0; i < matriz.size(); ++i) { // Itera sobre as linhas
            const auto& linha = matriz[i];

            // Exibe o número da linha com um espaço extra antes da primeira casa
            std::cout << i + 1 << "   ";

            // Exibe as peças da linha com os separadores "|"
            for (size_t j = 0; j < linha.size(); ++j) {
                exibirPeca(linha[j]); // Exibe a peça
                if (j < linha.size() - 1) { // Adiciona "|", exceto no final da linha
                    std::cout << " | ";
                }
            }
            std::cout << "\n";

            // Adiciona os separadores entre as linhas, exceto no final do tabuleiro
            if (i < matriz.size() - 1) {
                std::cout << "   ---+---+---\n";
            }
        }

    // const auto& matriz = tabuleiro->getTabuleiro();
    // const size_t tamanho = matriz.size();

    // const int largura = 3; // Largura fixa para cada célula (ajuste conforme necessário)

    // // Exibe os números das colunas
    // std::cout << std::setw(largura - 1) << "  "; // Espaço para alinhar com os números das linhas
    // for (size_t coluna = 0; coluna < tamanho; ++coluna) {
    //     std::cout << std::setw(largura + 1) << coluna + 1;
    // }
    // std::cout << "\n";

    // for (size_t i = 0; i < matriz.size(); ++i) { // Itera sobre as linhas
    //     const auto& linha = matriz[i];

    //     // Exibe o número da linha
    //     std::cout << std::setw(largura) << i + 1 << " "; // Numeração das linhas

    //     // Exibe as peças da linha com os separadores "|"
    //     for (size_t j = 0; j < linha.size(); ++j) {
    //         exibirPeca(linha[j]); // Exibe a peça
    //         if (j < linha.size() - 1) { // Adiciona "|", exceto no final da linha
    //             std::cout << " | ";
    //         }
    //     }
    //     std::cout << "\n";

    //     // Adiciona os separadores entre as linhas, exceto no final do tabuleiro
    //     if (i < matriz.size() - 1) {
    //         std::cout << std::setw(largura) << " "; // Espaço alinhado com a numeração das linhas
    //         for (size_t j = 0; j < linha.size(); ++j) {
    //             std::cout << std::string(largura, '-'); // Linha horizontal para cada célula
    //             if (j < linha.size() - 1) { // Adiciona o "|" entre os blocos
    //                 std::cout << "+";
    //             }
    //         }
    //         std::cout << "\n";
    //     }
    // }
}


void JogoDaVelha::fraseInicial() {
    std::cout << "Iniciando partida de Jogo da Velha entre " 
              << cor(1) << apelidoJogador1 << fimCor << " e " 
              << cor(2) << apelidoJogador2 << fimCor << "..." << std::endl;
}

void JogoDaVelha::lerJogada() {
    bool entradaValida = false;

    while (!entradaValida) {
        if (jogadorAtual == Tabuleiro::Peca::JOGADOR1) {
            std::cout << "Turno de " << cor(1) << apelidoJogador1 << fimCor << std::endl;
        } else if (jogadorAtual == Tabuleiro::Peca::JOGADOR2) {
            std::cout << "Turno de " << cor(2) << apelidoJogador2 << fimCor << std::endl;
        }
        std::cout << "Insira a linha e a coluna da sua jogada (ex: 1 2): ";

        std::cin >> jogadaLinha >> jogadaColuna;

        if (std::cin.fail()) {
            // Limpa o estado de erro e esvazia o buffer
            std::cin.clear();
            std::cin.ignore(10000, '\n'); // Valor grande para garantir que o buffer seja limpo
            std::cout << "Entrada invalida. Tente novamente.\n";
        } else {
            // Esvazia o buffer para descartar entradas extras
            std::cin.ignore(10000, '\n');
            entradaValida = true;
        }
    }
    --jogadaLinha; // ajustar índice para matriz
    --jogadaColuna;
}; 

bool JogoDaVelha::jogadaEValida() const {
    // Verifica se a posição está dentro dos limites do tabuleiro
    if (jogadaLinha < 0 || jogadaLinha >= tabuleiro->getLinhas() ||
        jogadaColuna < 0 || jogadaColuna >= tabuleiro->getColunas()) {
        std::cout << "Jogada invalida: posicao fora do tabuleiro.\n";
        return false;
    }

    // Verifica se a posição está vazia
    if (tabuleiro->getPosicao(jogadaLinha, jogadaColuna) != Tabuleiro::Peca::VAZIO) {
        std::cout << "Jogada invalida: posicao ja ocupada.\n";
        return false;
    }

    return true;
}; 

void JogoDaVelha::realizarJogada() {
    // Define a peça do jogador atual na posição indicada
    Tabuleiro::Peca pecaJogador = (jogadorAtual == Tabuleiro::Peca::JOGADOR1) ? Tabuleiro::Peca::JOGADOR1 : Tabuleiro::Peca::JOGADOR2;
    tabuleiro->setPosicao(jogadaLinha, jogadaColuna, pecaJogador);

    // Exibe o estado atualizado do tabuleiro
    exibirTabuleiro();

    // Troca para o próximo jogador
    trocarJogador();
}; 

bool JogoDaVelha::partidaAcabou() {
    // Verifica se algum jogador venceu (linhas, colunas ou diagonais)
    const auto& matriz = tabuleiro->getTabuleiro();

    // Verifica linhas
    for (const auto& linha : matriz) {
        if (linha[0] != Tabuleiro::Peca::VAZIO && 
            linha[0] == linha[1] && linha[1] == linha[2]) {
            vencedor = (linha[0] == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
            return true;
        }
    }

    // Verifica colunas
    for (int col = 0; col < 3; ++col) {
        if (matriz[0][col] != Tabuleiro::Peca::VAZIO && 
            matriz[0][col] == matriz[1][col] && matriz[1][col] == matriz[2][col]) {
            vencedor = (matriz[0][col] == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
            return true;
        }
    }

    // Verifica diagonais
    if (matriz[0][0] != Tabuleiro::Peca::VAZIO && 
        matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2]) {
        vencedor = (matriz[0][0] == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
        return true;
    }

    if (matriz[0][2] != Tabuleiro::Peca::VAZIO && 
        matriz[0][2] == matriz[1][1] && matriz[1][1] == matriz[2][0]) {
        vencedor = (matriz[0][2] == Tabuleiro::Peca::JOGADOR1) ? 1 : 2;
        return true;
    }

    // Verifica empate (nenhum espaço vazio)
    for (const auto& linha : matriz) {
        for (const auto& celula : linha) {
            if (celula == Tabuleiro::Peca::VAZIO) {
                return false; // Ainda há espaços disponíveis, o jogo continua
            }
        }
    }

    vencedor = 0; // Indica empate
    return true;
}; 

int JogoDaVelha::indicarFimDaPartida() {
    std::cout << "\n\n" << "TABULEIRO FINAL:\n" << std::endl;
    exibirTabuleiro();
    std::cout << "\nPARTIDA ENCERRADA\n" << std::endl;
    if (vencedor == 0) {
        std::cout << "A partida terminou em empate!\n";
        return 0;
    } else {
 std::cout << "Parabens, " 
           << ((vencedor == 1) ? cor(1) : cor(2))
           << fimCor
           << ((vencedor == 1) ? apelidoJogador1 : apelidoJogador2)
           << "! Voce venceu!" << std::endl;    
        return (vencedor == 1)? 1 : 2;
    }
};