#include "../include/lig4.hpp"

void lig4::exibirTabuleiro() const{
    for(const auto& linha : tabuleiro->getTabuleiro()){
        for(const auto& celula : linha){
            exibirPeca(celula);
            std::cout << " | ";
        }
        std::cout << "\n";
    }
    std::cout << std::string(29, '-') << "\n"; // separador visual
    for(int i = 0; i < 7; ++i){
        std::cout << "  " << i + 1 << "  ";
    }
    std::cout << "\n";
}

void lig4::exibirPeca(Tabuleiro::Peca peca) const{
    switch(peca) {
        case Tabuleiro::Peca::VAZIO:
        std::cout << "   ";
        break;
        case Tabuleiro::Peca::JOGADOR1:
        std::cout << "\033[31m X \033[0m"; // O em vermelho
        break;
        case Tabuleiro::Peca::JOGADOR2:
        std::cout << "\033[33m O \033[0m"; // O em amarelo
        break;
    }
}

void lig4::lerJogada() {
    std::cout << "Jogador " << (jogadorAtual == Tabuleiro::Peca::JOGADOR1 ? "1 (X)" : "2 (O)") << ", escolha uma coluna (1-7): ";
    std::cin >> colunaEscolhida;
    --colunaEscolhida; // ajusta para indice zero
}

bool lig4::jogadaEValida() const{
    return colunaEscolhida >= 0 && colunaEscolhida < 7 && tabuleiro->getPosicao(0, colunaEscolhida) == Tabuleiro::Peca::VAZIO;
}

void lig4::realizarJogada(){
    for (int i = 5; i >= 0; --i){
        if (tabuleiro->getPosicao(i, colunaEscolhida) == Tabuleiro::Peca::VAZIO){
            tabuleiro->setPosicao(i, colunaEscolhida, jogadorAtual);
            break;
        }
    }
}

bool lig4::partidaAcabou() {
    for (int linha = 0; linha < 6; ++linha){
        for (int coluna = 0; coluna < 7; ++coluna){
            if(tabuleiro->getPosicao(linha, coluna) != Tabuleiro::Peca::VAZIO && verificarVitoria(linha, coluna)){
                return true;
            }
        }
    }
    return false;
}

void lig4::indicarFimDaPartida() const{
    std::cout << "Jogador " << (jogadorAtual == Tabuleiro::Peca::JOGADOR1 ? "1 (X)" : "2 (O)") << "Venceu!\n";
}

bool lig4::verificarVitoria(int linha, int coluna) const{
    static const int direcoes[4][2] = { {0,1}, {1, 0}, {1, 1}, {1, -1}};
    Tabuleiro::Peca peca = tabuleiro->getPosicao(linha, coluna);

    for(const auto& dir : direcoes){
        int contagem = 1;
        for (int i = 1; i < 4; ++i){
            int novaLinha = linha + i * dir[0];
            int novaColuna = coluna + i * dir[1];
            if(dentroDosLimites(novaLinha, novaColuna) && tabuleiro->getPosicao(novaLinha, novaColuna) == peca){
                ++contagem;
            } else {
                break;
            }
        }

        for(int i = 1; i < 4; ++i){
            int novaLinha = linha - i * dir[0];
            int novaColuna = coluna - i * dir[1];
            if (dentroDosLimites(novaLinha, novaColuna) && tabuleiro->getPosicao(novaLinha, novaColuna) == peca){
                ++contagem;
            } else {
                break;
            }
        }
        for (int i = 1; i < 4; ++i){
            int novaLinha = linha - i * dir[0];
            int novaColuna = coluna - i * dir[1];
            if (dentroDosLimites(novaLinha, novaColuna) && tabuleiro->getPosicao(novaLinha, novaColuna) == peca){
                ++contagem;
            } else {
                break;
            }
        }
        if (contagem >= 4){
            return true;
        }
    } 
    return false;
}
bool lig4::dentroDosLimites(int linha, int coluna) const{
    return linha >= 0 && linha < 6 && coluna >= 0 && coluna < 7;
}