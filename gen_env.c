/*
** gen_env.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat Apr 21 15:54:41 2012 florian dewulf
** Last update Sat May 19 18:01:49 2012 kevin lansel
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<pwd.h>
#include	"42sh.h"

static char	*create_link(char *str, char *add)
{
  char		*tmp;
  char		*tempo;

  if ((tmp = concate(str, add)) == NULL)
    return (str);
  xfree(str);
  tempo = my_strcpy(":");
  str = concate(tmp, tempo);
  xfree(tmp);
  xfree(tempo);
  return (str);
}

char		*gen_path()
{
  char		*str;
  int		curs;

  curs = -1;
  str = my_strcpy(PATH);
  if (access(PATHBIN, F_OK) != -1)
    str = create_link(str, PATHBIN);
  if (access(PATHUBIN, F_OK) != -1)
    str = create_link(str, PATHUBIN);
  if (access(PATHSBIN, F_OK) != -1)
    str = create_link(str, PATHSBIN);
  if (access(PATHUSBIN, F_OK) != -1)
    str = create_link(str, PATHUSBIN);
  if (access(PATHULOCBIN, F_OK) != -1)
    str = create_link(str, PATHULOCBIN);
  if (access(PATHULOCSBIN, F_OK) != -1)
    str = create_link(str, PATHULOCSBIN);
  while (str[++curs + 1]);
  if (str[curs] == ':')
    str[curs] = '\0';
  return (str);
}

t_env		*gen_env()
{
  t_env		*env;
  struct passwd	*pass;
  char		buffer[512];

  env = NULL;
  if (add_to_list(&env, gen_path()) == -1)
    return (NULL);
  if (getcwd(buffer, 512) == NULL)
    return (my_puterror_null(EXIT_GETCWD));
  if (add_to_list(&env, concate(ENV_PWD, buffer)) == -1)
    return (NULL);
  pass = getpwuid(geteuid());
  if (pass == NULL)
    return (my_puterror_null(EXIT_GETPWUID));
  if (add_to_list(&env, concate(ENV_USER, pass->pw_name)) == -1)
    return (NULL);
  if (add_to_list(&env, concate(ENV_HOME, pass->pw_dir)) == -1)
    return (NULL);
  if (add_to_list(&env, my_strcpy(OLDPWD_DEFAULT)) == -1)
    return (NULL);
  if (add_to_list(&env, my_strcpy(ENV_TERM)) == -1)
    return (NULL);
  return (env);
}
