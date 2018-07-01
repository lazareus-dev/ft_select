/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 13:08:40 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/01 15:08:26 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termios.h>
# include "../libft/ft_printf/ft_printf.h"

# define TERM_NOT_SET	0
# define ACCESS_DB		1
# define TERM_NOT_FOUND	2

# define RESET	"\e[0m"
# define BOLD	"\e[1m"
# define GREEN	"\e[32m"
# define BLUE	"\e[96m"
# define PURP	"\e[35m"

typedef struct termios	t_ermios;

typedef struct		s_elem
{
	char			*name;
	int				selected;
	int				cursor;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_disp
{
	int				width;
	int				height;
	int				nb_col;
	int				nb_row;
	size_t			max_len;
}					t_disp;

typedef struct		s_select
{
	int				fd;
	t_ermios		term;
	t_ermios		orig_termios;
	t_disp			disp;
	t_headlst		*arglst;
	t_elem			*cur;
}					t_select;

void				init_term(void);
void				restore_term(t_select *select);

#endif
