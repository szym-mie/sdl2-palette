cc=gcc

$cc -c -o io.o io.c
$cc -c -o triangle.o triangle.c
$cc -o main main.c io.o triangle.o -lSDL2