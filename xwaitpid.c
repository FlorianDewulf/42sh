/*
** xwaitpid.c for 42sh in /home/seth
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Wed May 16 16:39:33 2012 kevin lansel
** Last update Sun May 20 18:40:49 2012 florian dewulf
*/

#include	<stdio.h>
#include	<stdlib.h>
#include        <unistd.h>
#include        <sys/types.h>
#include        <sys/wait.h>
#include	"42sh.h"

static char	**sig2(char **tab)
{
  tab[16] = my_strcpy("SIGCHLD");
  tab[17] = my_strcpy("SIGCONT");
  tab[18] = my_strcpy("SIGSTOP");
  tab[19] = my_strcpy("SIGTSTP");
  tab[20] = my_strcpy("SIGTTIN");
  tab[21] = my_strcpy("SIGTTOU");
  tab[22] = my_strcpy("SIGURG");
  tab[23] = my_strcpy("SIGXCPU");
  tab[24] = my_strcpy("SIGXFSZ");
  tab[25] = my_strcpy("SIGVTALRM");
  tab[26] = my_strcpy("SIGPROF");
  tab[27] = my_strcpy("SIGWINCH");
  tab[28] = my_strcpy("SIGPOLL");
  tab[29] = my_strcpy("SIGPWR");
  tab[30] = my_strcpy("SIGSYS");
  tab[31] = NULL;
  return (tab);
}

static char	**sig1()
{
  char		**tab;

  if ((tab = malloc(sizeof(char *) * 32)) == NULL)
    return (NULL);
  tab[0] = my_strcpy("SIGHUP");
  tab[1] = my_strcpy("SIGINT");
  tab[2] = my_strcpy("SIGQUIT");
  tab[3] = my_strcpy("SIGILL");
  tab[4] = my_strcpy("SIGTRAP");
  tab[5] = my_strcpy("SIGIOT");
  tab[6] = my_strcpy("SIGBUS");
  tab[7] = my_strcpy("SIGFPE");
  tab[8] = my_strcpy("SIGKILL");
  tab[9] = my_strcpy("SIGUSR1");
  tab[10] = my_strcpy("SIGSEGV");
  tab[11] = my_strcpy("SIGUSR2");
  tab[12] = my_strcpy("SIGPIPE");
  tab[13] = my_strcpy("SIGALRM");
  tab[14] = my_strcpy("SIGTERM");
  tab[15] = my_strcpy("SIGSTKFLT");
  return (sig2(tab));
}

static int	what_status(int status)
{
  int		i;
  char		**tab;

  i = 0;
  tab = sig1();
  while (i != (status - 1) && tab[i])
    i++;
  if (tab[i])
    printf("Process receive a %s\n", tab[i]);
  free_tab(tab);
  return (-1);
}

int		xwaitpid(int pid, int status, int options)
{
  if (waitpid(pid, &status, options) == -1)
    return (-2);
  if (status == 0)
    return (0);
  else if (status % 256 == 0 || status < -1)
    return (-1);
  else if (status >= 1 && status <= 31)
    return (what_status(status));
  return (-1);
}
