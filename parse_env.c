/*
** parse_env.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat Apr 21 14:26:26 2012 florian dewulf
** Last update Fri May 18 17:16:24 2012 kevin lansel
*/

#include	<stdlib.h>
#include	"42sh.h"

t_env		*parse_env(char **env)
{
  t_env		*list_env;

  if (*env == NULL)
    return (gen_env());
  list_env = malloc(sizeof(t_env));
  if (list_env == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  create_list(&list_env, env);
  return (list_env);
}
