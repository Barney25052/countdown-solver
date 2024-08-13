all: asmsolver.o
	ld -o asmsolver.out asmsolver.o
asmsolver.o: countdownsolver.asm
	nasm -f elf64 -o asmsolver.o countdownsolver.asm
