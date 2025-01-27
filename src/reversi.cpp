#include "../include/reversi.hpp"

#include <limits>
#include <iomanip>

#define fimCor "\033[0m"

std::string Reversi::cor(int jogador){
    if (jogador == 1){
        return "\033[35m"; // Magenta
    } else if (jogador == 2){
        return "\033[36m"; // Ciano
    }
}

Reversi::Reversi() : Jogos(8, 8), jogadaLinha(-1), jogadaColuna(-1) {
    // Inicializa o tabuleiro com as peças iniciais do Reversi
    tabuleiro->setPosicao(3, 3, Tabuleiro::Peca::JOGADOR2);
    tabuleiro->setPosicao(3, 4, Tabuleiro::Peca::JOGADOR1);
    tabuleiro->setPosicao(4, 3, Tabuleiro::Peca::JOGADOR1);
    tabuleiro->setPosicao(4, 4, Tabuleiro::Peca::JOGADOR2);
}

void Reversi::fraseInicial() {
    std::cout << "Iniciando partida de Reversi entre " 
              << cor(1) << apelidoJogador1 << fimCor << " e " 
              << cor(2) << apelidoJogador2 << fimCor << "..." << std::endl;
}

void Reversi::exibirPeca(Tabuleiro::Peca peca) const {
    switch (peca) {
        case Tabuleiro::Peca::VAZIO: 
            std::cout << "  ";
            break;
        case Tabuleiro::Peca::JOGADOR1:
            std::cout << "\033[35m O \033[0m"; // "O" em magenta
            break;
        case Tabuleiro::Peca::JOGADOR2:
            std::cout << "\033[36m O \033[0m"; // "O" em ciano
            break;
    }
}

void Reversi::exibirTabuleiro() const {
    const auto& matriz = tabuleiro->getTabuleiro();
    const size_t tamanho = matriz.size();

    const int largura = 3; // Largura fixa para cada célula (ajuste conforme necessário)

    // Exibe os números das colunas
    std::cout << std::setw(largura - 1) << "  "; // Espaço para alinhar com os números das linhas
    for (size_t coluna = 0; coluna < tamanho; ++coluna) {
        std::cout << std::setw(largura + 1) << coluna + 1;
    }
    std::cout << "\n";

    for (size_t i = 0; i < matriz.size(); ++i) { // Itera sobre as linhas
        const auto& linha = matriz[i];

        // Exibe o número da linha
        std::cout << std::setw(largura) << i + 1 << " "; // Numeração das linhas

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
            std::cout << std::setw(largura) << " "; // Espaço alinhado com a numeração das linhas
            for (size_t j = 0; j < linha.size(); ++j) {
                std::cout << std::string(largura, '-'); // Linha horizontal para cada célula
                if (j < linha.size() - 1) { // Adiciona o "|" entre os blocos
                    std::cout << "+";
                }
            }
            std::cout << "\n";
        }
    }
}

bool Reversi::haJogadasPossiveis() {
    for (int i = 0; i < tabuleiro->getLinhas(); ++i) {
        for (int j = 0; j < tabuleiro->getColunas(); ++j) {
            if (tabuleiro->getPosicao(i, j) == Tabuleiro::Peca::VAZIO) {
                // Verifica se a jogada é válida para o jogador atual
                jogadaLinha = i;
                jogadaColuna = j;
                if (jogadaEValida()) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Reversi::lerJogada() {
    bool entradaValida = false;

    while (!entradaValida) {
        if (!haJogadasPossiveis()) {
            std::cout << "Não ha jogadas disponiveis para o jogador " 
                      << ((jogadorAtual == Tabuleiro::Peca::JOGADOR1)? apelidoJogador1 : apelidoJogador2) 
                      << ". Pressione Enter para passar a vez...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer
            std::cin.get(); // Espera o jogador pressionar Enter
            std::cout << ((jogadorAtual == Tabuleiro::Peca::JOGADOR1)? apelidoJogador1 : apelidoJogador2) 
                      << " passou a vez.\n";
            trocarJogador(); // Passa a vez para o outro jogador
            return;
        }

        if (jogadorAtual == Tabuleiro::Peca::JOGADOR1) {
            std::cout << "Turno de " << cor(1) << apelidoJogador1 
                      << fimCor << std::endl;
        } else if (jogadorAtual == Tabuleiro::Peca::JOGADOR2) {
            std::cout << "Turno de " << cor(2) << apelidoJogador2 
                      << fimCor << std::endl;
        }
        std::cout << "Insira a linha e a coluna da sua jogada (ex: 1 2): ";

        std::cin >> jogadaLinha >> jogadaColuna;

        if (std::cin.fail()) {
            // Limpa o estado de erro e esvazia o buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Tente novamente.\n";
        } else {
            // Esvazia o buffer para descartar entradas extras
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            entradaValida = true;
        }
    }
    --jogadaLinha; // Ajusta para índice zero da matriz
    --jogadaColuna; // Ajusta para índice zero da matriz
}

bool Reversi::jogadaEValida() const {
    if (!dentroDosLimites(jogadaLinha, jogadaColuna) || 
        tabuleiro->getPosicao(jogadaLinha, jogadaColuna) != Tabuleiro::Peca::VAZIO) {
        return false;
    }

    Tabuleiro::Peca peca = jogadorAtual;
    // Verifica se há pelo menos uma direção válida para captura
    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if ((deltaLinha != 0 || deltaColuna != 0) && 
                direcaoValida(jogadaLinha, jogadaColuna, deltaLinha, deltaColuna, peca)) {
                return true;
            }
        }
    }
    return false;
}

void Reversi::realizarJogada() {
    if (!jogadaEValida()) return;

    Tabuleiro::Peca peca = jogadorAtual;
    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if ((deltaLinha != 0 || deltaColuna != 0) && 
                direcaoValida(jogadaLinha, jogadaColuna, deltaLinha, deltaColuna, peca)) {
                capturarPecas(jogadaLinha, jogadaColuna, peca);
            }
        }
    }

    tabuleiro->setPosicao(jogadaLinha, jogadaColuna, peca);
    exibirTabuleiro();
    trocarJogador();
}

