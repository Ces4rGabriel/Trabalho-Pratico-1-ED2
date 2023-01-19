all: main.o pesquisa.o gerador.o
	@gcc -o exe main.o pesquisa.o
	@gcc -o gerador gerador.o

main.o: main.c
	@gcc main.c -c -Wall

pesquisa.o: pesquisa.c
	@gcc pesquisa.c -c -Wall

exe:
	@./exe