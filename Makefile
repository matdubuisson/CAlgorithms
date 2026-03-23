all: build

.PHONY: build
build:
	cmake -S . -B build/
	cmake --build build/

test:
	cd build/ && ctest -VV -R $(regex)

test_all:
	cd build/ && ctest -VV

clean:
	rm -rf build/
