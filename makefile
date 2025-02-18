.PHONY: build run gc clean

build:
	mkdir -p build
	cd build && cmake ..
	cd build && make

run:
	./bin/Linux64/main

clean:
	rm -rf bin

gc:
	rm -rf bin
	rm -rf build
