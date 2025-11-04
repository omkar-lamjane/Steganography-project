omkar.exe : main.o decode.o encode.o 
	gcc -o omkar.exe main.o decode.o encode.o
main.o : main.c
	gcc -c main.c
decode.o : decode.c
	gcc -c decode.c
encode.o : encode.c
	gcc -c encode.c
clean : 
	rm *.exe *.o
