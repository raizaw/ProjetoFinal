# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Nome do executável
TARGET = bin/main.exe

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Lista de arquivos fonte
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/gestaoDeJogadores.cpp \
       $(SRC_DIR)/tabuleiro.cpp \
       $(SRC_DIR)/jogos.cpp \
       $(SRC_DIR)/jogador.cpp \
       $(SRC_DIR)/jogoDaVelha.cpp \
       $(SRC_DIR)/reversi.cpp \
       $(SRC_DIR)/lig4.cpp

# Lista de objetos gerados (com caminho para a pasta obj/)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Detectar o sistema operacional
ifeq ($(OS),Windows_NT)
    # Comandos para Windows
    MKDIR = mkdir
    RMDIR = rmdir /s /q
    DEL = del /q
    TARGET := $(TARGET:.exe=.exe) # Mantém a extensão .exe no Windows
else
    # Comandos para Linux
    MKDIR = mkdir -p
    RMDIR = rm -rf
    DEL = rm -f
    TARGET := $(TARGET:.exe=) # Remove a extensão .exe no Linux
endif

# Regra padrão
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJS)
	@if not exist $(BIN_DIR) $(MKDIR) $(BIN_DIR)  # Cria a pasta bin/ se não existir
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar cada arquivo .cpp em um objeto .o na pasta obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(OBJ_DIR) $(MKDIR) $(OBJ_DIR)  # Cria a pasta obj/ se não existir
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
ifeq ($(OS),Windows_NT)
	$(DEL) $(OBJ_DIR)\*.o $(BIN_DIR)\*.exe
else
	$(DEL) $(OBJ_DIR)/*.o $(BIN_DIR)/*
endif

# Executar o programa
run: $(TARGET)
	$(TARGET)