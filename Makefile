all: main.o pesquisa.o
	@gcc main.o pesquisa.o -o exe 

main.o: main.c
	@gcc main.c -c -Wall

pesquisa.o: pesquisa.c
	@gcc pesquisa.c -c -Wall

exe:
	@./exe