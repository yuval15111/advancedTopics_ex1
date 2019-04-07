COMP = g++-5.3.0
#put all your object files here
OBJS = main.o FileHandler.o Manager.o Player.o MainAux.o
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp FileHandler.h Manager.h Player.h MainAux.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FileHandler.o: FileHandler.h Manager.h Player.h MainAux.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Manager.o: Manager.h Player.h MainAux.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player.o: Player.h MainAux.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MainAux.o: MainAux.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)