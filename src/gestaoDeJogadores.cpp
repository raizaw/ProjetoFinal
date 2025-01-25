#include "../include/gestaoDeJogadores.hpp"

//Construtor e destrutor
GestaoDeJogadores::GestaoDeJogadores(const std::string& caminho)
    : caminhoDoArquivo(caminho){
    std::ifstream arquivo(caminhoDoArquivo);
    //Ve se arquivo pode ser aberto
    if(!arquivo.is_open()){
        //Tenta criar o arquivo
        std::ofstream novoArquivo(caminhoDoArquivo);
        if (!novoArquivo) {
            throw std::runtime_error("Erro: Nao foi possivel criar o arquivo: " + caminhoDoArquivo);
        }
    novoArquivo.close();
    }
}
GestaoDeJogadores::~GestaoDeJogadores(){}


//Métodos para manipulação do arquivo
void GestaoDeJogadores::carregarTodoArquivo(){
    jogadores_map.clear(); //Limpa o mapa antes de carregar dados
    std::ifstream arquivo(caminhoDoArquivo);

    //Confere se arquivo esta vazio
    arquivo.seekg(0, std::ios::end); //Vai para o final do arquivo
    if (arquivo.tellg() == 0) {
        throw std::runtime_error("Erro: O arquivo '"+ caminhoDoArquivo +"' esta vazio para carregar dados.");
    } //Se posicao for 0, entao arquivo esta vazio
    arquivo.seekg(0, std::ios::beg); //Volta ao inicio para leitura

    std::string linha;
    while(std::getline(arquivo, linha)){
        inserirLinhaNoMapa(linha);
    }
    arquivo.close();
}
void GestaoDeJogadores::carregarDoisJogadores(const std::string &apelido1,const std::string &apelido2){
    if(apelido1 == apelido2){
        throw std::runtime_error("Erro: Apelidos duplicados foram fornecidos.");
    }
    //Encontra linha dos jogadores no arquivo
    std::string linha1 = buscarLinhaDoJogador(apelido1);
    std::string linha2 = buscarLinhaDoJogador(apelido2);
    jogadores_map.clear(); // Limpa o mapa antes de carregar dados
    //Insere jogadores no mapa limpo
    if(!linha1.empty()){
        inserirLinhaNoMapa(linha1);
    }else{
        throw std::runtime_error("Jogador com apelido '"+ apelido1 + "' nso existe no arquivo");
    }
    if(!linha2.empty()){
        inserirLinhaNoMapa(linha2);
    }else
        throw std::runtime_error("Jogador com apelido '"+ apelido2 + "' nao existe no arquivo");
}
bool GestaoDeJogadores::inserirNovoJogador(const std::unique_ptr<Jogador>& NovoJogador){
    std::fstream arquivo(caminhoDoArquivo, std::ios::app | std::ios::out); //abre o arquivo para leitura e edicao
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo");
    }
    std::string linha = NovoJogador->formatarJogadorComoCSV();
    //Insere novo jogador formatado no final do aruqivo
    if(!(arquivo << linha)){
        arquivo.close();
        throw std::runtime_error("Erro: Falha ao escrever os dados do jogador no arquivo.");
    }
    arquivo.close();
    return true;
}
bool GestaoDeJogadores::atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar_map){
    if (jogadoresParaAtualizar_map.empty()) {
        throw std::runtime_error("Erro: Mapa de jogadores para atualizar esta vazio.");
    }

    std::fstream arquivo(caminhoDoArquivo, std::ios::in | std::ios::out); // Abrir para leitura e escrita
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Nao foi possivel abrir o arquivo: " + caminhoDoArquivo);
    }

    arquivo.seekg(0, std::ios::end); // Vai para o final do arquivo
    if (arquivo.tellg() == 0) {
        throw std::runtime_error("Erro: O arquivo '"+ caminhoDoArquivo +"' esta vazio.");
    } // Se posicao for 0, entao arquivo esta vazio
    arquivo.seekg(0, std::ios::beg); // Volta ao inicio para leitura

    std::string linha;
    std::streampos posAnterior = arquivo.tellg(); // Marca a posicao inicial
    std::set<std::string> jogadoresAtualizados; //Para rastrear quais jogadores foram atualizados

    // Percorre o arquivo linha por linha
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string apelidoExistente;
        std::getline(ss, apelidoExistente, ',');

        // Verifica se o apelido existe no mapa de jogadores a atualizar
        auto it = jogadoresParaAtualizar_map.find(apelidoExistente);
        if (it != jogadoresParaAtualizar_map.end()) {
            const auto& jogador = it->second;
    
            // Move o ponteiro para o inicio da linha atual
            arquivo.clear(); // Limpa flags de erro, se houver
            arquivo.seekp(posAnterior);

            // Sobrescreve a linha com os dados do jogador
            std::string novaLinha = jogador->formatarJogadorComoCSV();
            arquivo << std::setw(novaLinha.size()) << std::left << novaLinha;
            jogadoresAtualizados.insert(apelidoExistente);
        }
        posAnterior = arquivo.tellg(); // Atualiza a posicao da linha atual
    }
    arquivo.close();
    if (jogadoresAtualizados.size() != jogadoresParaAtualizar_map.size()){
        return false;
    }
    return true;
}


