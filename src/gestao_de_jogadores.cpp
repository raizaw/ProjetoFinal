#include "gestao_de_jogadores.hpp"

GestaoDeJogadores::GestaoDeJogadores(const std::string& caminho)
    : caminhoDoArquivo(caminho){} //ver questao do arquivo
GestaoDeJogadores::~GestaoDeJogadores(){}

std::string GestaoDeJogadores::buscarLinhaDoJogador(const std::string &apelido) const{
    std::ifstream arquivo(caminhoDoArquivo);
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo");
    }
    if(arquivo.peek() == EOF){
        throw std::runtime_error("Erro: O arquivo está vazio.");
    }

    std::ifstream arquivo(caminhoDoArquivo);
    std::string linha;
    while(std::getline(arquivo, linha)){
        std::stringstream ss(linha);
        std::string apelidoExistente;
        std::getline(ss, apelidoExistente, ',');
        if(apelidoExistente == apelido){
            return linha;
        }
    }
    return "";
}
bool GestaoDeJogadores::jogadorExiste(const std::string& apelido) const{
    return !buscarLinhaDoJogador(apelido).empty();
}
void GestaoDeJogadores::processarLinha(const std::string& linha){
    std::stringstream ss(linha);
    std::string apelido, nome;
    std::getline(ss, apelido, ',');
    std::getline(ss, nome, ',');

    auto novoJogador = std::make_unique<Jogador>(apelido, nome);

    for(int i=REVERSI;i<TOTAL_DE_JOGOS;i++){
        int vitoria, derrota;
        if(!(ss >> vitoria >> derrota)){
            std::cerr << "ERRO: Formato inválido na linha: " << linha << std::endl;
            return;
        }
        novoJogador->adicionarVitoria(static_cast<TipoDeJogo>(i), vitoria);
        novoJogador->adicionarDerrota(static_cast<TipoDeJogo>(i), derrota);
    }
    jogadores_map[apelido] = std::move(novoJogador);
}
void GestaoDeJogadores::carregarTodoArquivo(){
    std::ifstream arquivo(caminhoDoArquivo);
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo");
    }
    if(arquivo.peek() == EOF){
        throw std::runtime_error("Erro: O arquivo está vazio.");
    }
    if(!jogadores_map.empty()){
        jogadores_map.clear(); //Caso não esteja vazio, limpa o mapa antes de carregar jogadores(nao precisa de delete, por usar unique_ptr)
    }
    std::string linha;
    while(std::getline(arquivo, linha)){
        processarLinha(linha);
    }
}
void GestaoDeJogadores::carregarDoisJogadores(const std::string &apelido1,const std::string &apelido2){
    if(apelido1 == apelido2){
        throw std::runtime_error("Erro: Apelidos duplicados foram fornecidos.");
    }
    std::ifstream arquivo(caminhoDoArquivo);
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo");
    }
    if(arquivo.peek() == EOF){
        throw std::runtime_error("Erro: O arquivo está vazio.");
    } 
    if(!jogadores_map.empty()){
        jogadores_map.clear(); //Caso não esteja vazio, limpa o mapa antes de carregar jogadores(nao precisa de delete, por usar unique_ptr)
    }
    
    std::string linha1 = buscarLinhaDoJogador(apelido1);
    std::string linha2 = buscarLinhaDoJogador(apelido2);

    if(!linha1.empty()){
        processarLinha(linha1);
    }
    if(!linha2.empty()){
        processarLinha(linha2);
    }
}
bool GestaoDeJogadores::salvarNovoJogador(const std::unique_ptr<Jogador>& NovoJogador){
    std::fstream arquivo(caminhoDoArquivo, std::ios::app | std::ios::out);
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo");
    }
    arquivo << NovoJogador->formatarJogadorComoCSV();
    arquivo.close();
    return true;
}
bool GestaoDeJogadores::atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar_map) {
    if (jogadoresParaAtualizar_map.empty()) {
        throw std::runtime_error("Erro: Mapa de jogadores para atualizar está vazio.");
    }

    std::fstream arquivo(caminhoDoArquivo, std::ios::in | std::ios::out); // Abrir para leitura e escrita
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo.");
    }

    // Verifica se o arquivo está vazio
    arquivo.seekg(0, std::ios::end);
    if (arquivo.tellg() == 0) {
        throw std::runtime_error("Erro: O arquivo está vazio.");
    }
    arquivo.seekg(0, std::ios::beg); // Volta ao início para leitura

    std::string linha;
    std::streampos posAnterior = arquivo.tellg(); // Marca a posição inicial
    bool atualizado = false;

    // Percorre o arquivo linha por linha
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string apelidoExistente;
        std::getline(ss, apelidoExistente, ',');

        // Verifica se o apelido existe no mapa de jogadores a atualizar
        auto it = jogadoresParaAtualizar_map.find(apelidoExistente);
        if (it != jogadoresParaAtualizar_map.end()) {
            const auto& jogador = it->second;
    
            // Move o ponteiro para o início da linha atual
            arquivo.clear(); // Limpa flags de erro, se houver
            arquivo.seekp(posAnterior);

            // Sobrescreve a linha com os dados do jogador
            std::string novaLinha = jogador->formatarJogadorComoCSV();
            arquivo << std::setw(novaLinha.size()) << std::left << novaLinha;
            atualizado = true;
        }
        posAnterior = arquivo.tellg(); // Atualiza a posição da linha atual
    }
    arquivo.close();
    if (!atualizado) {
        throw std::runtime_error("Nenhuma linha do arquivo foi atualizada.");
    }
    return atualizado;
}
bool GestaoDeJogadores::cadastrarJogador(const std::string &apelido, const std::string &nome){
    //Erro se nome ou apelido forem vazios
    if (apelido.empty() || nome.empty()) {
        throw std::runtime_error("ERRO: Apelido ou nome não podem ser vazios.");
    }
    //Testa se apelido já existe
    if(jogadorExiste(apelido)){
        throw std::runtime_error("ERRO: jogador com apelido'" + apelido + "' já existe."); 
    }
    auto novoJogador = std::make_unique<Jogador>(nome, apelido);
    //Teste se houve erro no salvamento do jogador no arquivo
    if (!salvarNovoJogador(novoJogador)) {
        throw std::runtime_error("ERRO: Falha ao salvar o jogador no arquivo.");
    }

    std::cout << "Jogador " << apelido << " cadastrado com sucesso." << std::endl;
    return true;
}


    //AINDA FALTA atualizar alterações nas implemetações dos métodos abaixo

