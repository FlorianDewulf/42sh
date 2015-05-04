/*
** my_cd_moin.c for cd-42sh in /home/peelou/Documents/Projets/42sh/42sh-total
** 
** Made by gery baudry
** Login   <baudry_g@epitech.net>
** 
** Started on  Thu May 10 16:30:51 2012 gery baudry
** Last update Fri May 18 21:24:52 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

int		my_cd_moin(t_env *env)
{
  t_env		*tmp;
  char		*pwd;

  tmp = env;
  while (tmp && !compegal(tmp->line, "OLDPWD"))
    tmp = tmp->next;
  if (tmp == NULL)
    return (my_puterror_int(EXIT_MISS_OLDPWD));
  pwd = decoup_from_egal(tmp->line);
  if (pwd == NULL)
    return (my_puterror_int(EXIT_MALLOC));
  if (xchdir(pwd) == -1)
    return (my_puterror_int(EXIT_CHDIR));
  return (old_to_pwd(pwd, env));
}
