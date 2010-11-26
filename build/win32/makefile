PROGRAM=pyzzlix.exe
CXX=g++
SDK= /cygdrive/c/SDK

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

OBJECTS=$(SOURCE:.cpp=.o)


all: $(PROGRAM)


%.o: $(SRCPATH)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCPATHS) -c $< -o $@


$(PROGRAM): $(OBJECTS) $(REALDEPS)
	$(CXX) $(CXXFLAGS) $(LIBPATHS) $(INCPATHS) $(OBJECTS) $(LIBS)  -o $(PROGRAM)


clean:
	rm -f $(OBJECTS) $(PROGRAM)
