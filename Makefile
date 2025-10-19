CXX = gcc
CXXFLAGS = -g3 -Wall -Werror
LIBS = -lm

EXEC = main
OBJS = main.o point.o rectangle.o line.o canvas.o

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $^

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

clean: 
	rm -rf $(OBJS) $(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)