bool GestaoDeJogadores::removerJogador(const std::string &apelido){ 
    std::streampos posicaoJogador;
    //Testa se o jogador existe no arquivo, e obtém a posição da linha
    if (!buscaPorApelido(apelido, &posicaoJogador)) {
        std::cout << "ERRO: Jogador com apelido '" << apelido << "' não encontrado." << std::endl;
        return false;
    }

    // Abrir o arquivo original para leitura e o temporário para escrita
    std::ifstream arquivoOriginal(caminhoDoArquivo);
    if (!arquivoOriginal.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return false;
    }

    std::ofstream arquivoTemporario("temp.csv");
    if (!arquivoTemporario.is_open()) {
        std::cerr << "Erro ao criar o arquivo temporário." << std::endl;
        return false;
    }

    std::string linha;
    bool jogadorRemovido = false;

    //Copiar todo o arquivo, exceto a linha do jogador a ser removido
    std::streampos posicaoAtual = arquivoOriginal.tellg();
    while (std::getline(arquivoOriginal, linha)) {
        if(posicaoAtual == posicaoJogador) {
            //Linha encontrada para o jogador a ser removido, não copiamos ela
            jogadorRemovido = true;
        } else {
            // Copia as outras linhas para o arquivo temporário, garantindo o '\n' no final de cada linha
            if (!linha.empty() && linha[linha.size() - 1] != '\n') {
                arquivoTemporario << linha << "\n";
            } else {
                arquivoTemporario << linha;
            }       
        }
        posicaoAtual = arquivoOriginal.tellg(); // Atualiza a posição no arquivo original
    }

    arquivoOriginal.close();
    arquivoTemporario.close();

    if (!jogadorRemovido) {
        std::cerr << "ERRO: jogador com apelido '" << apelido << "' não encontrado." << std::endl;
        return false;
    }

    //Substitui o arquivo original pelo temporário
    std::remove(caminhoDoArquivo.c_str());
    std::rename("temp.csv", caminhoDoArquivo.c_str());

    std::cout << "Jogador '" << apelido << "' removido com sucesso." << std::endl;
    return true;
}
void GestaoDeJogadores::listarJogadores() {
    //Recarrega todos dados do arquivo
    carregarDoArquivo();

    //Ordena os jogadores por Apelido e, em caso de empate, por Nome
    std::sort(jogadores_vec.begin(), jogadores_vec.end(), [](Jogador* a, Jogador* b) {
        if (a->getApelido() == b->getApelido()) {
            return a->getNome() < b->getNome();  //Desempate pelo Nome
        }
        return a->getApelido() < b->getApelido();  //Ordena pelo Apelido
    });

     //Exibe a lista de jogadores com suas estatísticas
    for (auto& _jogador : jogadores_vec) {
        std::cout << "LJ [A] " << std::setw(15) << std::left << _jogador->getApelido()
                  << _jogador->getNome() << std::endl;
        // Exibe as estatísticas de vitórias e derrotas de cada jogo
        for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
            auto estatisticas = _jogador->getEstatisticasDoJogo(static_cast<TipoDeJogo>(i));
            std::cout << getNomeDoJogo(static_cast<TipoDeJogo>(i))
                      << " - V: " << estatisticas.first   // Vitória
                      << " D: " << estatisticas.second  // Derrota
                      << std::endl;
        }
        std::cout << std::endl;
    }
}

std::string GestaoDeJogadores::getNomeDoJogo(TipoDeJogo jogo) {
    switch (jogo) {
        case REVERSI: return "REVERSI";
        case LIG4:    return "LIG4";
        case VELHA:   return "VELHA";
        default:      return "JOGO_INVALIDO";
    }
}
bool GestaoDeJogadores::buscaPorApelido(const std::string& apelido, std::streampos* posicao /*= nullptr*/) const {
    std::ifstream arquivo(caminhoDoArquivo);
    if(!arquivo.is_open()){
        throw("Erro: Não foi possível abrir o arquivo");
    }else if(arquivo.peek() == EOF){
        throw("Erro: O arquivo está vazio para buscar jogador por apelido.");
    }

    std::string linha;
    std::streampos posAnterior = arquivo.tellg();

    while(std::getline(arquivo, linha)){
        std::stringstream ss(linha);
        std::string _apelidoExistente;
        std::getline(ss, _apelidoExistente, ',');

        if(_apelidoExistente == apelido){
            if(posicao){
                *posicao = posAnterior; //Armazena a posição se solicitada
            }
            return true; //Apelido encontrado
        }
        posAnterior = arquivo.tellg(); // Atualiza posição anterior
    }

    return false; // Apelido não encontrado
}