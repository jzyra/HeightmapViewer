CXX=g++
CXXFLAGS=-W -Wall
LDFLAGS=-lSDL2 -lGL -lGLEW -lSDL2_image
EXEC=heightmapviewer

all: $(EXEC)

heightmapviewer: Camera.o Heightmap.o Landscape.o Shader.o Window.o
	$(CXX) -o heightmapviewer Camera.o Heightmap.o Landscape.o Shader.o Window.o main.cpp $(CXXFLAGS) $(LDFLAGS)

Camera.o: Camera.cpp
	$(CXX) -o Camera.o -c Camera.cpp $(CXXFLAGS) $(LDFLAGS)

Heightmap.o: Heightmap.cpp
	$(CXX) -o Heightmap.o -c Heightmap.cpp $(CXXFLAGS) $(LDFLAGS)

Landcsape.o: Landscape.cpp
	$(CXX) -o Landscape.o -c Landscape.cpp $(CXXFLAGS) $(LDFLAGS)

Shader.o: Shader.cpp
	$(CXX) -o Shader.o -c Shader.cpp $(CXXFLAGS) $(LDFLAGS)

Window.o: Window.cpp
	$(CXX) -o Window.o -c Window.cpp $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
