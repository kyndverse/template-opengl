.PHONY: init build rebuild run clean

init:
	cmake -S . -B build

build:
	cmake --build build

rebuild:
	cmake --build build --clean-first

run:
	.\build\Debug\OpenGLProject.exe

clean:
	cmake --build build --target clean