all: build clean

build: main.o cmdline.o parser.o processus.o utils.o builtin.o
	@echo "\033[31m\033[1mCreation de l'executable :\033[0m"
	@gcc -o minishell main.o cmdline.o parser.o processus.o utils.o builtin.o 
	@echo "\033[31m\033[1mCreation de l'executable effectuée\033[0m"

exec: build clean
	@echo "\033[31m\033[1mExecution du minishell :\033[0m"
	@./minishell

execrb: rebuild
	@echo "\033[31m\033[1mExecution du minishell :\033[0m"
	@./minishell

rebuild: mrproper build

main.o: main.c
	@echo "\033[31m\033[1mCompilation de main.c :\033[0m"
	@gcc -o main.o -c main.c 
	@echo "\033[31m\033[1mCompilation de main.c effectuée\033[0m"

cmdline.o: cmdline.c
	@echo "\033[31m\033[1mCompilation de cmdline.c :\033[0m"
	@gcc -o cmdline.o -c cmdline.c 
	@echo "\033[31m\033[1mCompilation de cmdline.c effectuée\033[0m"

parser.o: parser.c
	@echo "\033[31m\033[1mCompilation de parser.c :\033[0m"
	@gcc -o parser.o -c parser.c  
	@echo "\033[31m\033[1mCompilation de parser.c effectuée\033[0m"

processus.o: processus.c
	@echo "\033[31m\033[1mCompilation de processus.c :\033[0m"
	@gcc -o processus.o -c processus.c  
	@echo "\033[31m\033[1mCompilation de processus.c effectuée\033[0m"

utils.o: utils.c
	@echo "\033[31m\033[1mCompilation de utils.c :\033[0m"
	@gcc -o utils.o -c utils.c 
	@echo "\033[31m\033[1mCompilation de utils.c effectuée\033[0m"

builtin.o: builtin.c
	@echo "\033[31m\033[1mCompilation de builtin.c :\033[0m"
	@gcc -o builtin.o -c builtin.c  
	@echo "\033[31m\033[1mCompilation de builtin.c effectuée\033[0m"

clean:
	@echo "\033[31m\033[1mNettoyage des fichiers .o effectuée\033[0m"
	@rm -rf *.o

mrproper:
	@echo "\033[31m\033[1mNettoyage des fichiers .o et de l'executable minishell effectuée\033[0m"
	@rm -rf *.o
	@rm -rf minishell

mrproper2:
	@echo "\033[31m\033[1mNettoyage des fichiers .o et .txt et de l'executable minishell effectuée\033[0m"
	@rm -rf *.o
	@rm -rf *.txt
	@rm -rf minishell
