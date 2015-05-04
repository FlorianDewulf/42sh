/*
** execution.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sun May 13 15:58:28 2012 florian dewulf
** Last update Tue May 22 22:42:50 2012 florian dewulf
*/

#include	<string.h>
#include	<sys/wait.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

static int	take_name_bin(char *bin)
{
  int		curs;
  char		*name;

  curs = strlen(bin) - 1;
  while (curs > 0 && bin[curs] != '/')
    curs--;
  name = cut_chain(curs + 1, strlen(bin), bin);
  if (name == NULL || (name && !comp(name, "history")))
    {
      if (name)
	xfree(name);
      return (0);
    }
  xfree(name);
  return (1);
}

int		exe_simple(char *line, t_env *env)
{
  char		**tabv;
  char		*str;
  int		pid;
  t_env		*tmp;
  int		status;

  status = 0;
  tmp = env;
  tabv = split_tab(line);
  if ((pid = builtin(tabv[0], line, env)) != 1)
    return (pid);
  str = tabv[0];
  if (((str = check_access(str, tmp)) == NULL) || (pid = fork()) == -1)
    return (-1);
  tmp = env;
  if (pid == 0)
    execution(str, tabv, tmp);
  xfree(str);
  return (xwaitpid(pid, status, 0));
}

void		execution(char *bin, char **tabv, t_env *env)
{
  if (take_name_bin(bin))
    {
      execve(bin, tabv, convert_to_tab_history(g_histo));
      exit(EXIT_SUCCESS);
    }
  execve(bin, tabv, convert_to_tab(env));
  exit(EXIT_FAILURE);
}
