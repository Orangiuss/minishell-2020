#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include "main2.h"

int main()
{
    char c;
    char buff[100];
    //while(p=getch()) {
    //   printf("%c ", p);
    //}
    int i;

    
    do {
    c = getch();
    if (c == '\t') {
        if(strcmp(buff,"exec") == 0)
            printf("ution");
         	//printf("Autocomplete");
             // Autocomplete
             // Print the rest of the word here
    }
    else if(c==127) {
        buff[i] = '\0';
        i--;
        printf("\033[1D");
        printf(" ");
        printf("\033[1D");
        //printf("");
        //fprintf(stdout,"%s ", buff);
    }
    else if (c==27)
    {
        if (getch()==91)
           {
               c = getch();
               if (c==65)
               {
                   printf("FLECHE HAUT\n");
               }
               if (c==66)
               {
                   printf("FLECHE BAS\n");
               }
               if (c==67)
               {
                   printf("FLECHE DROITE\n");
               }
               if (c==68)
               {
                   printf("FLECHE GAUCHE\n");
               }
           }   
    }
    else {
        buff[i++] = c;
        printf("\r");
        printf("%d\n", c);
        //fprintf(stdout,"%s", buff);
    }

 	} while (c != '\n' && c!='\r');

    printf("%s", buff);

    return 0;
}

