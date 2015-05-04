/*
** my_readline.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu May  3 18:20:55 2012 florian dewulf
** Last update Sat May 19 17:44:02 2012 kevin lansel
*/

#include	<sys/ioctl.h>
#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"42sh.h"

void			insere_char(char *buffer, int *curs, char c)
{
  int			pos_tempo;
  char			tmp;
  int			count;
  char			*cap;

  if (c == '')
    {
      put_caractere(curs, buffer, c);
      return;
    }
  pos_tempo = curs[0] - 1;
  cap = (count = strlen(buffer)) ? NULL : NULL;
  while (buffer[++pos_tempo] && count + 1 < 512)
    {
      tmp = buffer[pos_tempo];
      buffer[pos_tempo] = c;
      c = tmp;
    }
  buffer[pos_tempo] = c;
  buffer[pos_tempo + 1] = '\0';
  pos_tempo = curs[0];
  my_putchar(buffer[pos_tempo]);
  xtgetstr_exe(cap, "sc");
  tcput_word(buffer, pos_tempo);
  curs[0]++;
}

void			go_to_left(int *curs)
{
  int			nb;
  char			*cap;

  cap = NULL;
  if (((curs[0] + curs[2]) % curs[1]) == 0)
    {
      nb = curs[1];
      cap = xtgetstr_exe(cap, "up");
      while (nb > 0)
	{
	  cap = xtgetstr_exe(cap, "nd");
	  nb--;
	}
      nb = strlen(g_prompt);
      while (nb > 0)
	{
	  cap = xtgetstr_exe(cap, "nd");
	  nb--;
	}
    }
  else
    cap = xtgetstr_exe(cap, "le");
  curs[0]--;
}

void			go_to_right(int *curs)
{
  char			*cap;

  cap = NULL;
  if (((curs[0] + curs[2] + 1) % curs[1]) == 0)
    {
      cap = xtgetstr_exe(cap, "do");
      while (curs[1] > 0)
	{
	  cap = xtgetstr_exe(cap, "le");
	  curs[1]--;
	}
    }
  else
    cap = xtgetstr_exe(cap, "nd");
  curs[0]++;
}

t_history		*check_commande(char *buffer, int *curs, char *carac,
					t_history **history)
{
  t_history		*tmp;

  tmp = *history;
  if (my_strlen(carac) == 3)
    {
      if (comp(carac, UP_TOUCH))
	*history = modif_buff_read_up(buffer, &tmp, curs);
      else if (comp(carac, DOWN_TOUCH))
	*history = modif_buff_read_down(buffer, &tmp, curs);
      else if (comp(carac, RIGHT_TOUCH) && buffer[curs[0]] != '\0')
	go_to_right(curs);
      else if (comp(carac, LEFT_TOUCH) && curs[0] > 0)
	go_to_left(curs);
    }
  return (*history);
}

int			*init_curs(struct winsize *win)
{
  int			*ret;

  ret = malloc(4 * sizeof(int));
  if (ret == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  ret[0] = 0;
  ret[1] = win->ws_col;
  ret[2] = strlen(g_prompt);
  ret[3] = 0;
  return (ret);
}
