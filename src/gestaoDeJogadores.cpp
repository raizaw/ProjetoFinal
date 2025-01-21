#include "../include/gestaoDeJogadores.hpp"

//Construtor e destrutor
GestaoDeJogadores::GestaoDeJogadores(const std::string& caminho)
    : caminhoDoArquivo(caminho){} //ver questao do arquivo
GestaoDeJogadores::~GestaoDeJogadores(){}

//Métodos para manipulação do arquivo
    /*Método carregarTodoArquivo():
    - Objetivo: Carregar dados de todos jogadores do arquivo para um mapa.
    - Lança exceções se: Método auxiliar lançar.
    - Métodods auxiliares utilizados: Gestão de Jogadores: abrirArquivoParaLeitura() e inserirLinhaNoMapa().
    - Testes:
      - Garantir que o mapa é limpo antes de carregar os dados.
      - Verificar se todos os jogadores são corretamente adicionados ao mapa.
      - Testar o comportamento com arquivos vazios, corrompidos ou contendo dados inconsistentes.
    - A olhar:
      -
    - Exemplo de uso:
      file.cpp
      GestaoDeJogadores gestao("jogadores.csv");
      try {
          gestao.carregarTodoArquivo();
          std::cout << "Arquivo carregado com sucesso!" << std::endl;
      } catch (const std::exception& e) {
          std::cerr << "Erro ao carregar o arquivo: " << e.what() << std::endl;
      }
    */
void GestaoDeJogadores::carregarTodoArquivo(){
    jogadores_map.clear(); // Limpa o mapa antes de carregar dados
    std::ifstream arquivo = abrirArquivoParaLeitura();
    std::string linha;
    while(std::getline(arquivo, linha)){
        inserirLinhaNoMapa(linha);
    }
    arquivo.close();
}
    /*Método carregarDoisJogadores():
    - Objetivo: Carregar dados de dois jogadores, identificados pelos apelidos, para um mapa.
    - Recebe: Apelidos de dois jogadores.
    - Lança exceções se:
      - Os apelidos fornecidos forem iguais.
      - Os apelidos não forem encontrados usar buscarLinhaDoJogador().
      - Método auxiliar lançar.
    - Métodos auxiliares utilizados: Gestão de Jogadores: buscarLinhaDoJogador() e inserirLinhaNoMapa().
    - Testes:
      - Apelidos duplicados.
      - Garantir que o mapa é limpo antes de carregar os dados.
      - Verificar o comportamento ao passar apelidos inválidos ou inexistentes.
    - A olhar:
        -
    - Exemplo de uso:
      file.cpp
      GestaoDeJogadores gestao("jogadores.csv");
      try {
          gestao.carregarDoisJogadores("apelido1", "apelido2");
          std::cout << "Jogadores carregados com sucesso!" << std::endl;
      } catch (const std::runtime_error& e) {
          std::cerr << "Erro ao carregar jogadores: " << e.what() << std::endl;
      }
    */