//Métodos para gerenciar jogadores
bool GestaoDeJogadores::cadastrarJogador(const std::string &apelido, const std::string &nome){
    //Erro se nome ou apelido forem vazios
    if (apelido.empty() || nome.empty()) {
        throw std::runtime_error("ERRO: Apelido ou nome nao podem ser vazios para o cadastro.");
    }
    //Testa se apelido já existe
    if(!buscarLinhaDoJogador(apelido).empty()){
        throw std::runtime_error("ERRO: jogador com apelido'" + apelido + "' ja existe."); 
    }

    //Cria novo jogador
    auto novoJogador = std::make_unique<Jogador>(nome, apelido);

    //Teste se houve erro no salvamento do jogador no arquivo
    if (!inserirNovoJogador(novoJogador)) {
        throw std::runtime_error("ERRO: Falha ao salvar o jogador no arquivo.");
    }

    std::cout << "Jogador " << apelido << " cadastrado com sucesso." << std::endl;
    return true;
}
bool GestaoDeJogadores::removerJogador(const std::string &apelido){ 
    if(apelido.empty()){
        std::cout << "Erro: Apelido nao pode ser vazio para a remocao." <<std::endl;
    }
    carregarTodoArquivo(); // Coloca todos jogadores do arquivo num mapa
    if(jogadores_map.find(apelido) == jogadores_map.end()){
        std::cout << "Erro: Jogador com apelido '" + apelido + "' nao existe." << std::endl;
    }
    //remove jogador do mapa
    jogadores_map.erase(apelido);
    std::ofstream arquivo(caminhoDoArquivo, std::ios::trunc); //trunc reseta o arquivo para 0 bytes
    if(!arquivo.is_open()){
        throw std::runtime_error("ERRO: Nao foi possível abrir o arquivo");
    }
    for(const auto&  pair: jogadores_map){
        const auto& _jogador = pair.second;
        arquivo << _jogador->formatarJogadorComoCSV();
    }

    arquivo.close();
    std::cout << "Jogador: '" << apelido << "' removido com sucesso." << std::endl;
    return true;
}
void GestaoDeJogadores::listarJogadores(){
    //Recarrega todos dados do arquivo
    carregarTodoArquivo();
    //Exibe a lista de jogadores com suas estatisticas
    for (const auto& pair : jogadores_map){
        const auto& _jogador = pair.second;
        //Exibe apelido e nome do jogador
        std::cout << "LJ [A] " << std::setw(15) << std::left << _jogador->getApelido()
                  << _jogador->getNome() << std::endl;
        //Exibe as estatisticas de vitorias e derrotas de cada jogo
        for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
            auto estatisticas = _jogador->getEstatisticasDoJogo(static_cast<TipoDeJogo>(i));
            std::cout << nomeDoJogo(static_cast<TipoDeJogo>(i))
                      << " - V: " << estatisticas.first   // Vitoria
                      << " D: " << estatisticas.second  // Derrota
                      << std::endl;
        }
        std::cout << std::endl;
    }
}


//Métodos auxiliares
std::string GestaoDeJogadores::buscarLinhaDoJogador(const std::string &apelido) const{
    std::ifstream arquivo(caminhoDoArquivo);
    std::string linha;
    // Le o arquivo linha a linha
    while(std::getline(arquivo, linha)){
        std::stringstream ss(linha);
        std::string apelidoNoArquivo;
        std::getline(ss, apelidoNoArquivo, ',');
        if(apelidoNoArquivo == apelido){
            return linha;
        }
    }
    arquivo.close();
    return "";
}
void GestaoDeJogadores::inserirLinhaNoMapa(const std::string& linha){
    std::stringstream ss(linha);
    std::string apelido, nome;
    std::getline(ss, apelido, ',');
    std::getline(ss, nome, ',');

    if (apelido.empty() || nome.empty()) {
        std::cerr << "Erro: Linha mal formatada no CSV - " << linha << std::endl;
        return; // Continua processando outras linhas
    }

    auto novoJogador = std::make_unique<Jogador>(apelido, nome);
    for(int i=REVERSI;i<TOTAL_DE_JOGOS;i++){
        int vitoria, derrota;
        if (!(ss >> vitoria >> derrota)) {
            throw std::runtime_error("Erro: Estatísticas mal formatadas na linha - " + linha);
        }
        novoJogador->adicionarVitoria(static_cast<TipoDeJogo>(i), vitoria);
        novoJogador->adicionarDerrota(static_cast<TipoDeJogo>(i), derrota);
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