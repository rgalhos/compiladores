default: build

build:
	cd ./bnf && \
	python3 gen_tables.py && \
	cd .. && \
	g++ -Wall -I src/lib src/main.cpp -std=c++20 -o rppp
