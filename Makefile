exec: minishell
	@echo "\033[31m\033[1mExecution du minishell :\033[0m"
	@./minishell

minishell: main.o cmdline.o parser.o processus.o utils.o
	@gcc -o minishell main.o cmdline.o parser.o processus.o utils.o -Wall

main.o: main.c
	@gcc -o main.o -c main.c -Wall

cmdline.o: cmdline.c
	@gcc -o cmdline.o -c cmdline.c -Wall 

parser.o: parser.c
	@gcc -o parser.o -c parser.c -Wall 

processus.o: processus.c
	@gcc -o processus.o -c processus.c -Wall 

utils.o: utils.c
	@gcc -o utils.o -c utils.c -Wall 

clean:
	@echo "\033[31mNettoyage des fichiers .o effectuée\033[0m"
	@rm -rf *.o

mrproper:
	@echo "\033[31m\033[1mNettoyage des fichiers .o et de l'executable minishell effectuée\033[0m"
	@rm -rf *.o
	@rm -rf minishell
