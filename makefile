CXXFLAGS=-O2 -Wall
LIBS=-lSDL2 -lSDL2_image
SRCS=main.cpp  graphic.cpp  game.cpp  robot.cpp  anim.cpp 
HDRS=main.hpp  graphic.hpp  game.hpp  robot.hpp  anim.hpp
OBJS=main.o graphic.o game.o robot.o anim.o
TGT=runbot

all: $(TGT)

$(TGT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJS) -o $(TGT)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) -f *.o

depend: .depend

.depend: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend

include .depend
