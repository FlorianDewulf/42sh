/*
** alias_command.c for 42sh in /home/lund/Dossier courant/42sh/v1.0
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri May 18 23:59:08 2012 florian dewulf
** Last update Sun May 20 02:55:49 2012 florian dewulf
*/

#include	<string.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"42sh.h"

static char	*take_off(char *str)
{
  char		*tmp;
  int		curs;
  int		pos;

  pos = 0;
  curs = 0;
  if ((tmp = malloc(strlen(str) - 1)) == NULL)
    return (str);
  while (str[++curs] && str[curs + 1])
    tmp[pos++] = str[curs];
  tmp[pos] = '\0';
  xfree(str);
  return (tmp);
}

static char	*transform_alias(char *tab1, char *tab2)
{
  char		*tab0;
  char		*tempo;

  if ((tab0 = my_strcpy("alias ")) == NULL)
    return (NULL);
  if ((tempo = concate(tab0, tab1)) == NULL)
    return (NULL);
  xfree(tab0);
  if ((tab0 = concate(tempo, "='")) == NULL)
    return (NULL);
  xfree(tempo);
  if ((tempo = concate(tab0, tab2)) == NULL)
    return (NULL);
  xfree(tab0);
  tab0 = concate(tempo, "'\n");
  xfree(tempo);
  return (tab0);
}

static int	go_to_alias_file(char *str, t_env *env)
{
  t_env		*tmp;
  char		*tempo;
  int		fd;
  char		*string;

  tmp = env;
  while (tmp && !compegal(tmp->line, "HOME"))
    tmp = tmp->next;
  if (!tmp)
    return (my_puterror_int("Cannot access to the alias file\n"));
  tempo = decoup_from_egal(tmp->line);
  string = concate(tempo, "/.42shrc");
  xfree(tempo);
  if (access(string, F_OK) == -1)
    fd = open(tempo, O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC,
	      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
  else
    fd = open(string, O_RDWR | O_APPEND);
  if (fd == -1)
    return (my_puterror_int("Cannot access to the alias file\n"));
  xfree(string);
  write(fd, str, my_strlen(str));
  close(fd);
  xfree(str);
  return (0);
}

static void	put_to_alias_list(t_alias **alias, char *str1,
				  char *str2)
{
  t_alias	*elem;
  t_alias	*tmp;

  if ((elem = malloc(sizeof(t_alias))) == NULL)
    return;
  elem->pattern = my_strcpy(str1);
  elem->exp = my_strcpy(str2);
  elem->next = NULL;
  if (*alias == NULL)
    *alias = elem;
  else
    {
      tmp = *alias;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = elem;
    }
}

int		alias_command(char *str, t_alias **alias, t_env *env)
{
  char		**tab;
  int		curs;
  char		*tmp;
  t_alias	*ali;

  ali = *alias;
  curs = -1;
  if (str != NULL)
    {
      if ((tab = split_tab(str)) == NULL)
	return (-1);
      while (tab[++curs]);
      if (curs != 3)
	return (-1);
      if (tab[2][0] == '"' || tab[2][0] == '\'')
	tab[2] = take_off(tab[2]);
      if ((tmp = transform_alias(tab[1], tab[2])) == NULL)
	return (-1);
      if (go_to_alias_file(tmp, env) == -1)
	return (-1);
      put_to_alias_list(&ali, tab[1], tab[2]);
      free_tab(tab);
    }
  *alias = ali;
  return (0);
}
