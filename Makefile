CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -I/usr/include
LIBS     := -lglfw -lGLEW -lGL

OUT := triangle
SRC := main.cpp src/utils.cpp src/shader.cpp  src/camera.cpp src/model.cpp src/vao.cpp

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LIBS) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)

.PHONY: all run clean
