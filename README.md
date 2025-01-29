#   Trabalho Prático PDS2 - Jogos de Tabuleiro

Bem-vindo ao repositório do **Trabalho Prático PDS2**! Este projeto é um sistema desenvolvido em **C++11** para gerenciamento de jogadores e execução de jogos clássicos de tabuleiro. Aqui você encontrará uma solução robusta para cadastrar jogadores, jogar partidas de **Jogo da Velha**, **Lig4** e **Reversi**, e gerar estatísticas detalhadas para cada jogador.

---

##   Desenvolvido por:

- **Arthur Ferreira Rabelo**  
- **Luís Henrique Emediato de Rezende Lara**  
- **Marco Aurélio Gonçalves de Souza**  
- **Raiza Wunsch Pinto**  

 **Contato:** [arthurfrabelo06@gmail.com](mailto:arthurfrabelo06@gmail.com)  
 **Repositório:** [https://github.com/luisemediato/ProjetoFinal/](https://github.com/luisemediato/ProjetoFinal/)  

---

##   Tabela de Conteúdos

- Instalação e Compilação
- Funcionalidades do Sistema
- Estrutura do Projeto
- Dificuldades Enfrentadas
- Documentação

---

##   Instalação e Compilação

### Pré-requisitos

- **Compilador C++** compatível com C++11 (ex: g++, clang)
- **Doxygen** (para gerar a documentação)
- **Make** para compilar e executar

### Passo a Passo

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/luisemediato/ProjetoFinal.git
   cd ProjetoFinal
   ```

2. **Compile o projeto**:
   ```bash
   make
   ```

3. **Execute o programa**:
   ```bash
   make run
   ```
⚠️ Certifique-se de ter o `make` instalado para compilar e executar o projeto corretamente utilizando o nosso Makefile.

---

##   Funcionalidades do Sistema

###   Sistema de Jogadores
Implementamos um módulo para cuidar do cadastro de jogadores. Cada jogador tem um nome, um apelido único, e estatísticas com o número de vitórias e derrotas nos jogos. Além disso criamos métodos para:

- **Cadastrar/Remover Jogadores**: Permite o cadastro e remoção de jogadores com apelido único.
- **Listagem Detalhada**: Exibe estatísticas detalhadas por jogo para cada jogador.
- **Persistência em Arquivo csv**: O cadastro de jogadores é mantido entre diferentes execuções do sistema, com mecanismos para salvar e ler os dados a partir de um arquivo.
- **Funcionalidade Extras**: 
     * O código exibe no tabuleiro do Reversi as posições válidas para a jogada, marcando-as de forma clara e seguindo as regras do jogo.
     * O código, ao listar os jogadores, exibe estatísticas detalhadas, incluindo o aproveitamento de cada usuário cadastrado em cada jogo, destacando-o com cores: vermelho (0-25%), amarelo (25-50%), azul (50-75%) e verde (75-100%), proporcionando uma visão clara e visualmente intuitiva do desempenho

###   Relação dos Jogos Implementados

| Jogo          | Tamanho do Tabuleiro | Modo de Vitória                     | Características Únicas              |
|---------------|----------------------|-------------------------------------|-----------------------------------------|
| Jogo da Velha |          3x3        | Linha/Coluna/Diagonal               | Possibilidade de empate no jogo              |
| Lig4      |        6x7    | 4 peças em linha vertical/horizontal/diagonal | Sistema de colocar peça nas colunas                     |
| Reversi       |         8x8         | Contagem de peças                   | Mecânica de captura de peças            |

###   Estatísticas
- Mecânica de vitórias, de derrotas e de aproveitamento de cada jogador, em cada jogo.
          
---

##   Estrutura do Projeto

O sistema foi desenvolvido em **C++11** e segue uma arquitetura modular, com separação clara entre as funcionalidades de gerenciamento de jogadores e a lógica dos jogos. A persistência dos dados é feita através de arquivo csv, e a documentação foi gerada utilizando **Doxygen**.

```
📦 ProjetoFinal
├── 📂 bin
│   └── main.exe                # Executável gerado
├── 📂 include
│   ├── gestaoDeJogadores.hpp   # Gerenciamento de jogadores (cabeçalho)
│   ├── tabuleiro.hpp           # Interface base de tabuleiro (cabeçalho)
│   ├── jogos.hpp               # Interface base para jogos (cabeçalho)
│   ├── jogador.hpp             # Interface base para jogador (cabeçalho)
│   ├── jogoDaVelha.hpp         # Implementação do Jogo Da Velha (cabeçalho)
│   ├── reversi.hpp             # Implementação do Reversi (cabeçalho)
│   └── lig4.hpp                # Implementação do Lig 4 (cabeçalho)
├── 📂 obj
│   ├── main.o                  # Objeto gerado a partir do arquivo main.cpp (ponto de entrada do programa)
│   ├── gestaoDeJogadores.o     # Objeto gerado a partir do arquivo gestaoDeJogadores.cpp (gerenciamento de jogadores)
│   ├── tabuleiro.o             # Objeto gerado a partir do arquivo tabuleiro.cpp (interface base de tabuleiro)
│   ├── jogos.o                 # Objeto gerado a partir do arquivo jogos.cpp (interface base para jogos)
│   ├── jogador.o               # Objeto gerado a partir do arquivo jogador.cpp (interface base para jogador)
│   ├── jogoDaVelha.o           # Objeto gerado a partir do arquivo jogoDaVelha.cpp (implementação do Jogo Da Velha)
│   ├── reversi.o               # Objeto gerado a partir do arquivo reversi.cpp (implementação do Reversi)
│   └── lig4.o                  # Objeto gerado a partir do arquivo lig4.cpp (implementação do Lig 4)
├── 📂 src
│   ├── gestaoDeJogadores.hpp   # Gerenciamento de jogadores (implementação)
│   ├── tabuleiro.cpp           # Interface base de tabuleiro (implementação)
│   ├── jogos.cpp               # Interface base para jogos (implementação)
│   ├── jogador.cpp             # Interface base para jogador (implementação)
│   ├── jogoDaVelha.cpp         # Implementação do Jogo Da Velha (implementação)
│   ├── reversi.cpp             # Implementação do Reversi (implementação)
│   ├── lig4.cpp                # Implementação do Lig 4 (implementação)
│   └── main.cpp                # Executa o programa
├── 📂 gameData
│   └── dados.csv               # Banco de dados de jogadores e suas pontuações
├── 📂 tests
│   ├── teste_gestaoDeJogadores.hpp   # Arquivo de teste da Classe Gestão de Jogadores
│   ├── teste_jogador.hpp             # Arquivo de teste da Classe Jogador
│   ├── teste_jogoDaVelha.hpp         # Arquivo de teste da Classe JogoDaVelha
│   ├── teste_jogos.hpp               # Arquivo de teste da Classe Jogos
│   ├── teste_lig4.hpp                # Arquivo de teste da Classe Lig4
│   ├── teste_reversi.hpp             # Arquivo de teste da Classe Reversi
│   ├── teste_tabueleiro.hpp          # Arquivo de teste da Classe Tabuleiro
│   ├── doctest.h                     # Módulo do doctest para efetuar os testes nos arquivos
├── 📂 docs
└── Makefile                    # Instruções de compilação para o programa
```
---

##   Dificuldades Enfrentadas
🔴 [**gestaoDoJogadores**] , [**dados.csv**]: Manipular o preenchimento dos dados no arquivo csv, seja para adição, edição e remoção de jogadores e/ou atributos

🔴 [**jogoDaVelha**], [**reversi**], [**lig4**]: Implementar a dinâmica com o tabuleiro, dentro da lógica de funcionamento do jogo e da dinâmica de jogadores

🔴 [**main**]: Estabelecer a interação com o usuário e aumentar a robustez do sistema a comportamentos excepcionais

🔴 [**tests**]: Implementar os métodos para atender os casos de teste em cada função, de modo a alcançar a melhor cobertura possível e fomentar a robustez do sistema

   Vale ressaltar que tivemos muita dificuldade com o uso do doctest, já que mesmo instalando-o corretamente no sistema e utilizando a versão atualizada, houve um problema com uma das dependências da biblioteca padrão std.
      
      tests/doctest.h:3175:50: error: 'mutex' is not a member of 'std'
       #define DOCTEST_LOCK_MUTEX(name) std::lock_guard<std::mutex> DOCTEST_ANONYMOUS(DOCTEST_ANON_LOCK_)(name);
    
   ⚠️ Essa foi apenas uma das várias mensagens exibidas, mas todas estão relacionadas ao mutex.

   Com isso, após tentar de todas as formas compilar os arquivos de teste, não conseguimos superar esse erro que ocorreu com nosso sistema. Entretanto, pelo fim de um resultado agradável e completo do trabalho, buscamos desenvolver todos arquivos de teste para que mesmo na ausência da solução que julgamos adequada, o sistema fosse completo. Além disso, buscamos compensar esse problema com um foco maior em todas as demais áreas do projeto, de modo a equilibrar a deficiência mencionada. Enquanto isso, continuaremos a buscar uma solução para que possamos validar nossos testes e tirar novas conclusões sobre o projeto que desenvolvemos. 

   

---

##   Documentação

A documentação do projeto foi gerada utilizando **Doxygen**. Para acessar a documentação completa, siga os passos de geração da documentação acima ou consulte nosso [**Dropbox**](https://www.dropbox.com/scl/fo/cpsmt833zej46z91zy0oa/AIg3R8hfDKZPSqEW0vHZ2tA?rlkey=69vu5iw26xmrg4sam75rd0upm&st=q36j61u3&dl=0) onde, além da documentação, colocamos todos os recursos utilizados para o projeto.
