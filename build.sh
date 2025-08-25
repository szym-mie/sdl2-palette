cc=gcc

$cc -c -o triangle.o triangle.c
$cc -o main main.c triangle.o -lSDL2