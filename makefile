PROG = sim

all:
	g++ main.cpp sim.cpp -o $(PROG) --std=c++23

run: all
	./$(PROG)

clean: 
	rm $(PROG)