void GestaoDeJogadores::carregarDoisJogadores(const std::string &apelido1,const std::string &apelido2){
    if(apelido1 == apelido2){
        throw std::runtime_error("Erro: Apelidos duplicados foram fornecidos.");
    }
    jogadores_map.clear(); // Limpa o mapa antes de carregar dados
    //Encontra linha dos jogadores no arquivo
    std::string linha1 = buscarLinhaDoJogador(apelido1);
    std::string linha2 = buscarLinhaDoJogador(apelido2);
    //Insere no mapa
    if(!linha1.empty()){
        inserirLinhaNoMapa(linha1);
    }else{
        throw std::runtime_error("Jogador com apelido '"+ apelido1 + "' não exxiste no arquivo");
    }
    if(!linha2.empty()){
        inserirLinhaNoMapa(linha2);
    }else
        throw std::runtime_error("Jogador com apelido '"+ apelido2 + "' não exxiste no arquivo");
}
    /*Método inserirNovoJogador():
    - Objetivo: Inserir os dados de um novo jogador no fim do arquivo especificado, utilizando o formato CSV.
    - Recebe: Ponteiro para um objeto Jogador.
    - Retorna: `true` se o jogador for inserido com sucesso no arquivo.
    - Lança exceções se:
      - O arquivo não puder ser aberto.
      - Não for possível escrever (inserir)
    - Métodos auxiliares: Jogador::formatarJogadorComoCSV().
    - Testes:
      - Garantir que o jogador é adicionado ao arquivo no formato correto.
      - Validação da escrita.
    - A olhar:
      -
    - Exemplo de uso:
        file.cpp
        std::unique_ptr<Jogador> novoJogador = std::make_unique<Jogador>("Nome", 25, "Posição");
        GestaoDeJogadores gestao("jogadores.csv");
        try {
            if (gestao.inserirNovoJogador(novoJogador)) {
                std::cout << "Novo jogador inserido com sucesso!" << std::endl;
            }
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    */
bool GestaoDeJogadores::inserirNovoJogador(const std::unique_ptr<Jogador>& NovoJogador){
    std::fstream arquivo(caminhoDoArquivo, std::ios::app | std::ios::out); //abre o arquivo para leitura e edicao
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo");
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
    /*Método atualizarEstatisticas():
    - Objetivo: Substituir as linhas correspondentes a cada jogador no arquivo pelos seus dados atualizados.
    - Recebe: Mapa dos jogadores a atualizar.
    - Retorna:
      - true: se todos jogadores foram atualizados.
      - false: caso contrário.
    - Lança exceções se:
      - O mapa fornecido estiver vazio.
      - O arquivo não puder ser aberto ou estiver vazio.
    - Testes:
      - Mapa vazio.
      - Arquivo aberto ou vazio.
      - Garantir que apenas as linhas correspondentes no arquivo são atualizadas.
    - A olhar:
      - Avaliar como o método lida com arquivos grandes.
    - Exemplo de uso:
        Após termino das partidas, quando mapa gerado ao carregarDoisJogadores() se torna jogadoresParaAtualizar_map
    */
bool GestaoDeJogadores::atualizarEstatisticas(const std::map<std::string, std::unique_ptr<Jogador>>& jogadoresParaAtualizar_map){
    if (jogadoresParaAtualizar_map.empty()) {
        throw std::runtime_error("Erro: Mapa de jogadores para atualizar está vazio.");
    }

    std::fstream arquivo(caminhoDoArquivo, std::ios::in | std::ios::out); // Abrir para leitura e escrita
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo: " + caminhoDoArquivo);
    }

    arquivo.seekg(0, std::ios::end); // Vai para o final do arquivo
    if (arquivo.tellg() == 0) {
        throw std::runtime_error("Erro: O arquivo '"+ caminhoDoArquivo +"' está vazio.");
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
    /*Método cadastrarJogador():
    - Objetivo: Criar um novo jogador e o salvar no arquivo especificado.
    - Recebe:
      - `apelido` do jogador a ser cadastrado.
      - `nome` do jogador a ser cadastrado.
    - Retorna:
      - `true` se o jogador for cadastrado e salvo com sucesso.
    - Lança exceções se:
      - O nome ou apelido forem vazios.
      - Já existir um jogador com o apelido fornecido.
      - Houver falha ao tentar salvar o jogador no arquivo.
      - Método auxiliar lançar.
    - Auxiliares utilizados: buscarLinhaDoJogador, inserirNovoJogador.
    - Testes:
      - Apelido ou nome vazios.
      - Apelido repetido.
      - Jogador é salvo com sucesso e quando ocorre uma falha.
      - Mensagem de sucesso é exibida quando o cadastro é bem-sucedido.
    - A olhar:
    - Exemplo de uso:
        file.cpp
        GestaoDeJogadores gestao("jogadores.csv");
        try {
            if (gestao.cadastrarJogador("apelido123", "Jogador Nome")) {
                std::cout << "Cadastro realizado!" << std::endl;
            }
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    */
bool GestaoDeJogadores::cadastrarJogador(const std::string &apelido, const std::string &nome){
    //Erro se nome ou apelido forem vazios
    if (apelido.empty() || nome.empty()) {
        throw std::runtime_error("ERRO: Apelido ou nome não podem ser vazios para o cadastro.");
    }
    //Testa se apelido já existe
    if(!buscarLinhaDoJogador(apelido).empty()){
        throw std::runtime_error("ERRO: jogador com apelido'" + apelido + "' já existe."); 
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
    /* Método removerJogador(): 
    - Objetivo: Remover jogador do arquivo de armazenamento.
    - Recebe: Apelido o jogador a ser removido.
    - Retorna: `true` se o jogador for removido com sucesso.
    - Lança exceções se:
      - O apelido fornecido for vazio.
      - O jogador com o apelido especificado não existir no mapa.
      - O arquivo não puder ser aberto para reescrita.
      - Método auxiliar lançar.
    - Métodos auxiliares utilizados:
      - Gestão de Jogadores: carregarTodoArquivo().
      - Jogador: formatarJogadorComoCSV().
    - Testes:
      - Apelido fornecido vazio ou existe.
      - Garantir que o mapa é limpo antes de carregar os dados.
      - Arquivo aberto
      - Mensagem de sucesso é exibida quando a remoção é bem-sucedido.
    - A olhar:
      -
    - Exemplo de uso:
        GestaoDeJogadores gestao;
        gestao.removerJogador("apelido_jogador");
    */
bool GestaoDeJogadores::removerJogador(const std::string &apelido){ 
    if(apelido.empty()){
        throw std::runtime_error("ERRO: Apelido não pode ser vazio para a remoção.");
    }
    carregarTodoArquivo(); // Coloca todos jogadores do arquivo num mapa
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
    /* Método listarJogadores(): 
    - Objetivo: Exibir uma lista de todos os jogadores registrados, junto com suas estatísticas de vitórias e derrotas para cada jogo.
        OBS:Como o mapa armazena em ordem das chaves (apelidos), basta exibir jogadores na ordem do mapa.
    - Lança exceções se: Método auxiliar lançar.
    - Métodos auxiliares utilizados:
      - Gestão de Jogadores: carregarTodoArquivo(), nomeDoJogo().
      - Jogador: getApelido(), getNome(), getEstatisticasDoJogo().
    - Testes:
      - Garante exibir todos os jogadores com suas respectivas estatísticas.
    - A olhar:
      -
    - Exemplo de uso:
        GestaoDeJogadores gestao;
        gestao.listarJogadores();
    */
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
            std::cout << nomeDoJogo(static_cast<TipoDeJogo>(i))
                      << " - V: " << estatisticas.first   // Vitória
                      << " D: " << estatisticas.second  // Derrota
                      << std::endl;
        }
        std::cout << std::endl;
    }
}

//Métodos auxiliares
    /* Método abrirArquivoParaLeitura(): 
    - Objetivo: Abrir um arquivo para leitura e verificar se ele está acessível e não vazio.
    - Retorna: arquivo aberto e válido para leitura.
    - Lança exceções se:
      - O arquivo não puder ser aberto.
      - O arquivo estiver vazio.
    - Testes:
      - Arquivo aberto e vazio
    - A olhar:
      - Garantir que o arquivo seja fechado corretamente após o uso.
      - Validar o caminho do arquivo antes de chamar este método.
    - Exemplo de uso:
      GestaoDeJogadores gestao;
      std::ifstream arquivo = gestao.abrirArquivoParaLeitura();
      arquivo.close();
      // Use o arquivo para operações de leitura, lembre sempre de FECHAR o aquivo, pois o método apenas abre.
    */
std::ifstream GestaoDeJogadores::abrirArquivoParaLeitura() const{
    std::ifstream arquivo(caminhoDoArquivo);
    if(!arquivo.is_open()){
        throw std::runtime_error("Erro: Não foi possível abrir o arquivo: " + caminhoDoArquivo);
    }

    arquivo.seekg(0, std::ios::end); // Vai para o final do arquivo
    if (arquivo.tellg() == 0) {
        throw std::runtime_error("Erro: O arquivo '"+ caminhoDoArquivo +"' está vazio.");
    } // Se posicao for 0, entao arquivo esta vazio

    arquivo.seekg(0, std::ios::beg); // Volta ao inicio para leitura

    return arquivo;
}
    /* Método buscarLinhaDoJogador(): 
    - Objetivo: Localizar e retornar a linha correspondente a um jogador específico no arquivo, identificada pelo apelido.
    - Recebe: O apelido do jogador a ser procurado.
    - Retorna:
      - Uma std::string contendo a linha completa do jogador correspondente no arquivo, caso encontrada.
      - Uma string vazia (""), caso o jogador não seja encontrado.
    - Lança exceções se:
      - Método auxiliar lançar.
    - Métodos auxiliares utilizados: Gestão de Jogadores::abrirArquivoParaLeitura().
    - Testes:
      - Apelido existente no arquivo.
    - A olhar:
      - Certificar que a comparação do apelido não falha devido a espaços ou caracteres especiais.
    - Exemplo de uso:
        GestaoDeJogadores gestao;
        std::string linha = gestao.buscarLinhaDoJogador("apelidoExemplo");
        if (!linha.empty()) {
            std::cout << "Linha encontrada: " << linha << std::endl;
        } else {
            std::cout << "Jogador não encontrado." << std::endl;
        }
    */
std::string GestaoDeJogadores::buscarLinhaDoJogador(const std::string &apelido) const{
    std::ifstream arquivo = abrirArquivoParaLeitura();
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
    /* Método inserirLinhaNoMapa(): 
    - Objetivo: Processar uma linha do arquivo CSV e inserir as informações no mapa de jogadores.
    - Recebe: A linha CSV do arquivo contendo as informações de um jogador.
    - Lança exceções se: As estatísticas do jogador na linha estiverem mal formatadas (não forem números inteiros).
    - Métodos auxiliares utilizados: Jogador: adicionarVitoria(), adicionarDerrota().
    - Testes:
      - Linha bem formatada com dados completos
    - A olhar:
      -
    - Exemplo de uso:
        GestaoDeJogadores gestao;
        std::string linha;
        while(std::getline(arquivo, linha)){
            inserirLinhaNoMapa(linha);
        }
    */
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
    /* Método nomeDoJogo(): 
    - Objetivo: Retornar o nome de um jogo baseado no tipo enumerado.
    - Recebe: O tipo de jogo a ser convertido para nome.
    - Retorna:O nome do jogo correspondente ao tipo, ou "JOGO_INVALIDO" se o tipo não for válido.
    - A olhar:
      -
    - Exemplo de uso:
       TipoDeJogo jogo = REVERSI;
       std::string nome = nomeDoJogo(jogo);
       std::cout << nome << std::endl;  // Imprime "REVERSI"
    */
std::string GestaoDeJogadores::nomeDoJogo(TipoDeJogo jogo) {
    switch (jogo) {
        case REVERSI: return "REVERSI";
        case LIG4:    return "LIG4";
        case VELHA:   return "VELHA";
        default:      return "JOGO_INVALIDO";
    }
}