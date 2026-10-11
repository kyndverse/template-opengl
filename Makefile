.PHONY: init init-debug build run dev

init:
	cmake -S . -B build

init-debug:
	cmake -S . -B build-debug -DFETCHCONTENT_QUIET=OFF --log-level=VERBOSE

build:
	cmake --build build

run:
	.\build\Debug\OpenGLProject.exe

dev:
	cmake --build build
	.\build\Debug\OpenGLProject.exe