SRCDIR:=src
BUILDDIR:=build

CXXFLAGS:=-O2 -Wall
LIBS:=-lSDL2 -lSDL2_image
SRCS:=$(wildcard $(SRCDIR)/*.cpp)
HDRS:=$(wildcard $(SRCDIR)/*.hpp)
OBJS:= $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
TGT:=runbot

all: $(BUILDDIR) $(TGT)

$(TGT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OBJS) -o $(TGT)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	$(RM) -r build

depend: .depend

.depend: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -MM $^ | sed 's|[a-zA-Z0-9_-]*\.o|$(BUILDDIR)/&|' > .depend

include .depend
