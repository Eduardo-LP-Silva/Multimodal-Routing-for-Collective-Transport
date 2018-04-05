CXX		 = g++
CXXFLAGS = -std=c++11 -g
LDFLAGS  =
DEPS	 = Source.cpp  Vertex.h Vertex.cpp MutablePriorityQueue.h Interface.cpp Interface.h connection.cpp connection.h Edge.cpp Edge.h Funcs.h Funcs.cpp GPSCoord.cpp GPSCoord.h Graph.cpp Graph.h graphviewer.cpp graphviewer.h Info.cpp Info.h makefile
OBJFILES = Vertex.o Interface.o graphviewer.o Graph.o Source.o GPSCoord.o Funcs.o Edge.o connection.o Info.o
TARGET	 = grafos

all: $(TARGET)

$(TARGET): $(OBJFILES) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