bool Reversi::partidaAcabou() {
    // Verifica se o tabuleiro está cheio
    bool tabuleiroCheio = true;
    for (int i = 0; i < tabuleiro->getLinhas(); ++i) {
        for (int j = 0; j < tabuleiro->getColunas(); ++j) {
            if (tabuleiro->getPosicao(i, j) == Tabuleiro::Peca::VAZIO) {
                tabuleiroCheio = false;
                break;
            }
        }
        if (!tabuleiroCheio) break;
    }

    // Verifica se ambos os jogadores não têm jogadas possíveis
    if (!haJogadasPossiveis()) {
        trocarJogador(); // Verifica o outro jogador
        if (!haJogadasPossiveis()) {
            return true; // Ambos os jogadores não têm jogadas possíveis
        }
        trocarJogador(); // Volta ao jogador original
    }

    return tabuleiroCheio;
}

std::pair<int, int> Reversi::contarPecas() const {
    int jogador1 = 0, jogador2 = 0;
    for (const auto& linha : tabuleiro->getTabuleiro()) {
        for (const auto& celula : linha) {
            if (celula == Tabuleiro::Peca::JOGADOR1) ++jogador1;
            if (celula == Tabuleiro::Peca::JOGADOR2) ++jogador2;
        }
    }
    return {jogador1, jogador2};
}



int Reversi::indicarFimDaPartida() {
    // Chamada à função contarPecas, que retorna um std::pair
    std::pair<int, int> pecas = contarPecas();

    // Extrai os valores manualmente
    int pecasJogador1 = pecas.first;
    int pecasJogador2 = pecas.second;

    exibirTabuleiro();
    std::cout << "PARTIDA ENCERRADA!\nContagem de pontos:";
    std::cout << apelidoJogador1 << ": " << pecasJogador1 << std::endl;
    std::cout << apelidoJogador2 << ": " << pecasJogador2 << std::endl;

    if (pecasJogador1 > pecasJogador2) {
        std::cout << "\nParabens, " << cor(1) << apelidoJogador1 << fimCor << ", voce venceu!" << std::endl;
        return 1;
    } else if (pecasJogador1 < pecasJogador2) {
        std::cout << "\nParabens, " << cor(2) << apelidoJogador2 << fimCor << ", voce venceu!" << std::endl;
        return 2;
    } else {
        std::cout << "\nO jogo terminou empatado!" << std::endl;
        return 0;
    }
}



bool Reversi::dentroDosLimites(int linha, int coluna) const {
    return linha >= 0 && linha < tabuleiro->getLinhas() && coluna >= 0 && coluna < tabuleiro->getColunas();
}

bool Reversi::direcaoValida(int linha, int coluna, int deltaLinha, int deltaColuna, Tabuleiro::Peca peca) const {
    linha += deltaLinha;
    coluna += deltaColuna;

    bool encontrouOponente = false;
    while (dentroDosLimites(linha, coluna)) {
        if (tabuleiro->getPosicao(linha, coluna) == Tabuleiro::Peca::VAZIO) {
            return false;
        } else if (tabuleiro->getPosicao(linha, coluna) != peca) {
            encontrouOponente = true;
        } else {
            return encontrouOponente;
        }
        linha += deltaLinha;
        coluna += deltaColuna;
    }
    return false;
}

bool Reversi::capturarPecas(int linha, int coluna, Tabuleiro::Peca peca) {
    bool capturou = false;

    for (int deltaLinha = -1; deltaLinha <= 1; ++deltaLinha) {
        for (int deltaColuna = -1; deltaColuna <= 1; ++deltaColuna) {
            if ((deltaLinha != 0 || deltaColuna != 0) &&
                direcaoValida(linha, coluna, deltaLinha, deltaColuna, peca)) {

                int x = linha + deltaLinha;
                int y = coluna + deltaColuna;
                while (tabuleiro->getPosicao(x, y) != peca) {
                    tabuleiro->setPosicao(x, y, peca);
                    x += deltaLinha;
                    y += deltaColuna;
                }
                capturou = true;
            }
        }
    }

    return capturou;
}
