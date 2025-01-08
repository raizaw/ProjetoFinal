#include "teste.hpp"

GestaoDeJogadores::GestaoDeJogadores(const std::string& caminho)
    : caminhoDoArquivo(caminho){
    carregarDoArquivo();
}
GestaoDeJogadores::~GestaoDeJogadores(){
    //Libera a memoria de todos os jogadores alocados dinamicamente
    for(auto* _jogador : jogadores_vec){
        delete _jogador;
    }
}

/*
Método carregarDoArquivo() :
- Se (0) nenhum apelido for fornecido, carrega todos os jogadores; (usado na listagem)
- Se (1) um apelido for fornecido, carrega o jogador correspondente a esse apelido; 
- Se (2) dois apelidos forem fornecidos, carrega ambos os jogadores correspondentes; (usado nos jogos para atualizar)
Caso o apelido do jogador seja encontrado no arquivo, suas estatísticas são carregadas.
Testes: abertura de arquivo, arquivo esta vazio, vetor de jogadores não esta vazio, se linha está desformatada.
A olhar: como tratar returns!
*/
void GestaoDeJogadores::carregarDoArquivo(const std::string& apelido1 /* ="" */, const std::string& apelido2 /* ="" */){
    std::ifstream arquivo(caminhoDoArquivo);
    //Testa se eh possivel abrir arquivo
    if(!arquivo.is_open()){
        std::cout << "Erro: Não foi possível abrir o arquivo.\n";
        return;
    }
    //Testa se o arquivo esta vazio
    if (arquivo.peek() == EOF) { 
        std::cout << "O arquivo está vazio.\n"; 
        return; 
    }
    //Garante que jogadores_vec esteja vazio antes de carregar dados do arquivo
    if(!jogadores_vec.empty()){
        for(auto* _jogador : jogadores_vec){
            delete _jogador;
        }
        jogadores_vec.clear();
    }

    std::string linha;

    while(std::getline(arquivo, linha)){
        std::string apelido, nome;
        int vitoria, derrota;
        std::stringstream ss(linha);

        std::getline(ss, apelido, ',');
        std::getline(ss, nome, ',');

        //Se ambos os apelidos estiverem vazios, processa todos os jogadores. É usado em listarJogadores()
        if(apelido1.empty() && apelido2.empty()){
            Jogador* novoJogador = new Jogador(apelido, nome);
            //Leitura das estatisticas
            for (int i = REVERSI; i < TOTAL_DE_JOGOS; i++) {
                if (!(ss >> vitoria >> derrota)) {
                    std::cerr << "ERRO: Formato inválido na linha: " << linha << std::endl;
                    delete novoJogador;
                    break; 
                }
                novoJogador->adicionarVitoria(static_cast<TipoDeJogo>(i), vitoria);
                novoJogador->adicionarDerrota(static_cast<TipoDeJogo>(i), derrota);
            }
            jogadores_vec.push_back(novoJogador);
        }
        //Se o apelido for igual ao apelido1 ou apelido2, carrega o jogador desejado. Será usado nas partidas 
        else if(apelido == apelido1 || apelido == apelido2){
            Jogador* novoJogador = new Jogador(apelido, nome);
            //Leitura das estatisticas
            for(int i=REVERSI;i<TOTAL_DE_JOGOS;i++){
                if(!(ss >> vitoria >> derrota)){
                    std::cerr << "ERRO: Formato inválido na linha: " << linha << std::endl;
                    break; 

                    /*
                    Como tratar esta exceção? continue ou break?
                    ver se é melhor quebrar o loop, se sim o que fazer
                    */

                }
                novoJogador->adicionarVitoria(static_cast<TipoDeJogo>(i), vitoria);
                novoJogador->adicionarDerrota(static_cast<TipoDeJogo>(i), derrota);
            }
            jogadores_vec.push_back(novoJogador);
        }
        if (!apelido2.empty() && jogadores_vec.size() == 2) {
            break; //Dois jogadores encontrados
        }
        if (apelido2.empty() && jogadores_vec.size() == 1) {
            break; //Um jogador encontrado
        }
    }
    arquivo.close();
}
/*
Método salvarNovasEstatisticas() :
Recebe um vetor de ponteiros para Jogador e atualiza os jogadores necessários
Testes: abertura de arquivo, vetor passado vazio, se ponteiros do vetor passado são nulos
A olhar:
*/
void GestaoDeJogadores::salvarNovasEstatisticas(const std::vector<Jogador*> &jogadoresParaAtualizar){
    //Testa se vetor esta vazio
    if (jogadoresParaAtualizar.empty()) {
        std::cerr << "ERRO: Nenhum jogador fornecido para atualização." << std::endl;
        return;
    }
    std::fstream arquivo(caminhoDoArquivo, std::ios::in | std::ios::out); //abrir arquivo para ler e escrever   
    //Testa se eh possivel abrir arquivo
    if(!arquivo.is_open()){
        std::cout << "Erro: Não foi possível abrir o arquivo para salvar." << std::endl;
        return;
    }
    //Testa se os ponteiros para os jogadores sao nulos
    for (const auto* _jogador : jogadoresParaAtualizar){
        if (_jogador == nullptr){
            std::cerr << "ERRO: Jogador inválido no vetor de atualização." << std::endl;
            continue;
        } 
        // Localiza a posicao do jogador no arquivo
        std::streampos pos;
        if(buscaPorApelido(_jogador->getApelido(), &pos)){
            //Move o ponteiro para a posição da linha encontrada
            arquivo.clear();
            arquivo.seekp(pos); //Move para a posicao do jogador
            //Reescreve a linha com as novas estatisticas
            std::string linhaAtualizada = _jogador->formatarJogadorComoCSV();
            arquivo << std::setw(linhaAtualizada.size()) << std::left << linhaAtualizada;
        }
    }
    arquivo.close();
}
/*
Método salvarNovoJogador() :
Recebe um ponteiro para jogador e salva no final do arquivo
OBS: cadastrarJogador() já confere se há um igual
Testes:abertura de arquivo
A olhar:
*/
bool GestaoDeJogadores::salvarNovoJogador(const Jogador* novoJogador){
    std::fstream arquivo(caminhoDoArquivo, std::ios::app | std::ios::out); //abrir arquivo para anexar e escrever
    //Testa se eh possivel abrir arquivo
    if(!arquivo.is_open()){
        std::cout << "Erro: Não foi possível abrir o arquivo para salvar." << std::endl;
        return false;
    }    
    arquivo << novoJogador->formatarJogadorComoCSV();
    arquivo.close();
    return true;
}
/*
Método cadastrarJogador() :
Recebe um apelido e um nome, cria um Jogador e adiciona no arquivo.
Testes: strings vazias, apelido repetido, erro no salvamento do joador
A olhar: 
- Adicionar uma validação para garantir que o apelido e o nome não sejam vazios e sigam algum formato esperado.
//std::cout << "ERRO: dados incorretos" <<std::endl;
- Melhorar mensagens de erro;
*/
bool GestaoDeJogadores::cadastrarJogador(const std::string &apelido, const std::string &nome){
    //Erro se nome ou apelido forem vazios
    if (apelido.empty() || nome.empty()) {
        std::cout << "ERRO: Apelido e nome não podem ser vazios." << std::endl;
        return false;
    }
    //Testa se apelido já existe
    if(buscaPorApelido(apelido) == true){
        std::cout << "ERRO: jogador repetido" << std::endl; 
        return false;
    }
    
    Jogador* novoJogador = new Jogador(nome, apelido);
    //Teste se houve erro no salvamento do jogador no arquivo
    if (!salvarNovoJogador(novoJogador)) {
        std::cerr << "ERRO: Falha ao salvar o jogador no arquivo." << std::endl;
        delete novoJogador;
        return false;
    }
    std::cout << "Jogador " << apelido << " cadastrado com sucesso" << std::endl;
    return true;
}

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
/*
Método listarJogadores() :
- Chama carregarDoArquivo para garantir que todos os jogadores são carregados antes de listar.
- Ordena os jogadores por apelido e nome.
- Exibe as estatísticas de cada jogador.
*/
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
/*
Método getNomeDoJogo() :
Utiliza do enum TipoDeJogo para retornar o nome do jogo de acordo com seu enum
*/
std::string GestaoDeJogadores::getNomeDoJogo(TipoDeJogo jogo) {
    switch (jogo) {
        case REVERSI: return "REVERSI";
        case LIG4:    return "LIG4";
        case VELHA:   return "VELHA";
        default:      return "JOGO_INVALIDO";
    }
}
/*
Método buscaPorApelido() :
- Se somente um apelido é fornecido, retorna o booleano resultado da busca do apelido no arquivo
- Se além do apelido, um "std::streampos* posicao" for fornecido, a posição do jogador no arquivo será armazenada
*/
bool GestaoDeJogadores::buscaPorApelido(const std::string& apelido, std::streampos* posicao /*= nullptr*/) const {
    std::ifstream arquivo(caminhoDoArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para busca por apelido." << std::endl;
        return false;
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


/*}
FALTA FAZER:
- Ordenar protecao dos metodos
- 
IDEIAS PARA FAZER:
- uma ordenacao por apelido sempre que um jogador for cadastrado
- 

reler codigo, conferir se algo falta, conferir se tudo solicitado foi feito
verificar interligacao com a parte de execução dos jogos
verificar como ficará a main
testar
conversar sobre proximas etapas
*/