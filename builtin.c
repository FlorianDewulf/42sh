/*
** builtin.c for 42sh in /home/lund/Dossier courant/42sh/v1.0
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu May 17 15:02:35 2012 florian dewulf
** Last update Mon May 21 14:01:09 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

int		builtin(char *bin, char *str, t_env *env)
{
  int		count;
  char		**argv;

  count = -1;
  if (comp(bin, "exit"))
    {
      if ((argv = split_tab(str)) && argv[1] != NULL)
	g_exit = my_getnbr(argv[1]);
      return (-2);
    }
  else if (comp(bin, "cd"))
    {
      argv = split_tab(str);
      while (argv[++count]);
      return (my_cd(count, argv, env));
    }
  else if (comp(str, "false"))
    return (-1);
  else if (comp(str, "true"))
    return (0);
  else if (comp(bin, "setenv") == 1 || (comp(bin, "unsetenv") == 1))
    return (my_env(str, env));
  else if (comp(bin, "alias") == 1)
    return (alias_command(str, &g_alias, env));
  return (1);
}

static void	cut_built(char *s, t_env *env, int fd)
{
  int		count;
  char		**argv;
  char		memo;

  count = -1;
  memo = '\0';
  if (comp(s, "exit") || comp(s, "false"))
    {
      write(fd, &memo, 1);
      exit(EXIT_FAILURE);
    }
  else if (comp(s, "cd"))
    {
      argv = split_tab(s);
      while (argv[++count]);
      my_cd(count, argv, env);
      write(fd, &memo, 1);
      exit(EXIT_SUCCESS);
    }
  else if (comp(s, "true") || comp(s, "setenv") || comp(s, "unsetenv") ||
	   comp(s, "alias"))
    {
      write(fd, &memo, 1);
      exit(EXIT_SUCCESS);
    }
}

void		builtin_pipe(char *s, t_env *env, int *fd)
{

  if (comp(s, "exit") || comp(s, "false") || comp(s, "cd") || comp(s, "true") ||
      comp(s, "setenv") || comp(s, "unsetenv") || comp(s, "alias"))
    close(fd[0]);
  cut_built(s, env, fd[1]);
}
