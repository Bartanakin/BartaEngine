clean:
	rm -rf build
	mkdir build

configure:
	cmake -B build -S . -G "Unix Makefiles"

build_p:
	cmake --build cmake-build-debug --target BartaEngine_lib --config Debug -j 18 --

build_tests:
	cmake --build cmake-build-debug --target BartaEngine_lib --config Debug -j 18 --

clang_format:
	cmake --build cmake-build-debug --target run_clang_format -j 18 --
# clang tidy doesn't work woth pch and g++
# clang_tidy_barta_engine:
#	cmake --build build --target BartaEngine_clangtidy

run:
	./build/bin/run_sandbox

run_tests:
	./cmake-build-debug/test/BartaTests
