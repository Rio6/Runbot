CXXFLAGS=-O2 -Wall
LIBS=-lSDL2
SRCS=main.cpp main.hpp graphic.cpp graphic.hpp game.cpp game.hpp
OBJS=main.o graphic.o game.o
TGT=runbot

all: $(TGT)

$(TGT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJS) -o $(TGT)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -f *.o

depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend
