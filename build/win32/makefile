PROGRAM=$(ROOTPATH)/bin/pyzzlix
CXX=g++
SDK= /cygdrive/d/SDK

include ../deps.mk

CXXFLAGS=
LIBPATHS=
INCPATHS=
LIBS=
OBJECTS=

CXXFLAGS+=-g -mno-cygwin -Wall

LIBPATHS+=-L$(SDK)/glfw/lib/win32
INCPATHS+=-I. -I$(SDK)/glfw/include

LIBS+=-lglfw -lOpengl32

OBJECTS=$(REALSOURCE:.cpp=.o)

all: $(PROGRAM)


$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBPATHS) $(INCPATHS) $(OBJECTS) $(LIBS)  -o $(PROGRAM)


%.o: %.cpp  $(REALDEPS)
	$(CXX) $(CXXFLAGS) $(INCPATHS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(PROGRAM)
