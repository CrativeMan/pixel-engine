all:
	./build/bin/PixelEngine

debug:
	./build/bin/PixelEngine debug

trace:
	./build/bin/PixelEngine trace

count: 
	cloc --exclude-list-file=.clocignore .
