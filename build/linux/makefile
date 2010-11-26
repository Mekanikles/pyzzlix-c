PROGRAM=pyzzlix
CXX=g++

include ../deps.mk

CXXFLAGS=
LIBPATHS=
INCPATHS=
LIBS
OBJECTS=

CXXFLAGS+=-g

LIBPATHS+=-L/usr/local/lib
INCPATHS+=-I. -I/usr/local/include

LIBS+=-lglfw -lX11 -lGL

OBJECTS=$(REALSOURCE:.cpp=.o)

all: $(PROGRAM)


$(PROGRAM): $(OBJECTS) $(REALDEPS)
	$(CXX) $(CXXFLAGS) $(LIBPATHS) $(INCPATHS) $(OBJECTS) $(LIBS)  -o $(PROGRAM)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCPATHS) -c $> -o $@

