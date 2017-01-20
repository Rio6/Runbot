CFLAGS=-O2 -Wall
LIBS=-lSDL2
OBJS=main.o graphic.o game.o
TGT=runbot

all: $(TGT)

$(TGT): $(OBJS)
	$(CXX) $(CFLAGS) $(LIBS) $(OBJS) -o $(TGT)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) -f *.o
