# 🎮 Trabalho Prático PDS2 - Jogos de Tabuleiro

Bem-vindo ao repositório do **Trabalho Prático PDS2**! Este projeto é um sistema desenvolvido em **C++11** para gerenciamento de jogadores e execução de jogos clássicos de tabuleiro. Aqui você encontrará uma solução robusta para cadastrar jogadores, jogar partidas de **Jogo da Velha**, **Connect4** e **Reversi**, e gerar estatísticas detalhadas para cada jogador.

---

## 👥 Desenvolvido por:

- **Arthur Ferreira Rabelo**  
- **Luís Henrique Emediato de Rezende Lara**  
- **Marco Aurélio Gonçalves de Souza**  
- **Raiza Wunsch Pinto**  

📧 **Contato:** [arthurfrabelo06@gmail.com](mailto:arthurfrabelo06@gmail.com)  
🌐 **Repositório:** [https://github.com/luisemediato/ProjetoFinal/](https://github.com/luisemediato/ProjetoFinal/)  

---

## 📋 Tabela de Conteúdos

- [🛠️ Instalação e Compilação](#️-instalação-e-compilação)
- [✨ Funcionalidades](#-funcionalidades)
- [🏗️ Arquitetura do Sistema](#️-arquitetura-do-sistema)
- [📚 Documentação](#-documentação)

---

## 🛠️ Instalação e Compilação

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
   g++ -std=c++11 -o sistema_jogos main.cpp Jogador.cpp Jogo.cpp JogoDaVelha.cpp Connect4.cpp Reversi.cpp
   ```

3. **Execute o programa**:
   ```bash
   ./sistema_jogos
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

## ✨ Funcionalidades

### 🧑💻 Sistema de Jogadores
Implementamos um módulo para cuidar do cadastro de jogadores. Cada jogador tem um nome, um apelido único, e estatísticas com o número de vitórias e derrotas nos jogos. Além disso criamos métodos para:

- **Cadastrar/Remover Jogadores**: Permite o cadastro e remoção de jogadores com apelido único.
- **Listagem Detalhada**: Exibe estatísticas detalhadas por jogo para cada jogador.
- **Persistência em Arquivo csv**: O cadastro de jogadores é mantido entre diferentes execuções do sistema, com mecanismos para salvar e ler os dados a partir de um arquivo.


### 🎲 Jogos Implementados

| Jogo         | Tabuleiro | Modo de Vitória                     | Características Especiais               |
|--------------|-----------|-------------------------------------|-----------------------------------------|
| Jogo da Velha| 3x3       | Linha/Coluna/Diagonal               | Detecção de empate                      |
| Connect4     | Variável  | 4 em linha vertical/horizontal/diagonal | Sistema de colunas                     |
| Reversi      | 8x8       | Contagem de peças                   | Mecânica de captura de peças            |

### 📊 Estatísticas


---

## 🏗️ Arquitetura de Sistema

O sistema foi desenvolvido em **C++11** e segue uma arquitetura modular, com separação clara entre as funcionalidades de gerenciamento de jogadores e a lógica dos jogos. A persistência dos dados é feita através de arquivos texto, e a documentação foi gerada utilizando **Doxygen**.

---

## 📚 Documentação

A documentação do projeto foi gerada utilizando **Doxygen**. Para acessar a documentação completa, siga os passos de geração da documentação acima ou consulte nosso **Dropbox** onde, além da documentação, colocamos todos os recursos utilizados para o projeto.

