SRC_CXX=\
	Utils.cxx MainFrame.cxx Piece.cxx Chessboard.cxx Player.cxx WhitePlayer.cxx BlackPlayer.cxx King.cxx Queen.cxx Rook.cxx Knight.cxx Bishop.cxx Pawn.cxx

OBJ=${SRC_CXX:.cxx=.o}

all: main

main: $(OBJ) main.o
	g++ $(OBJ) main.o -o prog -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cxx
	g++ -c $<

clean:
	@rm -f $(OBJ) *.o prog *~
