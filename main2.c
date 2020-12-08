#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include "main2.h"
#include <ncurses.h>
#include <ctype.h>
#include <errno.h>

#include "parser.h"
#include "processus.h"
#include "utils.h"
#include "cmdline.h"


int main(int argc, char **argv, char **envp)
{
    char str[MAX_LINE_SIZE];
    char *tokens[MAX_ARGS];
    processus_t proc[MAX_ARGS];
    for (int i = 0; i < MAX_LINE_SIZE; ++i)
    {
      str[i]=NULL;
    }
    char cwd[PATH_MAX];

    if( ! initscr() ) {
      fprintf(stderr, "Erreur lors l'initialisation (initscr())\n");
      return(-1);
    }
    if( keypad(stdscr, TRUE) == ERR ) {
      fprintf(stderr, "Erreur lors l'initialisation (keypad())\n");
      return(-1);
    }

    idlok(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    
    nonl();   /* Pas de retour à la ligne lors d'un RETURN */
    cbreak();
    noecho(); /* Pas d'echo des caratères sur le terminal */
    keypad(stdscr, TRUE);
    idcok(stdscr, FALSE);

    int c;
    int i=0;
    int x = 0, y = 0; /* Position courante du curseur */
    int  x_end, y_end; /* Position du dernier caractère de la commande */
    int y_prompt, x_prompt; /* Position du permier caractère de la commande */
    int prompt_len = strlen("karimrichard@minishell:");
    int backspace_char = erasechar();
    //p=wgetch()
    //printf("%c", p);
    addstr("karimrichard@minishell:");
    refresh();
    getsyx(y_prompt, x_prompt);
    x_end = x_prompt;
    y_end = y_prompt;

    while( (c = getch()) != 27) {
    getsyx(y, x);
    switch(c) {
      case KEY_BACKSPACE: 
      if( x > prompt_len ) {
        x--;
        mvdelch(y, x);
        x_end--;
      }
      break;
      case KEY_UP:
          mvprintw(24, 24, "HAUT");
          refresh();

          break;
      case KEY_DOWN:
          mvprintw(24, 24, "BAS");
          refresh();
          break;
      case KEY_LEFT:
      if( x > prompt_len ) {
  x--;
  setsyx(y, x);
      }
      break;
   
    case KEY_RIGHT:
      if( x >= COLS-1 ) {
  y = y < LINES ? ++y : LINES;
  x = 0;
  setsyx(y, 0);
      }
      else { 
  x++;
  setsyx(y, x);
      }
      break;
      case '\r':
          def_prog_mode();
          reset_shell_mode();
          strtok(str, "\n");
          int nombreArgs = tokenize_str(str, tokens);
          env_str(tokens);
          init_process(proc, tokens);
          exec_cmdline(proc);
          reset_prog_mode();
          getsyx(y, x);
          mvaddstr(y,0,"karimrichard@minishell:");
          for (int i = 0; i < MAX_LINE_SIZE; ++i)
          {
            str[i]=NULL;
          }
    default:
      /* Pour la compatibilité de BACKSPACE en mode xterm */
      if( c == backspace_char ) {
  if( x > prompt_len ) {
    x--;
    mvdelch(y, x);
    x_end--;
  }
      }
      /* Lorsque un SIGUSR2 est reçu on recoit le caractère 'ÿ' !?
       * surement un bug de ncurses
       */
      if( c != 'ÿ' ) {
  x_end++;
  str[i++]=c;
  mvinsch(y, x, c);
  refresh();
  x++;
  setsyx(y, x);
      }
    }
    doupdate();
  }

  endwin();
  printf("Bye !\n");
}

/*
    //wgetstr(win, buff);
    while(c!=27)
    { 
      //getyx(win,cursory, cursorx);
      //wmove(win,cursory, cursorx);
      //refresh();
      //c = wgetstr(win, buff);
      c = mvwgetch(win, cursory, cursorx);
      switch(c)
      { case KEY_UP:
          mvprintw(24, 24, "HAUT");
          refresh();

          break;
        case KEY_DOWN:
          mvprintw(24, 24, "BAS");
          refresh();
          break;
        case 10:
          //Recuperer la chaine et l'executer
          //mvwprintw(win,24, 24, "ENTREE");
          //init_termios();
          reset_shell_mode();
          strtok(str, "\n");
          int nombreArgs = tokenize_str(str, tokens);
          env_str(tokens);
          init_process(proc, tokens);
          exec_cmdline(proc);
          getyx(win,cursory, cursorx);
          refresh();
          reset_prog_mode();
          mvwaddstr(win,cursory,0,"karimrichard@minishell:");
          //refresh();
          //mvprintw(24, 24, "CURSEUR Y : %d, CURSEUR X: %d", cursory, cursorx);
          //getparyx(win,cursory, cursorx);
          for (int i = 0; i < MAX_LINE_SIZE; ++i)
          {
            str[i]=NULL;
          }
          break;
        case KEY_RIGHT:
          cursorx++;
          i++;
          //mvprintw(24, 24, "CURSEUR Y : %d, CURSEUR X: %d", cursory, cursorx);
          //mvwprintw(win,cursory,0,"karimrichard@minishell:");
          wmove(win,cursory, cursorx);
          //mvprintw(24, 24, "DROITE");
          refresh();
          break;
        case KEY_LEFT:
          if (cursorx!=23)
          {
            cursorx--;
            i--;
            //mvprintw(24, 24, "CURSEUR Y : %d, CURSEUR X: %d", cursory, cursorx);
            //mvwprintw(win,cursory,0,"karimrichard@minishell:");
            wmove(win,cursory, cursorx);
            //mvprintw(24, 24, "GAUCHE");
            refresh();
          }
          break;
        case KEY_BACKSPACE:
          //wdelch(win);
          if (cursorx!=23)
          {
            cursorx--;
            i--;
            //mvprintw(24, 24, "CURSEUR Y : %d, CURSEUR X: %d", cursory, cursorx);
            //mvwprintw(win,cursory,0,"karimrichard@minishell:");
            wmove(win,cursory, cursorx);
            mvdelch(cursory, cursorx);
            //mvprintw(24, 24, "DELETE");
            refresh();
          }
          break;    
        default:
          //winsch(win, c);
          //insch(c);
          str[i++]=c;
          //mvprintw(24, 24, "CURSEUR Y : %d, CURSEUR X: %d", cursory, cursorx);
          //mvwprintw(win,cursory,0,"karimrichard@minishell:");
          //mvinsch(cursory, cursorx, c);
          mvwprintw(win,cursory,cursorx,"%c",c);
          cursorx++;
          wmove(win,cursory, cursorx);
          refresh();
          break;
      }
      doupdate();
    }

  clrtoeol();
  refresh();
  endwin(); 

}
/*
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
        //printf("\r");
        printf("%c", c);
        //fprintf(stdout,"%s", buff);
    }

 	} while (1);

    printf("%s", buff);

    return 0;
} */

/*

struct termios orig_termios;

/*** terminal 

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/*** init 

int main() {
  char str[MAX_LINE_SIZE];
    char *tokens[MAX_ARGS];
    processus_t proc[MAX_ARGS];

    char cwd[PATH_MAX];
 
  int i=0;
  enableRawMode();

  while (1) {
    char c = NULL;
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
    if (iscntrl(c)) {
        if (c!=0)
        {
            printf("%d\r\n", c);
        }
    } else {
        if (c!=0)
        {
            printf("%d ('%c')\r\n", c, c);
            str[i++]=c;
        }
    }
    if (c == 's') break;
  }
  printf("%s", str);
  strtok(str, "\n");
  int nombreArgs = tokenize_str(str, tokens);
  env_str(tokens);
  init_process(proc, tokens);
  exec_cmdline(proc);
  return 0;
} */