SRC_CXX=\
	Utils.cxx MainFrame.cxx Piece.cxx Echiquier.cxx Joueur.cxx JoueurBlanc.cxx JoueurNoir.cxx Roi.cxx Reine.cxx Tour.cxx Cavalier.cxx Fou.cxx Pion.cxx

OBJ=${SRC_CXX:.cxx=.o}

all: testPiece

testPiece: $(OBJ) testPiece.o
	g++ $(OBJ) testPiece.o -o testPiece -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cxx
	g++ -c $<

clean:
	@rm -f $(OBJ) testPiece.o testPiece *~
