exec: build
	@echo "\033[31m\033[1mExecution du minishell :\033[0m"
	@./exe

execrb: rebuild
	@echo "\033[31m\033[1mExecution du minishell :\033[0m"
	@./exe

rebuild: mrproper build

build: main.o cmdline.o parser.o processus.o utils.o
	@echo "\033[31m\033[1mCreation de l'executable :\033[0m"
	@gcc -o exe main.o cmdline.o parser.o processus.o utils.o -Wall
	@echo "\033[31m\033[1mCreation de l'executable effectuée\033[0m"

main.o: main.c
	@echo "\033[31m\033[1mCompilation de main.c :\033[0m"
	@gcc -o main.o -c main.c -Wall
	@echo "\033[31m\033[1mCompilation de main.c effectuée\033[0m"

cmdline.o: cmdline.c
	@echo "\033[31m\033[1mCompilation de cmdline.c :\033[0m"
	@gcc -o cmdline.o -c cmdline.c -Wall 
	@echo "\033[31m\033[1mCompilation de cmdline.c effectuée\033[0m"

parser.o: parser.c
	@echo "\033[31m\033[1mCompilation de parser.c :\033[0m"
	@gcc -o parser.o -c parser.c -Wall 
	@echo "\033[31m\033[1mCompilation de parser.c effectuée\033[0m"

processus.o: processus.c
	@echo "\033[31m\033[1mCompilation de processus.c :\033[0m"
	@gcc -o processus.o -c processus.c -Wall 
	@echo "\033[31m\033[1mCompilation de processus.c effectuée\033[0m"

utils.o: utils.c
	@echo "\033[31m\033[1mCompilation de utils.c :\033[0m"
	@gcc -o utils.o -c utils.c -Wall 
	@echo "\033[31m\033[1mCompilation de utils.c effectuée\033[0m"

clean:
	@echo "\033[31m\033[1mNettoyage des fichiers .o effectuée\033[0m"
	@rm -rf *.o

mrproper:
	@echo "\033[31m\033[1mNettoyage des fichiers .o et de l'executable minishell effectuée\033[0m"
	@rm -rf *.o
	@rm -rf exe
