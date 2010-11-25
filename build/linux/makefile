PROGRAM=pyzzlix
CXX=g++

CXXFLAGS=
LIBPATHS=
INCPATHS=
LIBS=
SOURCE=
OBJECTS=

SRCPATH=../../src



CXXFLAGS+=-g

LIBPATHS+=-L/usr/local/lib
INCPATHS+=-I. -I/usr/local/include

LIBS+=-lglfw -lX11 -lGL

DEPS+=
SOURCE+=main.cpp

REALSOURCE = $(addprefix $(SRCPATH)/, $(SOURCE))
OBJECTS=$(REALSOURCE: .cpp=.o)


all: $(PROGRAM)


$(PROGRAM): $(OBJECTS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(LIBPATHS) $(INCPATHS) $(OBJECTS) $(LIBS)  -o $(PROGRAM)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCPATHS) -c $> -o $@

