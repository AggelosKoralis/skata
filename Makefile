CXX = gcc
CXXFLAGS = -g3 -Wall -Werror

EXEC = main
OBJS = main.o point.o rectangle.o line.o

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $^

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) -lm

clean: 
	rm -rf $(OBJS) $(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)