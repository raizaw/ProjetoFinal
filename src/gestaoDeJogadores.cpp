#include "../include/gestaoDeJogadores.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include <stdexcept>

// Construtor e destrutor
GestaoDeJogadores::GestaoDeJogadores(const std::string& caminho)
    : caminhoDoArquivo(caminho) {
    std::ifstream arquivo(caminhoDoArquivo);
    //Verifica se arquivo pode ser aberto
    if (!arquivo.is_open()) {
        //Se não, tenta criar o arquivo
        std::ofstream novoArquivo(caminhoDoArquivo);
        if (!novoArquivo) {
            throw std::runtime_error("Erro: Nao foi possivel criar o arquivo: " + caminhoDoArquivo);
        }
        novoArquivo.close();  //Fecha o arquivo apenas se foi criado com sucesso
    }
}
GestaoDeJogadores::~GestaoDeJogadores() {}

// Métodos para manipulação do arquivo
bool GestaoDeJogadores::carregarTodoArquivo() {
    jogadores_map.clear(); //Limpa o mapa antes de carregar dados
    std::ifstream arquivo(caminhoDoArquivo);

    //Verifica se o arquivo está vazio
    arquivo.seekg(0, std::ios::end);
    if (arquivo.tellg() == 0) { //Vai para o final do arquivo
        std::cout << "Nenhum jogador cadastrado." << std::endl;
        return false;  // Retorna false se o arquivo estiver vazio
    }
    arquivo.seekg(0, std::ios::beg); //Volta ao início do arquivo

    std::string linha;
    while (std::getline(arquivo, linha)) {
        inserirLinhaNoMapa(linha);
    }
    arquivo.close();
    return true;
}
bool GestaoDeJogadores::carregarDoisJogadores(const std::string &apelido1, const std::string &apelido2) {
    //Encontra linha dos jogadores no arquivo
    std::string linha1 = buscarLinhaDoJogador(apelido1);
    std::string linha2 = buscarLinhaDoJogador(apelido2);

    bool apelido1Cadastrado = !linha1.empty();
    bool apelido2Cadastrado = !linha2.empty();

    if (!apelido1Cadastrado && !apelido2Cadastrado) {
        std::cerr << "Erro: Ambos os apelidos '" << apelido1 << "' e '" << apelido2 << "' nao estao cadastrados." << std::endl;
        return false;
    } else if (!apelido1Cadastrado) {
        std::cerr << "Erro: O apelido '" << apelido1 << "' nao esta cadastrado." << std::endl;
        return false;
    } else if (!apelido2Cadastrado) {
        std::cerr << "Erro: O apelido '" << apelido2 << "' nao esta cadastrado." << std::endl;
        return false;
    }

    //Limpa o buffer de erro antes de prosseguir
    std::cerr.clear();
    //Insere jogadores no mapa limpo
    jogadores_map.clear();
    inserirLinhaNoMapa(linha1);
    inserirLinhaNoMapa(linha2);

    return true;
}
bool GestaoDeJogadores::inserirNovoJogador(const std::unique_ptr<Jogador>& NovoJogador) {
    std::fstream arquivo(caminhoDoArquivo, std::ios::app | std::ios::out); //Abre o arquivo para leitura e edição
    //Testa se o arquivo pode ser aberto
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo");
    }

    std::string linha = NovoJogador->formatarJogadorComoCSV();
    //Insere novo jogador formatado no final do arquivo
    if (!(arquivo << linha)) {
        arquivo.close();
        throw std::runtime_error("Erro: Falha ao escrever os dados do jogador no arquivo.");
    }
    arquivo.close();
    return true;
}
bool GestaoDeJogadores::atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar_map) {
    //Verifica se mapa recebido está vazio
    if (jogadoresParaAtualizar_map.empty()) {
        std::cerr << "Erro: Mapa de jogadores para atualizar esta vazio." << std::endl;
        return false;
    }

    std::ifstream arquivoEntrada(caminhoDoArquivo);
    //Verifica se aquivo pode ser aberto
    if (!arquivoEntrada.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo: " + caminhoDoArquivo);
    }
    //Cria um arquivo temporário
    std::ofstream arquivoTemp("./gameData/temp.csv");
    //Verifica se aquivo pode ser aberto
    if (!arquivoTemp.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel criar o arquivo temporario.");
    }

    //Percorre o arquivo linha a linha
    std::string linha;
    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        std::string apelidoExistente;
        std::getline(ss, apelidoExistente, ',');

        //Verifica se o apelido do arquivo existe no mapa de jogadores a atualizar
        auto it = jogadoresParaAtualizar_map.find(apelidoExistente);
            // Se for, formata jogador do mapa como CSV e insere no arquivo temporário
        if (it != jogadoresParaAtualizar_map.end()) {
            const auto& jogador = it->second;
            arquivoTemp << jogador->formatarJogadorComoCSV();
            // Se não, apenas insere linha no arquivo temporário
        } else {
            arquivoTemp << linha << std::endl;
        }
    }

    arquivoEntrada.close();
    arquivoTemp.close();

    // Substitui o arquivo original pelo temporário
    if (std::remove(caminhoDoArquivo.c_str()) != 0) {
        throw std::runtime_error("Erro: Nao foi possivel remover o arquivo original.");
    }
    if (std::rename("./gameData/temp.csv", caminhoDoArquivo.c_str()) != 0) {
        throw std::runtime_error("Erro: Nao foi possivel renomear o arquivo temporario.");
    }

    return true;
}

