# Chemins vers les répertoires des bibliothèques
GLEW_DIR = $(HOME)/glew
GLFW_DIR = $(HOME)/glfw

# Fichiers source
SRC = main.cpp

# Fichier exécutable
TARGET = main

# Options de compilation
CXX = g++
CXXFLAGS = -std=c++11 -I$(GLEW_DIR)/include -I$(GLFW_DIR)/include
LDFLAGS = -L$(GLEW_DIR)/lib -L$(GLFW_DIR)/src -lGL -lGLU -lglfw -lGLEW -Wl,-rpath,$(GLEW_DIR)/lib -Wl,-rpath,$(GLFW_DIR)/src

# Règles de compilation
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
