all: main.exe

CPP = g++
CFLAGS = -g

clean:
	@rm -f *.exe ./src/*.o *.out

main.exe: src/main.o
	$(CPP) $(CFLAGS) $^ -o $@

## Creates a .out file with memory report. Needs to have valgrind installed in order to run this command (sudo apt-get install valgrind)
memcheck: main.exe
	@valgrind --leak-check=full --show-leak-kinds=definite,indirect,possible,reachable --track-origins=yes --verbose --log-file=listmemcheck.out ./main.exe >/dev/null

%.o:%.c
	@$(CPP) $(CFLAGS) -o $@ -c $<