// Métodos para gerenciar jogadores
bool GestaoDeJogadores::cadastrarJogador(const std::string &apelido, const std::string &nome) {
    //Testa se apelido já existe
    if (!buscarLinhaDoJogador(apelido).empty()) {
        std::cerr << "Erro: ja existe um jogador com o apelido '" + apelido + "'. Por favor, insira outro." << std::endl;
        return false;
    }

    //Cria novo jogador
    std::unique_ptr<Jogador> novoJogador(new Jogador(apelido, nome));
    
    //Teste se houve erro no salvamento do jogador no arquivo
    if (!inserirNovoJogador(novoJogador)) {
        throw std::runtime_error("ERRO: Falha ao salvar o jogador no arquivo.");
    }
    std::cout << "Jogador '" << apelido << "' cadastrado com sucesso." << std::endl;
    return true;
}
bool GestaoDeJogadores::removerJogador(const std::string &apelido) {
    // Coloca todos jogadores do arquivo em um mapa
    if (!carregarTodoArquivo()) {
        return false;
    }
    //Verifica se exite jogador com esse apelido
    if (jogadores_map.find(apelido) == jogadores_map.end()) {
        std::cerr << "Erro: Nao existe Jogador com o apelido: '" + apelido + "'" << std::endl;
        return false;
    }
    //Remove jogador do mapa
    jogadores_map.erase(apelido);
    std::ofstream arquivo(caminhoDoArquivo, std::ios::trunc); //trunc reseta o arquivo para 0 bytes
    if (!arquivo.is_open()) {
        throw std::runtime_error("ERRO: Nao foi possivel abrir o arquivo para removerJogador");
    }
    //Formata e insere todos jogadores no arquivo
    for (const auto& pair : jogadores_map) {
        const auto& _jogador = pair.second;
        arquivo << _jogador->formatarJogadorComoCSV();
    }

    arquivo.close();
    std::cout << "Jogador: '" << apelido << "' removido com sucesso." << std::endl;
    return true;
}
void GestaoDeJogadores::listarJogadores() {
    // Coloca todos jogadores do arquivo em um mapa
    if (!carregarTodoArquivo()) {
        std::cerr << "Nao foi possivel carregar todo o arquivo para listar jogadores" << std::endl;
        return;
    }
    
    for (const auto& pair : jogadores_map) {
        //Exibe apelido e nome do jogador
        const auto& _jogador = pair.second;
        std::cout << "\n" << "[A|N] " << std::setw(15) << std::left << _jogador->getApelido()
                  << std::left << _jogador->getNome() << std::endl;
        //Exibe as estatísticas de vitórias e derrotas em cada jogo
        for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
            float media;
            float nPartidas;

            auto estatisticas = _jogador->getEstatisticasDoJogo(static_cast<TipoDeJogo>(i));
            nPartidas = estatisticas.first + estatisticas.second;

            if(nPartidas == 0){
                media = 0;
            }else{
                media = (estatisticas.first/nPartidas)*100;
            }

            std::string cor;

            if (nPartidas == 0) {
                cor = "\033[0m";       // Padrão
            }else if (media >= 75) {
                cor = "\033[1;32m";    // Verde em negrito
            } else if (media >= 50) {
                cor = "\033[36m";      // Ciano
            } else if (media >= 25){
                cor = "\033[33m";      // Amarelo
            } else {
                cor = "\033[31m";      // Vermelho
            } 

            std::cout << std::setw(10) << std::left << nomeDoJogo(static_cast<TipoDeJogo>(i))
                      << " - V: " << std::setw(3) << std::left << estatisticas.first  //Vitórias
                      << " D: " << std::setw(3) << std::left << estatisticas.second  //Derrotas
                      << " | A: " << std::setw(3) << std::left << cor               //Cor da média
                      << std::fixed << std::setprecision(2) << media << "%\033[0m" //Média
                      << std::endl;
        }
    }
}

