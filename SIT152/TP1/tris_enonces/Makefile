
a.exe :	tris.o data.o utilisation.o
	gcc tris.o data.o utilisation.o -o a.exe
	
b.exe : tris.o data.o utilisation.o
	gcc tris.o data.o utilisation.o -o b.exe


tris.o : tris.h tris.c
	gcc -c tris.c -o tris.o

	
data.o : data.h data.c
	gcc -c data.c -o data.o


utilisation.o : utilisation.c tris.h data.h
	gcc -c utilisation.c -o utilisation.o



