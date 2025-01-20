#include "gestaoDeJogadores.hpp"

//Construtor e destrutor
GestaoDeJogadores::GestaoDeJogadores(const std::string& caminho)
    : caminhoDoArquivo(caminho){} //ver questao do arquivo
GestaoDeJogadores::~GestaoDeJogadores(){}

//Métodos para manipulação do arquivo
void GestaoDeJogadores::carregarTodoArquivo(){
    jogadores_map.clear();
    std::ifstream arquivo = abrirArquivoParaLeitura();

    std::string linha;
    while(std::getline(arquivo, linha)){
        processarLinhaCSV(linha);
    }
}
void GestaoDeJogadores::carregarDoisJogadores(const std::string &apelido1,const std::string &apelido2){
    if(apelido1 == apelido2){
        throw std::runtime_error("Erro: Apelidos duplicados foram fornecidos.");
    }
    if(!jogadores_map.empty()){
        jogadores_map.clear(); //Caso não esteja vazio, limpa o mapa antes de carregar jogadores(nao precisa de delete, por usar unique_ptr)
    }
    std::string linha1 = buscarLinhaDoJogador(apelido1);
    std::string linha2 = buscarLinhaDoJogador(apelido2);

    if(!linha1.empty()){
        processarLinhaCSV(linha1);
    }
    if(!linha2.empty()){
        processarLinhaCSV(linha2);
    }
}
bool GestaoDeJogadores::inserirNovoJogador(const std::unique_ptr<Jogador>& NovoJogador){
    std::fstream arquivo(caminhoDoArquivo, std::ios::app | std::ios::out);
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo");
    }
    arquivo << NovoJogador->formatarJogadorComoCSV();
    arquivo.close();
    return true;
}
bool GestaoDeJogadores::atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar_map){
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

//Métodos para gerenciar jogadores
bool GestaoDeJogadores::cadastrarJogador(const std::string &apelido, const std::string &nome){
    //Erro se nome ou apelido forem vazios
    if (apelido.empty() || nome.empty()) {
        throw std::runtime_error("ERRO: Apelido ou nome não podem ser vazios para o cadastro.");
    }
    //Testa se apelido já existe
    if(jogadorExiste(apelido)){
        throw std::runtime_error("ERRO: jogador com apelido'" + apelido + "' já existe."); 
    }
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
        throw std::runtime_error("ERRO: Apelido não pode ser vazio para a remoção.");
    }
    carregarTodoArquivo();
    if(jogadores_map.find(apelido) == jogadores_map.end()){
        throw std::runtime_error("Erro: Jogador com apelido '" + apelido + "' não existe.");
    }
    //remove jogador do mapa
    jogadores_map.erase(apelido);

    std::ofstream arquivo(caminhoDoArquivo, std::ios::trunc); //trunc reseta o arquivo para 0 bytes
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo");
    }
    for(const auto&  [_apelido, _jogador]: jogadores_map){
        arquivo << _jogador->formatarJogadorComoCSV();
    }

    arquivo.close();
    std::cout << "Jogador: '" << apelido << "' removido com sucesso." << std::endl;
    return true;
}
void GestaoDeJogadores::listarJogadores(){
    //Recarrega todos dados do arquivo
    carregarTodoArquivo();
     //Exibe a lista de jogadores com suas estatísticas
    for (const auto& [_apelido, _jogador] : jogadores_map) {
        std::cout << "LJ [A] " << std::setw(15) << std::left << _jogador->getApelido()
                  << _jogador->getNome() << std::endl;
        // Exibe as estatísticas de vitórias e derrotas de cada jogo
        for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
            auto estatisticas = _jogador->getEstatisticasDoJogo(static_cast<TipoDeJogo>(i));
            std::cout << NomeDoJogo(static_cast<TipoDeJogo>(i))
                      << " - V: " << estatisticas.first   // Vitória
                      << " D: " << estatisticas.second  // Derrota
                      << std::endl;
        }
        std::cout << std::endl;
    }
}

//Métodos auxiliares
std::ifstream GestaoDeJogadores::abrirArquivoParaLeitura() const{
    std::ifstream arquivo(caminhoDoArquivo);
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo: " + caminhoDoArquivo);
    }
    if(arquivo.peek() == EOF){
        throw std::runtime_error("Erro: O arquivo '"+ caminhoDoArquivo +"'está vazio.");
    }
    return arquivo;
}
std::string GestaoDeJogadores::buscarLinhaDoJogador(const std::string &apelido) const{
    std::ifstream arquivo = abrirArquivoParaLeitura();
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
void GestaoDeJogadores::processarLinhaCSV(const std::string& linha){
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
std::string GestaoDeJogadores::NomeDoJogo(TipoDeJogo jogo) {
    switch (jogo) {
        case REVERSI: return "REVERSI";
        case LIG4:    return "LIG4";
        case VELHA:   return "VELHA";
        default:      return "JOGO_INVALIDO";
    }
}