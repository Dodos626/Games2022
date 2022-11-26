meme: main.exe

CPP = g++
CFLAGS = -g -I CS454/Engine/Src/Headers

clean:
	@rm -f *.exe ./src/*.o *.out

%.o:%.c
	@$(CPP) $(CFLAGS) -o $@ -c $<

main.exe: CS454/UnitTests/UnitTest1Media/main.o
	$(CPP) $(CFLAGS) main.o -o CS454.exe

all:
	cl.exe CS454/UnitTests/UnitTest1Media/main.cpp CS454/Engine/Src/Tiles/Parser/TileParser.cpp -I CS454/Engine/Src/Headers/ -o CS454.exe