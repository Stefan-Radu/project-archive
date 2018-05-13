CXX = g++
CXXFLAGS = -std=c++14
LIBS = -lGL -lGLEW -lglfw

POBJ = obj/
TARGET = main
SOURCES = main.cpp Renderer.cpp VertexBuffer.cpp IndexBuffer.cpp
OBJECTS = $(addprefix $(POBJ), $(SOURCES:.cpp=.o))

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

obj/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(LIBS)

obj/Renderer.o: Renderer.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(LIBS)

obj/VertexBuffer.o: VertexBuffer.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(LIBS)

obj/IndexBuffer.o: IndexBuffer.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(LIBS)

# obj/NAME.o: NAME.cpp
# 	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(LIBS)

clean:
	rm obj/* $(TARGET)
