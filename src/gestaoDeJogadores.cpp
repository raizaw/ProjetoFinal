// #include "../include/gestaoDeJogadores.hpp"

// //Construtor e destrutor
// GestaoDeJogadores::GestaoDeJogadores(const std::string& caminho)
//     : caminhoDoArquivo(caminho){
//     std::ifstream arquivo(caminhoDoArquivo);
//     //Ve se arquivo pode ser aberto
//     if(!arquivo.is_open()){
//         //Tenta criar o arquivo
//         std::ofstream novoArquivo(caminhoDoArquivo);
//         if (!novoArquivo) {
//             throw std::runtime_error("Erro: Nao foi possivel criar o arquivo: " + caminhoDoArquivo);
//         }
//     novoArquivo.close();
//     }
// }
// GestaoDeJogadores::~GestaoDeJogadores(){}


// //Métodos para manipulação do arquivo
// bool GestaoDeJogadores::carregarTodoArquivo(){
//     jogadores_map.clear(); //Limpa o mapa antes de carregar dados
//     std::ifstream arquivo(caminhoDoArquivo);

//     //Confere se arquivo esta vazio
//     arquivo.seekg(0, std::ios::end); //Vai para o final do arquivo
//     if (arquivo.tellg() == 0) {
//         std::cout << "Nenhum jogador cadastrado." << std::endl;
//         return false;
//     } //Se posicao for 0, entao arquivo esta vazio
//     arquivo.seekg(0, std::ios::beg); //Volta ao inicio para leitura

//     std::string linha;
//     while(std::getline(arquivo, linha)){
//         inserirLinhaNoMapa(linha); //impede linha corrompida
//     }
//     arquivo.close();
//     return true;
// }
// bool GestaoDeJogadores::carregarDoisJogadores(const std::string &apelido1,const std::string &apelido2){
//     //Encontra linha dos jogadores no arquivo
//     std::string linha1 = buscarLinhaDoJogador(apelido1);
//     if(linha1.empty()){
//         std::cerr << "Erro: O apelido '" + apelido1 + "' nao esta cadastrado.'" << std::endl;
//         return false;
//     }

//     std::string linha2 = buscarLinhaDoJogador(apelido2);
//     if(linha2.empty()){
//         std::cerr << "Erro: O apelido '" + apelido2 + "' nao esta cadastrado.'" << std::endl;
//         return false;
//     }
//     //Insere jogadores no mapa limpo
//     jogadores_map.clear();
//     inserirLinhaNoMapa(linha1);
//     inserirLinhaNoMapa(linha2);
//     return true;
// }
// bool GestaoDeJogadores::inserirNovoJogador(const std::unique_ptr<Jogador>& NovoJogador){
//     std::fstream arquivo(caminhoDoArquivo, std::ios::app | std::ios::out); //abre o arquivo para leitura e edicao
//     if(!arquivo.is_open()){
//         throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo");
//     }
//     std::string linha = NovoJogador->formatarJogadorComoCSV();
//     //Insere novo jogador formatado no final do aruqivo
//     if(!(arquivo << linha)){
//         arquivo.close();
//         throw std::runtime_error("Erro: Falha ao escrever os dados do jogador no arquivo.");
//     }
//     arquivo.close();
//     return true;
// }
// bool GestaoDeJogadores::atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar_map){
//     if (jogadoresParaAtualizar_map.empty()) {
//         std::cerr << "Erro: Mapa de jogadores para atualizar esta vazio." << std::endl;
//         return false;
//     }

//     std::fstream arquivo(caminhoDoArquivo, std::ios::in | std::ios::out); // Abrir para leitura e escrita
//     if (!arquivo.is_open()) {
//         throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo: " + caminhoDoArquivo);
//     }

//     arquivo.seekg(0, std::ios::end); // Vai para o final do arquivo
//     if (arquivo.tellg() == 0) {
//         std::cerr << "Erro: O arquivo '"+ caminhoDoArquivo +"' esta vazio." << std::endl;
//     } // Se posicao for 0, entao arquivo esta vazio
//     arquivo.seekg(0, std::ios::beg); // Volta ao inicio para leitura

