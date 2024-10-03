CXX = g++
CXXFLAGS = -Iinclude -Wall

all: main

main: main.cpp src/glad.c
	$(CXX) $(CXXFLAGS) main.cpp src/glad.c -lglfw -ldl -o main
