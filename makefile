.PHONY: build run gc clean count

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

count:
	cloc --exclude-list-file=.clocignore .
