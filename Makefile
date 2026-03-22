all: build

.PHONY: build

build:
	cmake -S . -B build/
	cmake --build build/

test:
	cd build/ && ctest -V

clean:
	rm -rf build/