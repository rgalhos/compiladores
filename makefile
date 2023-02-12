default: build

build:
	g++ -Wall -I src/lib src/main.cpp -std=c++20 -o rppp
