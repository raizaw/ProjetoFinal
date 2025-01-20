INCLUDEDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

$(BINDIR)/jogo: $(OBJDIR)/main.o $(OBJDIR)/executaPartida.o $(OBJDIR)/reversi.o $(OBJDIR)/lig4.o $(OBJDIR)/jogoDaVelha.o $(OBJDIR)/gestaoDeJogadores.o $(OBJDIR)/jogador.o $(OBJDIR)/jogos.o $(OBJDIR)/tabuleiro.o
	g++ $(OBJDIR)/main.o $(OBJDIR)/executaPartida.o $(OBJDIR)/reversi.o $(OBJDIR)/lig4.o $(OBJDIR)/jogoDaVelha.o $(OBJDIR)/gestaoDeJogadores.o $(OBJDIR)/jogador.o $(OBJDIR)/jogos.o $(OBJDIR)/tabuleiro.o -o $(BINDIR)/jogo

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCLUDEDIR)/executaPartida.hpp
	g++ -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/executaPartida.o: $(SRCDIR)/executaPartida.cpp $(INCLUDEDIR)/executaPartida.hpp $(INCLUDEDIR)/reversi.hpp $(INCLUDEDIR)/lig4.hpp $(INCLUDEDIR)/jogoDaVelha.hpp $(INCLUDEDIR)/gestaoDeJogadores.hpp
	g++ -c $(SRCDIR)/executaPartida.cpp -o $(OBJDIR)/executaPartida.o

$(OBJDIR)/gestaoDeJogadores.o: $(SRCDIR)/gestaoDeJogadores.cpp $(INCLUDEDIR)/gestaoDeJogadores.hpp $(INCLUDEDIR)/jogador.hpp
	g++ -c $(SRCDIR)/gestaoDeJogadores.cpp -o $(OBJDIR)/gestaoDeJogadores.o

$(OBJDIR)/jogador.o: $(SRCDIR)/jogador.cpp $(INCLUDEDIR)/jogador.hpp
	g++ -c $(SRCDIR)/jogador.cpp -o $(OBJDIR)/jogador.o

$(OBJDIR)/reversi.o: $(SRCDIR)/reversi.cpp $(INCLUDEDIR)/reversi.hpp $(INCLUDEDIR)/jogos.hpp
	g++ -c $(SRCDIR)/reversi.cpp -o $(OBJDIR)/reversi.o

$(OBJDIR)/lig4.o: $(SRCDIR)/lig4.cpp $(INCLUDEDIR)/lig4.hpp $(INCLUDEDIR)/jogos.hpp
	g++ -c $(SRCDIR)/lig4.cpp -o $(OBJDIR)/lig4.o

$(OBJDIR)/jogoDaVelha.o: $(SRCDIR)/jogoDaVelha.cpp $(INCLUDEDIR)/jogoDaVelha.hpp $(INCLUDEDIR)/jogos.hpp
	g++ -c $(SRCDIR)/jogoDaVelha.cpp -o $(OBJDIR)/jogoDaVelha.o

$(OBJDIR)/jogos.o: $(SRCDIR)/jogos.cpp $(INCLUDEDIR)/jogos.hpp $(INCLUDEDIR)/tabuleiro.hpp
	g++ -c $(SRCDIR)/jogos.cpp -o $(OBJDIR)/jogos.o

$(OBJDIR)/tabuleiro.o: $(SRCDIR)/tabuleiro.cpp $(INCLUDEDIR)/tabuleiro.hpp
	g++ -c $(SRCDIR)/tabuleiro.cpp -o $(OBJDIR)/tabuleiro.o

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/jogo