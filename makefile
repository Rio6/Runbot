CFLAGS=-O2 -Wall
LIBS=-lSDL2
OBJS=main.o graphic.o
TGT=runbot

all: $(TGT)

$(TGT): $(OBJS)
	$(CXX) $(CFLAGS) $(LIBS) $(OBJS) -o $(TGT)

clean:
	$(RM) -f *.o
