PROGRAM=$(ROOTPATH)/bin/pyzzlix
CXX=g++

include ../deps.mk

CXXFLAGS=
LIBPATHS=
INCPATHS=
LIBS=
OBJECTS=

CXXFLAGS+= -g -Wall

LIBPATHS+=-L/usr/local/lib
INCPATHS+=-I. -I/usr/local/include

LIBS+=-lglfw -lX11 -lGL

OBJECTS=$(REALSOURCE:.cpp=.o)

all: $(PROGRAM)


$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBPATHS) $(INCPATHS) $(OBJECTS) $(LIBS)  -o $(PROGRAM)


%.o: %.cpp  $(REALDEPS)
	$(CXX) $(CXXFLAGS) $(INCPATHS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(PROGRAM)
