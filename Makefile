clean:
	rm -rf build
	mkdir build

configure:
	cmake -B build -S . -G "Unix Makefiles"

build_p:
	cmake --build build --target BartaEngine_runTest --config Debug

run:
	./build/test/run/BartaEngine_runTest
