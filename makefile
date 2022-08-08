CXX = g++
CXXFLAGS = -g -Wall -Wextra

.PHONY : all
all : program

program : menu.cpp book.cpp rbtree.cpp 
	$(CXX) $(CXXFLAGS) -o program menu.cpp book.cpp rbtree.cpp

.PHONY : clean
clean:
	$(RM) *.o
	$(RM) program