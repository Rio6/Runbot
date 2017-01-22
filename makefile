CFLAGS=-O2 -Wall
LIBS=-lSDL2
SRCS=main.cpp main.hpp graphic.cpp graphic.hpp game.cpp game.hpp
OBJS=main.o graphic.o game.o
TGT=runbot

all: $(TGT)

$(TGT): $(OBJS)
	$(CXX) $(CFLAGS) $(LIBS) $(OBJS) -o $(TGT)

.cpp.o:
	$(CXX) $(CFLAGS) -c $<

clean:
	$(RM) -f *.o

depend: $(SRCS)
	$(CXX) $(CFLAGS) -MM $^ > .depend