//     std::string linha;
//     std::streampos posAnterior = arquivo.tellg(); // Marca a posicao inicial
//     std::set<std::string> jogadoresAtualizados; //Para rastrear quais jogadores foram atualizados

//     // Percorre o arquivo linha por linha
//     while (std::getline(arquivo, linha)) {
//         std::stringstream ss(linha);
//         std::string apelidoExistente;
//         std::getline(ss, apelidoExistente, ',');

//         // Verifica se o apelido existe no mapa de jogadores a atualizar
//         auto it = jogadoresParaAtualizar_map.find(apelidoExistente);
//         if (it != jogadoresParaAtualizar_map.end()) {
//             const auto& jogador = it->second;
    
//             // Move o ponteiro para o inicio da linha atual
//             arquivo.clear(); // Limpa flags de erro, se houver
//             arquivo.seekp(posAnterior);

//             // Sobrescreve a linha com os dados do jogador
//             std::string novaLinha = jogador->formatarJogadorComoCSV();
//             arquivo << std::setw(novaLinha.size()) << std::left << novaLinha;
//             jogadoresAtualizados.insert(apelidoExistente);
//         }
//         posAnterior = arquivo.tellg(); // Atualiza a posicao da linha atual
//     }
//     arquivo.close();
//     if (jogadoresAtualizados.size() != jogadoresParaAtualizar_map.size()){
//         return false;
//     }
//     return true;
// }


// //Métodos para gerenciar jogadores
// bool GestaoDeJogadores::cadastrarJogador(const std::string &apelido, const std::string &nome){
//     //Testa se apelido já existe
//     if(!buscarLinhaDoJogador(apelido).empty()){
//         std::cerr << "Erro: jogador com o apelido '" + apelido + "' ja existe. Insira outro." << std::endl;
//         return false;
//     }
//     //Cria novo jogador
//     std::unique_ptr<Jogador> novoJogador(new Jogador(apelido, nome));
//     //Teste se houve erro no salvamento do jogador no arquivo
//     if (!inserirNovoJogador(novoJogador)) {
//         throw std::runtime_error("ERRO: Falha ao salvar o jogador no arquivo.");
//     }
//     std::cout << "Jogador " << apelido << " cadastrado com sucesso." << std::endl;
//     return true;
// }
// bool GestaoDeJogadores::removerJogador(const std::string &apelido){ 
//     if(!carregarTodoArquivo()){
//         return false;
//     } 
//     // Coloca todos jogadores do arquivo num mapa
//     if(jogadores_map.find(apelido) == jogadores_map.end()){
//         std::cerr << "Erro: Nao existe Jogador com o apelido: '" + apelido + "'" << std::endl;
//         return false;
//     }
//     //remove jogador do mapa
//     jogadores_map.erase(apelido);
//     std::ofstream arquivo(caminhoDoArquivo, std::ios::trunc); //trunc reseta o arquivo para 0 bytes
//     if(!arquivo.is_open()){
//         throw std::runtime_error("ERRO: Nao foi possível abrir o arquivo para removerJogador");
//     }
//     for(const auto&  pair: jogadores_map){
//         const auto& _jogador = pair.second;
//         arquivo << _jogador->formatarJogadorComoCSV();
//     }

//     arquivo.close();
//     std::cout << "Jogador: '" << apelido << "' removido com sucesso." << std::endl;
//     return true;
// }
// void GestaoDeJogadores::listarJogadores(){
//     //Recarrega todos dados do arquivo
//     if(!carregarTodoArquivo()){
//         std::cerr << "Não foi possível carregar todo o arquivo para listar jogadores" << std::endl;
//     }
//     //Exibe a lista de jogadores com suas estatisticas
//     for (const auto& pair : jogadores_map){
//         const auto& _jogador = pair.second;
//         //Exibe apelido e nome do jogador
//         std::cout << "[A|N] " << std::setw(15) << std::left << _jogador->getApelido()
//                   << std::left << _jogador->getNome() << std::endl;
//         //Exibe as estatisticas de vitorias e derrotas de cada jogo
//         for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
//             auto estatisticas = _jogador->getEstatisticasDoJogo(static_cast<TipoDeJogo>(i));
//             std::cout << std::setw(10) << std::left << nomeDoJogo(static_cast<TipoDeJogo>(i))
//                       << " - V: " << std::setw(3) << std::left << estatisticas.first   // Vitoria
//                       << " D: " << std::setw(3) << std::left << estatisticas.second  // Derrota
//                       << std::endl;
//         }
//         std::cout << std::endl;
//     }
// }


// //Métodos auxiliares
// std::string GestaoDeJogadores::buscarLinhaDoJogador(const std::string &apelido) const{
//     std::ifstream arquivo(caminhoDoArquivo);
//     std::string linha;
//     // Le o arquivo linha a linha
//     while(std::getline(arquivo, linha)){
//         std::stringstream ss(linha);
//         std::string apelidoNoArquivo;
//         std::getline(ss, apelidoNoArquivo, ',');
//         if(apelidoNoArquivo == apelido){
//             return linha;
//         }
//     }
//     arquivo.close();
//     return "";
// }
// // bool GestaoDeJogadores::apelidoEstaCadastrado(const std::string& apelido) const {
// //     return !buscarLinhaDoJogador(apelido).empty();
// // }

// void GestaoDeJogadores::inserirLinhaNoMapa(const std::string& linha){
//     std::stringstream ss(linha);
//     std::string apelido, nome;
//     std::getline(ss, apelido, ',');
//     std::getline(ss, nome, ',');

//     if (apelido.empty() || nome.empty()) {
//         std::cerr << "Erro: Linha mal formatada no CSV - " << linha << std::endl;
//         return; // Continua processando outras linhas
//     }

//     std::unique_ptr<Jogador> novoJogador(new Jogador(apelido, nome));

//     std::string estatistica;
//     int contaJogos = 0;

//     for(int i=REVERSI;i<TOTAL_DE_JOGOS;i++){
//         int vitoria, derrota;

//         //Le vitorias (se nao conseguir ler a estatistica ou nao colocar em vitoria)
//         if (!std::getline(ss, estatistica, ',') || !(std::istringstream(estatistica) >> vitoria)) {
//             std::cerr << "Erro: Estatísticas mal formatadas para o jogo " << i << " na linha - " << linha << std::endl;
//             return; //Continua processando outras linhas
//         }
//         //Le derrotas
//         if (!std::getline(ss, estatistica, ',') || !(std::istringstream(estatistica) >> derrota)) {
//             std::cerr << "Erro: Estatísticas mal formatadas para o jogo " << i << " na linha - " << linha << std::endl;
//             return; //Continua processando outras linhas
//         }
//         novoJogador->adicionarVitoria(static_cast<TipoDeJogo>(i), vitoria);
//         novoJogador->adicionarDerrota(static_cast<TipoDeJogo>(i), derrota);
//         contaJogos++;
//     }
//     // Verifique se o número de jogos lidos é o esperado
//     if (contaJogos != (TOTAL_DE_JOGOS - REVERSI)) {
//         std::cerr << "Erro: Número incorreto de jogos na linha - " + linha << std::endl;
//         return; //Continua processando outras linhas
//     }
//     jogadores_map[apelido] = std::move(novoJogador);
// }
// std::string GestaoDeJogadores::nomeDoJogo(TipoDeJogo jogo) {
//     switch (jogo) {
//         case REVERSI: return "REVERSI";
//         case LIG4:    return "LIG4";
//         case VELHA:   return "VELHA";
//         default:      return "JOGO_INVALIDO";
//     }
// }

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
    if (!arquivo.is_open()) {
        std::ofstream novoArquivo(caminhoDoArquivo);
        if (!novoArquivo) {
            throw std::runtime_error("Erro: Nao foi possivel criar o arquivo: " + caminhoDoArquivo);
        }
        novoArquivo.close();  // Fecha o arquivo apenas se foi criado com sucesso
    }
}

