.PHONY: all build run clean # even if build/ exists, still runs

all: build run

build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	cmake --build .

run:
	./build/nocturne

clean:
	rm -rf build/