// Métodos auxiliares
std::string GestaoDeJogadores::buscarLinhaDoJogador(const std::string &apelido) const {
    std::ifstream arquivo(caminhoDoArquivo);
    //Verifica se aquivo pode ser aberto
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo: " + caminhoDoArquivo);
    }

    //Percorre o arquivo linha a linha
    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string apelidoNoArquivo;
        std::getline(ss, apelidoNoArquivo, ',');
        // Se apelido do arquivo for o recebido, retorna a linha em CSV
        if (apelidoNoArquivo == apelido) {
            arquivo.close();
            return linha;
        }
    }
    arquivo.close();
    // Se não achar alguma linha correspondente, retorna uma string vazia
    return "";
}
void GestaoDeJogadores::inserirLinhaNoMapa(const std::string& linha) {
    //Percorre a string CSV armazenando apelido e nome nas respectivas variáveis
    std::stringstream ss(linha);
    std::string apelido, nome;
    std::getline(ss, apelido, ',');
    std::getline(ss, nome, ',');

    //Verifica e avisa se existem algum apelido ou nome no arquivo
    if (apelido.empty() || nome.empty()) {
        std::cerr << "Erro: Linha mal formatada no CSV - " << linha << std::endl;
        return; //Continua processando outras linhas
    }

    //Cria novo jogador
    std::unique_ptr<Jogador> novoJogador(new Jogador(apelido, nome));
  
    //Percorre string CSV armazenando vitórias e derrotas nas respectivas variáveis
    std::string estatistica;
    int contaJogos = 0;

    for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
        int vitoria, derrota;

        //Armazena vitórias nas variáveis
        if (!std::getline(ss, estatistica, ',') || !(std::istringstream(estatistica) >> vitoria)) {
            std::cerr << "Erro: Estatisticas mal formatadas para o jogo " + nomeDoJogo(static_cast<TipoDeJogo>(i)) + " na linha - " << linha << std::endl;
            return;
        }
        //Armazena derrotas nas variáveis
        if (!std::getline(ss, estatistica, ',') || !(std::istringstream(estatistica) >> derrota)) {
            std::cerr << "Erro: Estatisticas mal formatadas para o jogo " + nomeDoJogo(static_cast<TipoDeJogo>(i)) + " na linha - " << linha << std::endl;
            return;
        }
        //Armazena variáveis no mapa
        novoJogador->adicionarVitoria(static_cast<TipoDeJogo>(i), vitoria);
        novoJogador->adicionarDerrota(static_cast<TipoDeJogo>(i), derrota);
        contaJogos++;
    }
    // Verifique se o número de jogos lidos é o esperado
    if (contaJogos != (TOTAL_DE_JOGOS - REVERSI)) {
        std::cerr << "Erro: Numero incorreto de jogos na linha - " << linha << std::endl;
        return;
    }
    jogadores_map[apelido] = std::move(novoJogador);
}
//Recebe o TipoDeJogo e retorna a string respectiva do tipoDeJogo
std::string GestaoDeJogadores::nomeDoJogo(TipoDeJogo jogo) {
    switch (jogo) {
        case REVERSI: return "REVERSI";
        case LIG4:    return "LIG4";
        case VELHA:   return "VELHA";
        default:      return "JOGO_INVALIDO";
    }
}