GestaoDeJogadores::~GestaoDeJogadores() {}

// Métodos para manipulação do arquivo
bool GestaoDeJogadores::carregarTodoArquivo() {
    jogadores_map.clear();
    std::ifstream arquivo(caminhoDoArquivo);

    arquivo.seekg(0, std::ios::end);
    if (arquivo.tellg() == 0) {
        std::cout << "Nenhum jogador cadastrado." << std::endl;
        return false;  // Retorna false se o arquivo estiver vazio
    }
    arquivo.seekg(0, std::ios::beg);

    std::string linha;
    while (std::getline(arquivo, linha)) {
        inserirLinhaNoMapa(linha);
    }
    arquivo.close();
    return true;
}

bool GestaoDeJogadores::carregarDoisJogadores(const std::string &apelido1, const std::string &apelido2) {
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

    // Limpa o buffer de erro antes de prosseguir
    std::cerr.clear();

    jogadores_map.clear();
    inserirLinhaNoMapa(linha1);
    inserirLinhaNoMapa(linha2);
    return true;
}

bool GestaoDeJogadores::inserirNovoJogador(const std::unique_ptr<Jogador>& NovoJogador) {
    std::fstream arquivo(caminhoDoArquivo, std::ios::app | std::ios::out);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo");
    }

    std::string linha = NovoJogador->formatarJogadorComoCSV();
    if (!(arquivo << linha)) {
        arquivo.close();
        throw std::runtime_error("Erro: Falha ao escrever os dados do jogador no arquivo.");
    }
    arquivo.close();
    return true;
}

