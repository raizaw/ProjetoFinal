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

- [ Instalação e Compilação](#️-instalação-e-compilação)
- [ Funcionalidades](#-funcionalidades)
- [ Estrutura do Projeto](#️-estrutura-do-projeto)
- [ Documentação](#-documentação)

---

##   Instalação e Compilação

### Pré-requisitos

- **Compilador C++** compatível com C++11 (ex: g++, clang)
- **Doxygen** (para gerar a documentação)

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

### Geração da Documentação

Para gerar a documentação com Doxygen:

1. Certifique-se de que o Doxygen está instalado.
2. Execute o comando:
   ```bash
   doxygen Doxyfile
   ```
3. A documentação será gerada na pasta `docs/`.

---

##   Funcionalidades

###   Sistema de Jogadores
Implementamos um módulo para cuidar do cadastro de jogadores. Cada jogador tem um nome, um apelido único, e estatísticas com o número de vitórias e derrotas nos jogos. Além disso criamos métodos para:

- **Cadastrar/Remover Jogadores**: Permite o cadastro e remoção de jogadores com apelido único.
- **Listagem Detalhada**: Exibe estatísticas detalhadas por jogo para cada jogador.
- **Persistência em Arquivo csv**: O cadastro de jogadores é mantido entre diferentes execuções do sistema, com mecanismos para salvar e ler os dados a partir de um arquivo.


###   Jogos Implementados

| Jogo          | Tamanho do Tabuleiro | Modo de Vitória                     | Características Especiais               |
|---------------|----------------------|-------------------------------------|-----------------------------------------|
| Jogo da Velha |          3x3        | Linha/Coluna/Diagonal               | Detecção de empate no jogo              |
| Lig4      |        Variável     | 4 em linha vertical/horizontal/diagonal | Sistema de colunas                     |
| Reversi       |         8x8         | Contagem de peças                   | Mecânica de captura de peças            |

###   Estatísticas
Tamanho do 
          

---

##   Estrutura do Projeto

O sistema foi desenvolvido em **C++11** e segue uma arquitetura modular, com separação clara entre as funcionalidades de gerenciamento de jogadores e a lógica dos jogos. A persistência dos dados é feita através de arquivos texto, e a documentação foi gerada utilizando **Doxygen**.

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
├── dados.csv                   # Banco de dados de jogadores e suas pontuações
├── 📂 tests
├── 📂 docs
└── Makefile                    # Instruções de compilação para o programa
```
---

##   Documentação

A documentação do projeto foi gerada utilizando **Doxygen**. Para acessar a documentação completa, siga os passos de geração da documentação acima ou consulte nosso [**Dropbox**](https://www.dropbox.com/scl/fo/cpsmt833zej46z91zy0oa/AIg3R8hfDKZPSqEW0vHZ2tA?rlkey=69vu5iw26xmrg4sam75rd0upm&st=q36j61u3&dl=0) onde, além da documentação, colocamos todos os recursos utilizados para o projeto.
