/*
** main.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat Apr 21 13:39:34 2012 florian dewulf
** Last update Sun May 20 02:45:27 2012 florian dewulf
*/

#include	<signal.h>
#include	<unistd.h>
#include	<string.h>
#include	<stdlib.h>
#include	"42sh.h"

static int	init_shell(char **env, t_env **env_list,
			   t_alias **alias, t_history **history)
{
  char		**tab_env;
  t_alias	*tmp;
  t_env		*tmp_env;
  t_history	*tmp_history;
  int		fd;

  *env_list = NULL;
  *alias = NULL;
  *history = NULL;
  tmp = *alias;
  tmp_env = *env_list;
  tmp_history = *history;
  tab_env = copy_env(env);
  tmp_env = parse_env(tab_env);
  if (tmp_env == NULL)
    return (0);
  init_alias(&tmp, tmp_env);
  *alias = tmp;
  fd = init_history(&tmp_history, tmp_env);
  add_build_path(&tmp_env);
  *history = tmp_history;
  *env_list = tmp_env;
  return (fd);
}

static int	mini_loop(t_history **history, t_env **env_list, t_alias **alias)
{
  t_env		*env;

  env = *env_list;
  while (*history && (*history)->next)
    (*history) = (*history)->next;
  if (check_env(&env) == -1)
    return (-2);
  g_alias = *alias;
  g_histo = *history;
  *env_list = env;
  return (0);
}

static int	main_loop(int fd, t_history **history,
			  t_alias **alias, t_env **env_list)
{
  char		*str;
  t_env		*env;

  env = *env_list;
  if (mini_loop(history, &env, alias) == -2)
    return (-2);
  if (init_termcap(env) != -1)
    {
      if ((str = take_command(*history)) && comp(str, ""))
	str = read_simple(str);
      termcap_desinit(env);
    }
  else
    str = read_simple(NULL);
  *env_list = (g_buffer = NULL) ? env : env;
  if (str == NULL)
    return (-2);
  if (str && str[0] != '\0')
    str = lex_hist(str, *history);
  if (str && str[0] != '\0')
    *history = limit_history(*history, str, fd, *env_list);
  if (str[0] != '\0' && lexer(str, *env_list, *alias) == -2)
    return (-2);
  return (1);
}

int		main(int ac, char **av, char **env)
{
  t_env		*env_list;
  t_alias	*alias;
  t_history	*history;
  int		fd;

  if ((fd = init_shell(env, &env_list, &alias, &history)) == 0)
    return (0);
  if (ac == 3 && comp(av[1], "-c"))
    {
      fd = check_arg_passif(my_strcpy(av[2]), env_list);
      free_env(env_list);
      free_history(history);
      free_alias(alias);
      return (fd);
    }
  signal(SIGINT, catch_ctrlc);
  signal(SIGTSTP, catch_ctrlz);
  take_prompt(env_list);
  while (main_loop(fd, &history, &alias, &env_list) != -2)
    env_list = suppr_useless(&env_list);
  termcap_desinit(env_list);
  free_env(env_list);
  free_history(history);
  free_alias(alias);
  return (g_exit);
}