bool GestaoDeJogadores::atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar_map) {
    if (jogadoresParaAtualizar_map.empty()) {
        std::cerr << "Erro: Mapa de jogadores para atualizar esta vazio." << std::endl;
        return false;
    }

    std::ifstream arquivoEntrada(caminhoDoArquivo);
    if (!arquivoEntrada.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo: " + caminhoDoArquivo);
    }

    std::ofstream arquivoTemp("temp.csv");
    if (!arquivoTemp.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel criar o arquivo temporario.");
    }

    std::string linha;
    while (std::getline(arquivoEntrada, linha)) {
        std::stringstream ss(linha);
        std::string apelidoExistente;
        std::getline(ss, apelidoExistente, ',');

        auto it = jogadoresParaAtualizar_map.find(apelidoExistente);
        if (it != jogadoresParaAtualizar_map.end()) {
            const auto& jogador = it->second;
            arquivoTemp << jogador->formatarJogadorComoCSV();
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
    if (std::rename("temp.csv", caminhoDoArquivo.c_str()) != 0) {
        throw std::runtime_error("Erro: Nao foi possivel renomear o arquivo temporario.");
    }

    return true;
}

// Métodos para gerenciar jogadores
bool GestaoDeJogadores::cadastrarJogador(const std::string &apelido, const std::string &nome) {
    if (!buscarLinhaDoJogador(apelido).empty()) {
        std::cerr << "Erro: jogador com o apelido '" + apelido + "' ja existe. Insira outro." << std::endl;
        return false;
    }

    std::unique_ptr<Jogador> novoJogador(new Jogador(apelido, nome));
    if (!inserirNovoJogador(novoJogador)) {
        throw std::runtime_error("ERRO: Falha ao salvar o jogador no arquivo.");
    }
    std::cout << "Jogador " << apelido << " cadastrado com sucesso." << std::endl;
    return true;
}

bool GestaoDeJogadores::removerJogador(const std::string &apelido) {
    if (!carregarTodoArquivo()) {
        return false;
    }

    if (jogadores_map.find(apelido) == jogadores_map.end()) {
        std::cerr << "Erro: Nao existe Jogador com o apelido: '" + apelido + "'" << std::endl;
        return false;
    }

    jogadores_map.erase(apelido);
    std::ofstream arquivo(caminhoDoArquivo, std::ios::trunc);
    if (!arquivo.is_open()) {
        throw std::runtime_error("ERRO: Nao foi possível abrir o arquivo para removerJogador");
    }

    for (const auto& pair : jogadores_map) {
        const auto& _jogador = pair.second;
        arquivo << _jogador->formatarJogadorComoCSV();
    }

    arquivo.close();
    std::cout << "Jogador: '" << apelido << "' removido com sucesso." << std::endl;
    return true;
}

void GestaoDeJogadores::listarJogadores() {
    if (!carregarTodoArquivo()) {
        std::cerr << "Não foi possível carregar todo o arquivo para listar jogadores" << std::endl;
        return;
    }

    for (const auto& pair : jogadores_map) {
        const auto& _jogador = pair.second;
        std::cout << "\n" << "[A|N] " << std::setw(15) << std::left << _jogador->getApelido()
                  << std::left << _jogador->getNome() << std::endl;

        for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
            auto estatisticas = _jogador->getEstatisticasDoJogo(static_cast<TipoDeJogo>(i));
            std::cout << std::setw(10) << std::left << nomeDoJogo(static_cast<TipoDeJogo>(i))
                      << " - V: " << std::setw(3) << std::left << estatisticas.first
                      << " D: " << std::setw(3) << std::left << estatisticas.second
                      << std::endl;
        }
    }
}

// Métodos auxiliares
std::string GestaoDeJogadores::buscarLinhaDoJogador(const std::string &apelido) const {
    std::ifstream arquivo(caminhoDoArquivo);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo: " + caminhoDoArquivo);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string apelidoNoArquivo;
        std::getline(ss, apelidoNoArquivo, ',');
        if (apelidoNoArquivo == apelido) {
            arquivo.close();
            return linha;
        }
    }
    arquivo.close();
    return "";
}

void GestaoDeJogadores::inserirLinhaNoMapa(const std::string& linha) {
    std::stringstream ss(linha);
    std::string apelido, nome;
    std::getline(ss, apelido, ',');
    std::getline(ss, nome, ',');

    if (apelido.empty() || nome.empty()) {
        std::cerr << "Erro: Linha mal formatada no CSV - " << linha << std::endl;
        return;
    }

    std::unique_ptr<Jogador> novoJogador(new Jogador(apelido, nome));

    std::string estatistica;
    int contaJogos = 0;

    for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
        int vitoria, derrota;

        if (!std::getline(ss, estatistica, ',') || !(std::istringstream(estatistica) >> vitoria)) {
            std::cerr << "Erro: Estatísticas mal formatadas para o jogo " << i << " na linha - " << linha << std::endl;
            return;
        }
        if (!std::getline(ss, estatistica, ',') || !(std::istringstream(estatistica) >> derrota)) {
            std::cerr << "Erro: Estatísticas mal formatadas para o jogo " << i << " na linha - " << linha << std::endl;
            return;
        }
        novoJogador->adicionarVitoria(static_cast<TipoDeJogo>(i), vitoria);
        novoJogador->adicionarDerrota(static_cast<TipoDeJogo>(i), derrota);
        contaJogos++;
    }

    if (contaJogos != (TOTAL_DE_JOGOS - REVERSI)) {
        std::cerr << "Erro: Número incorreto de jogos na linha - " << linha << std::endl;
        return;
    }
    jogadores_map[apelido] = std::move(novoJogador);
}

std::string GestaoDeJogadores::nomeDoJogo(TipoDeJogo jogo) {
    switch (jogo) {
        case REVERSI: return "REVERSI";
        case LIG4:    return "LIG4";
        case VELHA:   return "VELHA";
        default:      return "JOGO_INVALIDO";
    }
}