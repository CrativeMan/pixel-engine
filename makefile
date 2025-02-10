all: build run
	
build:
	mkdir -p build
	cd build && cmake .. && cmake --build .
	
run:
	cd build && ./bin/PixelEngine
