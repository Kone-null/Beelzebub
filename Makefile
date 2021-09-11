CXX = g++
CXXFLAGS = -std=c++17 -Wall

clean:
	$(RM) lib/*.o

Beelzebub: lib/list.o lib/node.o main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
	echo "Ready to Run"